#ifndef DISPLAY_H
#include <avr/io.h>
#define DISPLAY_H
/**
   These should be the things controlling what ports are being used for which parts of the display.
   @NOTE This will make 'portability' easier and make this more like a real library.
   
   Each segement and digit should be set in order e.g. segment A should be PC0 if you're using PORTC
**/

#define DIGIT_PORT  PORTC
#define SEGMENT_PORT PORTB
#define BUTTON_INC PD2
#define BUTTON_DEC PD3
#define BUTTON_PIN PIND


/* displays the hexadecimal value on 7 segement display
   @param hex value for character or number, digit on a multi-digit display to show the character on,*/
void display_hex(int hex, int digit);

/*Pretty much the same as hex_char but this returns an number 
  instead of a char/string  */
int num_to_hex(uint16_t num);

unsigned int count(unsigned int);



/* prints only numbers to the 7 segement display */
void print_num(uint16_t num);

/* Simple list of most if not all of the possible character and
   number combinations for a 7segment display */
int hex_char(char in);

/* Simple convenience function to print out a leeter to each digit of the
   display it assumes you're starting at zero on the displays
   @param str including numbers need to be passed as strings as well*/
void _print(char* str);

/* prints out 'Err1' onto 4 digit display */
void err_msg();

/*displays a simple demo on the displays lighting up each digit with its number
  starting from 1-4 */
void demo();


/*Plan to maket his function scroll along the display if
  the string is greater than 4 characters */ 
void scrolling_Print();
#endif
