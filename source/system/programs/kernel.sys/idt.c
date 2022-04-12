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
#include <kernel.lib/memory.h>
#include <kernel.sys/idt.h>
#include <kernel.sys/irq.h>
#include <kernel.sys/isr.h>

/**
 * ~ IDTSetGate
 * ! Sets an IDT gate.
 * @ number Gate number.
 * @ base Gate base.
 * @ selector Gate selector.
 * @ flags Gate flags.
 * #
 */
void IDTSetGate(unsigned char number, unsigned long base,
	unsigned short selector, unsigned char flags)
{
	IDT[number].baseLow = (base & 0xFFFF);
	IDT[number].baseHigh = (base >> 16) & 0xFFFF;
	IDT[number].selector = selector;
	IDT[number].zero = 0;
	IDT[number].flags = flags;
}

/**
 * ~ IDTInitialize
 * ! Initializes the IDT.
 * @
 * #
 */
void IDTInitialize()
{
	IDTPointer.limit = (sizeof(struct TIDTEntry) * 0xFF) - 1;
	IDTPointer.base = (int)&IDT;

	// Zero out the IDT
	MemorySet((unsigned char *)&IDT, 0, sizeof(struct TIDTEntry) * 256);

	// Install the default gates
	IDTSetGate(0x00, (unsigned)ISR00, 0x08, 0x8E);
	IDTSetGate(0x01, (unsigned)ISR01, 0x08, 0x8E);
	IDTSetGate(0x02, (unsigned)ISR02, 0x08, 0x8E);
	IDTSetGate(0x03, (unsigned)ISR03, 0x08, 0x8E);
	IDTSetGate(0x04, (unsigned)ISR04, 0x08, 0x8E);
	IDTSetGate(0x05, (unsigned)ISR05, 0x08, 0x8E);
	IDTSetGate(0x06, (unsigned)ISR06, 0x08, 0x8E);
	IDTSetGate(0x07, (unsigned)ISR07, 0x08, 0x8E);
	IDTSetGate(0x08, (unsigned)ISR08, 0x08, 0x8E);
	IDTSetGate(0x09, (unsigned)ISR09, 0x08, 0x8E);
	IDTSetGate(0x0A, (unsigned)ISR0A, 0x08, 0x8E);
	IDTSetGate(0x0B, (unsigned)ISR0B, 0x08, 0x8E);
	IDTSetGate(0x0C, (unsigned)ISR0C, 0x08, 0x8E);
	IDTSetGate(0x0D, (unsigned)ISR0D, 0x08, 0x8E);
	IDTSetGate(0x0E, (unsigned)ISR0E, 0x08, 0x8E);
	IDTSetGate(0x0F, (unsigned)ISR0F, 0x08, 0x8E);
	IDTSetGate(0x10, (unsigned)ISR10, 0x08, 0x8E);
	IDTSetGate(0x11, (unsigned)ISR11, 0x08, 0x8E);
	IDTSetGate(0x12, (unsigned)ISR12, 0x08, 0x8E);
	IDTSetGate(0x13, (unsigned)ISR13, 0x08, 0x8E);
	IDTSetGate(0x14, (unsigned)ISR14, 0x08, 0x8E);
	IDTSetGate(0x15, (unsigned)ISR15, 0x08, 0x8E);
	IDTSetGate(0x16, (unsigned)ISR16, 0x08, 0x8E);
	IDTSetGate(0x17, (unsigned)ISR17, 0x08, 0x8E);
	IDTSetGate(0x18, (unsigned)ISR18, 0x08, 0x8E);
	IDTSetGate(0x19, (unsigned)ISR19, 0x08, 0x8E);
	IDTSetGate(0x1A, (unsigned)ISR1A, 0x08, 0x8E);
	IDTSetGate(0x1B, (unsigned)ISR1B, 0x08, 0x8E);
	IDTSetGate(0x1C, (unsigned)ISR1C, 0x08, 0x8E);
	IDTSetGate(0x1D, (unsigned)ISR1D, 0x08, 0x8E);
	IDTSetGate(0x1E, (unsigned)ISR1E, 0x08, 0x8E);
	IDTSetGate(0x1F, (unsigned)ISR1F, 0x08, 0x8E);
	IDTSetGate(0x20, (unsigned)ISR20, 0x08, 0x8E);
	IDTSetGate(0x21, (unsigned)ISR21, 0x08, 0x8E);
	IDTSetGate(0x22, (unsigned)ISR22, 0x08, 0x8E);
	IDTSetGate(0x23, (unsigned)ISR23, 0x08, 0x8E);
	IDTSetGate(0x24, (unsigned)ISR24, 0x08, 0x8E);
	IDTSetGate(0x25, (unsigned)ISR25, 0x08, 0x8E);
	IDTSetGate(0x26, (unsigned)ISR26, 0x08, 0x8E);
	IDTSetGate(0x27, (unsigned)ISR27, 0x08, 0x8E);
	IDTSetGate(0x28, (unsigned)ISR28, 0x08, 0x8E);
	IDTSetGate(0x29, (unsigned)ISR29, 0x08, 0x8E);
	IDTSetGate(0x2A, (unsigned)ISR2A, 0x08, 0x8E);
	IDTSetGate(0x2B, (unsigned)ISR2B, 0x08, 0x8E);
	IDTSetGate(0x2C, (unsigned)ISR2C, 0x08, 0x8E);
	IDTSetGate(0x2D, (unsigned)ISR2D, 0x08, 0x8E);
	IDTSetGate(0x2E, (unsigned)ISR2E, 0x08, 0x8E);
	IDTSetGate(0x2F, (unsigned)ISR2F, 0x08, 0x8E);
	IDTSetGate(0x30, (unsigned)ISR30, 0x08, 0x8E);
	IDTSetGate(0x31, (unsigned)ISR31, 0x08, 0x8E);
	IDTSetGate(0x32, (unsigned)ISR32, 0x08, 0x8E);
	IDTSetGate(0x33, (unsigned)ISR33, 0x08, 0x8E);
	IDTSetGate(0x34, (unsigned)ISR34, 0x08, 0x8E);
	IDTSetGate(0x35, (unsigned)ISR35, 0x08, 0x8E);
	IDTSetGate(0x36, (unsigned)ISR36, 0x08, 0x8E);
	IDTSetGate(0x37, (unsigned)ISR37, 0x08, 0x8E);
	IDTSetGate(0x38, (unsigned)ISR38, 0x08, 0x8E);
	IDTSetGate(0x39, (unsigned)ISR39, 0x08, 0x8E);
	IDTSetGate(0x3A, (unsigned)ISR3A, 0x08, 0x8E);
	IDTSetGate(0x3B, (unsigned)ISR3B, 0x08, 0x8E);
	IDTSetGate(0x3C, (unsigned)ISR3C, 0x08, 0x8E);
	IDTSetGate(0x3D, (unsigned)ISR3D, 0x08, 0x8E);
	IDTSetGate(0x3E, (unsigned)ISR3E, 0x08, 0x8E);
	IDTSetGate(0x3F, (unsigned)ISR3F, 0x08, 0x8E);
	IDTSetGate(0x40, (unsigned)IRQ00, 0x08, 0x8E);
	IDTSetGate(0x41, (unsigned)IRQ01, 0x08, 0x8E);
	IDTSetGate(0x42, (unsigned)IRQ02, 0x08, 0x8E);
	IDTSetGate(0x43, (unsigned)IRQ03, 0x08, 0x8E);
	IDTSetGate(0x44, (unsigned)IRQ04, 0x08, 0x8E);
	IDTSetGate(0x45, (unsigned)IRQ05, 0x08, 0x8E);
	IDTSetGate(0x46, (unsigned)IRQ06, 0x08, 0x8E);
	IDTSetGate(0x47, (unsigned)IRQ07, 0x08, 0x8E);
	IDTSetGate(0x48, (unsigned)IRQ08, 0x08, 0x8E);
	IDTSetGate(0x49, (unsigned)IRQ09, 0x08, 0x8E);
	IDTSetGate(0x4A, (unsigned)IRQ0A, 0x08, 0x8E);
	IDTSetGate(0x4B, (unsigned)IRQ0B, 0x08, 0x8E);
	IDTSetGate(0x4C, (unsigned)IRQ0C, 0x08, 0x8E);
	IDTSetGate(0x4D, (unsigned)IRQ0D, 0x08, 0x8E);
	IDTSetGate(0x4E, (unsigned)IRQ0E, 0x08, 0x8E);
	IDTSetGate(0x4F, (unsigned)IRQ0F, 0x08, 0x8E);

	// Now load the IDT
	IDTLoad();
}
