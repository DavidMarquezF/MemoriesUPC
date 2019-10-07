#include <avr/interrupt.h>
#include <avr/io.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>//serial

#include "printf2serial.h"
#include "serial_device.h"
#include "tmr0.h"
#include "utils.h"

/********************************************
          Using printf with AVR-GCC
---------------------------------------------
-print2fserial module
with this module we just need to include 
init_stdout();
in the setup section

-serial_device module
configured at 115200bps

-tmr0 module
An interrupt is activated each 1s (ocr0a=255, tmr0_pre=256)

-debug output
The digital output PD4 is set to '1' 
at the beginning of the ISR and to '0' at the end.

September 21, 2019
*********************************************/

#define ini 48

void setup(){
  //tmr0
  setup_tmr0(255,256);//(ocr0a, tmr0_pre)
  //tmr0_pre 1,default=8,64,256,1024
  //TMR0=prescaler*(ocr0a+1)*T_clk

  // serial
  serial_open();

  // to send printf to serial with avr-gcc
  init_stdout();

  // debug output
  sbi(DDRD,DDD4);//DDRD |=(1<<DDD4);//pin 4 Arduino as an output. It shows sampling period (period) and ISR execution time (pulse wide)
  
  sei();
}

int main(void){
  setup();
  printf("\n\nPRINTF with AVR-GCC\n\n");
  while(1){}
}

ISR(TIMER0_COMPA_vect){
  static uint8_t n=0;
  static uint8_t uint8=ini;
  static uint16_t uint16=ini;
  static uint32_t uint32=ini;
  static float a_float,b_float=ini;
  static char dat[40];

  sbi(PORTD,PD4);

  n++;
  if (n==0) {
    uint8++;
    uint16++;
    uint32++;
    a_float++;
    b_float=cos(a_float+M_PI+sqrt(3));

    printf("\nchar: %c\n", uint8);
    printf("hex: 0x%X\n", uint8);
    printf("octal: %o\n", uint8);
    printf("uint8: %d\n", uint8);
    printf("uint16 %d\n", uint16);
    printf("uint32 %ld\n", uint32);
    printf("float sqrt %.5f\n",sqrt(a_float));
    printf("float sqrt %.5f\n",(double)sqrt(a_float));
    printf("float cos %.5f\n",(double)b_float);

    sprintf(dat,"float cos %.5f\n",(double)b_float);
    for(uint8_t i = 0; dat[i] != '\0'; i++)
      serial_put(dat[i]);
  }

  cbi(PORTD,PD4);
}

