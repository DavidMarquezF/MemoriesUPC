#include <avr/interrupt.h>
#include <avr/io.h>//it includes <avr/sfr_defs.h>, <avr/portpins.h>, <avr/common.h>, <avr/version.h>
#include <stdint.h>

#include "adc.h"
#include "pwm_tmr2.h"
#include "tmr0.h"
#include "utils.h"

/********************************************
                Clock measurement
---------------------------------------------
-adc module
This program takes samples from the analog
input A5 of the Arduino UNO Board.
The conversion time is 13/fadc_clk, fadc_clk=16e6/adc_pre.

-pwm_tmr2 module
With the 8 most significant bits of the 10-bit ADC
it updates the PWM output at terminal ~3 or ~11.

-tmr0 module
An interrupt is activated each 50us (ocr0a=99, tmr0_pre=8)

-debug output
The digital output PD4 is set to '1' 
at the beginning of the ISR and to '0' at the end.

September 21, 2019
*********************************************/

void setup(){
  // adc
  setup_ADC(5,5,16);//(adc_input,v_ref,adc_pre)
  //adc_input (0-5 (default=5),8 Tª, 14 1.1V, 15 GND 
  //v_ref 0 (AREF), 1(1.1V), default=5 (5V)
  //adc_pre 2,4,8,16(default),32,64,128
  start_ADC();//actual value will be read next sampling time

  // tmr0
  setup_tmr0(99,8);//(ocr0a, tmr0_pre)
  //tmr0_pre 1,default=8,64,256,1024
  //TMR0=prescaler*(ocr0a+1)*T_clk

  // pwm
  setup_pwm_tmr2(11);//(pwm_out) 3,default=11
  set_prescaler_tmr2(1);
  
  // debug output
  sbi(DDRD,DDD4);//DDRD |=(1<<DDD4);//pin 4 Arduino as an output. It shows sampling period (period) and ISR execution time (pulse wide)

  sei();
}

int main(void){
  setup();
  while(1){}
}

ISR(TIMER0_COMPA_vect){
  sbi(PORTD,PD4);//PORTD |= (1<<PD4);
  uint8_t value=read8_ADC();
  start_ADC();//actual value will be read next sampling time
  set_pwm_tmr2(value,11);
  cbi(PORTD,PD4);//PORTD &= ~(1<<PD4);
}
