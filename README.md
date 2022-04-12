# Xense

This is a small operating system kernel that I was building during the
winter of 2007-2008.  The kernel is written for the i686 architecture in
the C programming language.  At the time of import, it implements the
following functions:

  - Multiboot header
  - Global Descriptor Table (GDT)
  - Interrupt Descriptor Table (IDT)
  - Interrupt Service Routine (ISR)
    - Interrupt Request (IRQ)
  - Character-based video
    - Monochrome or color
    - Cursor
    - Scrolling
  - Programmable Interrupt Timer (IRQ0)
    - Tick-based sleep
  - Keyboard (IRQ1)
  - Floppy disk parameter retrieval
  - printf-style formatting
  - Command-line interface
    - Commands: reboot, about, clear, memory, bootinfo, floppyinfo,
      uptime, ticks, help

# Objectives

The objectives of this project, beyond archiving some of my old code,
are to:

  - Refactor to improve code quality
  - Implement virtual memory
  - Implement preemptive multitasking

Optional objectives, or stretch goals, are to:

  - Implement a hard disk driver (AHCI)
  - Implement a file system (Ext2)
  - Implement executable loading (ELF)

# License

> Copyright 2007-2022 Jeremiah Griffin
>
> Permission to use, copy, modify, and/or distribute this software for
> any purpose with or without fee is hereby granted, provided that the
> above copyright notice and this permission notice appear in all
> copies.
>
> THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
> WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
> WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
> AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
> DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
> PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
> TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
> PERFORMANCE OF THIS SOFTWARE.
