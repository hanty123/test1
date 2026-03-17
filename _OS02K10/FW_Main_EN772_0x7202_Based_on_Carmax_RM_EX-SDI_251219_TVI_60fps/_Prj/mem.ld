


MEMORY
		{
			boot	: ORIGIN = 0x01000000,					LENGTH = 0x8000
			stack   : ORIGIN = 0x00000000,					LENGTH = (32*1024)

			flash	: ORIGIN = ORIGIN(boot)+LENGTH(boot),	LENGTH = (128*0x1000) - LENGTH(boot) - (4*0x1000)	/* FLS_SIZE - BOOT - USER_SIZE */
			ram     : ORIGIN = 0x00000E70,					LENGTH = LENGTH(stack) - 0xE70 - 0x400 - 0x2000		/* RAM0_SIZE - reset - except_stack(-isr_stack) - minimum_stack */
		}

SECTIONS
{
		.reset :
		{
			__reset_s = ALIGN(4);
		} > flash

		.text :
		{
			*(.text)
			*(.rodata)
			*(.rodata.*)
		} > flash

		.ispm_text : AT ( (LOADADDR (.text) + SIZEOF(.text) + 3) & ~ (4 - 1))
		{
			__ispm_text_s = ALIGN(4);
			*(.ispmtext)
			__ispm_text_e = ALIGN(4);
		} > ram

		__rom_ispm_text_s = LOADADDR(.ispm_text);

		.data : AT ( (LOADADDR(.ispm_text) + SIZEOF(.ispm_text) + 3) & ~ (4-1) )
		{
			__data_s = ALIGN(4);
			*(.data)
			*(.data.rel)
			*(.data.rel.local)
			*(.sdata)
			__data_e = ALIGN(4);
		} > ram

		__rom_data_s = LOADADDR(.data);
		__rom_data_e = ( (LOADADDR(.data) + SIZEOF(.data) + 3) & ~ (4-1) ) - LOADADDR(.reset);

		.bss (NOLOAD) :
		{
			__bss_s = ALIGN(4);
			*(.bss) *(COMMON)
			__bss_e = ALIGN(4);
		} > ram

		__except_stack = ORIGIN(stack) + LENGTH(stack) - 4;
    	__isr_stack    = ORIGIN(stack) + LENGTH(stack) - 4;

		.stack (__isr_stack - 1024) (NOLOAD) :
		{
			__stack = .;
			*(._stack)
		}
}

