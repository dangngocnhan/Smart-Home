#include <16f877a.h>
#device *=16 adc=8
#use delay (clock=20M) 
#include "DHT11.c"

#use i2c(Master,Fast=100000, sda=PIN_C4, scl=PIN_C3,force_sw)
#include "i2c_Flex_LCD.c"

unsigned int8 dh_nhiet_do,dh_nhiet_do2,dh_do_am,dh_do_am2;
unsigned int8 str[20];


void main() { 
   //khai bao bien cuc bo o day
   
   
   lcd_init(0x4E,16,2);
   lcd_backlight_led(ON);
   lcd_init(0x40,16,2);
   lcd_backlight_led(ON);

   lcd_putc('\f'); 
   lcd_gotoxy(1,1); 
   printf(lcd_putc,"READING DHT11");
   delay_ms(500); 
   lcd_putc('\f');
   
   while(TRUE) {
   //TO00: User Code 
      if (DHT_GetTemHumi(dh_nhiet_do,dh_nhiet_do2,dh_do_am,dh_do_am2))
      { 
         sprintf(str,"DO Am: %u,%u",dh_do_am,dh_do_am2);
         lcd_gotoxy(1,1); 
         printf(lcd_putc,"%s",str); 
         lcd_putc('%'); 
         sprintf(str,"NHIET D0: %u,%u",dh_nhiet_do,dh_nhiet_do2);
         lcd_gotoxy(1,2); 
         printf(lcd_putc,"%s",str); 
         lcd_putc(223); 
         lcd_putc('C'); 
      } 
   }
  
} 
