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

#ifndef __KERNEL_SYS_KEYBOARD_H__
#define __KERNEL_SYS_KEYBOARD_H__

// Includes
#include <kernel.lib/assembly.h>

// Definitions
#define KEY_CONTROL 29
#define KEY_LSHIFT 42
#define KEY_RSHIFT 54
#define KEY_ALT 56
#define KEY_CLOCK 58
#define KEY_F1 59
#define KEY_F2 60
#define KEY_F3 61
#define KEY_F4 62
#define KEY_F5 63
#define KEY_F6 64
#define KEY_F7 65
#define KEY_F8 66
#define KEY_F9 67
#define KEY_F10 68
#define KEY_NLOCK 69
#define KEY_SLOCK 70
#define KEY_HOME 71
#define KEY_UARROW 72
#define KEY_PAGEUP 73
#define KEY_LARROW 75
#define KEY_RARROW 77
#define KEY_END 79
#define KEY_DARROW 80
#define KEY_PAGEDOWN 81
#define KEY_INSERT 82
#define KEY_DELETE 83
#define KEY_F11 87
#define KEY_F12 88

// Variables
extern unsigned char keyChr;

// Routines
extern void KeyboardRead(char* buffer, int size);
extern void KeyboardClearKey();
extern void KeyboardHandler(struct TRegisters* registers);
extern void KeyboardInitialize();

#endif // !__KERNEL_SYS_KEYBOARD_H__
