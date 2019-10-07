#include <avr/io.h>//it includes <avr/sfr_defs.h>, <avr/portpins.h>, <avr/common.h>, <avr/version.h>

#include "pwm_tmr2.h"

void set_prescaler_tmr2(uint16_t pre){
  //pre 0 (stop),default=1,8,32,64,128,256,1024
  switch (pre){
  case 0:TCCR2B &= 0b11111000;break;
  case 1:TCCR2B |= 0b00000001;TCCR1B &= 0b11111001;break;
  case 8:TCCR2B |= 0b00000010;TCCR1B &= 0b11111010;break;
  case 32:TCCR2B |= 0b00000011;TCCR1B &= 0b11111011;break;
  case 64:TCCR2B |= 0b00000100;TCCR1B &= 0b11111100;break;
  case 128:TCCR2B |= 0b00000101;TCCR1B &= 0b11111101;break;
  case 256:TCCR2B |= 0b00000110;TCCR1B &= 0b11111110;break;
  case 1024:TCCR2B |= 0b00000111;TCCR1B &= 0b11111111;break;
  default:TCCR2B |= 0b00000001;TCCR1B &= 0b11111001;break;
  }
}

void setup_pwm_tmr2(uint8_t pwm_out){
  // pwm output values:3,11
  switch (pwm_out){
  case 3:
    DDRD |= (1 << DDD3);
    TCCR2A |= 0b00100011;//OC2B(b5-b4) : Fast PWM(b1-b0)
    break;
 case 11:
    DDRB |= (1 << DDB3);
    TCCR2A |= 0b10000011;//OC2A(b7-b6) : Fast PWM(b1-b0)
    break;
  default:
    DDRB |= (1 << DDB3);
    TCCR2A |= 0b10000011;//OC2A(b7-b6) : Fast PWM(b1-b0)
    break;
  }
}

void set_on_pwm_tmr2(uint8_t pwm_out){
  // pwm output values:3,default=11
  switch (pwm_out){
  case 3:
    TCCR2A |= 0b00100011;//OC2B(b5-b4) : Fast PWM(b1-b0)
    break;
 case 11:
    TCCR2A |= 0b10000011;//OC2A(b7-b6) : Fast PWM(b1-b0)
    break;
  default:
    TCCR2A |= 0b10000011;//OC2A(b7-b6) : Fast PWM(b1-b0)
    break;
  }
}

void set_off_pwm_tmr2(uint8_t pwm_out){
  // pwm output values:3,default=11
  switch (pwm_out){
  case 3:
    TCCR2A &= 0b11011111;//OC2B(b5-b4) : Fast PWM(b1-b0)
    break;
 case 11:
    TCCR2A &= 0b01111111;//OC2A(b7-b6) : Fast PWM(b1-b0)
    break;
  default:
    TCCR2A &= 0b01111111;//OC2A(b7-b6) : Fast PWM(b1-b0)
    break;
  }
}

void set_pwm_tmr2(uint8_t ocr2b,uint8_t pwm_out){
 switch (pwm_out){
 case 3:OCR2B=ocr2b;break;//OC2B:
 case 11:OCR2A=ocr2b;break;//OC2A:
 default:OCR2A=ocr2b;break;//OC2A:
 }
}
