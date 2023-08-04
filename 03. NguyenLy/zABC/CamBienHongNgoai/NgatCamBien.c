#include <16F877A.h>

#device *=16 adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES HS

#use delay(crystal=20000000)
#include <def_877a.h>

#include "DHT11.c"

#use i2c(Master,Fast=400000, sda=PIN_C4, scl=PIN_C3,force_sw)
#include "i2c_Flex_LCD.c"

unsigned int8 dh_nhiet_do,dh_nhiet_do2,dh_do_am,dh_do_am2;
unsigned int8 str[20];




#int_ext // giup vao ngat
void Ngat_int_ext()
{
//!    CLEAR_INTERRUPT(int_ext);
    if(input_state(PIN_B1)==0 && dh_do_am >= 80){ 
        output_toggle(PIN_D4);
    }
    if(input_state(PIN_B2)==0){
        output_toggle(PIN_D4);
    }
    if(input_state(PIN_A1)==0){
        output_toggle(PIN_D4);
    }
    if(input_state(PIN_A2)==0){
        output_toggle(PIN_D4);
    }
    if(input_state(PIN_A3)==0){
        output_toggle(PIN_D4);
    }
    if(input_state(PIN_A4)==0){
        output_toggle(PIN_D4);
    }
}

int timer1 = 0;
#int_timer1
void Ngat_Timer1(){
//!   timer1++;
//!   if(timer1 == 1){
//!      timer1 = 0;
      if(input_state(PIN_B4)==1) {output_high(PIN_D0);}
         else output_low(PIN_D0);
      if(input_state(PIN_B5)==1){output_high(PIN_D1);}
         else output_low(PIN_D1);
      if(input_state(PIN_B6)==1) {output_high(PIN_D2);}
         else output_low(PIN_D2);
      if(input_state(PIN_B7)==1) {output_high(PIN_D6);}
         else output_low(PIN_D6);
//!   }
}

void main()
{
   TRISB = 0xFF;        //PORTB CHANGE INTERRUPT
   TRISD = 0x00;        //RD0 IS OUTPUT
   PORTD = 0;           //OFF PIN D0
    
   
//!   lcd_init(0x4E,16,2);
//!   lcd_backlight_led(ON);
//!   lcd_init(0x40,16,2);
//!   lcd_backlight_led(ON);
//!
//!   lcd_putc('\f'); 
//!   lcd_gotoxy(1,1); 
//!   printf(lcd_putc,"READING DHT11");
//!   delay_ms(500); 
//!   lcd_putc('\f');

  
   //INTERRUPT SETTING
  CLEAR_INTERRUPT(INT_RB); 
//!  ENABLE_INTERRUPTS(INT_RB);
  CLEAR_INTERRUPT(int_ext);
  enable_interrupts(int_ext) ; // cho phep ngat ngoai
  ext_int_edge(h_to_l) ; //chon canh kich ngat la tu cao xuong thap
  enable_interrupts (global);
  
  enable_interrupts(int_timer1);
  setup_timer_1(t1_internal|T1_DIV_BY_8); 
  set_timer1(0);
  
   while(TRUE)
   {
      //TODO: User Code
//!      if (DHT_GetTemHumi(dh_nhiet_do,dh_nhiet_do2,dh_do_am,dh_do_am2))
//!      { 
//!         sprintf(str,"DO Am: %u,%u",dh_do_am,dh_do_am2);
//!         lcd_gotoxy(1,1); 
//!         printf(lcd_putc,"%s",str); 
//!         lcd_putc('%'); 
//!         sprintf(str,"NHIET D0: %u,%u",dh_nhiet_do,dh_nhiet_do2);
//!         lcd_gotoxy(1,2); 
//!         printf(lcd_putc,"%s",str); 
//!         lcd_putc(223); 
//!         lcd_putc('C'); 
//!      } 
   }

}

#INT_RB
void portb_interrupt(void)
{
     CLEAR_INTERRUPT(INT_RB);    //clear flag interrupt
     if(input_state(PIN_B4)==1){
         output_high(PIN_D0);
     }
     if(input_state(PIN_B5)==1) {
         output_high(PIN_D1);
     }
     if(input_state(PIN_B6)==1)  {
         output_high(PIN_D2);
     }
     if(input_state(PIN_B7)==1) {
         output_high(PIN_D6);
     }
}
