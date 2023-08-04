#include <16F877A.h>

#device *=16 adc=8
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES HS
#use delay(crystal=20000000)
#include <def_877a.h>

//!#byte PORTE =0x09
//!#bit re2 =0x09.2
//!#bit re1 =0x09.1
//!#bit re0 =0x09.0
//!#use FIXED_IO( C_outputs=PIN_C2,PIN_C1,PIN_C0 )
//!#use FIXED_IO( D_outputs=PIN_D6,PIN_D5,PIN_D4,PIN_D3,PIN_D2,PIN_D1,PIN_D0)

#define DHT11        PIN_A0   //2
#define CB_Mua       PIN_A1   //3
#define CB_KhiGa     PIN_A2   //4
#define CB_LuaChua   PIN_A3   //5
#define N_VeSinh     PIN_A4   //6
#define N_TrongBep   PIN_A5   //7
#define NgatNgoai    PIN_B0   //33
#define CamBien1     PIN_B1   //34
#define CamBien2     PIN_B2   //35
//!#define RB3          PIN_B3   //36
#define TangT        PIN_B4   //37
#define GiamT        PIN_B5   //38
#define BaoDong      PIN_B6   //39
#define Start_Stop   PIN_B7   //40
//!#define RC0          PIN_C0   //15
//!#define RC1          PIN_C1   //16
//!#define RC2          PIN_C2   //17
//!#define LCD1         PIN_C3   //18
//!#define LCD2         PIN_C4   //23
//!#define RC5          PIN_C5   //24
#define TX           PIN_C6   //25
#define RX           PIN_C7   //26
#define DenKhach     PIN_D0   //19
#define QuatKhach    PIN_D1   //20
#define QuatBep      PIN_D2   //21
#define DenBep       PIN_D3   //22
#define BaoDong1     PIN_D4   //27
#define BaoDong2     PIN_D5   //28
#define DenVeSinh    PIN_D6   //29
//!#define RD7          PIN_D7   //30


