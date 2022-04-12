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
#include <kernel.lib/screen.h>
#include <kernel.sys/irq.h>

// Variables
void *IRQRoutines[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int volatile IRQWaiting[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/**
 * ~ IRQWait
 * ! Waits for an interrupt from the specified IRQ.
 * @ number IRQ number.
 * #
 */
void IRQWait(int number)
{
	IRQInstall(number, IRQWait2);
	IRQWaiting[number] = 1;

	while (IRQWaiting[number] == 1);
}

/**
 * ~ IRQWait2
 * ! Handler function for IRQWait.
 * @ registers Register information.
 * #
 */
void IRQWait2(struct TRegisters *registers)
{
	IRQWaiting[registers->intNumber] = 0;
}

/**
 * ~ IRQInstall
 * ! Installs an IRQ handler.
 * @ irq IRQ number.
 * @ handler Handler to execute.
 * #
 */
void IRQInstall(int irq, void(*handler)(struct TRegisters *registers))
{
	IRQRoutines[irq] = handler;
}

/**
 * ~ IRQUninstall
 * ! Uninstalls an IRQ handler.
 * @ irq IRQ number.
 * #
 */
void IRQUninstall(int irq)
{
	IRQRoutines[irq] = 0;
}

/**
 * ~ IRQHandler2
 * ! Interface to the custom IRQ handlers.
 * @ registers Interrupt information.
 * #
 */
void IRQHandler2(struct TRegisters *registers)
{
	void (*handler)(struct TRegisters *registers);
  
	handler = IRQRoutines[registers->intNumber];
	if (handler)
	{
		handler(registers);
	}
	else
	{
		if (registers->intNumber > 0x00)
		{
			PrintWarning("IRQHandler2: Received unknown interrupt #");
			PrintStr("%d\n", registers->intNumber);
		}
	}

	if (registers->intNumber >= 0x08)
	{
		OutputByte(0xA0, 0x20);
	}

	OutputByte(0x20, 0x20);
}

/**
 * ~ IRQHandler
 * ! Interface to irqHandler2.
 * @ registers Interrupt information.
 * #
 */
void IRQHandler(struct TRegisters *registers)
{
	IRQHandler2(registers);
}

/**
 * ~ IRQInitialize
 * ! Initializes the IRQ.
 * @
 * #
 */
void IRQInitialize()
{
	OutputByte(0x20, 0x11);
	OutputByte(0xA0, 0x11);
	OutputByte(0x21, 0x40);
	OutputByte(0xA1, 0x48);
	OutputByte(0x21, 0x04);
	OutputByte(0xA1, 0x02);
	OutputByte(0x21, 0x01);
	OutputByte(0xA1, 0x01);
	OutputByte(0x21, 0x00);
	OutputByte(0xA1, 0x00);
}
