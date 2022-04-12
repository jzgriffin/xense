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

// Variables
#include <kernel.lib/hardware.h>

/**
 * ~ OutputByte
 * ! Writes a byte to the hardware.
 * @ port Port to write to.
 * @ byte Byte to write.
 * #
 */
void OutputByte(unsigned short port, unsigned char byte)
{
	asm volatile("outb %1, %0" : : "dN" (port), "a" (byte));
}

/**
 * ~ InputByte
 * ! Reads a byte from the hardware.
 * @ port Port to read from.
 * # Byte.
 */
unsigned char InputByte(unsigned short port)
{
	unsigned char byte;

	asm volatile("inb %1, %0" : "=a" (byte) : "dN" (port));

	return byte;
}

/**
 * ~ OutputWord
 * ! Writes a word to the hardware.
 * @ port Port to write to.
 * @ word Word to write.
 * #
 */
void OutputWord(unsigned short port, unsigned short word)
{
	asm volatile("outw %0, %1" : : "a" (word), "Nd" (port));
}

/**
 * ~ InputWord
 * ! Reads a word from the hardware.
 * @ port Port to read from.
 * # Word.
 */
unsigned short InputWord(unsigned short port)
{
	register unsigned short word;

	asm volatile("inw %1, %0" : "=a" (word) : "Nd" (port));

	return word;
}

/**
 * ~ OutputLong
 * ! Writes a dword to the hardware.
 * @ port Port to write to.
 * @ dword - Dword to write.
 * #
 */
void OutputLong(unsigned short port, unsigned int dword)
{
	asm volatile("outl %0, %1" : : "a" (dword), "Nd" (port));
}

/**
 * ~ InputLong
 * ! Reads a dword from the hardware.
 * @ port Port to read from.
 * # Dword.
 */
unsigned int InputLong(unsigned short port)
{
	register unsigned int dword;

	asm volatile("inl %1, %0" : "=a" (dword) : "Nd" (port));

	return dword;
}
