// Copyright 2007-2022 Jeremiah Griffin
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
// SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
// OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
// CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#ifndef __KERNEL_LIB_SCREEN_H__
#define __KERNEL_LIB_SCREEN_H__

// Includes
#include <kernel.lib/argument.h>

// Definitions
#define VGA_MONOCHROME 0
#define VGA_COLOR 1
#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_BROWN 6
#define COLOR_LGREY 7
#define COLOR_DGREY 8
#define COLOR_LBLUE 9
#define COLOR_LGREEN 10
#define COLOR_LCYAN 11
#define COLOR_LRED 12
#define COLOR_LMAGENTA 13
#define COLOR_LBROWN 14
#define COLOR_WHITE 15
#define COLOR_DEFAULTF 7
#define COLOR_DEFAULTB 0

// Variables
extern int screenX, screenY;

// Routines
extern void PrintChr(char chr);
extern int PrintStr(const char* format, ...);
extern void PrintInfo(char* info);
extern void PrintWarning(char* warning);
extern void PrintError(char* error);
extern void ClearScreen();
extern void ScreenUpdateCursor();
extern void ScreenScroll();
extern int ScreenType();
extern int ScreenMakeColor(unsigned char fore, unsigned char back);
extern void ScreenSetColor(unsigned char fore, unsigned char back);
extern void ScreenGetColor(int* fore, int* back);
extern void ScreenInitialize();

#endif // __KERNEL_LIB_SCREEN_H__
