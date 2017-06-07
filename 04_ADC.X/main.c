/*******************************************************************************
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 24FJ128GB204 @ 32 MHz, 3.3v
 * Program: 04_ADC
 * Compiler: XC16 (Pro) (v1.31, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 * Program Description: This Program Allows PIC24FJ128GB204 to use ADC module
 * 
 * Hardware Description: 
 *                      RC0 -> POT1
 *                      RC1 -> POT2
 *                      
 * Created May 3rd, 2017, 5:20 PM
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
#include "adc.h"

#define LED LATAbits.LATA9

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
 void initMain(void);
 
/*******************************************************************************
 * Global Variables
 ******************************************************************************/
 uint16_t Pot_1, Pot1_Percent;
 uint16_t Pot_2, Pot2_Percent;

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
     
     // Enable the ADC channels
     ADC_ChannelEnable(ADC_CHANNEL_POTENTIOMETER_1);
     ADC_ChannelEnable(ADC_CHANNEL_POTENTIOMETER_2);
    
    
     while(1)
     {
         // Read pot value
         Pot_1 = ADC_Read10bit(ADC_CHANNEL_POTENTIOMETER_1);
         Pot_2 = ADC_Read10bit(ADC_CHANNEL_POTENTIOMETER_2);
         
         // Read pot value as percentage
         Pot1_Percent = ADC_ReadPercentage(ADC_CHANNEL_POTENTIOMETER_1);
         Pot2_Percent = ADC_ReadPercentage(ADC_CHANNEL_POTENTIOMETER_2);
         
         // Print ADC value
         printf("Pot_1:%d  \tPot_2:%d\n", Pot_1, Pot_2);
         
         // Print ADC percentages
         printf("Pot_1:%d  \tPot_2:%d\n", Pot1_Percent, Pot2_Percent);
         
         // Don't flood the ADC
         __delay_ms(1000);
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
    
    ADC_SetConfiguration(ADC_CONFIGURATION_DEFAULT);
     
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    
    RPINR18bits.U1RXR = 0x0007;   //RB7->UART1:U1RX;
    RPOR4bits.RP8R = 0x0003;   //RB8->UART1:U1TX;

    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
}
