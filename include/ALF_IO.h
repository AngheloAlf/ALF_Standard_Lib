#ifndef ALF_IO_h
#define ALF_IO_h

#include "ALF_common.h"

#define ALF_IO_major_version (1)
#define ALF_IO_minor_version (0)
#define ALF_IO_patch_version (0)
#define ALF_IO_version (ALF_IO_major_version.ALF_IO_minor_version)
#define ALF_IO_version_str (ALF_STR(ALF_IO_major_version)"."ALF_STR(ALF_IO_minor_version)"."ALF_STR(ALF_IO_patch_version))


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ALF_ANSI_COLOR_BLACK	"\x1b[30m"
#define ALF_ANSI_COLOR_RED		"\x1b[31m"
#define ALF_ANSI_COLOR_GREEN	"\x1b[32m"
#define ALF_ANSI_COLOR_YELLOW	"\x1b[33m"
#define ALF_ANSI_COLOR_BLUE		"\x1b[34m"
#define ALF_ANSI_COLOR_MAGENTA	"\x1b[35m"
#define ALF_ANSI_COLOR_CYAN		"\x1b[36m"
#define ALF_ANSI_COLOR_WHITE	"\x1b[37m"
#define ALF_ANSI_COLOR_RESET	"\x1b[0m"

/// Python-like input of data.
/** 
 * This functions prints out a message on screen.
 * Then asks for input via stdin.
 * The input string is propety of the caller, and he have to free it.
**/
char *ALF_raw_input(const char *outMessage);

/// 
/** 
 * 
**/
void ALF_puthex(unsigned char character);

/// 
/** 
 * 
**/
void ALF_printfColoredBlock(unsigned char character, int withNumber);

#endif /* ALF_LIB_IO */
