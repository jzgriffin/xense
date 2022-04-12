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
#include <kernel.lib/strings.h>

/**
 * ~ StringSize
 * ! Gets the size/length of a string.
 * @ str String to evaluate the size of.
 * # The string size.
 */
int StringSize(const char *str)
{
	int size;

	for (size = 0; *str != '\0'; size++, str++);

	return size;
}

/**
 * ~ Compare
 * ! Compares two strings.
 * @ str String to compare with str2.
 * @ str2 String to compare with str.
 * # 0 if the strings are the same, elsewise if they aren't.
 */
int Compare(const char *str, const char *str2) {
	if (StringSize(str) != StringSize(str2)) {
		return StringSize(str) - StringSize(str2);
	}

	for ( ; *str && *str2; ++str, ++str2)
	{
		if (*str != *str2)
		{
			return *str - *str2;
		}
	}

	return 0;
}
