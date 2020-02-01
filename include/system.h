//-------------------------------------------------
// Header for definitions of system attributes
//-------------------------------------------------

#ifndef _SYSDEFS_HEADER
#define _SYSDEFS_HEADER

	#include "emu.h"

//-------------------------------------------------

#define CHAR_ROWS	24
#define CHAR_COLS	32

// +-------+-----+-----+----+--------------------------------------------------+
// |SYSTEM |OLD  |NEW  |NO. |                                                  |
// |VARIA- |ROM  |ROM  |OF  |                                                  |
// |BLES   |ADDR.|ADDR.|BYT.|PURPOSE                                           |
// +-------+-----+-----+----+--------------------------------------------------+
// |ACC    |4022 |-    |2   |Value of last expression                          |
// |BERG   |-    |401E |1   |Used by floating poextern int calculator                 |
// |CDFLAG |-    |403B |1   |Flags relating to FAST/SLOW mode                  |
// |CH_ADD |4026 |4016 |2   |Address of the next character to extern interpret        |
// |COORDS |-    |4036 |2   |Coordinates of last poextern int PLOTed                  |
// |D_FILE |400C |400C |2   |Address of start of display file                  |
// |DB_ST  |-    |4027 |1   |Debounce status of keyboard                       |
// |DEST   |-    |4012 |2   |Address of variable being assigned                |
// |DF_CC  |-    |400E |2   |Address of prextern int position within display file     |
// |DF_EA  |400E |-    |2   |Address of start of lower part of screen          |
// |DF_END |4010 |-    |2   |Address of end of display file                    |
// |DF_SZ  |4012 |4022 |2   |Number of lines in lower part of screen           |
// |E_ADDR |4004 |-    |2   |Address of cursor in edit line                    |
// |E_LINE |400A |4014 |2   |Address of start of edit line                     |
// |E_PPC  |4006 |400A |2   |Line number of line with cursor                   |
// |ERR_NR |4000 |4000 |1   |Current report code minus one                     |
// |ERR_SP |-    |4002 |2   |Address of top of GOSUB stack                     |
// |FLAGS  |4001 |4001 |1   |Various flags                                     |
// |FLAGX  |4019 |402D |1   |Various flags                                     |
// |FRAMES |401E |4034 |2   |Updated once for every TV frame displayed         |
// |LAST_K |-    |4025 |2   |Keyboard scan taken after the last TV frame       |
// |MARGIN |-    |4028 |1   |Number of blank lines above or below picture      |
// |MEM    |-    |401F |2   |Address of start of calculator's memory area      |
// |MEMBOT |-    |405D |1E  |Area which may be used for calculator memory      |
// |MODE   |-    |4006 |1   |Current cursor mode                               |
// |NXTLIN |-    |4029 |2   |Address of next program line to be executed       |
// |OLDPPC |4017 |402B |2   |Line number to which CONT/CONTINUE jumps          |
// |PPC    |4002 |4007 |2   |Line number of line being executed                |
// |PR_CC  |-    |4038 |1   |Address of LPRextern int position (high part assumed 40) |
// |PRBUFF |-    |403C |21h |Buffer to store LPRextern int output                     |
// |RAMTOP |-    |4004 |2   |Address of reserved area (not wiped out by NEW)   |
// |S_POSN |4024 |4039 |2   |Coordinates of prextern int position                     |
// |S_TOP  |4013 |4023 |2   |Line number of line at top of screen              |
// |SEED   |401C |4032 |2   |Seed for random number generator                  |
// |SPARE1 |-    |4021 |1   |One spare byte                                    |
// |SPARE2 |-    |407B |2   |Two spare bytes                                   |
// |STKBOT |-    |401A |2   |Address of calculator stack                       |
// |STKEND |-    |401C |2   |Address of end of calculator stack                |
// |STRLEN |-    |402E |2   |Information concerning assigning of strings       |
// |T_ADDR |401A |4030 |2   |Address of next item in syntax table              |
// |V_ADDR |4020 |-    |2   |Address of variable name to be assigned           |
// |VARS   |4008 |4010 |2   |Address of start of variables area                |
// |VERSN  |-    |4009 |1   |First system variable to be SAVEd                 |
// |X_PTR  |4015 |4018 |2   |Address of char. preceding syntax error marker    |
// +-------+-----+-----+----+--------------------------------------------------+

#define	SYSREG_BERG			0x401e
#define	SYSREG_CDFLAG		0x403b
#define	SYSREG_CH_ADD		0x4016
#define	SYSREG_COORDS		0x4036
#define	SYSREG_D_FILE		0x400c
#define	SYSREG_DB_ST		0x4027
#define	SYSREG_DEST			0x4012
#define	SYSREG_DF_CC		0x400e
#define	SYSREG_DF_SZ		0x4022
#define	SYSREG_E_LINE		0x4014
#define	SYSREG_E_PPC		0x400A
#define	SYSREG_ERR_NR		0x4000
#define	SYSREG_ERR_SP		0x4002
#define	SYSREG_FLAGS		0x4001
#define	SYSREG_FLAGX		0x402D
#define	SYSREG_FRAMES		0x4034
#define	SYSREG_LAST_K		0x4025
#define	SYSREG_MARGIN		0x4028
#define	SYSREG_MEM			0x401F
#define	SYSREG_MEMBOT		0x405D
#define	SYSREG_MODE			0x4006
#define	SYSREG_NXTLIN		0x4029
#define	SYSREG_OLDPPC		0x402B
#define	SYSREG_PPC			0x4007
#define	SYSREG_PR_CC		0x4038
#define	SYSREG_PRBUFF		0x403c
#define	SYSREG_RAMTOP		0x4004
#define	SYSREG_S_POSN		0x4039
#define	SYSREG_S_TOP		0x4023
#define	SYSREG_SEED			0x4032
#define	SYSREG_SPARE1		0x4021
#define	SYSREG_SPARE2		0x407b
#define	SYSREG_STKBOT		0x401a
#define	SYSREG_STKEND		0x401c
#define	SYSREG_STRLEN		0x402e
#define	SYSREG_T_ADDR		0x4030
#define	SYSREG_VARS			0x4010
#define	SYSREG_VERSN		0x4009
#define	SYSREG_X_PTR		0x4018

//-------------------------------------------------

#define is_special_char(c)		((c >= 0 && c <= 63)|(c == 118)|(c >= 128 && c <= 191))

#define DFCHR_CR		118		// DFile carriage return

//-------------------------------------------------

#define NUM_DEFAULT_MEMBLOCKS		2
extern const struct Memblock const system_default_memblocks[NUM_DEFAULT_MEMBLOCKS];

extern int system_state_hblank;
extern int system_state_hdisplay;
extern int system_state_hretrace;
extern int system_state_vblank;
extern int system_state_display;
extern int system_state_binno;

extern int system_state_count;
extern int system_state_mi_enabled;
extern int system_state_linecntr;
extern int system_state_cassette_out;
extern int system_state_r_register;

extern bool system_vblank_active;
extern bool system_vretrace_active;
extern bool system_vdisplay_active;

extern bool system_hblank_active;
extern bool system_hdisplay_active;
extern bool system_hretrace_active;
extern bool system_wait_for_db_00;

extern bool system_nmi_enabled;

//-------------------------------------------------
#endif
