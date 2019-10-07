#ifndef _PWM_TMR2_
#define _PWM_TMR2_

#include <stdint.h>

void set_prescaler_tmr2(uint16_t pre);
void setup_pwm_tmr2(uint8_t pwm_out);// pwm output values:3,11
void set_on_pwm_tmr2(uint8_t pwm_out);// pwm output values:3,11
void set_off_pwm_tmr2(uint8_t pwm_out);// pwm output values:3,11
void set_pwm_tmr2(uint8_t ocr2b,uint8_t pwm_out);

#endif
