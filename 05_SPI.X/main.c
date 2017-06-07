/*******************************************************************************
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 24FJ128GB204 @ 32 MHz, 3.3v
 * Program: 05_SPI
 * Compiler: XC16 (Pro) (v1.31, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 * Program Description: This Program Allows PIC24FJ128GB204 to use SPI module
 * 
 * Hardware Description: 
 *                      SS   -> RB9
 *                      SCK1 -> RC6
 *                      SD11 -> RC7
 *                      SDO1 -> RC8
 *                      
 * Created May 3rd, 2017, 5:15 PM
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
#include <stdint.h>


/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
void initMain(void);
void digiPot_write(uint8_t i);


// Set chip select high
inline void CS_SetHigh(void)
{
    LATCbits.LATC3 = 1;
}

// Set chip select low
inline void CS_SetLow(void)
{
    LATCbits.LATC3 = 0;
}

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
#define LED         LATAbits.LATA9


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
     
     uint8_t value;
     
     while(1)
     {
         for(value = 0; value <= 127; value++){
         printf("%d\n", value);
         digiPot_write(value);
         __delay_ms(100);
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
    
    SPI1_Initialize();
    
    TRISAbits.TRISA9 = OUTPUT;
    TRISCbits.TRISC3 = OUTPUT;
}

/*******************************************************************************
 * Function:        void digiPot_write(uint8_t i)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Allows a value to be written to the digiPot via SPI
 * 
 * Usage:           digiPot_write(x);
 *
 * Note:            None
 ******************************************************************************/

void digiPot_write(uint8_t i){
    // Set SS Low
    CS_SetLow();
    
    // Slave address
    SPI1_Exchange8bit(0x00);
    
    // Data
    SPI1_Exchange8bit(i);
    
    // Set SS High
    CS_SetHigh();
}