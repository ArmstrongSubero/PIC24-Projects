/*******************************************************************************
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 24FJ128GB204 @ 32 MHz, 3.3v
 * Program: 07_I2C1
 * Compiler: XC16 (Pro) (v1.31, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 * Program Description: This Program Allows PIC24FJ128GB204 to use I2C module
 *                      with a I2C library modified from a PIC24 support library 
 *                      written by Robert B. Reese and team.
 * 
 * Hardware Description: 
 *                      SDA -> RA0
 *                      RCL -> RA1
 *                      
 * Created May 5th, 2017, 9:04 PM
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
#include "I2Clib.h"

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
 void initMain(void);
 void writeConfigDS1631(uint8_t u8_i);
 void startConversionDS1631();
 int16_t readTempDS1631();
 
/*******************************************************************************
 * Global Variables
 ******************************************************************************/
#define LED LATAbits.LATA9

#define DS1631ADDR 0x90   //DS1631 address with all pins tied low
#define ACCESS_CONFIG 0xAC
#define START_CONVERT 0x51
#define READ_TEMP 0xAA
 
 
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
     
     // Variables for conversion
     int16_t i16_temp;
     float  f_tempC,f_tempF;
     
     writeConfigDS1631(0x0C);    //continuous conversion, 12-bit mode
     startConversionDS1631();    //start conversions
     
     while(1)
     {
         __delay_ms(750);
         i16_temp = readTempDS1631();
         f_tempC = i16_temp;  //convert to floating point
         f_tempC = f_tempC/256;  //divide by precision
         f_tempF = f_tempC*9/5 + 32;
         printf("Temp is: 0x%0X, %4.4f (C), %4.4f (F)\n", i16_temp, (double) f_tempC, (double) f_tempF);
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
}


/*******************************************************************************
 * Function:        void writeConfigDS1631(uint8_t u8_i)
 *
 * PreCondition:    I2C1 Should have been initialized
 *
 * Input:           Configuration
 *
 * Output:          None
 *
 * Overview:        Allows user to configure DS1631
 * 
 * Usage:           initMain()
 *
 * Note:            None
 ******************************************************************************/
void writeConfigDS1631(uint8_t u8_i) {
  write2I2C1(DS1631ADDR, ACCESS_CONFIG, u8_i);
}

/*******************************************************************************
 * Function:        void startConversionDS1631()
 *
 * PreCondition:    I2C1 should have been initialized
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Sends command to start conversion
 * 
 * Usage:           startConversionDS1631()
 *
 * Note:            None
 ******************************************************************************/
void startConversionDS1631() {
  write1I2C1(DS1631ADDR, START_CONVERT);
}

/*******************************************************************************
 * Function:        int16_t readTempDS1631(void)
 *
 * PreCondition:    I2C1 must be initialized
 *
 * Input:           None
 *
 * Output:          Returns current temperature
 *
 * Overview:        Reads the DS1631 temperature sensor and returns current 
 *                  value
 * 
 * Usage:           initMain()
 *
 * Note:            None
 ******************************************************************************/
int16_t readTempDS1631(void) {
  uint8_t u8_lo, u8_hi;
  int16_t i16_temp;
  
  // Read DS1631 address 
  write1I2C1(DS1631ADDR, READ_TEMP);
  read2I2C1 (DS1631ADDR, &u8_hi, &u8_lo);
  i16_temp = u8_hi;
  
  // return temperature
  return ((i16_temp<<8)|u8_lo);
}
