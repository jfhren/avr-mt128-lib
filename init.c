/**
 * Copyright © 2013 Jean-François Hren <jfhren@gmail.com>
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */

/**
 * Define the interrupt vector which will be placed at the begining of the
 * flash. Each component of the interrupt vector is a jump to the interrupt
 * service routine.The first interrupt is a jump to the _reset fonction.
 */
asm(
    ".section .interrupt_vector, \"x\", @progbits ;\n"
    "jmp _reset                                   ;\n"
    "jmp _int0                                    ;\n"
    "jmp _int1                                    ;\n"
    "jmp _int2                                    ;\n"
    "jmp _int3                                    ;\n"
    "jmp _int4                                    ;\n"
    "jmp _int5                                    ;\n"
    "jmp _int6                                    ;\n"
    "jmp _int7                                    ;\n"
    "jmp _timer2_comp                             ;\n"
    "jmp _timer2_ovf                              ;\n"
    "jmp _timer1_capt                             ;\n"
    "jmp _timer1_compa                            ;\n"
    "jmp _timer1_compb                            ;\n"
    "jmp _timer1_ovf                              ;\n"
    "jmp _timer0_comp                             ;\n"
    "jmp _timer0_ovf                              ;\n"
    "jmp _spi_stc                                 ;\n"
    "jmp _usart0_rx                               ;\n"
    "jmp _usart0_udre                             ;\n"
    "jmp _usart0_tx                               ;\n"
    "jmp _adc                                     ;\n"
    "jmp _ee_ready                                ;\n"
    "jmp _analog_comp                             ;\n"
    "jmp _timer1_compc                            ;\n"
    "jmp _timer3_capt                             ;\n"
    "jmp _timer3_compa                            ;\n"
    "jmp _timer3_compb                            ;\n"
    "jmp _timer3_compc                            ;\n"
    "jmp _timer3_ovf                              ;\n"
    "jmp _usart1_rx                               ;\n"
    "jmp _usart1_udre                             ;\n"
    "jmp _usart1_tx                               ;\n"
    "jmp _twi                                     ;\n"
    "jmp _spm_ready                               ;\n"
    );


/**
 * These 5 variables will be defined by ld when linking.
 */
extern char _text_end;
extern char _bss_start;
extern char _bss_end;
extern char _data_start;
extern char _data_end;


/**
 * Default interrupt service routine doing nothing appart returnng from itself.
 */
__attribute__((naked,used)) void _default_handler(void) {
    asm("reti");
}


/**
 * Defining a weak aliasing between each interrupt and the _defaut_handler.
 */
__attribute__((weak, alias("_default_handler"))) void _int0(void);
__attribute__((weak, alias("_default_handler"))) void _int1(void);
__attribute__((weak, alias("_default_handler"))) void _int2(void);
__attribute__((weak, alias("_default_handler"))) void _int3(void);
__attribute__((weak, alias("_default_handler"))) void _int4(void);
__attribute__((weak, alias("_default_handler"))) void _int5(void);
__attribute__((weak, alias("_default_handler"))) void _int6(void);
__attribute__((weak, alias("_default_handler"))) void _int7(void);
__attribute__((weak, alias("_default_handler"))) void _timer2_comp(void);
__attribute__((weak, alias("_default_handler"))) void _timer2_ovf(void);
__attribute__((weak, alias("_default_handler"))) void _timer1_capt(void);
__attribute__((weak, alias("_default_handler"))) void _timer1_compa(void);
__attribute__((weak, alias("_default_handler"))) void _timer1_compb(void);
__attribute__((weak, alias("_default_handler"))) void _timer1_ovf(void);
__attribute__((weak, alias("_default_handler"))) void _timer0_comp(void);
__attribute__((weak, alias("_default_handler"))) void _timer0_ovf(void);
__attribute__((weak, alias("_default_handler"))) void _spi_stc(void);
__attribute__((weak, alias("_default_handler"))) void _usart0_rx(void);
__attribute__((weak, alias("_default_handler"))) void _usart0_udre(void);
__attribute__((weak, alias("_default_handler"))) void _usart0_tx(void);
__attribute__((weak, alias("_default_handler"))) void _adc(void);
__attribute__((weak, alias("_default_handler"))) void _ee_ready(void);
__attribute__((weak, alias("_default_handler"))) void _analog_comp(void);
__attribute__((weak, alias("_default_handler"))) void _timer1_compc(void);
__attribute__((weak, alias("_default_handler"))) void _timer3_capt(void);
__attribute__((weak, alias("_default_handler"))) void _timer3_compa(void);
__attribute__((weak, alias("_default_handler"))) void _timer3_compb(void);
__attribute__((weak, alias("_default_handler"))) void _timer3_compc(void);
__attribute__((weak, alias("_default_handler"))) void _timer3_ovf(void);
__attribute__((weak, alias("_default_handler"))) void _usart1_rx(void);
__attribute__((weak, alias("_default_handler"))) void _usart1_udre(void);
__attribute__((weak, alias("_default_handler"))) void _usart1_tx(void);
__attribute__((weak, alias("_default_handler"))) void _twi(void);
__attribute__((weak, alias("_default_handler"))) void _spm_ready(void);


/**
 * main course comes later.
 */
extern int main(void);

/**
 * Called when resetting. Clear SREG, set up the stack pointer, clearing the BSS
 * and copying the data segment to ram.
 */
__attribute__((naked, used)) void _reset(void) {

    /* Init SREG and the stack */
    asm(
        "ldi r16, 0    ;           \n"
        "out 0x3F, r16 ;SREG <- 0  \n"
        "ldi r16, 0x10 ;           \n"
        "out 0x3E, r16 ;SPH <- 0x10\n"
        "ldi r16, 0xFF ;           \n"
        "out 0x3D, r16 ;SPL <- 0xFF\n"
       );

    /* Init BSS */
    char* dst = &_bss_start;
    while(dst < &_bss_end)
        *dst++ = 0;

    /* Init data */
    char* src = &_text_end;
    dst = &_data_start;
    while(dst < &_data_end)
        *dst++ = *src++;

    main();

    while(1);

}
