
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

const struct Memblock const system_default_memblocks[NUM_DEFAULT_MEMBLOCKS] = {
	DEFINE_MEMBLOCK("ram0", NULL, 0x400, 0x4000, MEMBLOCK_FLAG_RW),
	DEFINE_MEMBLOCK("ram0-mirror", NULL, 0x400, 0x4000, MEMBLOCK_FLAG_MIRROR)
};

// System state vars
int system_state_hblank 			= 0;
int system_state_hdisplay 			= 0;
int system_state_hretrace 			= 0;
int system_state_vblank 			= 0;
int system_state_display 			= 0;
int system_state_binno 				= 0;

int system_state_count 				= 0;
int system_state_mi_enabled 		= NULL;
int system_state_linecntr 			= 0;
int system_state_cassette_out 		= NULL;
int system_state_r_register 		= 0xFF;

bool system_vblank_active 			= false;
bool system_vretrace_active  		= false;
bool system_vdisplay_active  		= false;

bool system_hblank_active  			= false;
bool system_hdisplay_active  		= false;
bool system_hretrace_active  		= false;
bool system_wait_for_db_00 			= true;

bool system_nmi_enabled				= true;

//-------------------------------------------------
