avr-mt128-lib
=============

A small library for the avr-mt128 from Olimex. The main purpose is for me to
play around with this development board.

The library is almost doing nothing for now. There is a linker script and the
associated initialization code. This code set the interrupt vector, clear SREG,
set the stack pointer, clear the BSS segment in the ram and copy the data
segment in the ram.
