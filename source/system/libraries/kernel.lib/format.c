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

// Variables
#include <kernel.lib/format.h>
#include <kernel.lib/strings.h>

/**
 * ~ FormatBackend
 * ! Formats a string.
 * @ format String to format.
 * @ arg Arguments.
 * @ helper Helper function.
 * @ pointer Argument for helper.
 * # Byte count.
 */
int FormatBackend(const char *format, TArgList arg, TFormatHelper helper,
	void *pointer)
{
	unsigned state, flags, radix, actualWd, count, givenWd;
	char *where, buffer[DF_BUFLEN];
	long num;

	state = flags = count = givenWd = 0;
	for ( ; *format; format++)
	{
		switch (state)
		{
		case 0:
			if (*format != '%')
			{
				helper(*format, &pointer);
				count++;
				break;
			}

			state++;
			format++;
		case 1:
			if (*format == '%')
			{
				helper(*format, &pointer);
				count++;
				state = flags = givenWd = 0;
				break;
			}

			if (*format == '-')
			{
				if (flags & DF_LJ)
				{
					state = flags = givenWd = 0;
				}
				else
				{
					flags |= DF_LJ;
				}
				break;
			}

			state++;

			if (*format == '0')
			{
				flags |= DF_LZ;
				format++;
			}
		case 2:
			if (*format >= '0' && *format <= '9')
			{
				givenWd = 10 * givenWd + (*format - '0');
				break;
			}

			state++;
		case 3:
			if (*format == 'F')
			{
				flags |= DF_FP;
				break;
			}

			if (*format == 'N')
			{
				break;
			}

			if (*format == 'l')
			{
				flags |= DF_32;
				break;
			}

			if (*format == 'h')
			{
				flags |= DF_16;
				break;
			}

			state++;
		case 4:
			where = buffer + DF_BUFLEN - 1;
			*where = '\0';

			switch (*format)
			{
			case 'X':
				flags |= DF_CA;
			case 'x':
			case 'p':
			case 'n':
				radix = 16;
				goto DO_NUM;
			case 'd':
			case 'i':
				flags |= DF_SG;
			case 'u':
				radix = 10;
				goto DO_NUM;
			case 'o':
				radix = 8;
				DO_NUM:
				if (flags & DF_32)
				{
					num = argInsert(arg, unsigned long);
				}
				else if (flags & DF_16)
				{
					if (flags & DF_SG)
					{
						num = argInsert(arg, short);
					}
					else
					{
						num = argInsert(arg, unsigned short);
					}
				}
				else
				{
					if (flags & DF_SG)
					{
						num = argInsert(arg, int);
					}
					else
					{
						num = argInsert(arg, unsigned int);
					}
				}

				if (flags & DF_SG)
				{
					if (num < 0)
					{
						flags |= DF_WS;
						num = -num;
					}
				}

				do
				{
					unsigned long temp;

					temp = (unsigned long)num % radix;
					where--;

					if (temp < 10)
					{
						*where = temp + '0';
					}
					else if (flags & DF_CA)
					{
						*where = temp - 10 + 'A';
					}
					else
					{
						*where = temp - 10 + 'a';
					}

					num = (unsigned long)num / radix;
				}

				while (num != 0);
				goto EMIT;
			case 'c':
				flags &= ~DF_LZ;
				where--;
				*where = (char)argInsert(arg, char);
				actualWd = 1;
				goto EMIT2;
			case 's':
				flags &= ~DF_LZ;
				where = argInsert(arg, char *);
				EMIT:
				actualWd = StringSize(where);

				if (flags & DF_WS)
				{
					actualWd++;
				}

				if ((flags & (DF_WS | DF_LZ)) == (DF_WS | DF_LZ))
				{
					helper('-', &pointer);
					count++;
				}
				EMIT2:
				if ((flags & DF_LJ) == 0)
				{
					while (givenWd > actualWd)
					{
						helper(flags & DF_LZ ? '0' : ' ', &pointer);
						count++;
						givenWd--;
					}
				}

				if ((flags & (DF_WS | DF_LZ)) == DF_WS)
				{
					helper('-', &pointer);
					count++;
				}

				while (*where != '\0')
				{
					helper(*where++, &pointer);
					count++;
				}

				if (givenWd < actualWd)
				{
					givenWd = 0;
				}
				else
				{
					givenWd -= actualWd;
				}

				for ( ; givenWd; givenWd--)
				{
					helper(' ', &pointer);
					count++;
				}
				break;
			default:
				break;
			}
		default:
			state = flags = givenWd = 0;
			break;
		}
	}

	return count;
}

/**
 * ~ FormatVH
 * ! Helper function for FormatV.
 * @ chr Character to handle.
 * @ pointer Destination.
 * # 0
 */
int FormatVH(unsigned chr, void **pointer)
{
	char *dest;

	dest = *pointer;
	*dest++ = (char)chr;
	*pointer = dest;

	return 0;
}

/**
 * ~ FormatV
 * ! Helper function for Format.
 * @ buffer Buffer to output to.
 * @ format String to format.
 * @ arg Argument to format with.
 * # Byte count.
 */
int FormatV(char *buffer, const char *format, TArgList arg)
{
	int returnValue;

	returnValue = FormatBackend(format, arg, FormatVH, (void *)buffer);
	buffer[returnValue] = '\0';

	return returnValue;
}

/**
 * ~ Format
 * ! Formats a string.
 * @ buffer Buffer to output to.
 * @ format String to format.
 * @ ... Arguments.
 * # Byte count.
 */
int Format(char *buffer, const char *format, ...)
{
	TArgList arg;
	int returnValue;

	argStart(arg, format);
	returnValue = FormatV(buffer, format, arg);
	argStop(arg);

	return returnValue;
}
