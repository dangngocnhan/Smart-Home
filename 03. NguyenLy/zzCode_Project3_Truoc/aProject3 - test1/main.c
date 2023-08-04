#include <main.h>

//!#use i2c(Master,Fast=400000, sda=PIN_C4, scl=PIN_C3,force_sw)
//!#include "i2c_Flex_LCD.c"
#include "DHT11.c"
#use rs232(BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7)

#define LCD_RS_PIN      PIN_D6
#define LCD_RW_PIN      PIN_D5
#define LCD_ENABLE_PIN  PIN_D4   
#define LCD_DATA4       PIN_C5
#define LCD_DATA5       PIN_C4
#define LCD_DATA6       PIN_D3
#define LCD_DATA7       PIN_D2
#include <lcd.c>

int16 timer0 = 0;
// khai bao cac bien
unsigned int8 kqUart;
unsigned int8 dh_nhiet_do,dh_nhiet_do2,dh_do_am,dh_do_am2;   //cac bien luu tru nhiet do do am
unsigned int8 str[20];
int8 soNguoi = 0;
int8 NhietDoDk_Bat = 30;
int8 NhietDoDk_Tat = 25;
int start_stop_b = 0;
int1 baodong_b = 0;
int1 checkDenKhach = 1;
int1 checkQuatKhach = 1;

void dk_Tang(){
   if(start_stop_b == 1){
      NhietDoDk_Bat++;
   }else if(start_stop_b == 2){
      NhietDoDk_Tat++;
   }
}

void dk_Giam(){
   if(start_stop_b == 1){
      NhietDoDk_Bat--;
   }else if(start_stop_b == 2){
      NhietDoDk_Tat--;
   }
}

#INT_RB
void portb_interrupt(void)
{  
   CLEAR_INTERRUPT(INT_RB);    //clear flag interrupt
   if(input_state(Start_Stop)==0) { 
      While(input_state(Start_Stop)==0); 
      start_stop_b++;
      if(start_stop_b > 2 ){
         start_stop_b = 0;
      }
   }
   if(input_state(TangT)==0) {
      While(input_state(TangT)==0);
      if(start_stop_b == 0){
         checkDenKhach = ~checkDenKhach;
      }else dk_Tang();
   }
   if(input_state(GiamT)==0) {
      While(input_state(GiamT)==0);
      if(start_stop_b == 0){
         checkQuatKhach = ~checkQuatKhach;
      }else dk_Giam();
   }
   if(input_state(BaoDong)==0) {
      While(input_state(BaoDong)==0);
      baodong_b=~baodong_b;
      if(baodong_b == 0){
         output_low(BaoDong1);
      }
      //
//!      if(baodong_b == 1){
//!         putc('5'); // bat bao dong
//!      }else putc('6'); // tat bao dong
   }
}

#INT_RDA
void uart_(){
   kqUart = getc();
   switch(kqUart){  
      case 's': // dk bien start/ stop
         start_stop_b++;
         if(start_stop_b > 2 ){
            start_stop_b = 0;
         }
         break;
      case 't': // tang nhiet do dieu khien quat
         dk_Tang();
         break;
      case 'g': // giam nhiet do dieu khien quat
         dk_Giam();
         break;
      case '1':  // bat den khach
         checkDenKhach = 1;
         break;
      case '2': // tat den khach
         checkDenKhach = 0;
         break;
      case '3':  // bat quat khach
         checkQuatKhach = 1;
         break;
      case '4': // tat quat khach
         checkQuatKhach = 0;
         break;
      case '5':  // bat bao dong
         baodong_b = 1;
         break;
      case '6':  // tat bao dong
         baodong_b = 0;
         if(input_state(BaoDong1)){
            output_low(BaoDong1);
         }
         break;
   }
}

void check_Den_Khach(){
   if(soNguoi > 0 && checkDenKhach){
      output_high(DenKhach);
      //lcd; gui data
//!      putc('1');
   }
   else {
      output_low(DenKhach);
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
//!    CLEAR_INTERRUPT(int_ext);
    if(input_state(CamBien1)==0){       // neu co nguoi di vao
      disable_interrupts(int_ext); 
      if(baodong_b == 1){              //bao dong chom khi da baat bao dong
         output_high(BaoDong1); 
         timer0 = 0; 
         enable_interrupts(INT_TIMER0);   //13ms 
         set_timer0(0);
      } //chua bat chong chom --> ng nha di vao
      while(input_state(CamBien2)); // di qua hoan tat
      soNguoi++;   
//!         putc(soNguoi);
    }else if(input_state(CamBien2)==0){ // nguoi ben trong di ra
      disable_interrupts(int_ext);
      if(baodong_b == 1){              //bao dong chom khi da baat bao dong
         output_high(BaoDong1); 
         timer0 = 0; 
         enable_interrupts(INT_TIMER0);   //13ms 
         set_timer0(0);
      } //chua bat chong chom --> ng nha di ra
      while(input_state(CamBien1)); // di ra hoan tat
      if(soNguoi <= 1) soNguoi = 0;
      else{
         soNguoi--;
         //lcd gui data 
//!            putc(soNguoi);
      }
     
   }
   enable_interrupts(int_ext);
}



//!int timer1 = 0;
int1 checkLuaChua = 0;
int1 nguoiTrongBep = 0;
#int_timer1
void Ngat_Timer1(){
//!   CLEAR_INTERRUPT(int_timer1);
   // bao chay
   if(input_state(CB_KhiGa) == 0 || input_state(CB_LuaChua) == 0) { // co khi ga
      checkLuaChua = 1; 
//!      putc('7'); // co khi ga
   }else {
      checkLuaChua = 0;
   }
   
   // nha ve sinh
   if(input_state(N_VeSinh) == 0){
      output_high(DenVeSinh);
   }else output_low(DenVeSinh);
      
    //nha bep  
   if(input_state(N_TrongBep) == 0) {
      nguoiTrongBep = 1;
      output_high(DenBep);
   }else { 
      nguoiTrongBep = 0;
      output_low(DenBep);
   }
   set_timer1(0);
}


void check_QuatBep(){  //21
   if((nguoiTrongBep && checkQuatKhachDHT11()) || checkLuaChua){
      output_high(QuatBep);
      // LCD; gui data
//!      putc('3');
   }
   else{
      output_low(QuatBep);
      //LCD; gui data
//!      putc('4');
   }
}

void check_BaoDong2(){
   if((nguoiTrongBep && baodong_b) || checkLuaChua){
      output_high(BaoDong2);
      // LCD; gui data
//!      putc('3');
   }
   else{
      output_low(BaoDong2);
      //LCD; gui data
//!      putc('4');
   }
}


#int_timer0
void ngat_Timer0(){ 
   timer0++;
   if(timer0 == 2300){
      timer0 = 0;
      if(baodong_b){
         if(input_state(BaoDong1)){
            output_low(BaoDong1);
            disable_interrupts(int_timer0);
         }
      }
   }
   set_timer0(0);
}


void main()
{
//!   TRISC0 = 0;TRISC1 = 0;TRISC2 = 0;
   TRISC3 = 0;TRISC4 = 0;TRISC5 = 0;
   TRISB = 0xFF;    
//!   PORTB = 1;
//!   TRISD = 0b00000100;  
   TRISD0 = 0;TRISD1 = 0;TRISD2 = 0;
   TRISD3 = 0;TRISD4 = 0;TRISD5 = 0; // RS
   TRISD6 = 0; TRISD7 = 0;
//!   TRISD = 0x00;
   PORTD = 0;      
   
//!   TRISA1 = 1; TRISA2 = 1; TRISA3 = 1; TRISA4 = 1; TRISA5 = 1;  
   TRISA = 0xFF;
   set_tris_e(0x00);
   PORTE = 0;
   
   lcd_init();
   lcd_putc('\f');
   lcd_gotoxy(1,1);
   printf(lcd_putc,"My Project 3");
   delay_ms(700);
   lcd_putc('\f');
   
   //INTERRUPT SETTING
  enable_interrupts(INT_RDA);
//!  enable_interrupts (global); 
  
  enable_interrupts(global);
  CLEAR_INTERRUPT(INT_RB);
  ENABLE_INTERRUPTS(INT_RB);
  
  CLEAR_INTERRUPT(int_ext);
  enable_interrupts(int_ext); // cho phep ngat ngoai
  ext_int_edge(h_to_l); //chon canh kich ngat la tu cao xuong thap 
  
  enable_interrupts(int_timer1);    // 100ms
  setup_timer_1(t1_internal|T1_DIV_BY_8); 
  set_timer1(0);
  
//!  enable_interrupts(INT_TIMER0);   //13ms
  setup_timer_0(T0_INTERNAL|T0_DIV_256);
  set_timer0(0);
  
   while(TRUE)
   {
      if(start_stop_b == 0){ //start
         lcd_putc('\f');
         if (DHT_GetTemHumi(dh_nhiet_do,dh_nhiet_do2,dh_do_am,dh_do_am2))
         { 
               //putc(dh_nhiet_do);
               //putc(dh_do_am);
         }  
         lcd_init();
         lcd_gotoxy(1,1); 
         printf(lcd_putc,"Do Am: %u,%u",dh_do_am,dh_do_am2);  lcd_putc('%'); 
         lcd_gotoxy(1,2);  
         printf(lcd_putc,"Nhiet Do: %u,%u",dh_nhiet_do,dh_nhiet_do2);
         lcd_putc(223); lcd_putc('C');
         
         lcd_gotoxy(15,1);
         printf(lcd_putc,"SoN:%2u",soNguoi); 
         
         if(baodong_b == 0){
            lcd_gotoxy(21,1);
            printf(lcd_putc,"Bao Dong:Off ");
         }else printf(lcd_putc,"Bao Dong:On "); 
         
         check_Den_Khach();
         check_Quat_Khach();
         check_BaoDong2();
         check_QuatBep();
         
         lcd_gotoxy(21,2); 
         sprintf(str,"DK: %u, %u, %u",start_stop_b,NhietDoDk_Bat,NhietDoDk_Tat);
         printf(lcd_putc,"%s",str); 
         
         //!//uart
         lcd_gotoxy(35,1); 
         printf(lcd_putc,"Uart:"); 
         //printf(lcd_putc,"%u",kqUart);  
         lcd_putc(kqUart);
         delay_ms(50);
      }else{ //dieu khien nhiet do bat quat
         if(start_stop_b == 1){  /// che do dieu khien nhiet do bat
            lcd_putc('\f');
            lcd_gotoxy(1,1);
            lcd_putc("  DK Nhiet Do Bat");
            lcd_gotoxy(1,2); 
            sprintf(str,"NhietDoDk_Bat: %u",NhietDoDk_Bat); 
            printf(lcd_putc,"%s",str);
            delay_ms(50);
         }
         if(start_stop_b == 2){   ///che do dieu khien nhiet do tat
            lcd_putc('\f');
            lcd_gotoxy(1,1);
            lcd_putc("  DK Nhiet Do Tat");
            lcd_gotoxy(1,2); 
            sprintf(str,"NhietDoDk_Tat: %u",NhietDoDk_Tat); 
            printf(lcd_putc,"%s",str);
            delay_ms(50);
         }
      } 
   }
}

