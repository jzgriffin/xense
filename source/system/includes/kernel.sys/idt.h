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

#ifndef __KERNEL_SYS_IDT_H__
#define __KERNEL_SYS_IDT_H__

// Structures
struct TIDTEntry
{
    unsigned short baseLow;
    unsigned short selector;
    unsigned char zero;
    unsigned char flags;
    unsigned short baseHigh;
} __attribute__((packed));
struct TIDTPointer
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));
struct TIDTEntry IDT[256];
struct TIDTPointer IDTPointer;

// Routines
extern void
IDTSetGate(unsigned char number, unsigned long base, unsigned short selector, unsigned char flags);
extern void IDTInitialize();
extern void IDTLoad(); // This is in start.asm

#endif // !__KERNEL_SYS_IDT_H__
