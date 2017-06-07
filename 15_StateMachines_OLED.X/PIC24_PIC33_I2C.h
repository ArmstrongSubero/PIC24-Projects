/*******************************************************************************
 * File: PIC24_PIC33_I2C.h
 * Author: Armstrong Subero (original Author unknown)
 * PIC: 24FJ128GB204 @ 32 MHz, 3.3v
 * Compiler: XC16 (Pro) (v1.31, MPLAX X v3.55)
 * Program Version: 1.1
 *                * Added comments
 *                * Added intermediate level functions
 *                * Modified to work on PIC24FJ128GB204
 *                * Modified to use I2C1 module
 *                * Changed types
 *                
 * Program Description: This Program allows setup for I2C on PIC24 and dsPIC33
 *                      microcontrollers.
 * 
 * Hardware Description: Standard connections as per MCC or PPS
 *                      
 * Created May 8th, 2017, 10:00 PM
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
 * IN NO EVENT SHALL THE "AUTHORS" BE LIABLE TO ANY PARTY for
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE "AUTHORS"
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE "AUTHORS" SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS for A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE "AUTHORS" HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Please maintain this header in its entirety when copying/modifying
 * these files.
 * 
 ******************************************************************************/

#include "PIC24FJ128GB204_STD.h"
#include "mcc_generated_files/mcc.h"
#include <stdint.h>

// Used by writing string to I2C
#define PAGESIZE 16

// General High Level Functions
void I2C1_INIT(void);
void I2C1_IDLE(void);
    
void I2C1_Write(uint8_t devAddr,uint16_t regAddr,uint8_t data);
void I2C1_WriteBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);
bool I2C1_WriteBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) ;
void I2C1_WriteBytes(uint8_t devAddr,uint8_t regAddr,uint8_t len,uint8_t *dptr);
void I2C1_WriteWord(uint8_t devAddr,uint8_t regAddr,uint16_t data);
uint8_t I2C1_Read(uint8_t devAddr,uint16_t regAddr);
uint8_t I2C1readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data);
uint8_t I2C1readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data);
void I2C1readBytes(uint8_t devAddr,uint8_t regAddr,uint8_t len,uint8_t *dptr);
void I2C1_page_Write(unsigned char deviceId,unsigned char address,unsigned char len,unsigned char *dataptr);
void I2C1_page_Read(unsigned char deviceId,unsigned char address,unsigned char len,unsigned char *dataptr);

//High Level Functions for Low Density Devices
uint8_t LDByteReadI2C(unsigned char, unsigned char, unsigned char*, unsigned char);
uint8_t LDByteWriteI2C1(unsigned char, unsigned char, unsigned char);
uint8_t LDPageWriteI2C1(unsigned char, unsigned char , unsigned char *,unsigned char );
uint8_t LDSequentialReadI2C(unsigned char, unsigned char, unsigned char*, unsigned char);

//High Level Functions for High Density Devices
uint8_t HDByteReadI2C(unsigned char, unsigned char, unsigned char, unsigned char*, unsigned char);
uint8_t HDByteWriteI2C1(unsigned char, unsigned char, unsigned char, unsigned char);
uint8_t HDPageWriteI2C1(unsigned char , unsigned char , unsigned char, unsigned char*,unsigned char);
uint8_t HDSequentialReadI2C(unsigned char, unsigned char, unsigned char, unsigned char*, unsigned char);

// Intermediate Level Functions
char MasterWriteI2C1(unsigned char data_out);
char MasterReadI2C1(void);
    
//Low Level Functions
uint8_t IdleI2C1(void);
uint8_t StartI2C1(void);
uint8_t WriteI2C1(unsigned char);
uint8_t StopI2C1(void);
uint8_t RestartI2C1(void);
uint8_t getsI2C1(unsigned char*, unsigned char);
uint8_t NotAckI2C11(void);
uint8_t InitI2C1(void);
uint8_t ACKStatus1(void);
uint8_t getI2C1(void);
uint8_t AckI2C1(void);
uint8_t EEAckPolling(unsigned char);
uint8_t putstringI2C1(unsigned char *,unsigned char );
    
