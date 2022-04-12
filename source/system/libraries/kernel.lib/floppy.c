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
#include <kernel.lib/hardware.h>
#include <kernel.lib/memory.h>
#include <kernel.lib/screen.h>
#include <kernel.sys/irq.h>
#include <kernel.sys/timer.h>

// Variables
const char *FloppyTypes[8] = {
	"None",
	"360kB 5.25\"",
	"1.2mB 5.25\"",
	"720kB 3.5\"",
	"1.44mB 3.5\"",
	"2.88mB 3.5\"",
	"Unknown",
	"Unknown"
};
TFloppyParams FloppyDisk;

/**
 * ~ FloppyType
 * ! Gets the floppy drive type.
 * @ result Integer array to store the result in.
 * #
 */
void FloppyType(int *result)
{
	OutputByte(0x70, 0x10);

	unsigned drives = InputByte(0x71);

	result[0] = drives >> 4; // Drive one
	result[1] = drives & 0xF; // Drive two
}

/**
 * ~ FloppyInitialize
 * ! Fills in the FloppyDisk parameter structure.
 * @
 * #
 */
void FloppyInitialize()
{
	MemoryCopy(&FloppyDisk, (unsigned char *)DISK_PARAMETER_ADDRESS,
		sizeof(TFloppyParams)
	);

	if (FloppyTypes[0][0] != 'N') { }
}
