#include <alcd.h>
#include <delay.h>
#include <mega16.h>
#include <stdlib.h>

int get_max(int b1, int b2, int b3) {
    int max = b1;
    if (b2 > max) max = b2;
    if (b3 > max) max = b3;
    return max;
}

void main() {
int number = 0;
int max = 0;
int waiting = 0;
int b1=0;
int b2=0;
int b3=0;
int y1,d1, y2,d2, y3,d3; // 7segments yekan & dahgan
unsigned char* n = '';
unsigned char* w = '';
int digit[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};

lcd_init(16);
DDRA = 0xff;
DDRB = 0xff;
DDRC = 0xff;
DDRD = 0x00;
while (1) {    
    if (PIND.0 == 1) {
        delay_ms(20);
        max = get_max(b1, b2, b3);
        number++;        
        lcd_clear();
        lcd_gotoxy(0,0);
        lcd_putsf("number =");
        itoa(number, n);
        lcd_gotoxy(9,0);
        lcd_puts(n);
        
        waiting = number - max;
        lcd_gotoxy(0,1);
        lcd_putsf("waiting =");
        itoa(waiting, w);
        lcd_gotoxy(10,1);
        lcd_puts(w);        
    }    
    if (PIND.5 == 1 && waiting > 0){
        delay_ms(25);            
        b1 = get_max(b1,b2,b3)+1;
        y1 = b1 % 10;
        d1 = b1 / 10;
        waiting--;
    }
    if (PIND.6 == 1 && waiting > 0) {
        delay_ms(25); 
        b2 = get_max(b1,b2,b3)+1;
        y2 = b2 % 10;
        d2 = b2 / 10;
        waiting--;
    }
    if (PIND.7 == 1 && waiting > 0) {
        delay_ms(25);          
        b3 = get_max(b1,b2,b3)+1;
        y3 = b3 % 10;
        d3 = b3 / 10; 
        waiting--;
    }
    
    // b1    
    PORTB = 0x01;
    PORTA = digit[d1];
    delay_ms(1);
    PORTB = 0x02;
    PORTA = digit[y1];
    delay_ms(1); 
    
    // b2    
    PORTB = 0x04;
    PORTA = digit[d2];
    delay_ms(1);
    PORTB = 0x08;
    PORTA = digit[y2];
    delay_ms(1);
    
    // b3
    PORTB = 0x10;
    PORTA = digit[d3];
    delay_ms(1);
    PORTB = 0x20;
    PORTA = digit[y3];
    delay_ms(1);                     
    }
}