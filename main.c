#include <avr/eeprom.h>
#include <avr/io.h>
#include <util/delay.h>
#include "display.h"
#include <string.h>
#include <avr/interrupt.h>

/* para e.g. pin = PINB pn = PB0 */




uint16_t prom_read;
volatile uint16_t _count;


/* keep this for future use (just in case...) */
uint8_t debounce(uint16_t pin,uint16_t pn){
  if (!bit_is_clear(pin,pn)) {
    _delay_ms(50); 
    if(!bit_is_clear(pin,pn)){
      _delay_ms(50);
      return (1);
    }
  }
  return (0);
}



ISR(PCINT2_vect){
  prom_read = eeprom_read_word((uint16_t*)500);
  _count = prom_read;

  if (!bit_is_clear(BUTTON_PIN,BUTTON_INC)) {

    _count++;
    eeprom_update_word((uint16_t*)500, _count);

  }
  if(!bit_is_clear(BUTTON_PIN,BUTTON_DEC)){

    if(_count>0){
      _count--;
      eeprom_update_word((uint16_t*)500, _count);
    }
  }
    
}


void initPCint2(){
  PCICR |= _BV(PCIE2);
  PCMSK2 |= (_BV(PD2) | _BV(PD3));
  sei();

}


/**
   NOTE: 7 segment display need to be ~ 'not-ed' in order to be turned on
   So in order to turn on a specific digit, you must not(~) the pin it's connected to. 
**/
/**
   TODO: find out how to delete eeprom DONE 
   TODO: add capacitor switch circuit 
   FIXME: 4th digit on display does not turn off DONE 
   TODO: get capacitance button working probably needs to implement PCI (pin change interrupt) DONE 
   TODO: add 3rd button resetting state of the display back to 0
   TODO: rewire project to expose INT0 and INT1 for increase and decrease DONE
**/

int main(void){

  DDRC |= 0xff; 
  DDRB |= 0xff;
  /* DDRD |= (_BV(2) | _BV(3)); */
  initPCint2();

  /* volatile uint16_t  _count=0;//I think this is a semaphore */
  /* uint16_t prom_read; */
  /* prom_read = eeprom_read_word((uint16_t*)500); */
  /* _count = prom_read; */

  /* _count--;/\* TODO find out why this works if this even does anything at all   * \ */

  while (1) {

    print_num(_count);

  }				    

  return 0;

}
