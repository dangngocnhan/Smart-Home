
//!#include <def_877a.h>
#bit ra0 =0x05.0
#bit TRISA0 =0x85.0
#device *=16 adc=8
#define  Data_Pin       Pin_D4                      // ket noi voi chan RD0
#define  Data_Pin_TRIS  SET_TRIS_D                // dieu khien chan data la output hay input 

int8 Data_DHT11[5];

int1 DHT11_Start(){    // start
   Data_Pin_TRIS(0);   // MCU output
   Output_low(Data_Pin);        // MCU keo chan data xuong muc thap >18 ms
   delay_ms(25);
   Output_high(Data_Pin);        // MCU keo chan data len muc cao 
   Data_Pin_TRIS(0xff);   // MCU input doi tin hieu tra ve cua DHT11 khoang 20 - 40 us
   delay_us(40);
   if(input(Data_Pin) == 0){    //DHT11 keo chan data xuong thap 80 us sau do keo len cao 80 us --> xac nhan ket noi
      delay_us(80);
      if(input(Data_Pin) == 1){
         delay_us(80);
         return 1;         // xac nhan ket noi thanh cong
      }
   }
}
 

int1 ReadData_DHT11(){       // doc data cua DHT11 tra ve
    for(int i = 0; i < 5; i++){        // data: 5 byte
      for(int j = 0; j < 8; j++){      // 1 byte 8 bit   tong 40 bit
         // data
         while(input(Data_Pin) == 0){};      // chay het 50us muc thap
         delay_us(30);              //  hon 26-28us van la muc cao --> DHT11 chuyen di muc 1
         if(input(Data_Pin) == 1){  
               Data_DHT11[i] = Data_DHT11[i]<<1 | 1;
               while(input(Data_Pin) == 1){} // chay het 70us muc cao
         }
         else{                   // tra ve bit 0
            Data_DHT11[i] = Data_DHT11[i]<<1 | 0;
         }
      }   
    }
    // ------- kiem tra byte 5 = sum(byte 1 + 2 + 3 + 4) --> chuyen data thanh cong. nguoc lai 
    if(Data_DHT11[4] == (Data_DHT11[0] + Data_DHT11[1] + Data_DHT11[2] + Data_DHT11[3])){
      return 1;
    }
}




void HienThi_Data_DHT11(){
    //------------------in ket qua-----------------------------------------------
    //in nhiet do
    lcd_init(0x4E,16,2);
    printf(lcd_putc, "Nhiet do = "); 
    for(int i = 13; i > 11; i--){
       lcd_gotoxy(i,1);       //hien thi hang don vi truoc >hang chuc
       printf(lcd_putc, "%d", Data_DHT11[2] % 10 + 48); 
       Data_DHT11[2]=Data_DHT11[2] / 10;
    }
    //in do am
    lcd_gotoxy(1,2);
    printf(lcd_putc, "Do am = ");  
    for(int i = 13; i > 11; i--){ 
       lcd_gotoxy(i,2);   
       printf(lcd_putc, "%d", Data_DHT11[0] % 10 + 48); //hien thi hang don vi truoc >hang chuc  //doi ra so thap phan +48 
       Data_DHT11[0]=Data_DHT11[0] / 10;
    }
      //hien thi don vi nhiet do va do am 
    LCD_Gotoxy(14,1);   
    LCD_putc(223);
    LCD_putc('C');
    LCD_Gotoxy(14,2);   
    LCD_putc('%');
}
//!
