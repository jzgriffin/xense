ENTRY(Start)
physical = 0x00100000;

SECTIONS
{
	.text physical : AT(physical)
	{
		code = .;
		*(.text)
		*(.rodata)
		. = ALIGN(4096);
	}
	.data : AT(physical + (data - code))
	{
		data = .;
		*(.data)
		. = ALIGN(4096);
	}
	.bss : AT(physical + (bss - code))
	{
		bss = .;
		*(.bss)
		. = ALIGN(4096);
	}
	end = .;
}
