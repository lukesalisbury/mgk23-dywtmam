/***********************************************************************************************************************
Copyright © Luke Salisbury
This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter
it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If
   you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not
   required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original
   software.
3. This notice may not be removed or altered from any source distribution.
***********************************************************************************************************************/

#include "shared/ourtypes.hpp"
#include "shared/gametypes.hpp"
#include "shared/texthandling.hpp"

#include <cmath>
#include <cstdlib>

#if PLATFORM_WINDOWS
	#define EXPORT extern "C" __declspec(dllexport)
#endif

#define ASSERT(Expression) if(!(Expression)) {__builtin_trap();}

#define ELIX_HASHMAP_IMPLEMENTATION
#include "shared/elix_hashmap.hpp"

#define IS_BIT_SET(value, bit) (value) & ((1<<(bit)))
#define SET_BIT(value, bit) (value) |= ((1<<(bit)))
#define BETWEEN(value, min, max ) if ( value > max ) { value = max; } else if ( value < min ) { value = min; }

static float sinTable[8] = {0, 0.707f, 1, 0.707f, 0, -0.707f, -1, -0.707f };

inline bool OnCamera( SDL_FRect camera, RenderItem & item) {
	return true;
	if ( (item.position.x + item.position.w) < camera.x ) {
		return false;
	}
	if ( item.position.x > camera.x + camera.w) {
		return false;
	}
	if ( (item.position.y + item.position.h) < camera.y) {
		return false;
	}
	if ( item.position.y > camera.y + camera.h) {
		return false;
	}
	return true;
}

void PushRenderitem( AppOne* app, RenderItem item ) {
	size_t q = app->display_queue.counter;
	if (app->display_queue.counter >= 8191) {
		return; 
	}
	for (size_t i = app->display_queue.counter; i > 0; i--) {
		if ( app->display_queue.items[i].layer < item.layer ) {
			app->display_queue.items[i+1] = app->display_queue.items[i];
		} else if ( app->display_queue.items[i].layer > item.layer ) {
			break;
		} else if ( item.zindex < app->display_queue.items[i].zindex ) {
			app->display_queue.items[i+1] = app->display_queue.items[i];
		} else {
			break;
		}
		q = i;
	}

	app->display_queue.items[q] = item;
	app->display_queue.counter++;
}
void CalulateRenderItemPositionF( AppOne * app, RenderItem & item, SDL_Rect dimensions, SDL_FPoint location, SDL_FPoint scale) {
	item.position.x = (float)(dimensions.x) + location.x;
	item.position.y = (float)(dimensions.y) + location.y;
	item.position.w = (float)(dimensions.w);
	item.position.h = (float)(dimensions.h);
	if ( item.layer ) {
		item.position.x -= app->camera.x;
		item.position.y -= app->camera.y;
		if ( scale.x != 1.0f ) {
			item.position.x *= scale.x;
			item.position.w *= scale.x;
		}
		if ( scale.y != 1.0f ) {
			item.position.y *= scale.y;
			item.position.h *= scale.y;
		}
	}
}

void CalulateRenderItemPosition( AppOne * app, RenderItem & item, SDL_Rect dimensions, SDL_Point location, SDL_FPoint scale) {
	item.position.x = (float)(dimensions.x + location.x);
	item.position.y = (float)(dimensions.y + location.y);
	item.position.w = (float)(dimensions.w);
	item.position.h = (float)(dimensions.h);
	if ( item.layer ) {
		item.position.x -= app->camera.x;
		item.position.y -= app->camera.y;
		if ( scale.x != 1.0f ) {
			item.position.x *= scale.x;
			item.position.w *= scale.x;
		}
		if ( scale.y != 1.0f ) {
			item.position.y *= scale.y;
			item.position.h *= scale.y;
		}
	}
}


void QueueTextureF( AppOne * app, SDL_Texture * texture, SDL_Rect * texture_area, SDL_FPoint world_location, SDL_Rect shape, SDL_Color colour, int16_t zindex, uint8_t layer ) {

	RenderItem item = {	{0,0,0,0}, colour, texture, texture_area, 0.0, zindex, layer };
	CalulateRenderItemPositionF(app, item, shape, world_location, app->scale);

	if ( !layer || OnCamera( app->camera, item) ) {
		PushRenderitem( app, item );
	}
}

void QueueTexture( AppOne * app, SDL_Texture * texture, SDL_Rect * texture_area, SDL_Point world_location, SDL_Rect shape, SDL_Color colour, int16_t zindex, uint8_t layer ) {

	RenderItem item = {	{0,0,0,0}, colour, texture, texture_area, 0.0, zindex, layer };
	CalulateRenderItemPosition(app, item, shape, world_location, app->scale);

	if ( !layer || OnCamera( app->camera, item) ) {
		PushRenderitem( app, item );
	}
}

void QueueQuad( AppOne * app,  SDL_Point world_location, SDL_Rect shape, SDL_Color colour, int16_t zindex, uint8_t layer ) {

	RenderItem item = {	{0,0,0,0}, colour, app->texture_blank, nullptr, 0.0, zindex, layer };
	CalulateRenderItemPosition(app, item, shape, world_location, app->scale);

	if ( !layer || OnCamera( app->camera, item) ) {
		PushRenderitem( app, item );
	}
}

void QueueTextSimple(AppOne *app, FontTexture * font, const char * string, SDL_Rect position, float scale, int16_t zindex, uint8_t layer ) {
	uint8_t * object = (uint8_t*)string;
	uint8_t print = false;

	uint32_t line_padding = font->padding[1];
	SDL_Texture * selected_texture = nullptr;
	SDL_Rect * srcarea = nullptr;
	SDL_Color colour = {255,255,255,255};

	SDL_Point area = {position.x, position.y};
	SDL_Rect dimensions = {0, 0, 0, 0};

	SDL_Point textarea = {position.x, position.y};
	SDL_Point shadowarea = {position.x, position.y};
	SDL_Rect shadowdimensions = {0, 0, 0, 0};

	uint32_t cchar;

	while ( (cchar = NextTextChar(object)) > 0  ) {
		if (cchar == '\n' || cchar == '\r') {
			area.y += line_padding;
			area.x = position.x;
			colour = {255,255,255,255};
			print = false;
			line_padding = font->padding[1];
		} else if ( cchar <= 32 ) {
			area.x += font->padding[0];
			colour = {255,255,255,255};
			print = false;
		} else if ( cchar == 0xA7 /* § */ ) {
			uint32_t nchar = NextTextChar(object);
			if ( nchar != 0xA7 ) {
				GetTextColour(nchar, colour);
			} else {
				cchar = nchar;
			}
		} else if ( cchar >= 0x2776 && cchar <= 0x27BF ) {
			//Button
			print = true;
		} else if ( cchar >= 0x25B2 && cchar <= 0x25D3 ) {
			//Axis
			print = true;
		} else if ( cchar >= 0x24CD && cchar <= 0x24CE ) {
				//Pointer
			print = true;
		} else {
			print = true;
		}

		if ( print ) {
				selected_texture = font->base_texture;
				if ( cchar >= 32 && cchar <= 128 ) {
					srcarea = &font->offset[cchar-32];
				} else if ( cchar  == 0x2026 ) {
					srcarea = &font->offset[97]; //…
				} else if ( cchar >= 0x2776 && cchar <= 0x27BF ) {
					if ( app->control_default->button[cchar - 0x2776].sprite.id ) {
						selected_texture = (SDL_Texture*)elix_hashmap_value_hash(&app->textures, app->control_default->button[cchar - 0x2776].sprite.id);
						srcarea = &app->control_default->button[cchar - 0x2776].sprite.offset;
					} else {
						srcarea = &font->offset[96]; // �
					}
				} else if ( cchar >= 0x25B2 && cchar <= 0x25D3 ) {
					uint8_t axis = 0;
					if ( cchar == 0x25C0 ) // U+25C0	◀	x-
						axis = 0;
					else if ( cchar == 0x25B6 ) // U+25B6	▶	x+
						axis = 1;
					else if ( cchar == 0x25B2 ) // U+25B2	▲	y-
						axis = 2;
					else if ( cchar == 0x25BC ) // U+25BC	▼	y+
						axis = 3;
					else if ( cchar == 0x25D0 ) // U+25D0	◐	z-
						axis = 4;
					else if ( cchar == 0x25D1 ) // U+25D1	◑	z+
						axis = 5;
					else if ( cchar == 0x25C1 ) // U+25C1	◀	x-
						axis = 6;
					else if ( cchar == 0x25B7 ) // U+25B7	▶	x+
						axis = 7;
					else if ( cchar == 0x25B3 ) // U+25B3	▲	y-
						axis = 8;
					else if ( cchar == 0x25BD ) // U+25BD	▼	y+
						axis = 9;
					else if ( cchar == 0x25D2 ) // U+25D2	◐	z-
						axis = 10;
					else if ( cchar == 0x25D3 ) // U+25D3	◓	z+
						axis = 11;
					if (app->control_default->left_stick.sprite[axis%6].id ) {
						selected_texture = (SDL_Texture*)elix_hashmap_value_hash(&app->textures, app->control_default->left_stick.sprite[axis%6].id);
						srcarea = &app->control_default->left_stick.sprite[axis%6].offset;
					} else {
						srcarea = &font->offset[96]; // �
					}
				} else if ( cchar >= 0x24CD && cchar <= 0x24CE ) {
					srcarea = &font->offset[96]; // �
				} else {
					srcarea = &font->offset[96]; // �
				}

				if ( srcarea ) {
					textarea.x = area.x;
					textarea.y = area.y - ( srcarea->h - font->padding[1]);
					dimensions.w = shadowdimensions.w = srcarea->w;
					dimensions.h = shadowdimensions.h = srcarea->h;

					shadowarea.x = textarea.x + 1;
					shadowarea.y = textarea.y + 1;

					QueueTexture(app, selected_texture, srcarea, shadowarea, shadowdimensions, {14,14,14,255}, 0, layer );
					QueueTexture(app, selected_texture, srcarea, textarea, dimensions, colour, 1, layer );

					line_padding = (srcarea->h > line_padding ? srcarea->h + 2 : line_padding);
					area.x += srcarea->w + 1;
			}
		}
	}
}


struct World {
	SDL_FRect location;
};

int32_t random( int32_t min, int32_t max ){
    return min + (rand() % max);
}

struct Polygon {
	SDL_Rect area;
	SDL_Point edges[512];
	size_t size = 0;
	size_t length = 512;
};

struct PointRef {
	SDL_Point p;
	uint32_t r;
};
struct PolygonRef {
	PointRef edges[512];
	size_t size = 0;
	size_t length = 512;
};

struct InteractableModel
{
	uint32_t quad_count;
	SDL_Rect quads[8];
};
struct Interactable
{
	InteractableModel model;
	SDL_Point position;
	SDL_FPoint position_offset;
	double angle;
	uint8_t type;
	uint8_t active;

};

struct Region
{
	uint32_t x, y, w, h;
};
enum doing_action {
	ROW_MOVE_LEFT,
	ROW_MOVE_RIGHT,
	COL_MOVE_UP,
	COL_MOVE_DOWN,
	ALL_MOVE_LEFT,
	ALL_MOVE_RIGHT,
	ALL_MOVE_UP,
	ALL_MOVE_DOWN,
	SWITCH_FIRST,
	SWITCH_SECOND,
};

enum CluesType {
	CASE_COLOUR, SKIN_COLOUR, HAIR_LENGTH, HAIR_COLOUR, HEIGHT, CLOTHES, NUMBER, CLUE_COUNT
};


struct Briefcase
{
	uint8_t value;
	uint8_t case_colour;
	uint8_t skin;
	uint8_t hair_length;
	uint8_t hair_colour;
	uint8_t height;
	uint8_t top_colour;
};

struct EventAction {
	SDL_Rect collision;
	uint8_t action;
	uint8_t ref;
};

struct ClueInfo {
	uint8_t positive;
	uint8_t negative;
	 
};

struct GameMemory
{
	Briefcase cases[25];
	Briefcase contestent;
	ClueInfo clues[CLUE_COUNT];
	uint8_t clues_picked[3];
	EventAction previous_action;
	uint8_t moves_left;
	uint8_t state;
};

GameMemory * game_object = nullptr;

#include "gamesettings.hpp"


void OverlayGrid( AppOne * app, SDL_Rect area, Interactable * player) {
	for (int32_t i = area.x; i < area.x + area.w; i += 10) {
		for (int32_t j = area.y; j < area.y + area.h; j += 10 ) {
			double dist = sqrt(((i - player->position.x)*(i - player->position.x)) + ((j - player->position.y)*(j - player->position.y)));
			if ( dist < 64.0 ) 
				QueueQuad(app, {i,j}, { 2,2, 8,8}, {0,233,0, 128}, 1, 1);
			else if ( (player->position.x+4)/10 == i/10 && (player->position.y+12)/10 == j/10) 
				QueueQuad(app, {i,j}, { 2,2, 8,8}, {233,0,0, 128}, 1, 1);
			else
				QueueQuad(app, {i,j}, { 2,2, 8,8}, {233,233,233, 128}, 1, 1);
		}
	}
}

uint8_t random8( int8_t max ){
    return (rand() % max);
}

uint8_t randomNot8( int8_t max, uint8_t not_this ){
	uint8_t v = random8(max);
    return ( v == not_this ? randomNot8(max,not_this): v);
}

uint8_t RandomiseBriefcases(AppOne * app) {
	for (size_t i = 0; i < 25; i++)
	{
		game_object->cases[i].value = random8(MAX_BRIEFCASES);
		game_object->cases[i].case_colour = random8(MAX_COLOURS);
		game_object->cases[i].skin = random8(5);
		game_object->cases[i].hair_length = random8(3);
		game_object->cases[i].hair_colour = random8(MAX_COLOURS);
		game_object->cases[i].height = random8(3);
		game_object->cases[i].top_colour = random8(MAX_COLOURS);
	}
	return 0;
}

uint8_t RandomiseContestent(AppOne * app) {
	
	game_object->contestent.value = random8(MAX_BRIEFCASES);

	game_object->contestent.case_colour = random8(MAX_COLOURS);
	game_object->contestent.skin = random8(5);
	game_object->contestent.hair_length = random8(3);
	game_object->contestent.hair_colour = random8(MAX_COLOURS);
	game_object->contestent.height = random8(3);
	game_object->contestent.top_colour = random8(MAX_COLOURS);

	Briefcase selected_case = game_object->cases[game_object->contestent.value];

	game_object->clues[0].positive = selected_case.top_colour;
	game_object->clues[0].negative = randomNot8(MAX_COLOURS, selected_case.top_colour);

	game_object->clues[0].positive = selected_case.case_colour;
	game_object->clues[0].negative = randomNot8(MAX_COLOURS, selected_case.case_colour);

	game_object->clues[1].positive = selected_case.skin;
	game_object->clues[1].negative = randomNot8(5, selected_case.skin);

	game_object->clues[2].positive = selected_case.hair_length;
	game_object->clues[2].negative = randomNot8(3, selected_case.hair_length);

	game_object->clues[3].positive = selected_case.hair_colour;
	game_object->clues[3].negative = randomNot8(MAX_COLOURS, selected_case.hair_colour);


	if (selected_case.height > game_object->contestent.height ) 
	{
		game_object->clues[4].positive = 255;
		game_object->clues[4].negative = game_object->contestent.height;
	}
	else
	{
		game_object->clues[4].positive = game_object->contestent.height;
		game_object->clues[4].negative = 255;
	}


	game_object->clues_picked[0] = random8(5);
	game_object->clues_picked[1] = randomNot8(5, game_object->clues_picked[0]);
	game_object->clues_picked[2] = randomNot8(5,game_object->clues_picked[0]);


	return 0;
}



uint8_t DrawHumaniod( AppOne * app, SDL_Point point, SDL_Point scale, Briefcase item, uint8_t status) {

	SDL_Rect head = {40,0,16,24};
	SDL_Rect hair[3] = {
		{56,0,16,24},
		{72,0,16,24},
		{88,0,16,24},
	};
	SDL_Rect body = {40,32,24,16};
	if ( item.height == 0 ) //short
	{ 
		//QueueQuad(app, point, {6, 20, 20, 20}, { 128, 0, 128 , 255}, 1, 1); //head
		//QueueQuad(app, point, {0, 40, 32, 24}, { 128, 128, 128 , 255}, 1, 1); //body

		QueueTexture(app, app->texture_sheet, &head, point, {4, 10, 16, 24}, {255,255,255,255}, 1, 1);
		QueueTexture(app, app->texture_sheet, &hair[item.hair_length], point, {4, 10, 16, 24}, {255,255,255,255}, 1, 1);

		QueueTexture(app, app->texture_sheet, &body, point, {0, 32, 24, 16}, {255,255,255,255}, 1, 1);
	}
	else if ( item.height == 2 ) //tall
	{
		//QueueQuad(app, point, {6, 4, 20, 20}, { 128, 0, 128 , 255}, 1, 1); //head
		//QueueQuad(app, point, {0, 24, 32, 40}, { 128, 128, 128 , 255}, 1, 1); //body

		QueueTexture(app, app->texture_sheet, &head, point, {4, 10, 16, 24}, {255,255,255,255}, 1, 1);
		QueueTexture(app, app->texture_sheet, &hair[item.hair_length], point, {4, 10, 16, 24}, {255,255,255,255}, 1, 1);

		QueueTexture(app, app->texture_sheet, &body, point, {0, 32, 24, 16}, {255,255,255,255}, 1, 1);

	}
	else
	{
		//QueueQuad(app, point, {6, 12, 20, 20}, { 128, 0, 128 , 255}, 1, 1); //head
		//QueueQuad(app, point, {0, 32, 32, 32}, { 128, 128, 128 , 255}, 1, 1); //body

		QueueTexture(app, app->texture_sheet, &head, point, {4, 10, 16, 24}, {255,255,255,255}, 1, 1);
		QueueTexture(app, app->texture_sheet, &hair[item.hair_length], point, {4, 10, 16, 24}, {255,255,255,255}, 1, 1);

		QueueTexture(app, app->texture_sheet, &body, point, {0, 32, 24, 16}, {255,255,255,255}, 1, 1);
	}
	return 0;
}

uint8_t DrawBriefcase( AppOne * app, SDL_Point & point, uint8_t number, Briefcase item, uint8_t status) {
	ASSERT(item.value < MAX_BRIEFCASES);

	SDL_Rect briefcase_text = {16,0,32,32};
	SDL_Rect briefcase_color[6] = {
		{8,16,24,16},
		{8,32,24,16},
		{8,48,24,16},
		{8,64,24,16},
		{8,80,24,16},
		{8,96,24,16},

	};
	SDL_Color hover_colour[2] = { {255, 255, 255, 255}, {255, 128, 128, 255}};

	

	if ( status != 255 ) {

		//QueueQuad(app, point, {8, 40, 32, 24}, BriefcaseColours[item.case_colour], 1, 1);
		QueueTexture(app, app->texture_sheet, &briefcase_text, point, {8, 40, 32, 24}, {255, 255, 255, 255}, 1, 1);
		//QueueTexture(app, app->texture_sheet, &briefcase_color[item.case_colour], point, {0, 32, 32, 32}, BriefcaseColours[item.case_colour], 1, 1);
		
		
		char briefcase_number[4] = { 0, 0, 0, 0};
		snprintf(briefcase_number, 4, "%02d", number);
		QueueTextSimple(app, &app->font_bitmap, briefcase_number, {point.x+16, point.y+44, 0, 0}, 1.0, 1, 0);
	}

//DrawHumaniod(app, {point.x+32, point.y}, {1,1}, item, status);

	

	return 0;
}



bool rect_collide(SDL_Rect a, SDL_Rect b)
{
	if(b.x + b.w < a.x)	return 0;
	if(b.x > a.x + a.w)	return 0;
	if(b.y + b.h < a.y)	return 0;
	if(b.y > a.y + a.h)	return 0;

	return 1;
}
bool point_collide(SDL_Rect a, int32_t x, int32_t y)
{
	if(x < a.x)	return 0;
	if(x > a.x + a.w)	return 0;
	if(y > a.y + a.h)	return 0;
	if(y < a.y)	return 0;

	return 1;
}


#ifdef PLATFORM_WINDOWS
	#define EXPORT_FUNCTION __declspec(dllexport)
#else
	#define EXPORT_FUNCTION __attribute__((visibility("default")))
#endif

extern "C" EXPORT_FUNCTION ConfigRequest GameConfig(AppOne * app, GameOne * game, uint8_t state ) {
	return { 268435456 };
}

uint8_t * mempool_push( uint8_t * memory, size_t offset) {
	return memory + offset;
}

uint8_t * mempool_get( uint8_t * memory, size_t offset) {
	return memory + offset;
}

extern "C" EXPORT_FUNCTION uint8_t GameDestory(AppOne * app, GameOne * game, uint8_t state ) {

	return state;
}


extern "C" EXPORT_FUNCTION uint8_t GameReload(AppOne * app, GameOne * game, uint8_t state ) {
	game_object = (GameMemory *)mempool_get(game->memory_pool, 0);
	SDL_Log("GameReload %p", game_object);

	return state;
}

extern "C" EXPORT_FUNCTION uint8_t GameInit(AppOne * app, GameOne * game, uint8_t state ) {
	game_object = (GameMemory *)mempool_push(game->memory_pool, 0);
	SDL_Log("GameInit %p", game_object);

	game_object->state = 0;

	return state;
}



uint8_t perform_action(AppOne * app, EventAction event) {

	switch (event.action)
	{
		case ROW_MOVE_LEFT:
		{
			///TODO: Replace hard coded 
			ASSERT( ROW_BRIEFCASES == 5)
			uint8_t buffer_cases[5];
			
			uint8_t offset = event.ref * 5;
			buffer_cases[0] = game_object->cases[offset + 0].value;
			buffer_cases[1] = game_object->cases[offset + 1].value;
			buffer_cases[2] = game_object->cases[offset + 2].value;
			buffer_cases[3] = game_object->cases[offset + 3].value;
			buffer_cases[4] = game_object->cases[offset + 4].value;

			game_object->cases[offset + 0].value = buffer_cases[1];
			game_object->cases[offset + 1].value = buffer_cases[2];
			game_object->cases[offset + 2].value = buffer_cases[3];
			game_object->cases[offset + 3].value = buffer_cases[4];
			game_object->cases[offset + 4].value = buffer_cases[0];
		}
		break;
	
		case ROW_MOVE_RIGHT:
		{
			///TODO: Replace hard coded 
			ASSERT( ROW_BRIEFCASES == 5)
			uint8_t buffer_cases[5];
			
			uint8_t offset = event.ref * 5;
			buffer_cases[0] = game_object->cases[offset + 0].value;
			buffer_cases[1] = game_object->cases[offset + 1].value;
			buffer_cases[2] = game_object->cases[offset + 2].value;
			buffer_cases[3] = game_object->cases[offset + 3].value;
			buffer_cases[4] = game_object->cases[offset + 4].value;

			game_object->cases[offset + 0].value = buffer_cases[4];
			game_object->cases[offset + 1].value = buffer_cases[0];
			game_object->cases[offset + 2].value = buffer_cases[2];
			game_object->cases[offset + 3].value = buffer_cases[3];
			game_object->cases[offset + 4].value = buffer_cases[4];
		}
		break;

		case COL_MOVE_UP:
		{
			///TODO: Replace hard coded 
			ASSERT( COL_BRIEFCASES == 5)
			uint8_t buffer_cases[5];
			
			uint8_t offset = event.ref * 5;
			buffer_cases[0] = game_object->cases[offset + (ROW_BRIEFCASES*0)].value;
			buffer_cases[1] = game_object->cases[offset + (ROW_BRIEFCASES*1)].value;
			buffer_cases[2] = game_object->cases[offset + (ROW_BRIEFCASES*2)].value;
			buffer_cases[3] = game_object->cases[offset + (ROW_BRIEFCASES*3)].value;
			buffer_cases[4] = game_object->cases[offset + (ROW_BRIEFCASES*4)].value;

			game_object->cases[offset + (ROW_BRIEFCASES*0)].value = buffer_cases[1];
			game_object->cases[offset + (ROW_BRIEFCASES*1)].value = buffer_cases[2];
			game_object->cases[offset + (ROW_BRIEFCASES*2)].value = buffer_cases[3];
			game_object->cases[offset + (ROW_BRIEFCASES*3)].value = buffer_cases[4];
			game_object->cases[offset + (ROW_BRIEFCASES*4)].value = buffer_cases[0];
		}
		break;

		case COL_MOVE_DOWN:
		{
			///TODO: Replace hard coded 
			ASSERT( COL_BRIEFCASES == 5)
			uint8_t buffer_cases[5];
			
			uint8_t offset = event.ref * 5;
			buffer_cases[0] = game_object->cases[offset + (ROW_BRIEFCASES*0)].value;
			buffer_cases[1] = game_object->cases[offset + (ROW_BRIEFCASES*1)].value;
			buffer_cases[2] = game_object->cases[offset + (ROW_BRIEFCASES*2)].value;
			buffer_cases[3] = game_object->cases[offset + (ROW_BRIEFCASES*3)].value;
			buffer_cases[4] = game_object->cases[offset + (ROW_BRIEFCASES*4)].value;

			game_object->cases[offset + (ROW_BRIEFCASES*0)].value = buffer_cases[4];
			game_object->cases[offset + (ROW_BRIEFCASES*1)].value = buffer_cases[0];
			game_object->cases[offset + (ROW_BRIEFCASES*2)].value = buffer_cases[1];
			game_object->cases[offset + (ROW_BRIEFCASES*3)].value = buffer_cases[2];
			game_object->cases[offset + (ROW_BRIEFCASES*4)].value = buffer_cases[3];
		}
		break;

		case ALL_MOVE_LEFT:
		{
			///TODO: Replace hard coded 
			uint8_t buffer_cases[25];
			for( uint8_t q = 0; q < 25; q++) {
				buffer_cases[q] = game_object->cases[q].value;
			}
			for( uint8_t w = 0; w < 5; w++) {
				uint8_t q = w; //(w + 1) % 5;
				game_object->cases[(w * ROW_BRIEFCASES) + 4].value = buffer_cases[(q * ROW_BRIEFCASES) + 0];
				game_object->cases[(w * ROW_BRIEFCASES) + 0].value = buffer_cases[(q * ROW_BRIEFCASES) + 1];
				game_object->cases[(w * ROW_BRIEFCASES) + 1].value = buffer_cases[(q * ROW_BRIEFCASES) + 2];
				game_object->cases[(w * ROW_BRIEFCASES) + 2].value = buffer_cases[(q * ROW_BRIEFCASES) + 3];
				game_object->cases[(w * ROW_BRIEFCASES) + 3].value = buffer_cases[(q * ROW_BRIEFCASES) + 4];

				//SDL_Log("ALL_MOVE_LEFT %d > %d", (q * ROW_BRIEFCASES), (w * ROW_BRIEFCASES));
			}
		}
		break;
		case ALL_MOVE_RIGHT:
		{
			///TODO: Replace hard coded 
			uint8_t buffer_cases[25];
			for( uint8_t q = 0; q < 25; q++) {
				buffer_cases[q] = game_object->cases[q].value;
			}
			for( uint8_t w = 0; w < 5; w++) {
				uint8_t q = w; //(w + 4) % 5;
				game_object->cases[(w * ROW_BRIEFCASES) + 1].value = buffer_cases[(q * ROW_BRIEFCASES) + 0];
				game_object->cases[(w * ROW_BRIEFCASES) + 2].value = buffer_cases[(q * ROW_BRIEFCASES) + 1];
				game_object->cases[(w * ROW_BRIEFCASES) + 3].value = buffer_cases[(q * ROW_BRIEFCASES) + 2];
				game_object->cases[(w * ROW_BRIEFCASES) + 4].value = buffer_cases[(q * ROW_BRIEFCASES) + 3];
				game_object->cases[(w * ROW_BRIEFCASES) + 0].value = buffer_cases[(q * ROW_BRIEFCASES) + 4];

				//SDL_Log("ALL_MOVE_RIGHT %d > %d", (w * ROW_BRIEFCASES), (w * ROW_BRIEFCASES));
			}
		}
		break;
		case ALL_MOVE_UP:
		{
			///TODO: Replace hard coded 
			uint8_t buffer_cases[25];
			for( uint8_t q = 0; q < 25; q++) {
				buffer_cases[q] = game_object->cases[q].value;
			}
			for( uint8_t w = 0; w < 5; w++) {
				uint8_t q = (w + 1) % 5;
				game_object->cases[(w * COL_BRIEFCASES) + 0].value = buffer_cases[(q * COL_BRIEFCASES) + 0];
				game_object->cases[(w * COL_BRIEFCASES) + 1].value = buffer_cases[(q * COL_BRIEFCASES) + 1];
				game_object->cases[(w * COL_BRIEFCASES) + 2].value = buffer_cases[(q * COL_BRIEFCASES) + 2];
				game_object->cases[(w * COL_BRIEFCASES) + 3].value = buffer_cases[(q * COL_BRIEFCASES) + 3];
				game_object->cases[(w * COL_BRIEFCASES) + 4].value = buffer_cases[(q * COL_BRIEFCASES) + 4];

				//SDL_Log("ALL_MOVE_UP %d > %d", (q * COL_BRIEFCASES), (w * COL_BRIEFCASES));
			}

		}
		break;
		case ALL_MOVE_DOWN:
		{
			///TODO: Replace hard coded 
			uint8_t buffer_cases[25];
			for( uint8_t q = 0; q < 25; q++) {
				buffer_cases[q] = game_object->cases[q].value;
			}
			for( uint8_t w = 0; w < 5; w++) {
				uint8_t q = (w + 4) % 5;
				game_object->cases[(w * COL_BRIEFCASES) + 0].value = buffer_cases[(q * COL_BRIEFCASES) + 0];
				game_object->cases[(w * COL_BRIEFCASES) + 1].value = buffer_cases[(q * COL_BRIEFCASES) + 1];
				game_object->cases[(w * COL_BRIEFCASES) + 2].value = buffer_cases[(q * COL_BRIEFCASES) + 2];
				game_object->cases[(w * COL_BRIEFCASES) + 3].value = buffer_cases[(q * COL_BRIEFCASES) + 3];
				game_object->cases[(w * COL_BRIEFCASES) + 4].value = buffer_cases[(q * COL_BRIEFCASES) + 4];

				//SDL_Log("ALL_MOVE_DOWN %d > %d", (q * COL_BRIEFCASES), (w * COL_BRIEFCASES));
			}
		}
		break;
		case SWITCH_SECOND:
		{
			uint8_t buffer_cases = game_object->cases[event.ref].value;
		}
		break;
		default:
		break;
	}

	return 1;

}


uint8_t PushEventAction(AppOne * app, EventAction available_events[256], uint8_t & available_counter, SDL_Rect collision, uint8_t action, uint8_t ref) {

	bool results = point_collide(collision, app->control_default->pointer.value[0], app->control_default->pointer.value[1]) ;

	available_events[available_counter] = { collision, action, ref };

	if ( results )
	{
		game_object->previous_action = available_events[available_counter];
	}

	available_counter++;

	return results;
}

void game_intro(AppOne * app) {

	char tries_text[256];
	snprintf(tries_text, 256, "Do You Want To Make An Millionaire\nYou have 3 moves to get the best value for the contestant.\n\n\n\nPress ❶ to play");
	QueueTextSimple(app, &app->font_bitmap, tries_text, {140, app->viewpoint.h/3, 0, 0}, 4.0, 1, 0);
	game_object->state = 1;
}


void game_new(AppOne * app) {
	RandomiseBriefcases(app);
	RandomiseContestent(app);
	game_object->moves_left = 3;
	game_object->state = 2;
}


void game_over(AppOne * app) {
	char tries_text[64];
	snprintf(tries_text, 64, "Your Contestant won %s.\n\nPress ❶ to play again.", BriefcaseValuesString[game_object->cases[game_object->contestent.value].value]);
	QueueTextSimple(app, &app->font_bitmap, tries_text, {140, app->viewpoint.h/3, 0, 0}, 4.0, 1, 0);

	DrawHumaniod( app, {100, app->viewpoint.h/3}, {4, 4}, game_object->contestent, 255);

	if ( app->control_default->button[0].value.state == BUTTON_RELEASED ) {
		game_object->state = 1;
	}


}
void game_active(AppOne * app) {

	srand(42);


	if ( app->control_default->button[0].value.state == BUTTON_RELEASED ) {
		RandomiseBriefcases(app);
	}


	SDL_Rect briefcase = {16,0,24,16};
	SDL_Rect up_arrow = {0,0,16,16};
	SDL_Rect left_arrow = {0,16,16,16};
	SDL_Rect down_arrow = {0,32,16,16};
	SDL_Rect right_arrow = {0,48,16,16};

	uint16_t offset[2] = {32,32};


	EventAction available_events[256] = {};
	uint8_t available_counter = 0;
	
	// 112x80

	bool hover_collision = false;
	SDL_Color hover_colour[2] = { {128, 128, 128, 255}, {255, 128, 128, 255}};

	for ( uint8_t row_ = 0; row_ < ROW_BRIEFCASES; row_++ ) {
		SDL_Point pos = { 8, 32 + (row_ * 80)};

		hover_collision = PushEventAction(app, available_events, available_counter, {pos.x, pos.y+ 8, 16, 16}, ROW_MOVE_LEFT, row_);
		//QueueQuad(app, pos, {0, 8, 16, 16}, hover_colour[hover_collision], 1, 1);
		QueueTexture(app, app->texture_sheet, &left_arrow, pos, {0, 8, 16, 16}, hover_colour[hover_collision], 1, 1);

		hover_collision = PushEventAction(app, available_events, available_counter, {pos.x, pos.y+ 32, 16, 16}, ROW_MOVE_RIGHT, row_);
		//QueueQuad(app, pos, {0, 32, 16, 16}, hover_colour[hover_collision], 1, 1);
		QueueTexture(app, app->texture_sheet, &right_arrow, pos, {0, 32, 16, 16}, hover_colour[hover_collision], 1, 1);
	}


	for ( uint8_t col_ = 0; col_ < COL_BRIEFCASES; col_++ ) {
		SDL_Point pos = { 32 + (col_ * 112), 8};

		hover_collision = PushEventAction(app, available_events, available_counter, {pos.x + 24, pos.y, 16, 16}, COL_MOVE_UP, col_);
		//QueueQuad(app, pos, {8, 0, 16, 16}, hover_colour[hover_collision], 1, 1);
		QueueTexture(app, app->texture_sheet, &up_arrow, pos, {24, 0, 16, 16}, hover_colour[hover_collision], 1, 1);
		
		hover_collision = PushEventAction(app, available_events, available_counter, {pos.x + 56, pos.y, 16, 16}, COL_MOVE_DOWN, col_);
		//QueueQuad(app, pos, {56, 0, 16, 16}, hover_colour[hover_collision], 1, 1);
		QueueTexture(app, app->texture_sheet, &down_arrow, pos, {56, 0, 16, 16}, hover_colour[hover_collision], 1, 1);
	}


	// ALL PUSH
	SDL_Point cycle_pos = { 208, 428 };

	hover_collision = PushEventAction(app, available_events, available_counter, {cycle_pos.x, cycle_pos.y, 16, 16}, ALL_MOVE_LEFT, 0);
	//QueueQuad(app, cycle_pos, {0, 0, 16, 16}, hover_colour[hover_collision], 1, 1);
	QueueTexture(app, app->texture_sheet, &left_arrow, cycle_pos, {0, 0, 16, 16}, hover_colour[hover_collision], 1, 1);

	hover_collision = PushEventAction(app, available_events, available_counter, {cycle_pos.x + 24, cycle_pos.y, 16, 16}, ALL_MOVE_UP, 0);
	//QueueQuad(app, cycle_pos, {24, 0, 16, 16}, hover_colour[hover_collision], 1, 1);
	QueueTexture(app, app->texture_sheet, &up_arrow, cycle_pos, {24, 0, 16, 16}, hover_colour[hover_collision], 1, 1);

	hover_collision = PushEventAction(app, available_events, available_counter, {cycle_pos.x + 204, cycle_pos.y, 16, 16}, ALL_MOVE_RIGHT, 0);
	//QueueQuad(app, cycle_pos, {180, 0, 16, 16}, hover_colour[hover_collision], 1, 1);
	QueueTexture(app, app->texture_sheet, &right_arrow, cycle_pos, {204, 0, 16, 16}, hover_colour[hover_collision], 1, 1);

	hover_collision = PushEventAction(app, available_events, available_counter, {cycle_pos.x + 180, cycle_pos.y, 16, 16}, ALL_MOVE_DOWN, 0);
	//QueueQuad(app, cycle_pos, {204, 0, 16, 16}, hover_colour[hover_collision], 1, 1);
	QueueTexture(app, app->texture_sheet, &down_arrow, cycle_pos, {180, 0, 16, 16}, hover_colour[hover_collision], 1, 1);

	QueueTextSimple(app, &app->font_bitmap, " MOVE ALL ", {cycle_pos.x + 64, cycle_pos.y+2, 0, 0}, 1.0, 1, 0);


	for ( uint8_t counter = 0; counter < 25; counter++)
	{
		uint8_t x = counter % 5;
		uint8_t y = counter / 5;
		SDL_Point pos = {offset[0] + (x * 112), offset[1] + (y * 80)};
		DrawBriefcase(app,pos, counter + 1, game_object->cases[counter], 0);

		QueueQuad(app, pos, {0, 0, 96, 16}, {128, 128, 128, 128}, 1, 1);
		QueueTextSimple(app, &app->font_bitmap, BriefcaseValuesString[game_object->cases[counter].value], {pos.x, pos.y+2, 0, 0}, 1.0, 1, 0);

	}
	


	char tries_text[4];
	snprintf(tries_text, 4, "%02d", game_object->moves_left);
	QueueTextSimple(app, &app->font_bitmap, "Moves", {600, 50, 0, 0}, 4.0, 1, 0);
	QueueTextSimple(app, &app->font_bitmap, tries_text, {616, 62, 0, 0}, 4.0, 1, 0);




	
game_object->clues_picked[0] = random8(5);
	game_object->clues_picked[1] = randomNot8(5, game_object->clues_picked[0]);
	game_object->clues_picked[2] =

	QueueTextSimple(app, &app->font_bitmap, "Clue 1:", {580, 190, 0, 0}, 4.0, 1, 0);
	QueueTextSimple(app, &app->font_bitmap, "Clue 1", {600, 200, 0, 0}, 4.0, 1, 0);

	QueueTextSimple(app, &app->font_bitmap, "Clue 2:", {580, 220, 0, 0}, 4.0, 1, 0);
	QueueTextSimple(app, &app->font_bitmap, "Clue 1", {600, 230, 0, 0}, 4.0, 1, 0);

	QueueTextSimple(app, &app->font_bitmap, "Clue 3:", {580, 250, 0, 0}, 4.0, 1, 0);
	QueueTextSimple(app, &app->font_bitmap, "Clue 1", {600, 260, 0, 0}, 4.0, 1, 0);




	DrawHumaniod( app, {600, 360}, {4, 4}, game_object->contestent, 255);






	if ( app->control_default->button[10].value.state == BUTTON_RELEASED )
	{
		for ( uint8_t ev = 0; ev < available_counter; ev++ )
		{
			if ( point_collide(available_events[ev].collision, app->control_default->pointer.value[0], app->control_default->pointer.value[1]) )
			{
				if ( perform_action(app, available_events[ev]) ) {
					if ( game_object->moves_left == 1 )
					{
						game_object->state = 3;
					}

					game_object->moves_left--;
				}
			}
		}
	}



}





extern "C" EXPORT_FUNCTION uint8_t GameFrame(AppOne * app, GameOne * game, uint8_t state ) {
	char debug[128];


	switch (game_object->state)
	{
	case 1:
		game_new(app);
		break;
	case 2:
		game_active(app);
		break;
	case 3:
		game_over(app);
		break;
	default:
		game_intro(app);
		break;
	}


	SDL_SetRenderDrawColor(app->renderer, 0,0,0,255);

	return state;
}




