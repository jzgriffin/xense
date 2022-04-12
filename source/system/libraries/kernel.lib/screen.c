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

// Includes
#include <kernel.lib/argument.h>
#include <kernel.lib/hardware.h>
#include <kernel.lib/format.h>
#include <kernel.lib/memory.h>
#include <kernel.lib/strings.h>
#include <kernel.lib/screen.h>

// Variables
unsigned short *screen;
int screenX = 0, screenY = 0, screenColor, screenColorF, screenColorB;

/**
 * ~ PrintChr
 * ! Prints a character to the screen.
 * @ chr Character to print.
 * #
 */
void PrintChr(char chr)
{
	if (chr == 0x08)
	{
		// Backspace
		if (screenX != 0)
		{
			screenX--;

			unsigned short *where;
			unsigned color;

			color = screenColor << 8;
			where = screen + (screenY * 80 + screenX);
			*where = ' ' | color;
		}
	}
	else if (chr == 0x09)
	{
		// Tab
		screenX += 8;
	}
	else if (chr == 0x0A)
	{
		// Linefeed
		screenX = 0;
		screenY++;
	}
	else if (chr == 0x0D)
	{ 
		// Carriage return
		screenX = 0;
	}
	else if (chr >= 0x20)
	{
		// Space and above
		unsigned short *where;
		unsigned color;

		color = screenColor << 8;
		where = screen + (screenY * 80 + screenX);
		*where = chr | color;

		screenX++;
	}

	// Time for a new line?
	if (screenX >= 80)
	{
		screenX = screenX - 80;
		screenY++;
	}

	// Update the cursor and scroll the screen (if necessary)
	ScreenUpdateCursor();
	ScreenScroll();
}

/**
 * ~ PrintStrVH
 * ! Helper function for PrintStrV.
 * @ chr Character to handle.
 * @ pointer Destination.
 * # 0
 */
int PrintStrVH(unsigned chr, void **pointer)
{
	// Gets rid of "unused parameter" warnings that cause errors with -Werror
	if (pointer == null) { }

	PrintChr(chr);

	return 0;
}

/**
 * ~ PrintStrV
 * ! Helper function for PrintStr.
 * @ format String to format.
 * @ arg Argument to format with.
 * # Byte count.
 */
int PrintStrV(const char *format, TArgList arg)
{
	return FormatBackend(format, arg, PrintStrVH, null);
}

/**
 * ~ PrintStr
 * ! Prints a null-terminated, formatted string.
 * @ format String to print
 * @ ... Formatting arguments.
 * # Number of characters printed.
 */
int PrintStr(const char *format, ...)
{
	TArgList arg;
	int returnValue;

	argStart(arg, format);
	returnValue = PrintStrV(format, arg);
	argStop(arg);

	return returnValue;
}

/**
 * ~ PrintInfo
 * ! Prints an [Info] line.
 * @ info Info to print.
 * #
 */
void PrintInfo(char *info)
{
	int fore, back;

	ScreenGetColor(&fore, &back); // Back up old color
	ScreenSetColor(COLOR_WHITE, COLOR_BLACK);
	PrintStr("[Info] ");
	ScreenSetColor(fore, back);
	PrintStr(info);
}

/**
 * ~ PrintWarning
 * ! Prints a [Warning] line.
 * @ warning Warning to print.
 * #
 */
void PrintWarning(char *warning)
{
	int fore, back;

	ScreenGetColor(&fore, &back); // Back up old color
	ScreenSetColor(COLOR_LBLUE, COLOR_BLACK);
	PrintStr("[Warning] ");
	ScreenSetColor(fore, back);
	PrintStr(warning);
}

/**
 * ~ PrintError
 * ! Prints an [Error] line.
 * @ error Error to print.
 * #
 */
void PrintError(char *error)
{
	int fore, back;

	ScreenGetColor(&fore, &back); // Back up old color
	ScreenSetColor(COLOR_LRED, COLOR_BLACK);
	PrintStr("[Error] ");
	ScreenSetColor(fore, back);
	PrintStr(error);
}

/**
 * ~ ClearScreen
 * ! Clears the screen of all data.
 * @
 * #
 */
void ClearScreen()
{
	int index;

	screenX = screenY = 0;

	for (index = 0; index < 80 * 25; index++)
	{
		PrintChr(' ');
	}

	screenX = screenY = 0;
	ScreenUpdateCursor();
}

/**
 * ~ ScreenUpdateCursor
 * ! Updates the VGA/CRT cursor position.
 * @
 * #
 */
void ScreenUpdateCursor()
{
	unsigned position = (screenY * 80) + screenX;

	// Cursor low port to the VGA index register
	OutputByte(0x3D4, 0x0F);
	OutputByte(0x3D5, position);

	// Cursor high port to the VGA index register
	OutputByte(0x3D4, 0x0E);
	OutputByte(0x3D5, position >> 8);
}

/**
 * ~ ScreenScroll
 * ! Scrolls the screen (if necessary).
 * @
 * #
 */
void ScreenScroll()
{
	unsigned blank, position;

	blank = 0x20 | (screenColor << 8);

	// Is the current row/Y greater than or equal to 25, the screen's
	// height?
	if (screenY >= 25)
	{
		position = screenY - 25 + 1;
		MemoryCopy(screen, screen + position * 80,
			(25 - position) * 80 * 2);
		MemorySetW(screen + (25 - position) * 80, blank, 80);
		screenY = 25 - 1;
	}
}

/**
 * ~ ScreenType
 * ! Detects whether the video card is monochrome or colored
 * @
 * # VGA_MONOCHROME for monochrome, VGA_COLOR for color
 */
int ScreenType()
{
	int type;
	char chr = (*(unsigned short *)0x410) & 0x30;

	if (chr == 0x30)
	{
		// 0x30 for monochrome
		type = VGA_MONOCHROME;
	}
	else
	{
		// 0x00 or 0x20 for color
		type = VGA_COLOR;
	}

	return type;
}

/**
 * ~ ScreenMakeColor
 * ! Makes a color code from two colors.
 * @ fore Foreground color
 * @ back Background color
 * # Color code
 */
int ScreenMakeColor(unsigned char fore, unsigned char back)
{
	// High bytes are the background, low bytes are the foreground
	return (back << 4) | (fore & 0x0F);
}

/**
 * ~ ScreenSetColor
 * ! Sets the color to print in.
 * @ fore Foreground color.
 * @ back Background color.
 * #
 */
void ScreenSetColor(unsigned char fore, unsigned char back)
{
	screenColor = ScreenMakeColor(fore, back);
	screenColorF = fore;
	screenColorB = back;
}

/**
 * ~ ScreenGetColor
 * ! Gets the console colors.
 * @ fore Pointer to foreground integer.
 * @ back Pointer to background integer.
 * #
 */
void ScreenGetColor(int *fore, int *back)
{
	*fore = screenColorF;
	*back = screenColorB;
}

/**
 * ~ ScreenInitialzie
 * ! Initializes the VGA system.
 * @
 * #
 */
void ScreenInitialize()
{
	if (ScreenType() == VGA_MONOCHROME)
	{
		screen = (unsigned short *)0xB0000;
	}
	else
	{
		screen = (unsigned short *)0xB8000;
	}

	ScreenSetColor(COLOR_DEFAULTF, COLOR_DEFAULTB);

	ClearScreen();
}
