/*******************************************************************************
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 24FJ128GB204 @ 32 MHz, 3.3v
 * Program: 03_Switch
 * Compiler: XC16 (Pro) (v1.31, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 * Program Description: This Program Allows PIC24FJ128GB204 to turn on an LED 
 *                      when a switch is pressed
 * 
 * Hardware Description: 
 *                      LED -> PIN A9
 *                      SW  -> PIN C9
 *                      
 * Created May 3rd, 2017, 1:15 PM
 * 
 *
 * License:
 * 
 * "Copyright (c) 2017 Armstrong Subero ("AUTHORS")"
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the authors appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE "AUTHORS" BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE "AUTHORS"
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE "AUTHORS" SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE "AUTHORS" HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Please maintain this header in its entirety when copying/modifying
 * these files.
 * 
 ******************************************************************************/


/*******************************************************************************
 * Includes and defines
 ******************************************************************************/
#include "PIC24FJ128GB204_STD.h"
#include <stdio.h>
#include "button.h"

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
 void initMain(void);
 
/*******************************************************************************
 * Global Variables
 ******************************************************************************/
#define LED LATAbits.LATA9
 

/*******************************************************************************
 * Function:        int main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Main program entry point
 * 
 * Usage:           None
 *
 * Note:            None
 ******************************************************************************/
 
 int main(void)
 {
     initMain();
     
     while(1)
     {
         if (BUTTON_IsPressed(BUTTON_S1))
         {
             // debounce delay
             __delay_ms(100);
             
             if (BUTTON_IsPressed(BUTTON_S1))
             {
                 LED = ON;
                 printf("Button pressed");
             }
         }
         
         else
         {
             LED = OFF;
         }
       
    }
     
     
     return 0;   
 }


/*******************************************************************************
 * Function:        void initMain(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Contains all initializations required to setup main
 * 
 * Usage:           initMain()
 *
 * Note:            None
 ******************************************************************************/
void initMain()
{
    SYSTEM_Initialize();
    
    TRISAbits.TRISA9 = OUTPUT;
    TRISCbits.TRISC9 = INPUT;
     
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    
    RPINR18bits.U1RXR = 0x0007;   //RB7->UART1:U1RX;
    RPOR4bits.RP8R = 0x0003;   //RB8->UART1:U1TX;

    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
}
