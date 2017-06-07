/*******************************************************************************
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 24FJ128GB204 @ 32 MHz, 3.3v
 * Program: 11_USB_CDC
 * Compiler: XC16 (Pro) (v1.31, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 * Program Description: This Program Allows PIC24FJ128GB204 to communicate via 
 *                      USB CDC
 * 
 * Hardware Description: 
 *                      D+ (Green)  -> RB10
 *                      D- (White)  -> RB11
 * 
 * A 2.2 uF cap is connected to VUSB3V3. An external 4MHz crystal is used and 
 * connected to pins 30 and 31. USBID is connected via a 1k resistor to ground.
 * VBUS is connected at the center of a 1k, 100k voltage divider.  
 *                
 * Created May 6th, 2017, 2:40 PM
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
#include "mcc_generated_files/usb/usb_device_cdc.h"
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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
         /* If the USB device isn't configured yet, we can't really do anything
          * else since we don't have a host to talk to.  So jump back to the
          * top of the while loop. */
         if( USBGetDeviceState() < CONFIGURED_STATE )
         {
             continue;
         }
         
         /* If we are currently suspended, then we need to see if we need to
        * issue a remote wakeup.  In either case, we shouldn't process any
        * keyboard commands since we aren't currently communicating to the host
        * thus just continue back to the start of the while loop. */
        if( USBIsDeviceSuspended()== true )
        {
            continue;
        }
    
        if( USBUSARTIsTxTrfReady() == true)
        {
            putrsUSBUSART("Hello From USB\r\n");
            __delay_ms(1000);
        }
        
        // Add your application code
        CDCTxService();
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
    
    // Setup USB UART
    line_coding.bCharFormat = 0;
    line_coding.bDataBits = 8;
    line_coding.bParityType = 0;
    line_coding.dwDTERate = 9600;
}
