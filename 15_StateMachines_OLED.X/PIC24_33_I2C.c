/*******************************************************************************
 * File: PIC24_PIC33_I2C.c
 * Author: Armstrong Subero (original Author unknown stated as "user")
 * PIC: 24FJ128GB204 @ 32 MHz, 3.3v
 * Compiler: XC16 (Pro) (v1.31, MPLAX X v3.55)
 * Program Version: 1.1
 *                * Added comments
 *                * Added intermediate level functions
 *                * Modified to work on PIC24FJ128GB204
 *                * Modified to use I2C1 module
 *                * Changed types
 *                
 * Program Description: This Program allows usage of I2C on PIC24 and dsPIC33
 *                      microcontrollers.
 * 
 * Hardware Description: Standard connections as per MCC or PPS
 *                      
 * Created May 8th, 2017, 9:00 PM
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

/*******************************************************************************
 * Includes and defines
 ******************************************************************************/
#include "mcc_generated_files/mcc.h"
#include "PIC24_PIC33_I2C.h"
#include "PIC24FJ128GB204_STD.h"


/*******************************************************************************
 * Function:        unsigned char MasterWriteI2C1(unsigned char data_out)
 *
 * PreCondition:    I2C must have been initialized
 *
 * Input:           Data to be written to I2C1 module
 *
 * Output:          Negative number on I2C collision
 *
 * Overview:        An intermediate library function that writes to the I2C1 
 *                  module
 * 
 * Usage:           MasterWriteI2C1(0x00);
 *
 * Note:            None
 ******************************************************************************/
char MasterWriteI2C1(unsigned char data_out) 
{ 
   I2C1TRN = data_out; 
   if(I2C1STATbits.IWCOL)        /* If write collision occurs,return -1 */ 
       return -1; 
   else 
   { 
       while(I2C1STATbits.TRSTAT);   // wait until write cycle is complete 
       I2C1_IDLE();                  // ensure module is idle 
       if ( I2C1STATbits.ACKSTAT )   // test for ACK condition received 
     return ( -2 ); 
    else return ( 0 );              // if WCOL bit is not set return non-negative # 
   } 
} 


/*******************************************************************************
 * Function:        char MasterReadI2C1(void)
 *
 * PreCondition:    I2C must have been initialized
 *
 * Input:           None
 *
 * Output:          Data read via I2C
 *
 * Overview:        An intermediate library function that reads from the I2C1
 *                  module
 * 
 * Usage:           MasterWriteI2C1(0x00);
 *
 * Note:            None
 ******************************************************************************/
char MasterReadI2C1(void)
{
    I2C1CON1bits.RCEN = 1;
    while(I2C1CON1bits.RCEN);
    I2C1STATbits.I2COV = 0;
    return(I2C1RCV);
}

/******************************************************************************/
void I2C1_INIT()
{
    I2C1BRG  =    141;     //400Khz
    I2C1STAT = 0x0000;
    I2C1CON1bits.I2CSIDL  =   0;
    I2C1CON1bits.SCLREL   =   0;
    I2C1CON1bits.A10M     =   0;
    I2C1CON1bits.DISSLW   =   0;
    I2C1CON1bits.SMEN     =   0;
    I2C1CON1bits.GCEN     =   0;
    I2C1CON1bits.STREN    =   0;
    I2C1CON1bits.ACKDT    =   0;
    I2C1CON1bits.ACKEN    =   0;
    I2C1CON1bits.RCEN     =   0;
    I2C1CON1bits.PEN      =   0;
    I2C1CON1bits.RSEN     =   0;
    I2C1CON1bits.SEN      =   0;
    I2C1CON1bits.I2CEN    =   1;
}

/******************************************************************************/
void I2C1_IDLE(void)
{
    // Wait until I2C Bus is Inactive
    uint8_t exit;
    while(1)
    {
        exit = 1;
        if(I2C1STATbits.IWCOL) I2C1STATbits.IWCOL=0;
        if(I2C1CON1bits.SEN) exit = 0;
        if(I2C1CON1bits.PEN) exit = 0;
        if(I2C1CON1bits.RCEN) exit = 0;
        if(I2C1CON1bits.RSEN) exit = 0;
        if(I2C1CON1bits.ACKEN) exit = 0;
        if(I2C1STATbits.TRSTAT) exit = 0;
        if(exit) break;
    }
    Nop();
}

/*******************************************************************************/
void I2C1_Write(uint8_t devAddr,uint16_t regAddr,uint8_t data)
{
    I2C1_IDLE();
    I2C1CON1bits.SEN = 1;
    while (I2C1CON1bits.SEN);
    IFS1bits.MI2C1IF = 0;
    
    MasterWriteI2C1(devAddr|0);
    MasterWriteI2C1(regAddr&0x00FF);
    MasterWriteI2C1(data);

    I2C1CON1bits.PEN = 1;
    while(I2C1CON1bits.PEN);                     
    IFS1bits.MI2C1IF = 0;
    __delay_ms(1);
}

/******************************************************************************/
void I2C1_WriteBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data) 
{
    uint8_t b;
    b = I2C1_Read(devAddr, regAddr);
    
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    I2C1_Write(devAddr, regAddr, b);
}

/******************************************************************************/
bool I2C1_WriteBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) 
{
    //      010 value to write
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    // 00011100 mask byte
    // 10101111 original value (sample)
    // 10100011 original & ~mask
    // 10101011 masked | value
    uint8_t b = I2C1_Read(devAddr, regAddr);
    uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    data <<= (bitStart - length + 1); // shift data into correct position
    data &= mask; // zero all non-important bits in data
    b &= ~(mask); // zero all important bits in existing byte
    b |= data; // combine data with existing byte
    I2C1_Write(devAddr, regAddr, b);
    return true;
}

/******************************************************************************/
void I2C1_WriteBytes(uint8_t devAddr,uint8_t regAddr,uint8_t len,uint8_t *dptr)
{
    while(len--)
    {
        I2C1_Write(devAddr,regAddr,*dptr++);
    }
}

/******************************************************************************/
void I2C1_WriteWord(uint8_t devAddr,uint8_t regAddr,uint16_t data)
{
    I2C1_Write(devAddr, regAddr++, (data>>8)&0xFF);
    I2C1_Write(devAddr, regAddr, data&0xFF);
}

/******************************************************************************/
uint8_t I2C1_Read(uint8_t devAddr,uint16_t regAddr)
{
    uint8_t read_data=0;

    I2C1CON1bits.SEN = 1;
    while (I2C1CON1bits.SEN);
    IFS1bits.MI2C1IF = 0; 
    
    MasterWriteI2C1(devAddr|0);
    MasterWriteI2C1(regAddr&0x00FF);
    
    I2C1CON1bits.RSEN = 1;
    while(I2C1CON1bits.RSEN);
    IFS1bits.MI2C1IF = 0;  
    
    MasterWriteI2C1(devAddr|1);
    read_data = MasterReadI2C1();

    I2C1CON1bits.PEN = 1;
    while(I2C1CON1bits.PEN);
    IFS1bits.MI2C1IF = 0;
    return  read_data;
}

/******************************************************************************/
uint8_t I2C1readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, 
        uint8_t *data) 
{
    uint8_t b=0;
    uint8_t count = I2C1_Read(devAddr, regAddr);
    *data = b & (1 << bitNum);
    return count;
}

/******************************************************************************/
uint8_t I2C1readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, 
        uint8_t length, uint8_t *data)
{
    // 01101001 read byte
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    //    010   masked
    //   -> 010 shifted
    uint8_t count=0, b=0;
    b = I2C1_Read(devAddr, regAddr);
    uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    b &= mask;
    b >>= (bitStart - length + 1);
    *data = b;
    return count;
}

/******************************************************************************/
void I2C1readBytes(uint8_t devAddr,uint8_t regAddr,uint8_t len,uint8_t *dptr)
{
    while(len--)
    {
        *dptr = I2C1_Read(devAddr,regAddr);
    }
}

/*******************************************************************************
* Function:        StartI2C1()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates an I2C Start Condition
*
* Note:			None
*******************************************************************************/
uint8_t StartI2C1(void)
{
	//This function generates an I2C start condition and returns status 
	//of the Start.

	I2C1CON1bits.SEN = 1;		//Generate Start COndition
	while (I2C1CON1bits.SEN);	//Wait for Start COndition
	//return(I2C1STATbits.S);	//Optionally return status
    return 0;
}


/*******************************************************************************
* Function:        RestartI2C1()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates a restart condition and optionally returns status
*
* Note:			None
*******************************************************************************/
uint8_t RestartI2C1(void)
{
	//This function generates an I2C Restart condition and returns status 
	//of the Restart.

	I2C1CON1bits.RSEN = 1;		//Generate Restart		
	while (I2C1CON1bits.RSEN);	//Wait for restart	
	//return(I2C1STATbits.S);	//Optional - return status
    return 0;
}


/*******************************************************************************
* Function:        StopI2C1()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates a bus stop condition
*
* Note:			None
*******************************************************************************/
uint8_t StopI2C1(void)
{
	//This function generates an I2C stop condition and returns status 
	//of the Stop.

	I2C1CON1bits.PEN = 1;		//Generate Stop Condition
	while (I2C1CON1bits.PEN);	//Wait for Stop
	//return(I2C1STATbits.P);	//Optional - return status
    return 0;
}


/*******************************************************************************
* Function:        WriteI2C1()
*
* Input:		Byte to write.
*
* Output:		None.
*
* Overview:		Writes a byte out to the bus
*
* Note:			None
*******************************************************************************/
uint8_t WriteI2C1(unsigned char byte)
{
	//This function transmits the byte passed to the function
	//while (I2C1STATbits.TRSTAT);	//Wait for bus to be idle
	I2C1TRN = byte;					//Load byte to I2C1 Transmit buffer
	while (I2C1STATbits.TBF);		//wait for data transmission
    return 0;
}


/*********************************************************************
* Function:        IdleI2C1()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Waits for bus to become Idle
*
* Note:			None
********************************************************************/
uint8_t IdleI2C1(void)
{
	while (I2C1STATbits.TRSTAT);		//Wait for bus Idle
    return 0;
}


/*********************************************************************
* Function:        LDByteWriteI2C1()
*
* Input:		Control Byte, 8 - bit address, data.
*
* Output:		None.
*
* Overview:		Write a byte to low density device at address LowAdd
*
* Note:			None
********************************************************************/
uint8_t LDByteWriteI2C1(unsigned char ControlByte, unsigned char LowAdd, unsigned char data)
{
	uint8_t ErrorCode;

	IdleI2C1();						//Ensure Module is Idle
	StartI2C1();						//Generate Start COndition
	WriteI2C1(ControlByte);			//Write Control byte
	IdleI2C1();

	ErrorCode = ACKStatus1();		//Return ACK Status
	
	WriteI2C1(LowAdd);				//Write Low Address
	IdleI2C1();

	ErrorCode = ACKStatus1();		//Return ACK Status

	WriteI2C1(data);					//Write Data
	IdleI2C1();
	StopI2C1();						//Initiate Stop Condition
//	EEAckPolling(ControlByte);		//Perform ACK polling
	return(ErrorCode);
}


/*********************************************************************
* Function:        LDByteReadI2C()
*
* Input:		Control Byte, Address, *Data, Length.
*
* Output:		None.
*
* Overview:		Performs a low density read of Length bytes and stores in *Data array
*				starting at Address.
*
* Note:			None
********************************************************************/
uint8_t LDByteReadI2C(unsigned char ControlByte, unsigned char Address, unsigned char *Data, unsigned char Length)
{
	IdleI2C1();					//wait for bus Idle
	StartI2C1();					//Generate Start Condition
	WriteI2C1(ControlByte);		//Write Control Byte
	IdleI2C1();					//wait for bus Idle
	WriteI2C1(Address);			//Write start address
	IdleI2C1();					//wait for bus Idle

	RestartI2C1();				//Generate restart condition
	WriteI2C1(ControlByte | 0x01);	//Write control byte for read
	IdleI2C1();					//wait for bus Idle

	getsI2C1(Data, Length);		//read Length number of bytes
	NotAckI2C11();				//Send Not Ack
	StopI2C1();					//Generate Stop
    return 0;
}

/*********************************************************************
* Function:        LDPageWriteI2C1()
*
* Input:		ControlByte, LowAdd, *wrptr.
*
* Output:		None.
*
* Overview:		Write a page of data from array pointed to be wrptr
*				starting at LowAdd
*
* Note:			LowAdd must start on a page boundary
********************************************************************/
uint8_t LDPageWriteI2C1(unsigned char ControlByte, unsigned char LowAdd, unsigned char *wrptr,unsigned char len)
{
	IdleI2C1();					//wait for bus Idle
	StartI2C1();					//Generate Start condition
	WriteI2C1(ControlByte);		//send controlbyte for a write
	IdleI2C1();					//wait for bus Idle
	WriteI2C1(LowAdd);			//send low address
	IdleI2C1();					//wait for bus Idle
	putstringI2C1(wrptr,len);		//send data
	IdleI2C1();					//wait for bus Idle
	StopI2C1();					//Generate Stop
	return(0);
}

/*********************************************************************
* Function:        LDSequentialReadI2C()
*
* Input:		ControlByte, address, *rdptr, length.
*
* Output:		None.
*
* Overview:		Performs a sequential read of length bytes starting at address
*				and places data in array pointed to by *rdptr
*
* Note:			None
********************************************************************/
uint8_t LDSequentialReadI2C(unsigned char ControlByte, unsigned char address, unsigned char *rdptr, unsigned char length)
{
    if(length)
    {
        IdleI2C1();						//Ensure Module is Idle
        StartI2C1();						//Initiate start condition
        WriteI2C1(ControlByte);			//write 1 byte
        IdleI2C1();						//Ensure module is Idle
        WriteI2C1(address);				//Write word address
        IdleI2C1();						//Ensure module is idle
        RestartI2C1();					//Generate I2C Restart Condition
        WriteI2C1(ControlByte | 0x01);	//Write 1 byte - R/W bit should be 1 for read
        IdleI2C1();						//Ensure bus is idle
        getsI2C1(rdptr, length);			//Read in multiple bytes
        NotAckI2C11();					//Send Not Ack
        StopI2C1();						//Send stop condition
    }
	return(0);
}

/*********************************************************************
* Function:        ACKStatus1()
*
* Input:		None.
*
* Output:		Acknowledge Status.
*
* Overview:		Return the Acknowledge status on the bus
*
* Note:			None
********************************************************************/
uint8_t ACKStatus1(void)
{
	return (!I2C1STATbits.ACKSTAT);		//Return Ack Status
}


/*********************************************************************
* Function:        NotAckI2C11()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates a NO Acknowledge on the Bus
*
* Note:			None
********************************************************************/
uint8_t NotAckI2C11(void)
{
	I2C1CON1bits.ACKDT = 1;			//Set for NotACk
	I2C1CON1bits.ACKEN = 1;
	while(I2C1CON1bits.ACKEN);		//wait for ACK to complete
	I2C1CON1bits.ACKDT = 0;			//Set for NotACk
    return 0;
}


/*********************************************************************
* Function:        AckI2C1()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates an Acknowledge.
*
* Note:			None
********************************************************************/
uint8_t AckI2C1(void)
{
	I2C1CON1bits.ACKDT = 0;			//Set for ACk
	I2C1CON1bits.ACKEN = 1;
	while(I2C1CON1bits.ACKEN);		//wait for ACK to complete
    return 0;
}


/*********************************************************************
* Function:       getsI2C1()
*
* Input:		array pointer, Length.
*
* Output:		None.
*
* Overview:		read Length number of Bytes into array
*
* Note:			None
********************************************************************/
uint8_t getsI2C1(unsigned char *rdptr, unsigned char Length)
{
	while (Length --)
	{
		*rdptr++ = getI2C1();		//get a single byte
		
		if(I2C1STATbits.BCL)		//Test for Bus collision
		{
			return(-1);
		}

		if(Length)
		{
			AckI2C1();				//Acknowledge until all read
		}
	}
	return(0);
}


/*********************************************************************
* Function:        getI2C1()
*
* Input:		None.
*
* Output:		contents of I2C1 receive buffer.
*
* Overview:		Read a single byte from Bus
*
* Note:			None
********************************************************************/
uint8_t getI2C1(void)
{
	I2C1CON1bits.RCEN = 1;			//Enable Master receive
	Nop();
	while(!I2C1STATbits.RBF);		//Wait for receive bufer to be full
	return(I2C1RCV);				//Return data in buffer
}


/*********************************************************************
* Function:        putstringI2C1()
*
* Input:		pointer to array.
*
* Output:		None.
*
* Overview:		writes a string of data upto PAGESIZE from array
*
* Note:			None
********************************************************************/
uint8_t putstringI2C1(unsigned char *wrptr,uint8_t len)
{
	unsigned char x;

	for(x = 0; x < len; x++)		//Transmit Data Until Pagesize
	{	
		if(WriteI2C1(*wrptr))			//Write 1 byte
		{
			return(-3);				//Return with Write Collision
		}
		IdleI2C1();					//Wait for Idle bus
		if(I2C1STATbits.ACKSTAT)
		{
			return(-2);				//Bus responded with Not ACK
		}
		wrptr++;
	}
	return(0);
}
//------------------------------------------------------------------------------


