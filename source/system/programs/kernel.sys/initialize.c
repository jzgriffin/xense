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
#include <kernel.lib/floppy.h>
#include <kernel.lib/format.h>
#include <kernel.lib/input.h>
#include <kernel.lib/strings.h>
#include <kernel.lib/screen.h>
#include <kernel.sys/gdt.h>
#include <kernel.sys/idt.h>
#include <kernel.sys/irq.h>
#include <kernel.sys/initialize.h>
#include <kernel.sys/keyboard.h>
#include <kernel.sys/timer.h>

/**
 * ~ About
 * ! Shows an about screen.
 * @
 * #
 */
void About()
{
	ScreenSetColor(COLOR_LGREEN, COLOR_BLACK);
	PrintStr("Xense ");
	ScreenSetColor(COLOR_LCYAN, COLOR_BLACK);
	PrintStr(VERSION);
	ScreenSetColor(COLOR_LGREY, COLOR_BLACK);
	PrintStr("\nBuilt on ");
	ScreenSetColor(COLOR_LBLUE, COLOR_BLACK);
	PrintStr(BUILT);
	ScreenSetColor(COLOR_LGREY, COLOR_BLACK);
	PrintStr("\n(C) 2007-2022 Jeremiah Griffin\n\n");
}

/**
 * ~ Initialize
 * ! C kernel entry point.
 * @ bootInfo Multiboot information.
 * #
 */
void Initialize(TBootInfo *bootInfo)
{
	ScreenInitialize();
	About();

	PrintStr("Booting with %dmB memory\n", bootInfo->memUpper / 1024);
	
	PrintInfo("Initializing the GDT...");
	GDTInitialize();
	PrintStr("done.\n");
	
	PrintInfo("Initializing the IDT...");
	IDTInitialize();
	PrintStr("done.\n");
	
	PrintInfo("Initializing the IRQ...");
	IRQInitialize();
	PrintStr("done.\n");
	
	PrintInfo("Initializing the timer...");
	TimerInitialize();
	PrintStr("done.\n");

	PrintInfo("Initializing the keyboard...");
	KeyboardInitialize();
	PrintStr("done.\n");

	PrintInfo("Initializing the floppy drive...");
	FloppyInitialize();
	PrintStr("done.\n");

	PrintInfo("Enabling interrupts...");
	Sti();
	PrintStr("done.\n\n");

	PrintStr("Type \"help\" for a list of commands\n");
	char buffer[1024];
	for (; ; )
	{
		PrintStr("$ ");
		GetStr(buffer, 1024);

		if (Compare(buffer, "reboot") == 0)
		{
			PrintStr("Thank you for using Xense, the system will now reboot.\n");
			Reboot();
		}
		else if (Compare(buffer, "clear") == 0)
		{
			ClearScreen();
		}
		else if (Compare(buffer, "about") == 0)
		{
			About();
		}
		else if (Compare(buffer, "memory") == 0)
		{
			PrintStr("%dkB (%dmB) upper memory\n", bootInfo->memUpper, bootInfo->memUpper / 1024);
			PrintStr("%dkB (%dmB) lower memory\n", bootInfo->memLower, bootInfo->memLower / 1024);
		}
		else if (Compare(buffer, "bootinfo") == 0)
		{
			PrintStr("Flags: %s\n", bootInfo->flags);
			PrintStr("Upper memory: %dkB (%dmB)\n", bootInfo->memUpper, bootInfo->memUpper / 1024);
			PrintStr("Lower memory: %dkB (%dmB)\n", bootInfo->memLower, bootInfo->memLower / 1024);
			PrintStr("Boot device: %d\n", bootInfo->device);
			PrintStr("Command: %s\n", bootInfo->command);
			PrintStr("Module count: %d\n", bootInfo->moduleCount);
			PrintStr("Module address: %08X\n", bootInfo->moduleAddr);
		}
		else if (Compare(buffer, "floppyinfo") == 0)
		{
			PrintStr("Bytes per sector: %d\n", FloppyDisk.bps);
			PrintStr("Sectors per track: %d\n", FloppyDisk.spt);
			int result[2];
			FloppyType(result);
			PrintStr("Floppy #1 type: %s\n", FloppyTypes[result[0]]);
			PrintStr("Floppy #2 type: %s\n", FloppyTypes[result[1]]);
		}
		else if (Compare(buffer, "uptime") == 0)
		{
			PrintStr("System uptime (in seconds): %d\n", SystemUptime());
		}
		else if (Compare(buffer, "ticks") == 0)
		{
			PrintStr("System uptime (in ticks): %d\n", SystemTicks());
		}
		else if (Compare(buffer, "help") == 0)
		{
			PrintStr("Commands:\n");
			PrintStr("\treboot\t\tReboots the system\n");
			PrintStr("\tabout\t\tDisplays the about message again\n");
			PrintStr("\tclear\t\tClears the screen\n");
			PrintStr("\tmemory\t\tDisplays the amount of available memory\n");
			PrintStr("\tbootinfo\t\tPrints multiboot information\n");
			PrintStr("\tfloppyinfo\t\tPrints information about the floppy disk\n");
			PrintStr("\tuptime\t\tPrints the system uptime, in seconds\n");
			PrintStr("\tticks\t\tPrints the system uptime, in ticks\n");
		}
		else if (Compare(buffer, "console") == 0)
		{
			//
		}
		else if (Compare(buffer, "console2") == 0)
		{
			//
		}
		else
		{
			PrintStr("Unknown command %s\n", buffer);
		}
	}

	for (; ; );
}
