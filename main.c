#include <avr/io.h>
#include <util/delay.h>
#include "display.h"
#define BV(bit) (1 << (bit))
#define setPORT(PORT) (PORT = 0x00)



int main(void)
{

  DDRD = 0xff;//segment control
  DDRC |= 0xff; //digit control

  //@NOTATION for some reason, (still don't know why) segment displays need to be ~ 'not-ed' in order to be turned on
  // So in order to turn on a specific digit, you must not the pin it's connected to. 
  

  while (1) {

    for (int i =1; i <= 4; i++) {
      /* _delay_ms(10); */
      /* PORTD |= 0x7D; */
      /* PORTC = ~BV(1); */
      /* _delay_ms(10); */
      /* PORTD |= 0x5B; */
      /* PORTC = ~BV(2); */
    }

    int hex_1 = hex_num_val(1);

    _delay_ms(1);
    PORTD |= hex_num_val(1);
    PORTC = ~BV(1);
    _delay_ms(1);
    setPORT(PORTD);
    /* PORTD &= 0x00; */
    _delay_ms(1);
    PORTD |= 0x5B;
    PORTC = ~BV(2);
    _delay_ms(1);
    //    PORTD &= 0x00;
    setPORT(PORTD);
  }
				    
  return 0;
}
