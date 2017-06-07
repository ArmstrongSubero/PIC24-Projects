/*******************************************************************************
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 24FJ128GB204 @ 32 MHz, 3.3v
 * Program: 16_FreeRTOS_Bare
 * Compiler: XC16 (Pro) (v1.31, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 * Program Description: This Program Allows PIC24FJ128GB204 to use FreeRTOS
 *                      and contains two main tasks, one task toggles an LED
 *                      and the other updates and OLED. The idle task also 
 *                      toggles an LED.
 * 
 * Hardware Description: 
 *                     An SSD1306 is connected to the microcontroller as per 
 *                     MCC generated code. 
 *                     SCL -> A0
 *                     SDA -> A1
 *                     4.7 k pullup resistors are used on the communication 
 *                     lines. An LED is connected to RA7 and another to RB9
 * 
 * Created May 10th, 2017, 4:00 PM
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
/* Standard includes. */
#include "PIC24_PIC33_I2C.h"
#include "PIC24FJ128GB204_STD.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "SSD1306_OLED.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
void prvSetupHardware();            // Setup Hardware

void vTask1(void *pvParameters);    // LED Task
void vTask2(void *pvParameters);    // OLED Task

void vApplicationIdleHook( void );  // IDLE Hook

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
#define MAIN_TASKS_STACK_SIZE			( configMINIMAL_STACK_SIZE * 2 )
#define MIN_TASKS_STACK_SIZE            ( configMINIMAL_STACK_SIZE )


#define SUPER_PRIORITY  4
#define HIGH_PRIORITY   3
#define MED_PRIORITY    2
#define LOW_PRIORITY    1
#define IDLE_PRIORITY   0

/*******************************************************************************
 * Function:        int main(void)
 *
 * PreCondition:    STD FreeRTOS requirements
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Program Entry Point
 * 
 * Usage:           None
 *
 * Note:            None
 ******************************************************************************/
int main(void)
{
    // Setup hardware 
    prvSetupHardware();
    
    /* ---  APPLICATION TASKS  --- */
    
           /*|---------------------------------------------------------------------------------|
               TaskPtr  TaskName      StackDepth(words)      Parameters     Priority     Handle
           * |---------------------------------------------------------------------------------|*/
    xTaskCreate(vTask1, "Task 1",     MIN_TASKS_STACK_SIZE,    NULL,      LOW_PRIORITY,   NULL);
    xTaskCreate(vTask2, "Task 2",     MAIN_TASKS_STACK_SIZE,   "Count: ",  SUPER_PRIORITY, NULL);
    
    // Start scheduler
    vTaskStartScheduler();
    
    /* ---   NOT REACHABLE --- */
    // Execution only reaches here due to insufficient heap
    for(;;);
    
    return 0;
}

/*******************************************************************************
 * Function:        void vTask1(void *pvParameters)
 *
 * PreCondition:    STD FreeRTOS requirements
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Toggles an LED at specific rate
 * 
 * Usage:           None
 *
 * Note:            None
 ******************************************************************************/
void vTask1(void *pvParameters)
{
    TickType_t xLastWakeTime;
    
    // Initialize with current tick count, updated after from vTaskDelayUntil()
    xLastWakeTime = xTaskGetTickCount();
    
    // implement in infinite loop
    for(;;)
    {
        // Toggle LED
        LATAbits.LATA7 = ~LATAbits.LATA7;
        
        // Execute every 500 ms exactly.
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(500));
    }
    
}

/*******************************************************************************
 * Function:        void vTask2(void *pvParameters)
 *
 * PreCondition:    STD FreeRTOS requirements
 *
 * Input:           *pcTaskName
 *
 * Output:          None
 *
 * Overview:        Increments an Integer and displays parameters passed on
 *                  OLED
 * 
 * Usage:           None
 *
 * Note:            None
 ******************************************************************************/
void vTask2(void *pvParameters)
{
    char *pcTaskName;
    TickType_t xLastWakeTime;
    
    // parameters to be passed
    pcTaskName = (char *) pvParameters;
    
    // Volatile to ensure not optimized
    volatile uint32_t count = 0;
    
    // Initialize with current tick count, updated after from vTaskDelayUntil()
    xLastWakeTime = xTaskGetTickCount();
    
    // implement in infinite loop
    for(;;)
    {
        
        // Write Text Passed as Parameters
        SSD1306_Write_Text    ( 0, 0, pcTaskName, 1, WHITE);
        // Write Count integer
        SSD1306_Write_Integer ( 0, 10, count, 1);
        // Write to OLED
        SSD1306_Write_Buffer();
        
        // Increment Count
        count++;
        
        // Clear Display
        SSD1306_Clear_Display();
        
        // Execute every second exactly.
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}


/*******************************************************************************
 * Function:        void prvSetupHardware(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Sets up hardware that is to be used by RTOS
 * 
 * Usage:           None
 *
 * Note:            None
 ******************************************************************************/

void prvSetupHardware(void)
{
    /////////////////////////
    //initialize the device
    ///////////////////////
     SYSTEM_Initialize();
     __delay_ms(1000);
    
     ///////////////////////
     // Initialize SSD1306
     //////////////////////
     SSD1306_INIT();
     __delay_ms(1000);
    
     // Write startup logo
     SSD1306_Write_Buffer();
     __delay_ms(2000);
     
     // Clear display
     SSD1306_Clear_Display();
    
     ////////////////////
     // Configure Ports
     ///////////////////
     
     // Configure LED
     TRISAbits.TRISA7 = 0;
     
     // Configure heartbeat LED for IDLE
     TRISBbits.TRISB9 = 0;
}

/*******************************************************************************
 * Function:        void vApplicationIdleHook(void)
 *
 * PreCondition:    configUSE_IDLE_HOOK in FreeTROSconfig.h must be set to 1
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        This task is called when the CPU has no tasks to run
 * 
 * Usage:           None
 *
 * Note:            Task MUST take no parameters and return void also must not
 *                  call blocking functions or attempt to suspend.
 ******************************************************************************/
void vApplicationIdleHook(void)
{
    // Toggle LED
    LATBbits.LATB9 = ~LATBbits.LATB9;
}
