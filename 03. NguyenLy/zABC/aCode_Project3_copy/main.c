#include <main.h>
//!#use rs232(BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7)
//!
#use i2c(Master,Fast=400000, sda=PIN_C4, scl=PIN_C3,force_sw)
#include "i2c_Flex_LCD.c"
#include "DHT11.c"

// khai bao cac bien
unsigned int8 kqUart;
unsigned int8 dh_nhiet_do,dh_nhiet_do2,dh_do_am,dh_do_am2;   //cac bien luu tru nhiet do do am
unsigned int8 str[20];
int8 soNguoi = 0;
int8 NhietDoDk_Bat = 25;
int8 NhietDoDk_Tat = 20;
int start_stop_b = 0;
int1 baodong_b = 0, checkDenKhach = 1, checkQuatKhach = 1;


//!#INT_RDA
//!void uart_(){
//!   kqUart = getc();
//!   switch(kqUart){
//!      case '1':
//!         checkDenKhach = 1;
//!         break;
//!      case '2':
//!         checkDenKhach = 0;
//!         break;
//!   }
//!}

void check_Den_Khach(){
   if(soNguoi > 0 && checkDenKhach){
      output_high(DenKhach);
      //lcd; gui data
//!      putc('1');
   }
   else {
      output_low(Denkhach);
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
//!      putc('A');
   }
   else{
      output_low(QuatKhach);
      //LCD; gui data
//!      putc('B');
   }
}


#INT_RB
void portb_interrupt(void)
{
   CLEAR_INTERRUPT(INT_RB);    //clear flag interrupt
   if(input_state(Start_Stop)==0) { 
      start_stop_b++;
      if(start_stop_b > 2 ){start_stop_b = 0;}
   }
   if(input_state(TangT)==0) {
      if(start_stop_b == 1){
         NhietDoDk_Bat++;
      }else if(start_stop_b == 2){
         NhietDoDk_Tat++;
      }
   }
   if(input_state(GiamT)==0) {
      if(start_stop_b == 1){
         NhietDoDk_Bat--;
      }else if(start_stop_b == 2){
         NhietDoDk_Tat--;
      }
   }
   if(input_state(BaoDong)==0) {
      baodong_b=~baodong_b;
   }
}


#int_ext // giup vao ngat
void Ngat_int_ext()
{
    CLEAR_INTERRUPT(int_ext);
    if(input_state(CamBien1)==0){
      disable_interrupts(int_ext); 
      while(input_state(CamBien2));
      soNguoi++;
    }else{
      if(input_state(CamBien2)==0){
         disable_interrupts(int_ext);
         while(input_state(CamBien1));
         if(soNguoi <= 1) soNguoi = 0;
         else soNguoi--;   
      }
   }
   enable_interrupts(int_ext);
}

//!int timer1 = 0;
#int_timer1
void Ngat_Timer1(){
   if(input_state(CB_KhiGa)==1) {output_high(QuatBep); output_high(BaoDong2);}
      else { output_low(QuatBep); output_low(BaoDong2); }
   if(input_state(CB_BaoChay)==1){output_high(BaoDong2);}
      else output_low(BaoDong2);
   if(input_state(N_VeSinh)==1) {output_high(DenVeSinh);}
      else output_low(DenVeSinh);
   if(input_state(N_O_Bep)==1) {output_high(DenBep);}
      else output_low(DenBep);
}



void main()
{
   TRISB = 0xFF;        //PORTB CHANGE INTERRUPT
   TRISD = 0x00;        //RD0 IS OUTPUT
   PORTD = 0;           //OFF PIN D0
   TRISA1 = 1;TRISA2 = 1;TRISA3 = 1;TRISA4 = 1;TRISA5 = 1;
    
   
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
  enable_interrupts(INT_RDA);
   
  CLEAR_INTERRUPT(INT_RB); 
  ENABLE_INTERRUPTS(INT_RB);
  
  CLEAR_INTERRUPT(int_ext);
  enable_interrupts(int_ext); // cho phep ngat ngoai
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
//!      sprintf(str,"DK: %u, %u, %u",start_stop_b,NhietDoDk_Bat,NhietDoDk_Tat);
//!      lcd_gotoxy(1,1); 
//!      printf(lcd_putc,"%s",str); 

//!      if(NhietDoDk_Bat > 25){
//!         output_high(DenBep);
//!      }else output_low(DenBep);
//!      if(NhietDoDk_Tat < 20){
//!         output_high(QuatBep);
//!      }else output_low(QuatBep);
      
      if(soNguoi){
         output_high(DenKhach);
      }else output_low(DenKhach);
      check_Den_Khach();
   }

}

