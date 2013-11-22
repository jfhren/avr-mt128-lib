/**
 * Copyright © 2013 Jean-François Hren <jfhren@gmail.com>
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */

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
