
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <GL/glew.h>

	#include <stdlib.h>
	#include <stdbool.h>
	#include <stdio.h>
	#include <time.h>
	#include <math.h>

	#include <z80.h>
	#include "system.h"
	#include "emu.h"

//-------------------------------------------------

const struct Memblock const system_default_memblocks[] = {
	DEFINE_MEMBLOCK("ram", NULL, 0xFFFF, 0x8000, MEMBLOCK_FLAG_RW)
};

//-------------------------------------------------
