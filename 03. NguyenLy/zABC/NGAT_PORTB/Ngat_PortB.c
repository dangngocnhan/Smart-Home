#include <16F877A.h>

#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=20000000)
#include <def_877a.h>

#INT_RB
void portb_interrupt(void)
{
     CLEAR_INTERRUPT(INT_RB);    //clear flag interrupt
     if(input_state(PIN_B4)==0)
     {
         
         output_toggle(PIN_D0);
     }
       if(input_state(PIN_B5)==0)
     {
         
         output_toggle(PIN_D0);
     }
       if(input_state(PIN_B6)==0)
     {
         
         output_toggle(PIN_D0);
     }
       if(input_state(PIN_B7)==0)
     {
         
         output_toggle(PIN_D0);
     }
}

void main()
{
   TRISB = 0xFF;        //PORTB CHANGE INTERRUPT
   TRISD = 0x01;        //RD0 IS OUTPUT
   PORTD = 0;           //OFF PIN D0
 

  
   
   //INTERRUPT SETTING
  //1.CLEAR FLAG INTERRUPT
  CLEAR_INTERRUPT(INT_RB);
  //2.ENABLE PORTB CHANGE
  ENABLE_INTERRUPTS(INT_RB);
  //3.ENABLE GLOBAL INTERRUPT
  ENABLE_INTERRUPTS(GLOBAL);

  
   while(TRUE)
   {
      //TODO: User Code
    
     
   }

}
