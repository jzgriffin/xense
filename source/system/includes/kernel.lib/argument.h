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

#ifndef __KERNEL_LIB_ARGUMENT_H__
#define __KERNEL_LIB_ARGUMENT_H__

// Typedefs
typedef unsigned char* TArgList;

// Definitions
#define argSize(type) ((sizeof(type) + sizeof(int) - 1) & ~(sizeof(int) - 1))
#define argStart(arg, arg2) (arg = ((TArgList) & (arg2) + argSize(arg2)))
#define argStop(arg)
#define argInsert(arg, type) (arg += argSize(type), *((type*)(arg - argSize(type))))

#endif // !__KERNEL_LIB_ARGUMENT_H__
