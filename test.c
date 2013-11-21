#define PORTA (*((volatile unsigned char*)0x3B))
#define DDRA (*((volatile unsigned char*)0x3A))
#define PINA (*((volatile unsigned char*)0x39))

int main(void) {

    PORTA = 0;
    DDRA = 0b01000000;
    PORTA = 0b01000000;

    return 0;

}
