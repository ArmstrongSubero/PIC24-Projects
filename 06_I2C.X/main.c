/*******************************************************************************
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 24FJ128GB204 @ 32 MHz, 3.3v
 * Program: 06_I2C
 * Compiler: XC16 (Pro) (v1.31, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 * Program Description: This Program Allows PIC24FJ128GB204 to use I2C to 
 *                      read an EEPROM. This program uses the MCC generated
 *                      I2C code.
 * 
 * Hardware Description: 
 *                      RA0 -> SDA
 *                      RA1 -> SCL
 *                      
 * Created May 3rd, 2017, 8:10 PM
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
#include "mcc_generated_files/i2c1.h"
#include <I2C.h>

I2C1_MESSAGE_STATUS I2C_Wflag;
I2C1_MESSAGE_STATUS I2C_Rflag;

#define SLAVE_I2C_GENERIC_RETRY_MAX           100
#define SLAVE_I2C_GENERIC_DEVICE_TIMEOUT      50   // define slave timeout 

#define slaveDeviceAddress  0x50   // slave device address

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
 void initMain(void);
 
 
/*******************************************************************************
 * Global Variables
 ******************************************************************************/
#define LED LATAbits.LATA9
 

 /*******************************************************************************
 * Function:        LC164_Read(uint8_t addrlo, uint8_t *pData)
 *
 * PreCondition:    I2C1 must hsve been set up and initialized
 *
 * Input:           Address and data
 *
 * Output:          Status of I2C transmission
 *
 * Overview:        Allows an EEPROM to be read via I2C
 * 
 * Usage:           LC164_Read(0, &temp)
 *
 * Note:            None
 ******************************************************************************/
 
uint8_t LC164_Read(uint8_t addrlo, uint8_t *pData)
{
    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;
    static I2C1_TRANSACTION_REQUEST_BLOCK trb[2];
    
    I2C1_MasterWriteTRBBuild(&trb[0], &addrlo, 1, slaveDeviceAddress);
    I2C1_MasterReadTRBBuild(&trb[1], pData, 1, slaveDeviceAddress);                
    I2C1_MasterTRBInsert(2, &trb[0], &status);
    
    while(status == I2C1_MESSAGE_PENDING);      // blocking

    return (status == I2C1_MESSAGE_COMPLETE); 
} 


/*******************************************************************************
 * Function:        uint8_t LC164_Write(uint8_t addrlo, uint8_t data)
 *
 * PreCondition:    I2C1 must be enabled
 *
 * Input:           Address and Data
 *
 * Output:          I2C Status
 *
 * Overview:        Writes data to EEPROM address
 * 
 * Usage:           LC164_Write(0, temp)
 *
 * Note:            None
 ******************************************************************************/

uint8_t LC164_Write(uint8_t addrlo, uint8_t data)
{
    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;
    static I2C1_TRANSACTION_REQUEST_BLOCK trb[2];
    uint8_t pack[2];
    pack[0] = addrlo;
    pack[1] = data;
    I2C1_MasterWriteTRBBuild(&trb[0], pack, 2, slaveDeviceAddress);
    I2C1_MasterTRBInsert(1, &trb[0], &status);
    
    while(status == I2C1_MESSAGE_PENDING);      // blocking

    return (status == I2C1_MESSAGE_COMPLETE); 
} 


  
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
    
     // variable to be written to I2C
     uint8_t temp;
    
     while(1)
     {
         // Read data at address 0
         if ( LC164_Read(0, &temp)){
             printf("Read: %d", temp);
            __delay_ms(1000);
         }
         // If can be read then nacked
         else{
             printf("Nacked");
             __delay_ms(1000);
        }
         // Add one to value read then rewrite
         if ( LC164_Write(0, temp + 1)){
             printf("Wrote %d", temp+1);
             __delay_ms(1000);
        }
         
         // Else nack
         else{
            printf("Nack write");
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
}

