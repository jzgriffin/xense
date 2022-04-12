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
#include <kernel.sys/gdt.h>

/**
 * ~ GDTSetGate
 * ! Sets a GDT gate.
 * @ number Gate number.
 * @ base Gate base.
 * @ limit Gate limit.
 * @ access Gate access.
 * @ granularity Gate granularity.
 * #
 */
void GDTSetGate(int number, unsigned long base, unsigned long limit,
	unsigned char access, unsigned char granularity
)
{
	GDT[number].baseLow = (base & 0xFFFF);
	GDT[number].baseMiddle = (base >> 16) & 0xFF;
	GDT[number].baseHigh = (base >> 24) & 0xFF;
	GDT[number].limitLow = (limit & 0xFFFF);
	GDT[number].granularity = ((limit >> 16) & 0x0F);
	GDT[number].granularity |= (granularity & 0xF0);
	GDT[number].access = access;
}

/**
 * ~ GDTInitialize
 * ! Initializes the GDT.
 * @
 * #
 */
void GDTInitialize()
{
	GDTPointer.limit = (sizeof(struct TGDTEntry) * 3) - 1;
	GDTPointer.base = (int)&GDT;
	
	// Set up the default gates
	GDTSetGate(0, 0, 0, 0, 0);
	GDTSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	GDTSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	
	// Flush it!
	GDTFlush();
}
