OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:51)

MEMORY {
    flash (rx) : ORIGIN = 0x0,        LENGTH = 128K
    ram   (rw) : ORIGIN = 0x800100, LENGTH = 4K
}

SECTIONS {
    . = 0 ;

    .text : {
        *(.interrupt_vector) ;
        *(.text*) ;
/* It might no be a good idea to put rodata in rom since lpm takes 3
   cycles when ld takes 2. */
        *(.rodata*) ;
    } > flash
    _text_end = . ;

    . = 0 ;
    .bss (NOLOAD) : {
        _bss_start = . ;
        *(.bss*) ;
    } > ram
    _bss_end = . ;

    .data : {
        _data_start = . ;
        *(.data*) ;
    } > ram AT>flash
    _data_end = . ;

}
