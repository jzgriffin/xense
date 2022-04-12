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

#ifndef __KERNEL_SYS_GDT_H__
#define __KERNEL_SYS_GDT_H__

// Structures
struct TGDTEntry
{
    unsigned short limitLow;
    unsigned short baseLow;
    unsigned char baseMiddle;
    unsigned char access;
    unsigned char granularity;
    unsigned char baseHigh;
} __attribute__((packed));
struct TGDTPointer
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));
struct TGDTEntry GDT[3];
struct TGDTPointer GDTPointer;

// Routines
extern void GDTSetGate(int number,
    unsigned long base,
    unsigned long limit,
    unsigned char access,
    unsigned char granularity);
extern void GDTInitialize();
extern void GDTFlush(); // This is in start.asm

#endif // !__KERNEL_SYS_GDT_H__
