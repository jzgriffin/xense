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

#ifndef __KERNEL_LIB_FORMAT_H__
#define __KERNEL_LIB_FORMAT_H__

// Includes
#include <kernel.lib/argument.h>

// Definitions
#define DF_LJ 0x01
#define DF_CA 0x02
#define DF_SG 0x04
#define DF_32 0x08
#define DF_16 0x10
#define DF_WS 0x20
#define DF_LZ 0x40
#define DF_FP 0x80
#define DF_BUFLEN 16

// Typedefs
typedef int (*TFormatHelper)(unsigned chr, void** helper);

// Routines
extern int FormatBackend(const char* format, TArgList arg, TFormatHelper helper, void* pointer);
extern int FormatVH(unsigned chr, void** pointer);
extern int FormatV(char* buffer, const char* format, TArgList arg);
extern int Format(char* buffer, const char* format, ...);

#endif // __KERNEL_LIB_FORMAT_H__
