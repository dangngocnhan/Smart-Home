#include <TimerOne.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>//Thư viện dùng cho I2C
//LiquidCrystal_I2C lcd(0x3F,16,2);//Khởi tạo LCD_I2C với địa chỉ 0x3F, 16 cột, 2 hàng
LiquidCrystal_I2C lcd(0x27,16,2);

#include "DHT.h"      
const int DHTPIN = 12;      
const int DHTTYPE = DHT11; 
DHT dht(DHTPIN, DHTTYPE);
// ================================================

const int tgNgat_timer1 = 3000;  // ngắt timer1 sau 3000us = 3ms

const int cbS1=2; const int cbS2=3;
int songuoi;
bool allow = 0; // cho phép bật thiết bị khi có người trong phòng

bool checkLed = 1; // cho phép bật đèn
const int led = 13; 

// DHT11 = 12

bool checkQuat_HC05 = 1; // cho phép bật quạt HC05
bool checkQuat_DHT11 = 1; // cho phép bật quạt DHT11 (T_DHT11 > T_NhietDo_DK)
const int quat = 11; 

const int Start_Stop = 10;
bool status_Start = 1;
float NhietDo_DK = 27;
const int tang_T = 9;
const int giam_T = 8;

float DoAm = 0;
float NhietDo = 0;

char dataHC05;

// Có người đi vào
void checkIn(){    // ngắt 0 xảy ra trước
   detachInterrupt(1);     // tắt sử dụng ngắt ngoài 1
    // NGƯỜI ĐI VÀO S1-->S2
   if(digitalRead(cbS1)== LOW){  // đi qua cảm biến 1 
      while(digitalRead(cbS2)); // đi qua cảm biến 2 --> có người vào
      songuoi++;    if(songuoi > 99){ songuoi = 99;}   
      if(songuoi){allow = 1;} // nếu có người cho phép bật thiết bị
      else {allow = 0;}       // ngược lại
      while(digitalRead(cbS1) == LOW);
      while(digitalRead(cbS2) == LOW);
   }
   attachInterrupt(1, checkOut, LOW);  // cho phép sử dụng lại ngắt ngoài 1
}

// có người đi ra
void checkOut(){   // ngắt 1 xảy ra trước
   detachInterrupt(0);  // tắt sử dụng ngắt ngoài 0
   // NGƯỜI ĐI RA  S2-->S1
   if (digitalRead(cbS2) == LOW){ // đi qua cảm biến 2
      while(digitalRead(cbS1));  // đi qua cảm biến 1 --> có người ra
      songuoi--;    if(songuoi <= 0) {songuoi = 0; asm volatile ( "jmp 0");}
      if(songuoi){allow = 1;} // nếu có người cho phép bật thiết bị
      else {allow = 0;}       // ngược lại
      while(digitalRead(cbS2) == LOW);
      while(digitalRead(cbS1) == LOW);
   } 
   attachInterrupt(0, checkIn, LOW);  // cho phép sử dụng lại ngắt ngoài 0
}

void HC05(){  // thực hiện sau ngắt timer1 
  while(Serial.available()){  //kiểm tra có dữ liệu được gửi về từ HC05
    dataHC05 = Serial.read(); // đọc dữ liệu được gửi đến
    // kiểm tra dữ liệu được gửi đến là gi và thực hiện nhiệm vụ
    if(dataHC05 == '1'){ 
      checkLed = 1;
//      Serial.println("Den bat");
    }
    if(dataHC05 == '0'){
      checkLed = 0;
//      Serial.println("Den tat");
    }
     if(dataHC05 == '2'){ 
      checkQuat_HC05 = 1;
//      Serial.println("Quat bat");
    }
    if(dataHC05 == '3'){
      checkQuat_HC05 = 0;
//      Serial.println("Quat tat");
    }
    if(dataHC05 == '4'){
//      lcd.clear();
//      if(status_Start){status_Start = 0;}
//      else status_Start = 1;
      status_Start = 0;
    }
    if(dataHC05 == '5'){
//      lcd.clear();
//      if(status_Start){status_Start = 0;}
//      else status_Start = 1;
      status_Start = 1;
    }
    if(dataHC05 == '6'){
      if(!status_Start){
        NhietDo_DK++; if(NhietDo_DK >= 50){NhietDo_DK = 50;}
      }
    }
    if(dataHC05 == '7'){
      if(!status_Start){
        NhietDo_DK--; if(NhietDo_DK <= 10){NhietDo_DK = 10;}
      }
    }
  } 
}

byte degree[8] = { // hiển thị đơn vị độ C
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};


void setup() {
  Serial.begin(9600);
  // LCD
  lcd.init();//Khởi tạo lcd 
  lcd.backlight();//Bật đèn nền lcd
  lcd.setCursor(0,0);//Đưa con trỏ đến cột 2, dòng 0
  lcd.print("Hello");//In dòng chữ 
  lcd.createChar(1, degree);
  
  // 2 cảm biến
  pinMode(cbS1,INPUT); pinMode(cbS2,INPUT);
  
  // thiết bị
  pinMode(led,OUTPUT);  pinMode(quat,OUTPUT);

  // điều khiển NhietDo_DK
  pinMode(Start_Stop,INPUT_PULLUP); 
  pinMode(tang_T,INPUT_PULLUP); pinMode(giam_T,INPUT_PULLUP);  
  
  
  attachInterrupt(0, checkIn, LOW);   // cho phép sử dụng ngắt ngoài 0
  attachInterrupt(1, checkOut, LOW);  // cho phép sử dụng ngắt ngoài 1

  Timer1.initialize(tgNgat_timer1);   // khởi động timer1
  Timer1.attachInterrupt(HC05);       // hàm được gọi khi ngắt timer1 xảy ra
 
 
}

// kiểm tra điều kiện để bật leb
void dieuKhienLed(){
  if(allow && checkLed){
     lcd.setCursor(4, 1); lcd.print(" L=bat "); 
     digitalWrite(led,HIGH);
  }else{
    lcd.setCursor(4, 1); lcd.print(" L=tat "); 
    digitalWrite(led,LOW);
  } 
}

// kiểm tra điều kiện để bật quạt
void dieuKhienQuat(){
  if(NhietDo >= NhietDo_DK){
    checkQuat_DHT11 = 1;
  }else {checkQuat_DHT11 = 0;}
  
  if(allow && checkQuat_DHT11 && checkQuat_HC05){
     lcd.setCursor(10, 1); lcd.print(" Q=bat"); 
     digitalWrite(quat,HIGH);
  }else{
    lcd.setCursor(10, 1); lcd.print(" Q=tat");
    digitalWrite(quat,LOW);
  }
}

void check_Start_Stop(){
  if(!digitalRead(Start_Stop)){
    delay(10);
    if(!digitalRead(Start_Stop)){
      lcd.clear();
      if(status_Start){status_Start = 0;}
      else status_Start = 1;
    }
    while(!digitalRead(Start_Stop)); 
  }  
}

void DK_NhietDo_BatQuat(){
  if(!digitalRead(tang_T)){
    delay(10);
    if(!digitalRead(tang_T)){
      NhietDo_DK++; if(NhietDo_DK >= 50){NhietDo_DK = 50;}
    }
    while(!digitalRead(tang_T)); 
  }  
  if(!digitalRead(giam_T)){
    delay(10);
    if(!digitalRead(giam_T)){
      NhietDo_DK--; if(NhietDo_DK <= 10){NhietDo_DK = 10;}
    }
    while(!digitalRead(giam_T));
  }  
}

void loop() {   
  check_Start_Stop();
  if(status_Start){
    DoAm = dht.readHumidity();
    NhietDo = dht.readTemperature();
  //  Serial.print("Độ Ẩm:"); Serial.print(DoAm);
  //  Serial.print("\tNhiệt Độ:"); Serial.print(NhietDo);
  //  Serial.print("\tSố Người:"); Serial.println(songuoi);
    lcd.setCursor(0, 1); lcd.print("N=");lcd.setCursor(2, 1); lcd.print(songuoi); if(songuoi<=9){lcd.setCursor(3, 1); lcd.print(" ");}
    lcd.setCursor(0, 0); lcd.print("T=");lcd.setCursor(2, 0); lcd.print(round(NhietDo));lcd.write(1); lcd.print("C      "); //
    lcd.setCursor(9, 0); lcd.print("H=");lcd.setCursor(11,0); lcd.print(round(DoAm)); lcd.print("%  "); 
    dieuKhienLed();
    dieuKhienQuat();
  }else{
    DK_NhietDo_BatQuat();
    lcd.setCursor(0, 0); lcd.print("NhietDo On Quat ");
    lcd.setCursor(0, 1); lcd.print("NhietDo >= ");lcd.setCursor(11, 1); lcd.print(round(NhietDo_DK));lcd.write(1); lcd.print("C  ");
  }
}
