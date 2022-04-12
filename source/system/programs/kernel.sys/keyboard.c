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
#include <kernel.lib/hardware.h>
#include <kernel.lib/memory.h>
#include <kernel.lib/strings.h>
#include <kernel.lib/screen.h>
#include <kernel.sys/irq.h>
#include <kernel.sys/keyboard.h>
#include <kernel.sys/timer.h>

// Structures
struct TKeyScan
{
	int volatile scanning;
	char *buffer;
	int index, startX;
};
struct TKeyScan *const keyScan;
unsigned short keyboardStatus = 0;
unsigned char keyboard[1][2][128] = {
	{
		{
			0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
			'-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
			'o', 'p', '[', ']', '\n', KEY_CONTROL, 'a', 's', 'd', 'f', 'g',
			'h', 'j', 'k', 'l', ';', '\'', '`', KEY_LSHIFT, '\\', 'z', 'x',
			'c', 'v', 'b', 'n', 'm', ',', '.', '/', KEY_RSHIFT, '*', KEY_ALT,
			' ', KEY_CLOCK, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7,
			KEY_F8, KEY_F9, KEY_F10, KEY_NLOCK, KEY_SLOCK, KEY_HOME, KEY_UARROW,
			KEY_PAGEUP, '-', KEY_LARROW, 0, KEY_RARROW, '+', KEY_END,
			KEY_DARROW, KEY_PAGEDOWN, KEY_INSERT, KEY_DELETE, 0, 0, 0, KEY_F11,
			KEY_F12, 0,
		},
		{
			0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
			'_', '+', '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
			'O', 'P', '{', '}', '\n', KEY_CONTROL, 'A', 'S', 'D', 'F', 'G',
			'H', 'J', 'K', 'L', ':', '"', '~', KEY_LSHIFT, '|', 'Z', 'X',
			'C', 'V', 'B', 'N', 'M', '<', '>', '?', KEY_RSHIFT, '*', KEY_ALT,
			' ', KEY_CLOCK, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7,
			KEY_F8, KEY_F9, KEY_F10, KEY_NLOCK, KEY_SLOCK, KEY_HOME, KEY_UARROW,
			KEY_PAGEUP, '-', KEY_LARROW, 0, KEY_RARROW, '+', KEY_END,
			KEY_DARROW, KEY_PAGEDOWN, KEY_INSERT, KEY_DELETE, 0, 0, 0, KEY_F11,
			KEY_F12, 0,
		},
	},
}, keyChr = '\0';

/**
 * ~ KeyboardRead
 * ! Starts reading to a user-specified buffer.
 * @ buffer Pointer to the buffer.
 * @ size Buffer size.
 * #
 */
void KeyboardRead(char *buffer, int size)
{
	keyScan->scanning = 1;
	keyScan->buffer = buffer;
	keyScan->index = 0;
	keyScan->startX = screenX;

	MemorySet(buffer, '\0', size);

	while (keyScan->scanning == 1);
}

/**
 * ~ KeyboardHandler
 * ! Handles keypresses.
 * @ registers Registers at the time of the event.
 * #
 */
void KeyboardHandler(struct TRegisters *registers)
{
	int extended = 0, up = 0;
	unsigned char scanCode;
	unsigned short temp;

	// Get rid of those nasty unused parameter warnings (we use -Werror)
	if (registers->intNumber == 1) { }

	// Read the byte from port 0x60
	scanCode = InputByte(0x60);

	if (scanCode == 0xE0)
	{
		extended = 1;
		return;
	}
	if (scanCode >= 0x80)
	{
		up = 1;
		scanCode &= 0x7F;
	}

	if (up && !extended)
	{
		switch (scanCode)
		{
		case KEY_LSHIFT:
		case KEY_RSHIFT:
			keyboardStatus &= ~KEY_LSHIFT;
			break;
		case KEY_ALT:
			keyboardStatus &= ~KEY_ALT;
			break;
		case KEY_CONTROL:
			keyboardStatus &= ~KEY_CONTROL;
			break;
		default:
			break;
		}
		return;
	}

	switch (scanCode)
	{
	case 0x01:
		if (keyboardStatus & KEY_CONTROL)
		{
			//KeyboardExtended(0x5B);
		}
		else
		{
			// Escape
		}
		return;
	case KEY_ALT:
		keyboardStatus |= KEY_ALT;
		return;
	case KEY_CONTROL:
		keyboardStatus |= KEY_CONTROL;
		return;
	case KEY_LSHIFT:
	case KEY_RSHIFT:
		keyboardStatus |= KEY_LSHIFT;
		extended = 0;
		return;
	case KEY_SLOCK:
		keyboardStatus ^= KEY_SLOCK;
		OutputByte(0x60, 0xED);
		temp = 0;
		if (keyboardStatus & KEY_SLOCK)
		{
			temp |= 1;
		}
		if (keyboardStatus & KEY_NLOCK)
		{
			temp |= 2;
		}
		if (keyboardStatus & KEY_CLOCK)
		{
			temp |= 4;
		}
		OutputByte(0x60, temp);
		return;
	case KEY_NLOCK:
		keyboardStatus ^= KEY_NLOCK;
		OutputByte(0x60, 0xED);
		temp = 0;
		if (keyboardStatus & KEY_SLOCK)
		{
			temp |= 1;
		}
		if (keyboardStatus & KEY_NLOCK)
		{
			temp |= 2;
		}
		if (keyboardStatus & KEY_CLOCK)
		{
			temp |= 4;
		}
		OutputByte(0x60, temp);
		return;
	case KEY_CLOCK:
		keyboardStatus ^= KEY_CLOCK;
		OutputByte(0x60, 0xED);
		temp = 0;
		if (keyboardStatus & KEY_SLOCK)
		{
			temp |= 1;
		}
		if (keyboardStatus & KEY_NLOCK)
		{
			temp |= 2;
		}
		if (keyboardStatus & KEY_CLOCK)
		{
			temp |= 4;
		}
		OutputByte(0x60, temp);
		return;
	default:
		break;
	}

	if (extended)
	{
		if (up)
		{
			scanCode += 0x80;
		}
		//KeyboardExtended(scanCode);
		return;
	}

	if (scanCode >= sizeof(keyboard[0][0]) / sizeof(keyboard[0][0][0]))
	{
		PrintWarning("Unknown scan code received from keyboard!\n");
		return;
	}

	keyChr = keyboard[0][0][scanCode];
	if (keyboardStatus & KEY_LSHIFT)
	{
		keyChr = keyboard[0][1][scanCode];
	}
	if (keyScan->scanning == 1)
	{
		if (scanCode != 0x4B && scanCode != 0x4D && scanCode != 0x48 && scanCode != 0x50 && keyChr != '\b')
		{
			PrintChr(keyChr);
		}
		else
		{
			if (scanCode == 0x4B)
			{
				if (screenX - 1 >= keyScan->startX)
				{
					screenX--;
				}
			}
			else if (scanCode == 0x4D)
			{
				if (keyScan->index + 1 < StringSize(keyScan->buffer) + 1)
				{
					screenX++;
				}
			}
			else if (keyChr == '\b')
			{
				if (screenX - 1 >= keyScan->startX)
				{
					PrintChr(keyChr);
				}
			}
			ScreenUpdateCursor();
		}

		if (keyChr == '\n')
		{
			keyScan->scanning = 0;
		}
		else if (keyChr == '\b')
		{
			if (keyScan->index - 1 >= 0)
			{
				keyScan->index--;
				keyScan->buffer[keyScan->index] = '\0';
			}
		}
		else if (keyChr == 127)
		{
			keyScan->buffer[keyScan->index] = '\0';
		}
		else if (scanCode == 0x4B)
		{
			if (keyScan->index > 0)
			{
				keyScan->index--;
			}
		}
		else if (scanCode == 0x4D)
		{
			if (keyScan->index + 1 < StringSize(keyScan->buffer) + 1)
			{
				keyScan->index++;
			}
		}
		else if (keyChr >= 32 && keyChr <= 126)
		{
			keyScan->buffer[keyScan->index] = keyChr;
			keyScan->index++;
		}
	}

	if (scanCode == 0x00 || scanCode == 0xFF)
	{
		// Do it Microsoft-style
		PrintStr("\nKeyboard controller error (scan code 0x%02X).\n", scanCode);
		PrintStr("Please check the keyboard is fully inserted into the port,\n");
		PrintStr("and restart your computer. If the problem persists, contact\n");
		PrintStr("your keyboard vendor.", scanCode);
		return;
	}

	if ((keyboardStatus & KEY_CONTROL) && (keyboardStatus & KEY_ALT))
	{
		switch (scanCode)
		{
		case KEY_DELETE:
			ClearScreen();
			PrintStr("Thank you for using Xense, the system will now reboot.\n");
			Reboot();
			break;
		default:
			break;
		}
	}
	if (keyboardStatus & KEY_ALT)
	{
		switch (scanCode)
		{
		case KEY_F1:
		case KEY_F2:
		case KEY_F3:
		case KEY_F4:
		case KEY_F5:
		case KEY_F6:
		case KEY_F7:
		case KEY_F8:
			PrintWarning("Virtual consoles have not yet been implemented.\n");
			break;
		case KEY_F9:
			PrintWarning("Graphic modes have not yet been implemented.\n");
			break;
		case KEY_F10:
			PrintWarning("Virtual consoles have not yet been implemented.\n");
			break;
		default:
			break;
		}
	}
}

/**
 * ~ KeyboardInitialize
 * ! Initializes the keyboard.
 * @
 * #
 */
void KeyboardInitialize()
{
	IRQInstall(1, KeyboardHandler);
}
