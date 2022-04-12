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

/**
 * ~ MemoryCopy
 * ! Copies memory.
 * @ dest Destination.
 * @ source Source.
 * @ count Count to copy.
 * # A pointer to dest.
 */
void *MemoryCopy(void *dest, const void *source, int count)
{
	const char *pSource = (const char *)source;
	char *pDest = (char *)dest;

	for ( ; count != 0; count--)
	{
		*pDest++ = *pSource++;
	}

	return dest;
}

/**
 * ~ MemorySet
 * ! Sets memory.
 * @ dest Destination.
 * @ value New value.
 * @ count Count to set.
 * # A pointer to dest.
 */
void *MemorySet(void *dest, char value, int count)
{
	char *pDest = (char *)dest;

	for ( ; count != 0; count--)
	{
		*pDest++ = value;
	}

	return dest;
}

/**
 * ~ MemorySetW
 * ! Sets memory (word version).
 * @ dest Destination.
 * @ value New value.
 * @ count Count to set.
 * # A pointer to dest.
 */
unsigned short *MemorySetW(unsigned short *dest, unsigned short value,
	int count)
{
	unsigned short *pDest = (unsigned short *)dest;

	for ( ; count != 0; count--)
	{
		*pDest++ = value;
	}

	return dest;
}
