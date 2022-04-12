; Copyright 2007-2022 Jeremiah Griffin
;
; Permission to use, copy, modify, and/or distribute this software for any
; purpose with or without fee is hereby granted, provided that the above
; copyright notice and this permission notice appear in all copies.
;
; THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
; REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
; AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
; INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
; LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
; OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
; PERFORMANCE OF THIS SOFTWARE.

; Kernel startup code.

	bits	32
	global	Start

Start:
	mov		esp, Stack
	jmp		Start2

	align	4
Multiboot:
	MULTIBOOT_PAGE_ALIGN	equ 1 << 0
	MULTIBOOT_MEMORY_INFO	equ 1 << 1
	MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
	MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
	MULTIBOOT_CHECKSUM		equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
	extern	code, bss, end
	dd		MULTIBOOT_HEADER_MAGIC
	dd		MULTIBOOT_HEADER_FLAGS
	dd		MULTIBOOT_CHECKSUM
	dd		Multiboot
	dd		code
	dd		bss
	dd		end
	dd		Start

Start2:
	mov		ebp, 0
	extern	Initialize
	push	ebx
	call	Initialize
	jmp		$

	global	GDTFlush
	extern	GDTPointer

GDTFlush:
	lgdt	[GDTPointer]
	mov		ax, 0x10
	mov		ds, ax
	mov		es, ax
	mov		fs, ax
	mov		gs, ax
	jmp		0x08:GDTFlush2

GDTFlush2:
	ret

	global	IDTLoad
	extern	IDTPointer

IDTLoad:
	lidt	[IDTPointer]
	ret

	global	ISR00
	global	ISR01
	global	ISR02
	global	ISR03
	global	ISR04
	global	ISR05
	global	ISR06
	global	ISR07
	global	ISR08
	global	ISR09
	global	ISR0A
	global	ISR0B
	global	ISR0C
	global	ISR0D
	global	ISR0E
	global	ISR0F
	global	ISR10
	global	ISR11
	global	ISR12
	global	ISR13
	global	ISR14
	global	ISR15
	global	ISR16
	global	ISR17
	global	ISR18
	global	ISR19
	global	ISR1A
	global	ISR1B
	global	ISR1C
	global	ISR1D
	global	ISR1E
	global	ISR1F
	global	ISR20
	global	ISR21
	global	ISR22
	global	ISR23
	global	ISR24
	global	ISR25
	global	ISR26
	global	ISR27
	global	ISR28
	global	ISR29
	global	ISR2A
	global	ISR2B
	global	ISR2C
	global	ISR2D
	global	ISR2E
	global	ISR2F
	global	ISR30
	global	ISR31
	global	ISR32
	global	ISR33
	global	ISR34
	global	ISR35
	global	ISR36
	global	ISR37
	global	ISR38
	global	ISR39
	global	ISR3A
	global	ISR3B
	global	ISR3C
	global	ISR3D
	global	ISR3E
	global	ISR3F

ISR00:
	cli
	push	byte 0
	push	byte 0
	jmp		ISRCommon

ISR01:
	cli
	push	byte 0
	push	byte 1
	jmp		ISRCommon

ISR02:
	cli
	push	byte 0
	push	byte 2
	jmp		ISRCommon

ISR03:
	cli
	push	byte 0
	push	byte 3
	jmp		ISRCommon

ISR04:
	cli
	push	byte 0
	push	byte 4
	jmp		ISRCommon

ISR05:
	cli
	push	byte 0
	push	byte 5
	jmp		ISRCommon

ISR06:
	cli
	push	byte 0
	push	byte 6
	jmp		ISRCommon

ISR07:
	cli
	push	byte 0
	push	byte 7
	jmp		ISRCommon

ISR08:
	cli
	push	byte 8
	jmp		ISRCommon

ISR09:
	cli
	push	byte 0
	push	byte 9
	jmp		ISRCommon

ISR0A:
	cli
	push	byte 10
	jmp		ISRCommon

ISR0B:
	cli
	push	byte 11
	jmp		ISRCommon

ISR0C:
	cli
	push	byte 12
	jmp		ISRCommon

ISR0D:
	cli
	push	byte 13
	jmp		ISRCommon

ISR0E:
	cli
	push	byte 14
	jmp		ISRCommon

ISR0F:
	cli
	push	byte 0
	push	byte 15
	jmp		ISRCommon

ISR10:
	cli
	push	byte 0
	push	byte 16
	jmp		ISRCommon

ISR11:
	cli
	push	byte 0
	push	byte 17
	jmp		ISRCommon

ISR12:
	cli
	push	byte 0
	push	byte 18
	jmp		ISRCommon

ISR13:
	cli
	push	byte 0
	push	byte 19
	jmp		ISRCommon

ISR14:
	cli
	push	byte 0
	push	byte 20
	jmp		ISRCommon

ISR15:
	cli
	push	byte 0
	push	byte 21
	jmp		ISRCommon

ISR16:
	cli
	push	byte 0
	push	byte 22
	jmp		ISRCommon

ISR17:
	cli
	push	byte 0
	push	byte 23
	jmp		ISRCommon

ISR18:
	cli
	push	byte 0
	push	byte 24
	jmp		ISRCommon

ISR19:
	cli
	push	byte 0
	push	byte 25
	jmp		ISRCommon

ISR1A:
	cli
	push	byte 0
	push	byte 26
	jmp		ISRCommon

ISR1B:
	cli
	push	byte 0
	push	byte 27
	jmp		ISRCommon

ISR1C:
	cli
	push	byte 0
	push	byte 28
	jmp		ISRCommon

ISR1D:
	cli
	push	byte 0
	push	byte 29
	jmp		ISRCommon

ISR1E:
	cli
	push	byte 0
	push	byte 30
	jmp		ISRCommon

ISR1F:
	cli
	push	byte 0
	push	byte 31
	jmp		ISRCommon
	
ISR20:
	cli
	push	byte 0
	push	byte 32
	jmp		ISRCommon
	
ISR21:
	cli
	push	byte 0
	push	byte 33
	jmp		ISRCommon
	
ISR22:
	cli
	push	byte 0
	push	byte 34
	jmp		ISRCommon
	
ISR23:
	cli
	push	byte 0
	push	byte 35
	jmp		ISRCommon
	
ISR24:
	cli
	push	byte 0
	push	byte 36
	jmp		ISRCommon

ISR25:
	cli
	push	byte 0
	push	byte 37
	jmp		ISRCommon

ISR26:
	cli
	push	byte 0
	push	byte 38
	jmp		ISRCommon
	
ISR27:
	cli
	push	byte 0
	push	byte 39
	jmp		ISRCommon
	
ISR28:
	cli
	push	byte 0
	push	byte 40
	jmp		ISRCommon

ISR29:
	cli
	push	byte 0
	push	byte 41
	jmp		ISRCommon

ISR2A:
	cli
	push	byte 0
	push	byte 42
	jmp		ISRCommon
	
ISR2B:
	cli
	push	byte 0
	push	byte 43
	jmp		ISRCommon
	
ISR2C:
	cli
	push	byte 0
	push	byte 44
	jmp		ISRCommon
	
ISR2D:
	cli
	push	byte 0
	push	byte 45
	jmp		ISRCommon
	
ISR2E:
	cli
	push	byte 0
	push	byte 46
	jmp		ISRCommon
	
ISR2F:
	cli
	push	byte 0
	push	byte 47
	jmp		ISRCommon

ISR30:
	cli
	push	byte 0
	push	byte 48
	jmp		ISRCommon
	
ISR31:
	cli
	push	byte 0
	push	byte 49
	jmp		ISRCommon
	
ISR32:
	cli
	push	byte 0
	push	byte 50
	jmp		ISRCommon
	
ISR33:
	cli
	push	byte 0
	push	byte 51
	jmp		ISRCommon

ISR34:
	cli
	push	byte 0
	push	byte 52
	jmp		ISRCommon
	
ISR35:
	cli
	push	byte 0
	push	byte 53
	jmp		ISRCommon
	
ISR36:
	cli
	push	byte 0
	push	byte 54
	jmp		ISRCommon
	
ISR37:
	cli
	push	byte 0
	push	byte 55
	jmp		ISRCommon

ISR38:
	cli
	push	byte 0
	push	byte 56
	jmp		ISRCommon
	
ISR39:
	cli
	push	byte 0
	push	byte 57
	jmp		ISRCommon
	
ISR3A:
	cli
	push	byte 0
	push	byte 58
	jmp		ISRCommon
	
ISR3B:
	cli
	push	byte 0
	push	byte 59
	jmp		ISRCommon

ISR3C:
	cli
	push	byte 0
	push	byte 60
	jmp		ISRCommon
	
ISR3D:
	cli
	push	byte 0
	push	byte 61
	jmp		ISRCommon
	
ISR3E:
	cli
	push	byte 0
	push	byte 62
	jmp		ISRCommon
	
ISR3F:
	cli
	push	byte 0
	push	byte 63
	jmp		ISRCommon

	extern	Fault

ISRCommon:
	pusha
	push	ds
	push	es
	push	fs
	push	gs
	mov		ax, 0x10
	mov		ds, ax
	mov		es, ax
	mov		fs, ax
	mov		gs, ax
	mov		eax, esp
	push	eax
	mov		eax, Fault
	call	eax
	pop		eax
	pop		gs
	pop		fs
	pop		es
	pop		ds
	popa
	add		esp, 8
	iret

	global	IRQ00
	global	IRQ01
	global	IRQ02
	global	IRQ03
	global	IRQ04
	global	IRQ05
	global	IRQ06
	global	IRQ07
	global	IRQ08
	global	IRQ09
	global	IRQ0A
	global	IRQ0B
	global	IRQ0C
	global	IRQ0D
	global	IRQ0E
	global	IRQ0F

IRQ00:
	cli
	push	byte 0
	push	byte 0
	jmp		IRQCommon

IRQ01:
	cli
	push	byte 0
	push	byte 1
	jmp		IRQCommon

IRQ02:
	cli
	push	byte 0
	push	byte 2
	jmp		IRQCommon

IRQ03:
	cli
	push	byte 0
	push	byte 3
	jmp		IRQCommon

IRQ04:
	cli
	push	byte 0
	push	byte 4
	jmp		IRQCommon

IRQ05:
	cli
	push	byte 0
	push	byte 5
	jmp		IRQCommon

IRQ06:
	cli
	push	byte 0
	push	byte 6
	jmp		IRQCommon

IRQ07:
	cli
	push	byte 0
	push	byte 7
	jmp		IRQCommon

IRQ08:
	cli
	push	byte 0
	push	byte 8
	jmp		IRQCommon

IRQ09:
	cli
	push	byte 0
	push	byte 9
	jmp		IRQCommon

IRQ0A:
	cli
	push	byte 0
	push	byte 0Ah
	jmp		IRQCommon

IRQ0B:
	cli
	push	byte 0
	push	byte 0Bh
	jmp		IRQCommon

IRQ0C:
	cli
	push	byte 0
	push	byte 0Ch
	jmp		IRQCommon

IRQ0D:
	cli
	push	byte 0
	push	byte 0Dh
	jmp		IRQCommon

IRQ0E:
	cli
	push	byte 0
	push	byte 0Eh
	jmp		IRQCommon

IRQ0F:
	cli
	push	byte 0
	push	byte 0Fh
	jmp		IRQCommon

	extern	IRQHandler2

IRQCommon:
	pusha
	push	ds
	push	es
	push	fs
	push	gs
	mov		ax, 0x10
	mov		ds, ax
	mov		es, ax
	mov		fs, ax
	mov		gs, ax
	mov		eax, esp
	push	eax
	mov		eax, IRQHandler2
	call	eax
	pop		eax
	pop		gs
	pop		fs
	pop		es
	pop		ds
	popa
	add		esp, 8
	iret

	section	.bss
	resb	8192
Stack:
