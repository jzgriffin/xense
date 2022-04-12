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

#ifndef __KERNEL_SYS_IRQ_H__
#define __KERNEL_SYS_IRQ_H__

// Includes
#include <kernel.lib/assembly.h>

// Routines
extern void IRQ00();
extern void IRQ01();
extern void IRQ02();
extern void IRQ03();
extern void IRQ04();
extern void IRQ05();
extern void IRQ06();
extern void IRQ07();
extern void IRQ08();
extern void IRQ09();
extern void IRQ0A();
extern void IRQ0B();
extern void IRQ0C();
extern void IRQ0D();
extern void IRQ0E();
extern void IRQ0F();
extern void IRQWait(int number);
extern void IRQWait2(struct TRegisters* registers);
extern void IRQInstall(int irq, void (*handler)(struct TRegisters* registers));
extern void IRQUninstall(int irq);
extern void IRQHandler2(struct TRegisters* registers);
extern void IRQHandler(struct TRegisters* registers);
extern void IRQInitialize();

#endif // !__KERNEL_SYS_IRQ_H__
