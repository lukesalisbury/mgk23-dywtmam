
#define MAX_BRIEFCASES 25
#define ROW_BRIEFCASES 5
#define COL_BRIEFCASES 5


char BriefcaseValuesString[MAX_BRIEFCASES][12] ={
	"$0", // 0
	"$50", // 1
	"$100", // 2
	"$250", // 3
	"$500", // 4
	"$750", // 5
	"$1000", // 6
	"$2500", // 7
	"$5000", // 8
	"$7500", // 9
	"$10,000", // 10
	"$25,000", // 11
	"$50,000", // 12
	"$75,000", // 13
	"$100,000", // 14
	"$200,000", // 15
	"$300,000", // 16
	"$400,000", // 17
	"$500,000", // 18
	"$600,000", // 19
	"$700,000", // 20
	"$800,000", // 21
	"$900,000", // 22
	"$1,000,000", // 23
	"$2,000,000", // 24
};

uint32_t BriefcaseValues[MAX_BRIEFCASES] =  {
	0, // 0
	50, // 1
	100, // 2
	250, // 3
	500, // 4
	750, // 5
	1000, // 6
	2500, // 7
	5000, // 8
	7500, // 9
	10000, // 10
	25000, // 11
	50000, // 12
	75000, // 13
	100000, // 14
	200000, // 15
	300000, // 16
	400000, // 17
	500000, // 18
	600000, // 19
	700000, // 20
	800000, // 21
	900000, // 22
	1000000, // 23
	2000000 // 24
};

#define MAX_COLOURS 6

char BriefcaseColoursString[MAX_COLOURS][10] {
    "Blue",
    "Red",
    "Green",
    "Yellow",
    "Purple",
    "Orange"
};
char BriefcasePatternString[MAX_COLOURS][10] {
    "Diamonds",
    "Hearts",
    "Spikes",
    "Stars",
    "Pentagons",
    "Circles"
};


SDL_Color BriefcaseColours[MAX_COLOURS] ={
    { 0, 0, 255, 255},
    { 255, 0, 0, 255},
    { 0, 255, 0, 255},
    { 255, 255, 0, 255},
    { 64, 0, 128, 255},
    { 255, 120, 0, 255},
};

char clue_positive_hints[CLUE_COUNT][128] = {
	"My favourite colour is %s.",
	"I like my fellow country folks.",
	"%s rocks!",
	"My partner has %s hair.",
	"%s people make me happy.",
	"People look good in %s.",
	"%s numbers"
};

char clue_negative_hints[CLUE_COUNT][128] = {
	"I would never picked %s briefcase.",
	"My fellow country folks can get on my nerves.",
	"%s make them look old.",
	"My ex partner left me for someone with %s hair.",
	"%s people intimidate me.",
	"People can't pull off %s clothing.",
	"%s numbers"
};
