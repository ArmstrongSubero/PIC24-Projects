/*******************************************************************************
 * File: button.c
 * Author: Armstrong Subero
 * PIC: 24FJ128GB204 @ 32 MHz, 3.3v
 * Compiler: XC16 (Pro) (v1.31, MPLAX X v3.55)
 * Program Version: 1.1
 *           * Removed functions
 *           * Modified comments
 *                
 * Program Description: This Program allows usage of pushbuttons
 * 
 * Hardware Description: Connections as per application
 *        
 * Created May 3rd, 2017, 4:00 PM
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
 * Original License:
 * 
 * Copyright 2016 Microchip Technology Inc. (www.microchip.com)
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 ******************************************************************************/


/*******************************************************************************
 * Includes and defines
 ******************************************************************************/
#include "button.h"

/*********************************************************************
 * Function:        bool BUTTON_IsPressed(BUTTON button);
 * 
 * PreCondition:    button configured via in initMain()
 *
 * Input:           BUTTON button 
 *
 * Output:          TRUE if pressed; FALSE if not pressed.
 * 
 * Overview:        Returns the current state of the requested button
 * 
 * Usage:           if (BUTTON_IsPressed (button)
 *                  {
 *                      LED = 1;
 *                  }
 * 
 * Note:            None
 *
 ********************************************************************/
bool BUTTON_IsPressed ( BUTTON button )
{
    switch (button)
    {
        // First Button
        case BUTTON_S1:
            return ( ( S1_PORT == BUTTON_PRESSED ) ? true : false ) ;

        // No Button
        case BUTTON_NONE:
            return false ;
    }

    return false ;
}