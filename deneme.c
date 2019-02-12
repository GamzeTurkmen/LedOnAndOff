/*
 * File:   main.c
 * Author: Khaled_Magdy
 * For More Information. Visit My Website @ DeepBlueMbedded.com
 */

// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000

float calc_dist(void);

void main(void) {
    // Create Distance Variable (char: 0->255)
    unsigned char dist=0;
    // Set PORTB To Be Output Port (All The 8 Pins)
    TRISB = 0x00;
    // Set PORTB To Be LOW For initial State
    PORTB = 0x00;
    // Set RC2 To Be Output Pin  ( Trigger )
    TRISC2 = 0;
    // Set RC3 To Be Input Pin    ( Echo )
    TRISC3 = 1;
    //--[ Configure Timer Module To Operate in Timer Mode ]--
    // Clear The Pre-Scaler Select Bits
    T1CKPS0=0;
    T1CKPS1=0;
    // Choose The Local Clock As Clock Source
    TMR1CS=0;
    // Write The System's Main Routine !
    PORTD=0X00;
    TRISE0 = 0;               /* Configure RE0 as o/p              */ 
    TRISB4 = 1;
    while(1)
    {
         
        if(RB5==0)               /* If SW3 is pressed, RB5 is low     */
  {
         RE0 = 1; 
       
            
        dist = calc_dist()/5;
        switch(dist)
        {
            case 1:
                PORTB=0X01; 
             
                break;
                
            case 2:
                PORTB=0X05;
                
                break; 
            case 3:
                PORTB=0X07;
                
                break;
            case 4:
                PORTB=0X0F;
               
                break;
            default :    
                PORTB=0X00;
        }
          __delay_ms(100);              
        }
        else  if(RB5 == 1)       /* If SW3 is released, RB5 is high   */
         {  
           RE0 = 0;
        }
    }
  
    return;
    
}
// Definition Of The calc_dist() Function
float calc_dist(void)
{
    float  distance=0; // For Precision Critical Situations, You'll have to make it a ((Floating-Point)) variable
    TMR1=0;
    RC2=1;
    __delay_us(10);
    RC2=0;
    while(!RC3);
    TMR1ON=1;
    while(RC3);
    TMR1ON=0;
    distance = (TMR1/58.82); // Note: fractions will be discarded. But it's OK in our basic tutorial
    
         return distance;
    
}