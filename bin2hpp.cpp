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

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>


#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION
#include "source/shared/stb_image.h"

void write_image_header( std::string source_file, std::string target_file, std::string variable_name ) {
	size_t file_size = 0;
	std::ifstream source_stream;
	std::ofstream target_stream;

	target_stream.open( target_file.c_str(), std::ios_base::binary );
	//source_stream.open( source_file.c_str(), std::ios_base::binary );

	//source_stream.seekg(0, source_stream.end);
	//file_size = source_stream.tellg();
	//source_stream.seekg(0, source_stream.beg);
	
	target_stream.flags( std::ios::showbase );

stbi_convert_iphone_png_to_rgb(1);

	int stb_width, stb_height, stb_bpp;
	uint32_t * pixels = (uint32_t *)stbi_load(source_file.c_str(), &stb_width, &stb_height, &stb_bpp, 4);

	target_stream << "static uint32_t " << variable_name << "[" << stb_height << "][" << stb_width << "] = { \n\t";
	size_t c = 0;
	for (size_t y = 0; y < stb_height; y++)
	{
		target_stream << "{ ";
		for (size_t x = 0; x < stb_width; x++)
		{
			if ( x == 4 ) {
				printf("%x,", pixels[c]);
			}
			target_stream << std::hex << pixels[c] << std::dec;
			if ( x+1 != stb_width) {
				target_stream  << ", ";
			}
			c++;
		}
		target_stream << "},\n\t";

	}

	target_stream << "\n};" << std::endl;

	target_stream.close();
	source_stream.close();

}


void write_header( std::string source_file, std::string target_file, std::string variable_name ) {
	int c;
	size_t file_size = 0;
	std::ifstream source_stream;
	std::ofstream target_stream;

	target_stream.open( target_file.c_str(), std::ios_base::binary );
	source_stream.open( source_file.c_str(), std::ios_base::binary );

	source_stream.seekg(0, source_stream.end);
	file_size = source_stream.tellg();
	source_stream.seekg(0, source_stream.beg);
	
	target_stream.flags( std::ios::showbase );

	target_stream << "uint8_t " << variable_name << "_data[" << file_size << "] = { \n\t";

	file_size = 0;
	while ( source_stream.good() ) {
		file_size++;
		c = source_stream.get();

		target_stream << std::hex << c;

		if ( source_stream.peek() == std::char_traits<char>::eof() ) {
			break;
		}

		target_stream << std::dec << ",";
		if ( !(file_size % 20) )
			target_stream << "\n\t";

	}
	target_stream << "\n};" << std::endl;

	target_stream.close();
	source_stream.close();

}


std::string GenerateTargetName( std::string & path ) {
	std::string new_path = path;
	int lastdot = new_path.find_last_of( '.', new_path.length() );

	if ( lastdot ) {
		new_path.erase( lastdot, new_path.length() - lastdot );
	}
	new_path.append(".hpp");
	return new_path;
}

std::string GenerateVaribleName( std::string & path ) {
	std::string new_path = path;
	size_t lastdot = new_path.find_last_of( '.' );

	if ( lastdot != std::string::npos) {
		new_path.erase( lastdot, new_path.length() - lastdot );
	}

	size_t lastslash = new_path.find_last_of( '/');
	if ( lastslash != std::string::npos) {
		new_path.erase( 0, lastslash+1 );
	}

	lastslash = new_path.find_last_of( '\\');
	if ( lastslash != std::string::npos) {
		new_path.erase( 0, lastslash+1 );
	}
	return new_path;
}


int main(int argc, char *argv[]) {
	if ( argc > 1 ) {
		std::string source_file(argv[1]);
		std::string variable_name = GenerateVaribleName(source_file);
		std::string target_file = GenerateTargetName(source_file);

		std::cout << "Converting Bin " << argv[1] << " to header file." << std::endl;

		std::cout << "Source:" << source_file << std::endl;
		std::cout << "Variable:" << variable_name << std::endl;
		std::cout << "Target:" << target_file << std::endl;

		write_image_header( source_file, target_file, variable_name );
	}

	return 0;
}