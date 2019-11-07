
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <GL/glew.h>

	#include <stdlib.h>
	#include <stdbool.h>
	#include <stdio.h>
	#include <time.h>
	#include <math.h>

	#include <charset.xpm>
	#include <system.h>
	#include <emu.h>

//-------------------------------------------------

SDL_Texture *charTexture;			// Texture containing the graphics for every character in the charset

//-------------------------------------------------

void setup_video(void) {
	// Create a character sheet texture from the charset data array
	// The texture allows us to manipulate the character graphics directly
	charTexture = SDL_CreateTextureFromSurface(renderer, IMG_ReadXPMFromArray(charset_xpm));
}

void render_vram(SDL_Renderer *renderer) {
	// Set the base in memory of the VRAM
	// Then go through each position on the screen and find where in this memory it maps to
	// Get the value in that place and use that to index the charset
	size_t screen_pos = CFG_REG_D_FILE;
	for (int x = 0; x < CHAR_COLS; x++) {
		for (int y = 0; y < CHAR_ROWS; y++) {
			char charval = read_memspace_byte(main_context, screen_pos+x+(y*24));
			// Position a char sized rectangle in the correct position on the character sheet
			// Based on the value read from the calculated memory position
			SDL_Rect src_char = { (charval%16)*8, (charval/16)*8, 8, 8};
			// Find the place on the screen texture where the character is supposed to be
			SDL_Rect dest_char = { x*8, y*8, 8, 8};
			// Copy the char from the character sheet onto the screen texture
			SDL_RenderCopy(renderer, charTexture, &src_char, &dest_char);
		}
	}
}
