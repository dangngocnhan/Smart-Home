
#include <16f877a.h>
#include <def_877a.h>

#FUSES HS
#FUSES NOWDT
#FUSES NOBROWNOUT
#FUSES NOLVP
#device *=16 adc=8
#use delay (crystal=20M) 
//!#use delay (clock=20M) 
//!#byte TRISE =0x89
#byte PORTE =0x09
#bit re2 =0x09.2
#bit re1 =0x09.1
#bit re0 =0x09.0

#define DHT11        PIN_A0
#define CB_Mua       PIN_A1
#define CB_KhiGa     PIN_A2
#define CB_BaoChay   PIN_A3
#define N_VeSinh     PIN_A4
#define N_O_Bep      PIN_A5
#define NgatNgoai    PIN_B0
#define CamBien1     PIN_B1
#define CamBien2     PIN_B2
//!#define RB3          PIN_B3
#define TangT        PIN_B4
#define GiamT        PIN_B5
#define BaoDong      PIN_B6
#define Start_Stop   PIN_B7
//!#define RC0          PIN_C0
//!#define RC1          PIN_C1
//!#define RC2          PIN_C2
//!#define LCD1         PIN_C3
//!#define LCD2         PIN_C4
//!#define RC5          PIN_C5
#define TX           PIN_C6
#define RX           PIN_C7
#define DenKhach     PIN_D0
#define QuatKhach    PIN_D1
#define QuatBep      PIN_D2
#define DenBep       PIN_D3
#define BaoDong1     PIN_D4
#define BaoDong2     PIN_D5
#define DenVeSinh    PIN_D6

#define LCD_RS_PIN      PIN_E0
#define LCD_RW_PIN      PIN_E1
#define LCD_ENABLE_PIN  PIN_E2   
#define LCD_DATA4       PIN_C3
#define LCD_DATA5       PIN_C4
#define LCD_DATA6       PIN_C5
#define LCD_DATA7       PIN_D7

#include <lcd.c>

//!#use i2c(Master,Fast=1000000, sda=PIN_C4, scl=PIN_C3,force_sw)
//!#include "i2c_Flex_LCD.c"

#include "DHT11.c"
unsigned int8 kqUart;
unsigned int8 dh_nhiet_do,dh_nhiet_do2,dh_do_am,dh_do_am2;   //cac bien luu tru nhiet do do am
unsigned int8 str[20];
int8 soNguoi = 0;
int8 NhietDoDk_Bat = 15;
int8 NhietDoDk_Tat = 10;
int start_stop_b = 0;
int1 baodong_b = 0, checkDenKhach = 1, checkQuatKhach = 1;



void check_Den_Khach(){
   if(soNguoi > 0 && checkDenKhach){
      output_high(Pin_D0);
      //lcd; gui data
//!      putc('1');
   }
   else {
      output_low(Pin_D0);
      //lcd; gui data
//!      putc('2');
   }
}

int1 checkQuatKhachDHT11(){
   if(NhietDoDk_Bat <= dh_nhiet_do){
      return 1;
   }
   if(NhietDoDk_Tat >= dh_nhiet_do){
      return 0;   
   }
}

void check_Quat_Khach(){
   if(soNguoi > 0 && checkQuatKhach && checkQuatKhachDHT11()){
      output_high(QuatKhach);
      // LCD; gui data
//!      putc('3');
   }
   else{
      output_low(QuatKhach);
      //LCD; gui data
//!      putc('4');
   }
}

#int_ext // giup vao ngat
void Ngat_int_ext()
{
    CLEAR_INTERRUPT(int_ext);
    if(input_state(Pin_B1)==0){
      disable_interrupts(int_ext); 
      while(input_state(Pin_B2));
      soNguoi++;
      //lcd gui data
//!      putc(soNguoi);
    }else{
      if(input_state(Pin_B2)==0){
         disable_interrupts(int_ext);
         while(input_state(Pin_B1));
         if(soNguoi <= 1) soNguoi = 0;
         else{
            soNguoi--;
            //lcd gui data
//!            putc(soNguoi);
         }
      }
   }
   enable_interrupts(int_ext);
}

void main() { 
   //khai bao bien cuc bo o day
//!   unsigned int8 dh_nhiet_do,dh_nhiet_do2,dh_do_am,dh_do_am2;
//!   unsigned int8 str[20];
   
//!   lcd_init(0x40,16,2);
//!   lcd_backlight_led(ON); 
   TRISC0 = 0;TRISC1 = 0;TRISC2 = 0;TRISC3 = 0;TRISC4 = 0;TRISC5 = 0;
   TRISB = 0xFF;         
   TRISD = 0x00;         
   PORTD = 0;            
   TRISA1 = 1;TRISA2 = 1;TRISA3 = 1;TRISA4 = 1;TRISA5 = 1;
   set_tris_e(0x02);
   output_low(Pin_D0);
   output_low(Pin_D1);
   
   lcd_init();
   lcd_putc('\f'); 
   lcd_gotoxy(1,1); 
   printf(lcd_putc,"READING DHT11");
   
   CLEAR_INTERRUPT(int_ext);
   enable_interrupts(int_ext); // cho phep ngat ngoai
   ext_int_edge(h_to_l) ; //chon canh kich ngat la tu cao xuong thap
   enable_interrupts (global);
   delay_ms(500); 
//!   delay_ms(500); 
//!   lcd_putc('\f');
//!   
   while(TRUE) {
//!      lcd_gotoxy(1,1); 
//!      printf(lcd_putc,"READING DHT11");
//!      lcd_gotoxy(1,2); 
//!      printf(lcd_putc,"READING DHT11");
//!   //TO00: User Code 
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
         if(dh_nhiet_do>0) {
            output_high(pin_D2);
         }else output_low(pin_D2);
      }
    check_Den_Khach();
    check_Quat_Khach();
   }
  
} 
