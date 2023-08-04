#define W 0
#define F 1

//----- Register Files------------------------------------------------------

#byte INDF =0x00
#byte TMR0 =0x01 
#byte PCL =0x02 
#byte STATUS =0x03 
#byte FSR =0x04 
#byte PORTA =0x05 
#byte PORTB =0x06 
#byte PORTC =0x07
#byte PORTD =0x08
#byte PORTE =0x09



#byte PCLATH =0x0A 
#byte PIR1 =0x0C
#byte PIR2 =0x0D

#byte TMR1L =0x0E
#byte TMR1H =0x0F
#byte T1CON =0x10
#byte TMR2 =0x11
#byte T2CON =0x12

#byte SSPCON =0x14
#byte CCPR1L =0x15
#byte CCPR1H =0x16
#byte CCP1CON =0x17
#byte RCSTA =0x18
#byte TXREG =0x19
#byte RCREG =0x1A
#byte CCPR2L =0x1B
#byte CCPR2H =0x1C
#byte CCP2CON =0x1D 

#byte ADRESH =0x1E
#byte ADCON0 =0x1F

/* bank 1 registers */

#byte OPTION_REG =0x81

#byte TRISA =0x85
#byte TRISB =0x86
#byte TRISC =0x87
#byte TRISD =0x88
#byte TRISE =0x89


#byte PIE1 =0x8C
#byte PIE2 =0x8D
#byte PCON =0x8E

#byte SSPCON2 =0x91
#byte PR2 =0x92
#byte SSPADD =0x93
#byte SSPSTAT =0x94

#byte TXSTA =0x98
#byte SPBRG =0x99

#byte ADRESL =0x9E
#byte ADCON1 =0x9F

/* bank 2 registers */

#byte EEDATA =0x010C
#byte EEADR =0x010D
#byte EEDATH =0x010E
#byte EEADRH =0x010F

/* bank 3 registers */

#byte EECON1 =0x018C
#byte EECON2 =0x018D


//----- STATUS Bits --------------------------------------------------------

// For Assembly Language - Note upper case
#define IRP 7
#define RP1 6
#define RP0 5
#define NOT_TO 4
#define NOT_PD 3
#define Z 2
#define DC 1
#define C 0

//----- INTCON Bits for c --------------------------------------------------------

#bit gie = 0x0b.7
#bit eeie = 0x0b.6
#bit t0ie = 0x0b.5
#bit inte = 0x0b.4
#bit rbie = 0x0b.3
#bit t0if = 0x0b.2
#bit intf = 0x0b.1
#bit rbif = 0x0b.0

//---------PORTA bits------------------
#bit ra5 =0x05.5
#bit ra4 =0x05.4
#bit ra3 =0x05.3
#bit ra2 =0x05.2
#bit ra1 =0x05.1
#bit ra0 =0x05.0

//---------PORTB bits------------------
#bit rb7 =0x06.7
#bit rb6 =0x06.6
#bit rb5 =0x06.5
#bit rb4 =0x06.4
#bit rb3 =0x06.3
#bit rb2 =0x06.2
#bit rb1 =0x06.1
#bit rb0 =0x06.0

//---------PORTC bits------------------
#bit rc7 =0x07.7
#bit rc6 =0x07.6
#bit rc5 =0x07.5
#bit rc4 =0x07.4
#bit rc3 =0x07.3
#bit rc2 =0x07.2
#bit rc1 =0x07.1
#bit rc0 =0x07.0

#bit rd7 =0x08.7
#bit rd6 =0x08.6
#bit rd5 =0x08.5
#bit rd4 =0x08.4
#bit rd3 =0x08.3
#bit rd2 =0x08.2
#bit rd1 =0x08.1
#bit rd0 =0x08.0

#bit re2 =0x09.2
#bit re1 =0x09.1
#bit re0 =0x09.0

//----- PIR1 Bits ----------------------------------------------------------
#bit PSPIF =0x0C.7
#bit ADIF =0x0C.6
#bit RCIF =0x0C.5
#bit TXIF =0x0C.4
#bit SSPIF =0x0C.3
#bit CCP1IF =0x0C.2
#bit TMR2IF =0x0C.1
#bit TMR1IF =0x0C.0

//----- PIR2 Bits ----------------------------------------------------------
#bit CMIF =0x0D.6
#bit EEIF =0x0D.4
#bit BCLIF =0x0D.3
#bit CCP2IF =0x0D.0

//----- T1CON Bits ---------------------------------------------------------
#bit T1CKPS1 =0x10.5
#bit T1CKPS0 =0x10.4
#bit T1OSCEN =0x10.3
#bit T1SYNC =0x10.2
#bit TMR1CS =0x10.1
#bit TMR1ON =0x10.0

//----- T2CON Bits ---------------------------------------------------------
#bit TOUTPS3 =0x12.6
#bit TOUTPS2 =0x12.5
#bit TOUTPS1 =0x12.4
#bit TOUTPS0 =0x12.3
#bit TMR2ON =0x12.2
#bit T2CKPS1 =0x12.1
#bit T2CKPS0 =0x12.0

//-------------SSPCON bits--------------------------
#bit WCOL =0x14.7
#bit SSPOV =0x14.6
#bit SSPEN =0x14.5 
#bit CKP =0x14.4
#bit SSPM3 =0x14.3
#bit SSPM2 =0x14.2
#bit SSPM1 =0x14.1
#bit SSPM0 =0x14.0

//---------------CCP1CON bits--------
#bit CCP1X =0x17.5
#bit CCP1Y =0x17.4
#bit CCP1M3 =0x17.3
#bit CCP1M2 =0x17.2
#bit CCP1M1 =0x17.1
#bit CCP1M0 =0x17.0

//---------------RCSTA bits-------------------

#bit SPEN =0x18.7
#bit RX9 =0x18.6
#bit SREN =0x18.5
#bit CREN =0x18.4
#bit ADDEN =0x18.3
#bit FERR =0x18.2
#bit OERR =0x18.1
#bit RX9D =0x18.0

//-----------------------CCP2CON bits----------

#bit CCP2X =0x1D.5
#bit CCP2Y =0x1D.4
#bit CCP2M3 =0x1D.3
#bit CCP2M2 =0x1D.2
#bit CCP2M1 =0x1D.1
#bit CCP2M0 =0x1D.0

//----- ADCON0 Bits --------------------------------------------------------
#bit ADCS1 =0x1F.7
#bit ADCS0 =0x1F.6
#bit CHS2 =0x1F.5 
#bit CHS1 =0x1F.4
#bit CHS0 =0x1F.3
#bit ADGO =0x1F.2
#bit ADON =0x1F.0

//----- OPTION_reg Bits --------------------------------------------------------

#bit RBPU =0x81.7 
#bit INTEDG =0x81.6 
#bit T0CS =0x81.5 
#bit T0SE =0x81.4 
#bit PSA =0x81.3 
#bit PS2 =0x81.2 
#bit PS1 =0x81.1 
#bit PS0 =0x81.0 

//------------------TRISA bits---------------------------

#bit TRISA5 =0x85.5
#bit TRISA4 =0x85.4
#bit TRISA3 =0x85.3
#bit TRISA2 =0x85.2
#bit TRISA1 =0x85.1 
#bit TRISA0 =0x85.0

//-----------------TRISB bits-----------------------------

#bit TRISB7 =0x86.7
#bit TRISB6 =0x86.6 
#bit TRISB5 =0x86.5
#bit TRISB4 =0x86.4 
#bit TRISB3 =0x86.3
#bit TRISB2 =0x86.2
#bit TRISB1 =0x86.1 
#bit TRISB0 =0x86.0 

//----------------TRISC bits-------------------

#bit TRISC7 =0x87.7
#bit TRISC6 =0x87.6
#bit TRISC5 =0x87.5 
#bit TRISC4 =0x87.4
#bit TRISC3 =0x87.3
#bit TRISC2 =0x87.2 
#bit TRISC1 =0x87.1
#bit TRISC0 =0x87.0

#bit TRISD7 =0x88.7
#bit TRISD6 =0x88.6
#bit TRISD5 =0x88.5 
#bit TRISD4 =0x88.4
#bit TRISD3 =0x88.3
#bit TRISD2 =0x88.2 
#bit TRISD1 =0x88.1
#bit TRISD0 =0x88.0

#bit TRISE2 =0x89.2 
#bit TRISE1 =0x89.1
#bit TRISE0 =0x89.0

//----- PIE1 Bits ----------------------------------------------------------

#bit PSPIE =0x8C.7
#bit ADIE =0x8C.6
#bit RCIE =0x8C.5 
#bit TXIE =0x8C.4 
#bit SSPIE =0x8C.3
#bit CCP1IE =0x8C.2 
#bit TMR2IE =0x8C.1
#bit TMR1IE =0x8C.0

//----- PIE2 Bits -----------------------------------------------------

#bit CMIE =0x8D.6
#bit EEIE =0x8D.4
#bit BCLIE =0x8D.3
#bit CCP2IE =0x8D.0

//----- PCON Bits ----------------------------------------------------------

#bit POR =0x8E.1
#bit BOD =0x8E.0

//-----------SSPCON2 bits---------------------------------------------

#bit GCEN =0x91.7
#bit ACKSTAT =0x91.6
#bit ACKDT =0x91.5 
#bit ACKEN =0x91.4
#bit RCEN =0x91.3 
#bit PEN =0x91.2
#bit RSEN =0x91.1
#bit SEN =0x91.0 

//---------------------SSPSTAT bits------------------------

#bit STAT_SMP =0x94.7
#bit STAT_CKE =0x94.6
#bit STAT_DA =0x94.5
#bit STAT_P =0x94.4
#bit STAT_S =0x94.3
#bit STAT_RW =0x94.2
#bit STAT_UA =0x94.1
#bit STAT_BF =0x94.0

//----------------TXSTA bits-----------------

#bit CSRC =0x98.7
#bit TX9 =0x98.6
#bit TXEN =0x98.5 
#bit SYNC =0x98.4
#bit BRGH =0x98.2
#bit TRMT =0x98.1
#bit TX9D =0x98.0

//--------------ADCON1 bits---------------

#bit ADFM =0x9F.7
#bit ADCS2 =0x9F.6
#bit PCFG3 =0x9F.3
#bit PCFG2 =0x9F.2
#bit PCFG1 =0x9F.1 
#bit PCFG0 =0x9F.0

//-----------EECON1 bits----------

#bit EEPGD =0x018C.7
#bit WRERR =0x018C.3
#bit WREN =0x018C.2 
#bit WR =0x018C.1
#bit RD =0x018C.0

//!const unsigned char Code7Seg_duong[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
//!const unsigned char Code7Seg_am[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0xFF};
