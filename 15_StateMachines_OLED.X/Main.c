/*******************************************************************************
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 24FJ128GB204 @ 32 MHz, 3.3v
 * Program: 15_StateMachines_SSD1306
 * Compiler: XC16 (Pro) (v1.31, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 * Program Description: This Program Allows PIC24FJ128GB204 to demonstrate 
 *                      SSD1306 library which includes, rectangles, circles,
 *                      lines, text and buttons. The main program is a simple
 *                      function pointer based state machine.
 * 
 * Hardware Description: 
 *                     An SSD1306 is connected to the microcontroller as per 
 *                     MCC generated code. 
 *                     SCL -> A0
 *                     SDA -> A1
 *                     4.7 k pullup resistors are used on the communication 
 *                     lines. 
 * 
 * Created May 9th, 2017, 6:20 PM
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

// Number of states for SM
#define NUM_STATES 4
 
/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
 void initMain(void);

 void SM_STATE_ONE(void);      // Text state
 void SM_STATE_TWO(void);      // Rectangle State
 void SM_STATE_THREE(void);    // Circle state
 void SM_STATE_FOUR(void);     // Number state
 
/*******************************************************************************
 * Global Variables
 ******************************************************************************/
 
 // enum of each state
 typedef enum
 {
     STATE_ONE,
     STATE_TWO,
     STATE_THREE,
     STATE_FOUR
 }StateType;

 // define state machine table structure
 typedef struct
 {
     StateType State;       // Define the command
     void(*func)(void);     // Defines the function to run
 }StateMachineType;
 
// Table that defines valid states of the sm and function to be executed for 
StateMachineType StateMachine[] =
 {
     {STATE_ONE, SM_STATE_ONE},
     {STATE_TWO, SM_STATE_TWO},
     {STATE_THREE, SM_STATE_THREE},
     {STATE_FOUR, SM_STATE_FOUR}
 };

// Store current state of state machine
StateType SM_STATE = STATE_ONE;
 

/*******************************************************************************
 * Function:        void SM_STATE_ONE(void)
 *
 * PreCondition:    Table structure for states should have been initialized
 *                  as well as enum for each state
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        State A demonstrates writing text on the SSD1306
 * 
 * Usage:           None
 *
 * Note:            None
 ******************************************************************************/
void SM_STATE_ONE(void)
{
    SSD1306_Draw_Button(0,  10, 60,  30, "Option 1", 1);
    SSD1306_Draw_Button(62, 10, 126, 30, "Option 2", 0);
    SSD1306_Draw_Button(0,  32, 60,  52, "Option 3", 0);
    SSD1306_Draw_Button(62, 32, 126, 52, "Option 4", 0);
    SSD1306_Write_Buffer();
    __delay_ms(2000);
    
    SSD1306_Clear_Display();
    
    // Scroll right
    SSD1306_Write_Text ( 0, 0, "Scroll Right", 1, WHITE);
    startscrollright(0, 128);
    SSD1306_Write_Buffer();
    __delay_ms(5000);
    stopscroll();
    
    SSD1306_Clear_Display();
    
    // Scroll left
    SSD1306_Write_Text ( 0, 0,  "Scroll Left", 1, WHITE);
    startscrollleft(128, 0);
    SSD1306_Write_Buffer();
    __delay_ms(5000);
    stopscroll();
    
    SSD1306_Clear_Display();
        
    // Scroll diag left
    SSD1306_Write_Text ( 0, 0,  "Scroll Diag Left", 1, WHITE);
    startscrolldiagleft(0, 120);
    SSD1306_Write_Buffer();
    __delay_ms(5000);
    stopscroll();
    
    SSD1306_Clear_Display();
    
    // Scroll diag right
    SSD1306_Write_Text ( 0, 0,  "Scroll Diag Right", 1, WHITE);
    startscrolldiagright(120, 0);
    SSD1306_Write_Buffer();
    __delay_ms(5000);
    stopscroll();
    
    SSD1306_Clear_Display();
    
    // Write text
    SSD1306_Write_Text ( 0,  0, "Text", 1, WHITE);
    SSD1306_Write_Text ( 0, 10, "Text", 2, WHITE);
    SSD1306_Write_Text ( 0, 30, "Text", 3, WHITE);
    SSD1306_Write_Buffer();
    __delay_ms(2000);
    
    SSD1306_Clear_Display();
      
    SM_STATE = STATE_TWO;
}


/*******************************************************************************
 * Function:        void SM_STATE_TWO(void)
 *
 * PreCondition:    Table structure for states should have been initialized
 *                  as well as enum for each state
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        State B demonstrates drawing a rectangle on the SSD1306
 * 
 * Usage:           None
 *
 * Note:            None
 ******************************************************************************/
void SM_STATE_TWO(void)
{
    SSD1306_Draw_Button(0,  10, 60,  30, "Option 1", 0);
    SSD1306_Draw_Button(62, 10, 126, 30, "Option 2", 1);
    SSD1306_Draw_Button(0,  32, 60,  52, "Option 3", 0);
    SSD1306_Draw_Button(62, 32, 126, 52, "Option 4", 0);
    SSD1306_Write_Buffer();
    __delay_ms(1000);
    SSD1306_Clear_Display();
    
    // Demonstrate drawing rectangles
    SSD1306_Write_Text ( 0, 0, "Rectangle", 2, WHITE);
    
    SSD1306_Draw_Rectangle ( 12, 43, 10, 12, 0, WHITE);
    SSD1306_Draw_Rectangle ( 52, 47, 25, 32, 0, WHITE);
    SSD1306_Draw_Rectangle ( 80, 43, 35, 52, 0, WHITE);
    SSD1306_Draw_Rectangle ( 120, 42, 48, 62, 0, WHITE);
    SSD1306_Draw_Rectangle ( 72, 41, 57, 32, 0, WHITE);
    
    SSD1306_Write_Buffer();
    __delay_ms(2000);
    SSD1306_Clear_Display();
    
    SM_STATE = STATE_THREE;
}

/*******************************************************************************
 * Function:        void SM_STATE_THREE(void)
 *
 * PreCondition:    Table structure for states should have been initialized
 *                  as well as enum for each state
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        State C demonstrates drawing a circle on the SSD1306
 * 
 * Usage:           None
 *
 * Note:            None
 ******************************************************************************/
void SM_STATE_THREE(void)
{
    SSD1306_Draw_Button(0,  10, 60,  30, "Option 1", 0);
    SSD1306_Draw_Button(62, 10, 126, 30, "Option 2", 0);
    SSD1306_Draw_Button(0,  32, 60,  52, "Option 3", 1);
    SSD1306_Draw_Button(62, 32, 126, 52, "Option 4", 0);
    SSD1306_Write_Buffer();
    
    __delay_ms(1000);
    SSD1306_Clear_Display();
     
    // Demonstrate writing circles
    SSD1306_Write_Text ( 0, 0, "Circle", 2, WHITE);
    
    SSD1306_Draw_Circle (10,  20, 10, 0, WHITE);
    SSD1306_Draw_Circle (50,  30, 20, 0, WHITE);
    SSD1306_Draw_Circle (70,  50, 15, 0, WHITE);
    SSD1306_Draw_Circle (90,  30, 35, 0, WHITE);
    SSD1306_Draw_Circle (120, 40, 5,  0, WHITE);
    SSD1306_Draw_Circle (30,  50, 40, 0, WHITE);
    
    SSD1306_Write_Buffer();
    __delay_ms(2000);
    SSD1306_Clear_Display();
    
    SM_STATE = STATE_FOUR;
}


/*******************************************************************************
 * Function:        void SM_STATE_FOUR(void)
 *
 * PreCondition:    Table structure for states should have been initialized
 *                  as well as enum for each state
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        State D demonstrates writing floats and int on the SSD1306
 * 
 * Usage:           None
 *
 * Note:            None
 ******************************************************************************/
void SM_STATE_FOUR(void)
{
    // Highlight option 4
    SSD1306_Draw_Button(0,  10, 60,  30, "Option 1", 0);
    SSD1306_Draw_Button(62, 10, 126, 30, "Option 2", 0);
    SSD1306_Draw_Button(0,  32, 60,  52, "Option 3", 0);
    SSD1306_Draw_Button(62, 32, 126, 52, "Option 4", 1);
    SSD1306_Write_Buffer();
    
    // Clear SSD1306_Write_Buffer
    __delay_ms(1000);
    SSD1306_Clear_Display();
      
    SSD1306_Write_Text ( 0, 0, "Numbers", 2, WHITE);
    
    // Variables for loop
    int   i;
    float f;
    
    // Demonstrates writing floats and int
    for (i = 0, f = 0.0; i <= 20; i++, f += 0.5)
    {
        SSD1306_Write_Text ( 0, 0, "Numbers", 2, WHITE);
        SSD1306_Write_Integer(0, 20, i, 2);
        SSD1306_Write_Float(0, 40, f, 2);
        SSD1306_Write_Buffer();
        __delay_ms(500);
        SSD1306_Clear_Display();
    }
      
    SM_STATE = STATE_ONE; 
}

/*******************************************************************************
 * Function:        RUN_STATEMACHINE(void)
 *
 * PreCondition:    Table structure for states should have been initialized
 *                  as well as enum for each state
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Allows state machine to run
 * 
 * Usage:           RUN_STATEMACHINE()
 *
 * Note:            None
 ******************************************************************************/
void RUN_STATEMACHINE (void)
{
    // Make Sure States is valid
    if (SM_STATE < NUM_STATES)
    {
        // Call function for state
        (*StateMachine[SM_STATE].func)();
    }
    else
    {
        // Code should never reach here
        while(1)
        {
            // Some exception handling;
        }
    }
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
    // Initialize main
    initMain();
    
    // Display Logo
    SSD1306_Write_Buffer();
    __delay_ms(2000);
    
    // Clear SSD1306 
    SSD1306_Clear_Display();
    
   
 
    while(1)
    {
        // Start the state machine
        RUN_STATEMACHINE();
      
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
void initMain(void)
{
     // Initialize system
    SYSTEM_Initialize();
    __delay_ms(1000);
    
    // Initialize SSD1306
    SSD1306_INIT();
    __delay_ms(2000);
}

