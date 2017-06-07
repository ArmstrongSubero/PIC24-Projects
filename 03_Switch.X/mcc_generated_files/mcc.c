/**
  @Generated MPLAB(c) Code Configurator Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - pic24-dspic-pic32mm : v1.25
        Device            :  PIC24FJ128GB204
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.26
        MPLAB             :  MPLAB X 3.45
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

// Configuration bits: selected in the GUI

// CONFIG4
#pragma config DSWDTPS = DSWDTPS1F    // Deep Sleep Watchdog Timer Postscale Select bits->1:68719476736 (25.7 Days)
#pragma config DSWDTOSC = LPRC    // DSWDT Reference Clock Select->DSWDT uses LPRC as reference clock
#pragma config DSBOREN = ON    // Deep Sleep BOR Enable bit->DSBOR Enabled
#pragma config DSWDTEN = ON    // Deep Sleep Watchdog Timer Enable->DSWDT Enabled
#pragma config DSSWEN = ON    // DSEN Bit Enable->Deep Sleep is controlled by the register bit DSEN
#pragma config PLLDIV = NODIV    // USB 96 MHz PLL Prescaler Select bits->Oscillator input used directly (4 MHz input)
#pragma config I2C1SEL = DISABLE    // Alternate I2C1 enable bit->I2C1 uses SCL1 and SDA1 pins
#pragma config IOL1WAY = ON    // PPS IOLOCK Set Only Once Enable bit->Once set, the IOLOCK bit cannot be cleared

// CONFIG3
#pragma config WPFP = WPFP127    // Write Protection Flash Page Segment Boundary->Page 127 (0x1FC00)
#pragma config SOSCSEL = ON    // SOSC Selection bits->SOSC circuit selected
#pragma config WDTWIN = PS25_0    // Window Mode Watchdog Timer Window Width Select->Watch Dog Timer Window Width is 25 percent
#pragma config PLLSS = PLL_FRC    // PLL Secondary Selection Configuration bit->PLL is fed by the on-chip Fast RC (FRC) oscillator
#pragma config BOREN = ON    // Brown-out Reset Enable->Brown-out Reset Enable
#pragma config WPDIS = WPDIS    // Segment Write Protection Disable->Disabled
#pragma config WPCFG = WPCFGDIS    // Write Protect Configuration Page Select->Disabled
#pragma config WPEND = WPENDMEM    // Segment Write Protection End Page Select->Write Protect from WPFP to the last page of memory

// CONFIG2
#pragma config POSCMD = NONE    // Primary Oscillator Select->Primary Oscillator Disabled
#pragma config WDTCLK = LPRC    // WDT Clock Source Select bits->WDT uses LPRC
#pragma config OSCIOFCN = OFF    // OSCO Pin Configuration->OSCO/CLKO/RA3 functions as CLKO (FOSC/2)
#pragma config FCKSM = CSDCMD    // Clock Switching and Fail-Safe Clock Monitor Configuration bits->Clock switching and Fail-Safe Clock Monitor are disabled
#pragma config FNOSC = FRCPLL    // Initial Oscillator Select->Fast RC Oscillator with PLL module (FRCPLL)
#pragma config ALTRB6 = APPEND    // Alternate RB6 pin function enable bit->Append the RP6/ASCL1/PMPD6 functions of RB6 to RA1 pin functions
#pragma config ALTCMPI = CxINC_RB    // Alternate Comparator Input bit->C1INC is on RB13, C2INC is on RB9 and C3INC is on RA0
#pragma config WDTCMX = WDTCLK    // WDT Clock Source Select bits->WDT clock source is determined by the WDTCLK Configuration bits
#pragma config IESO = ON    // Internal External Switchover->Enabled

// CONFIG1
#pragma config WDTPS = PS32768    // Watchdog Timer Postscaler Select->1:32768
#pragma config FWPSA = PR128    // WDT Prescaler Ratio Select->1:128
#pragma config WINDIS = OFF    // Windowed WDT Disable->Standard Watchdog Timer
#pragma config FWDTEN = OFF    // Watchdog Timer Enable->WDT disabled in hardware; SWDTEN bit disabled
#pragma config ICS = PGx1    // Emulator Pin Placement Select bits->Emulator functions are shared with PGEC1/PGED1
#pragma config LPCFG = OFF    // Low power regulator control->Disabled - regardless of RETEN
#pragma config GWRP = OFF    // General Segment Write Protect->Write to program memory allowed
#pragma config GCP = OFF    // General Segment Code Protect->Code protection is disabled
#pragma config JTAGEN = OFF    // JTAG Port Enable->Disabled

#include "mcc.h"

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    INTERRUPT_Initialize();
    UART1_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // CF no clock failure; NOSC FRCPLL; SOSCEN disabled; POSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
    __builtin_write_OSCCONL((uint8_t) (0x0100 & 0x00FF));
    // CPDIV 1:1; PLLEN enabled; RCDIV FRC/2; DOZE 1:8; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3120;
    // STOR disabled; STORPOL Interrupt when STOR is 1; STSIDL disabled; STLPOL Interrupt when STLOCK is 1; STLOCK disabled; STSRC SOSC; STEN disabled; TUN Center frequency; 
    OSCTUN = 0x0000;
    // ROEN disabled; ROSEL FOSC; ROSIDL disabled; ROSWEN disabled; ROOUT disabled; ROSLP disabled; 
    REFOCONL = 0x0000;
    // RODIV 0; 
    REFOCONH = 0x0000;
    // ROTRIM 0; 
    REFOTRIML = 0x0000;
    // WDTO disabled; TRAPR disabled; SLEEP disabled; BOR disabled; DPSLP disabled; CM disabled; SWR disabled; SWDTEN disabled; EXTR disabled; POR disabled; IDLE disabled; IOPUWR disabled; VREGS disabled; 
    RCON = 0x0000;
}

/**
 End of File
*/