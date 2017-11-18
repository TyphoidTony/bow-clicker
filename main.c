#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "display.h"
#include <string.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include "Lib/USART.h"
#define SENSE_TIME 22
#define THRESHOLD 15
/* para e.g. pin = PINB pn = PB0 */


uint16_t prom_read;
volatile uint16_t _count;
volatile uint16_t _chargeCount;



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
  _chargeCount++;

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

  DDRD |= _BV(PD7);
  _delay_us(1);
  DDRD &= ~_BV(PD7);
  PCIFR |=_BV(PCIF2);
   
}

void initPCint2(){
  PCICR |= _BV(PCIE2);
  PCMSK2 |= (_BV(PD2) | _BV(PD3) | _BV(PD7));
    sei();		/* Might not need this */
}

/**
   NOTE: 7 segment display need to be ~ 'not-ed' in order to be turned on
   So in order to turn on a specific digit, you must not(~) the pin it's connected to. 

   TODO: find out how to delete eeprom DONE 
   FIXME: 4th digit on display does not turn off DONE 
   TODO: get capacitance button working probably needs to implement PCI (pin change interrupt) DONE 
   TODO: add 3rd button resetting state of the display back to 0
   TODO: rewire project to expose INT0 and INT1 for increase and decrease DONE
   TODO: integrate cap-sensor DONE
   TODO: Fix issue with starting number of display being [6535] (C's unsigned int maximum) DONE sort of..
   
**/

int main(void){
  //   clock_prescale_set(clock_div_1);

  DDRC |= 0xff; 
  DDRB |= 0xff;
  MCUCR |= _BV(PUD);		
  PORTD |=_BV(PD7);

  initPCint2();

  _count++;
  _count--;
  eeprom_update_word((uint16_t*)500, _count); /* Crappy hack to 'work-around' the _count rollover issue.  */
     

  while (1) {

    _chargeCount=0;

    sei();
    _delay_ms(SENSE_TIME);
    cli();

    if (_chargeCount > THRESHOLD) {
      _count++;
      eeprom_update_word((uint16_t*)500, _count);
       
    }
    
     
    print_num(_count);
  }				    

  return 0;

}
