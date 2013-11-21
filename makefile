all: 
	avr-gcc -nostartfiles -Tinit.ld -Wall -gdwarf-2 -O0 -mmcu=atmega128 init.c test.c -o test.elf
	avr-objcopy -O ihex -R .eeprom test.elf test.hex

burn:
	sudo avarice -1 -j /dev/ttyUSB0 -e -P atmega128 -f test.hex
