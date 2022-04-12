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

#ifndef __KERNEL_LIB_ASSEMBLY_H__
#define __KERNEL_LIB_ASSEMBLY_H__

// Structures
struct TRegisters
{
    unsigned int ds, es, fs, gs;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int intNumber, errorCode;
    char* eip;
    unsigned int cs, eflags, useresp, ss;
};

// Typedefs
typedef struct
{
    unsigned long flags, memLower, memUpper, device;
    unsigned char command;
    unsigned long moduleCount, moduleAddr;
} TBootInfo, *PBootInfo;

// Routines
extern void Halt();
extern void Cli();
extern void Sti();
extern void Reboot();

#endif // !__KERNEL_LIB_ASSEMBLY_H__
