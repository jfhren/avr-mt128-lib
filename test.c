/**
 * Copyright © 2013 Jean-François Hren <jfhren@gmail.com>
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */

#define PORTA (*((volatile unsigned char*)0x3B))
#define DDRA (*((volatile unsigned char*)0x3A))
#define PINA (*((volatile unsigned char*)0x39))

int main(void) {

    PORTA = 0;
    DDRA = 0b01000000;
    PORTA = 0b01000000;

    return 0;

}
