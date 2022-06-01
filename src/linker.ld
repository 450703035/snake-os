ENTRY(_start64)

SECTIONS
{
	/*
	 * 设置snake-os的加载入口地址为0xffff000000080000
	 *
	 * 这里“.”表示location counter，当前位置
	 */
	. = 0xffff000000080000;
	/*. = 0x80000;*/

	/*
	 * text代码段
	 */
	_text = .;
	.text :
	{
		*(.text)
	}
	_etext = .;

	/*
	 * 只读数据段
	 */
	_rodata = .;
	.rodata :
	{
		*(.rodata)
	}
	_erodata = .;


	/*
	 * 数据段
	 */
	. = ALIGN(16);
	_data = .;
	.data : { *(.data) }
	_edata = .;


	/*
	 * bss段
	 *
	 * ALIGN(8)表示8个字节对齐
	 * bss_begin的起始地址以8字节对齐
	 */
	/* . = ALIGN(0x8); */
	_bss = .;
	.bss : { *(.bss*) } 
	_ebss = .;
	
	/* . = 0xffff0000008A2700;*/
	end = .;
}
