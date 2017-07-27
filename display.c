#include "display.h"
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
//#include <string.h>
#define BV(bit) (1 << (bit)) 
#define PORToff(PORT) (PORT = 0x00)
#define PORTon(PORT) (PORT = 0xff)


void display_hex(int hex,int digit){
  _delay_ms(5);
  PORTC = ~BV(digit);
  PORTD = hex;
}



int num_to_hex(uint16_t num){


  switch (num) {

  case 0:
    return 0x3f;
    break;

  case 1:
    return  0x06;
    break;

  case 2:
     return 0x5B;
     break;

  case 3:
     return  0x4F;
     break;

  case 4:
     return 0x66;
     break;

  case 5:
     return 0x6D;
     break;

  case 6:
     return 0x7D;
     break;

  case 7:
     return 0x07;
     break;

  case 8:
     return 0x7F;
     break;

  case 9:
     return 0x6F;
     break;

  default: 

     return 0x00;

 
  }
}

unsigned int count(unsigned int i){
  unsigned int counted =1;
  while (i/=10) {
    counted++;
  }
  return counted;
}


void print_num(uint16_t num ){

  volatile  int display[4];
  unsigned digit = count(num);

  while (digit--) {

    display[digit]= num%10;
    num/=10;

  }

  int i;
  for ( i=0; i<4; ++i) {
    display_hex(num_to_hex(display[i]), i);
    
    
  }
}


int hex_char(char in){

  switch(in){
 
  case 'a':
  case 'A':
    return 0x77;

  case 'B':  
  case 'b':
    return 0x7C;

  case 'c':
  case 'C':
    return 0x39;

  case 'D':
  case 'd':
    return 0x5E;

  case 'e':
  case 'E':
    return 0x79;

  case 'f':
  case 'F':
    return 0x71;

  case 'g':
  case 'G':
    return 0x3D;

  case 'h':
  case 'H':
    return 0x76;

  case 'N':
  case 'n':
    return 0x54;

  case 'O':
  case 'o':
    return 0x5C;
  case 'p':
  case 'P':
    return 0x73;

  case 'R':
  case 'r':
    return 0x50;

  case 'y':
  case 'Y':
    return 0x6E;

  case '0':
    return 0x3F;
    
  case '1':
    return  0x06;

  case '2':
    return 0x5B;

  case '3':
    return 0x4F;

  case '4':
    return 0x66;

  case '5':
    return 0x6D;

  case '6':
    return 0x7D;

  case '7':
    return 0x07;

  case '8':
    return 0x7F;

  case '9':
    return 0x6F;

  default:
    return 0;
    
  }
    
}

void _print(char* str){

  int len = strlen(str);
  int i;
  for (i=0; i<len; i++) {
    display_hex(hex_char(str[i]),i);
  }
}
 
void err_msg(){
  _print("err");
}

void demo(){
  int i;
  for ( i = 1; i <=3 ; i++) {
    display_hex(hex_char(i+1),i);
    _delay_ms(1000);
  }
}


  

