/*******************************************************************************
 * File: SSD1306_OLED.c
 * Author: Armstrong Subero (inspired by Adafruit library)
 * PIC: 24FJ128GB204 @ 32 MHz, 3.3v
 * Compiler: XC16 (Pro) (v1.31, MPLAX X v3.55)
 * Program Version: 1.1
 *                * Added comments
 *                * Added Functions
 *                * Converted functions from C++ to C
 *                * Buffer default from Adafruit logo to Microchip(c) logo
 *                * Removed unecessary code
 *                
 * Program Description: This Program allows usage of SSD1306 based OLEDs using
 *                      I2C
 * 
 * Hardware Description: Standard connections as per MCC or PPS
 *                      
 * Created May 9th, 2017, 8:00 PM
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
 * Original License:
 * 
 * Software License Agreement (BSD License)

 * Copyright (c) 2012, Adafruit Industries
 * All rights reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the
 * names of its contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/


/*******************************************************************************
 * Includes and defines
 ******************************************************************************/


#include "mcc_generated_files/mcc.h"
#include "SSD1306_OLED.h"
#include "PIC24FJ128GB204_STD.h"
#include <stdio.h>
#include <string.h>
#include "PIC24_PIC33_I2C.h"


/*******************************************************************************
 * Function:        static uint8_t buffer[SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8]
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Buffer for writing to the OLED size 1024 bytes prepopulated
 *                  with microchip technology logo
 * 
 * Usage:           None
 *
 * Note:            Create with BMP-LCD by www.hobbytronics.co.uk
 ******************************************************************************/
static uint8_t buffer[SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,
0xE0,0xE0,0xF0,0xF8,0xF8,0xFC,0xFC,0xFC,0xFE,0xFE,0xFE,0xFE,0xFE,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFE,0xFE,0xFE,0xFE,0xFE,0xFC,0xFC,0xF0,0xE0,0x80,0x00,0x10,0x00,
0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xF8,0xFC,0xFF,0xFF,0xFF,
0xFF,0xFF,0x3F,0x1F,0x0F,0x03,0x01,0x00,0x00,0x01,0x03,0x07,0x1F,0x3F,0xFF,0xFF,
0xFF,0xFF,0x3F,0x1F,0x07,0x03,0x01,0x00,0x00,0x01,0x03,0x07,0x1F,0x3F,0xFC,0xF8,
0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x3F,0x1F,0x0F,0x03,
0x03,0x0F,0x1F,0x7E,0xF8,0xF0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
0x07,0x0F,0x3F,0x7C,0xF8,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
0x07,0x1F,0x3F,0xFE,0xF8,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x80,0xC0,0xF0,0xFF,0xFF,0xFF,0xFE,0xF8,0xF0,0xC0,0x80,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x81,0xE3,0xFF,0xFF,0xFE,0xF8,0xF0,0xC0,0x80,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0x07,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,
0x1C,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF8,
0xF8,0xF8,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3E,0x3C,0x10,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0xE0,0xF0,0xF0,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,
0xE0,0xF0,0xF0,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0xFC,0xFF,0xFF,0xFF,0x1F,0x7F,0xFF,0xFC,0xE0,0x80,0x00,0xC0,0xF8,0xFE,0xFF,
0x3F,0x0F,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFE,0xFE,0xFE,0xFE,0x00,0x00,0xF8,0xFC,
0xFE,0x3E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x08,0x00,0x00,0xFE,0xFE,
0xFE,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0xFE,0xFE,0xFC,0x00,0x00,0xF8,0xFC,0xFE,
0x3E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0xFE,0xFE,0xFC,0xE0,0x00,0xF0,0xFC,0xFE,
0xFE,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1C,0x00,0x00,0xFE,0xFE,0xFE,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xFE,0xFE,0xFE,0x00,0x00,0x00,0xFE,0xFE,0xFE,
0x00,0x00,0xFE,0xFE,0xFE,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0xFE,0xFC,0xF8,

0xF0,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x03,0x0F,0x3F,0x7F,0x7F,0x7F,0x3F,0x07,0x00,
0x00,0x00,0x7F,0xFF,0xFF,0xFF,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0x00,0x00,0x3F,0x7F,
0xFF,0xF8,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0x70,0x00,0x00,0xFF,0xFF,
0xFF,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xF9,0x00,0x00,0x3F,0x7F,0xFF,
0xF8,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0x7F,0x0F,0x00,0x1F,0x7F,0xFF,
0xFF,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0x70,0x00,0x00,0xFF,0xFF,0xFF,
0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,
0x00,0x00,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x03
};

/*******************************************************************************
 * Function:        const char TEXT[51][5]
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Contains ASCII characters for writing to the display first 
 *                  half
 * 
 * Usage:           None
 *
 * Note:            None
 ******************************************************************************/

const char TEXT[51][5] = 
{
    {0x00, 0x00, 0x00, 0x00, 0x00}, // SPACE
    {0x00, 0x00, 0x5F, 0x00, 0x00}, // !
    {0x00, 0x03, 0x00, 0x03, 0x00}, // "
    {0x14, 0x3E, 0x14, 0x3E, 0x14}, // #
    {0x24, 0x2A, 0x7F, 0x2A, 0x12}, // $
    {0x43, 0x33, 0x08, 0x66, 0x61}, // %
    {0x36, 0x49, 0x55, 0x22, 0x50}, // &
    {0x00, 0x05, 0x03, 0x00, 0x00}, // '
    {0x00, 0x1C, 0x22, 0x41, 0x00}, // (
    {0x00, 0x41, 0x22, 0x1C, 0x00}, // )
    {0x14, 0x08, 0x3E, 0x08, 0x14}, // *
    {0x08, 0x08, 0x3E, 0x08, 0x08}, // +
    {0x00, 0x50, 0x30, 0x00, 0x00}, // ,
    {0x08, 0x08, 0x08, 0x08, 0x08}, // -
    {0x00, 0x60, 0x60, 0x00, 0x00}, // .
    {0x20, 0x10, 0x08, 0x04, 0x02}, // /
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
    {0x04, 0x02, 0x7F, 0x00, 0x00}, // 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
    {0x22, 0x41, 0x49, 0x49, 0x36}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
    {0x3E, 0x49, 0x49, 0x49, 0x32}, // 6
    {0x01, 0x01, 0x71, 0x09, 0x07}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x26, 0x49, 0x49, 0x49, 0x3E}, // 9
    {0x00, 0x36, 0x36, 0x00, 0x00}, // :
    {0x00, 0x56, 0x36, 0x00, 0x00}, // ;
    {0x08, 0x14, 0x22, 0x41, 0x00}, // <
    {0x14, 0x14, 0x14, 0x14, 0x14}, // =
    {0x00, 0x41, 0x22, 0x14, 0x08}, // >
    {0x02, 0x01, 0x51, 0x09, 0x06}, // ?
    {0x3E, 0x41, 0x59, 0x55, 0x5E}, // @
    {0x7E, 0x09, 0x09, 0x09, 0x7E}, // A
    {0x7F, 0x49, 0x49, 0x49, 0x36}, // B
    {0x3E, 0x41, 0x41, 0x41, 0x22}, // C
    {0x7F, 0x41, 0x41, 0x41, 0x3E}, // D
    {0x7F, 0x49, 0x49, 0x49, 0x41}, // E
    {0x7F, 0x09, 0x09, 0x09, 0x01}, // F
    {0x3E, 0x41, 0x41, 0x49, 0x3A}, // G
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H
    {0x00, 0x41, 0x7F, 0x41, 0x00}, // I
    {0x30, 0x40, 0x40, 0x40, 0x3F}, // J
    {0x7F, 0x08, 0x14, 0x22, 0x41}, // K
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // L
    {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // M
    {0x7F, 0x02, 0x04, 0x08, 0x7F}, // N
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
    {0x7F, 0x09, 0x09, 0x09, 0x06}, // P
    {0x1E, 0x21, 0x21, 0x21, 0x5E}, // Q
    {0x7F, 0x09, 0x09, 0x09, 0x76}  // R
};

/*******************************************************************************
 * Function:        const char TEXT[44][5]
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Contains ASCII characters for writing to the display second 
 *                  half
 * 
 * Usage:           None
 *
 * Note:            None
 ******************************************************************************/
const char TEXT2[44][5]=
{
    {0x26, 0x49, 0x49, 0x49, 0x32}, // S
    {0x01, 0x01, 0x7F, 0x01, 0x01}, // T
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, // U
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, // V
    {0x7F, 0x20, 0x10, 0x20, 0x7F}, // W
    {0x41, 0x22, 0x1C, 0x22, 0x41}, // X
    {0x07, 0x08, 0x70, 0x08, 0x07}, // Y
    {0x61, 0x51, 0x49, 0x45, 0x43}, // Z
    {0x00, 0x7F, 0x41, 0x00, 0x00}, // [
    {0x02, 0x04, 0x08, 0x10, 0x20}, //\
    {0x00, 0x00, 0x41, 0x7F, 0x00}, // ]
    {0x04, 0x02, 0x01, 0x02, 0x04}, // ^
    {0x40, 0x40, 0x40, 0x40, 0x40}, // _
    {0x00, 0x01, 0x02, 0x04, 0x00}, // `
    {0x20, 0x54, 0x54, 0x54, 0x78}, // a
    {0x7F, 0x44, 0x44, 0x44, 0x38}, // b
    {0x38, 0x44, 0x44, 0x44, 0x44}, // c
    {0x38, 0x44, 0x44, 0x44, 0x7F}, // d
    {0x38, 0x54, 0x54, 0x54, 0x18}, // e
    {0x04, 0x04, 0x7E, 0x05, 0x05}, // f
    {0x08, 0x54, 0x54, 0x54, 0x3C}, // g
    {0x7F, 0x08, 0x04, 0x04, 0x78}, // h
    {0x00, 0x44, 0x7D, 0x40, 0x00}, // i
    {0x20, 0x40, 0x44, 0x3D, 0x00}, // j
    {0x7F, 0x10, 0x28, 0x44, 0x00}, // k
    {0x00, 0x41, 0x7F, 0x40, 0x00}, // l
    {0x7C, 0x04, 0x78, 0x04, 0x78}, // m
    {0x7C, 0x08, 0x04, 0x04, 0x78}, // n
    {0x38, 0x44, 0x44, 0x44, 0x38}, // o
    {0x7C, 0x14, 0x14, 0x14, 0x08}, // p
    {0x08, 0x14, 0x14, 0x14, 0x7C}, // q
    {0x00, 0x7C, 0x08, 0x04, 0x04}, // r
    {0x48, 0x54, 0x54, 0x54, 0x20}, // s
    {0x04, 0x04, 0x3F, 0x44, 0x44}, // t
    {0x3C, 0x40, 0x40, 0x20, 0x7C}, // u
    {0x1C, 0x20, 0x40, 0x20, 0x1C}, // v
    {0x3C, 0x40, 0x30, 0x40, 0x3C}, // w
    {0x44, 0x28, 0x10, 0x28, 0x44}, // x
    {0x0C, 0x50, 0x50, 0x50, 0x3C}, // y
    {0x44, 0x64, 0x54, 0x4C, 0x44}, // z
    {0x00, 0x08, 0x36, 0x41, 0x41}, // {
    {0x00, 0x00, 0x7F, 0x00, 0x00}, // |
    {0x41, 0x41, 0x36, 0x08, 0x00}, // }
    {0x02, 0x01, 0x02, 0x04, 0x02}, // ~
    {0x00, 0x00, 0x00, 0x00, 0x00}
};



/*******************************************************************************
 * Function:        void SSD1306_COMMAND( uint8_t temp)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Sends commands to the OLED
 * 
 * Usage:           None
 *
 * Note:            None
 ******************************************************************************/
void SSD1306_COMMAND( uint8_t temp){
    
    I2C1_Write(0x3C<<1, 0x00, temp);
   
}


/*******************************************************************************
 * Function:        void SSD1306_INIT()
 *
 * PreCondition:    I2C bus should have been initialized
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Initializes the OLED
 * 
 * Usage:           None
 *
 * Note:            None
 ******************************************************************************/
void SSD1306_INIT(void)
{
    SSD1306_COMMAND(SSD1306_DISPLAYOFF);         // 0xAE
    SSD1306_COMMAND(SSD1306_SETDISPLAYCLOCKDIV); // 0xD5
    SSD1306_COMMAND(0x80);                    // the suggested ratio 0x80
    SSD1306_COMMAND(SSD1306_SETMULTIPLEX);       // 0xA8
    SSD1306_COMMAND(SSD1306_LCDHEIGHT - 1);
    SSD1306_COMMAND(SSD1306_SETDISPLAYOFFSET);   // 0xD3
    SSD1306_COMMAND(0x0);                        // no offset
    SSD1306_COMMAND(SSD1306_SETSTARTLINE | 0x0); // line #0
    SSD1306_COMMAND(SSD1306_CHARGEPUMP);         // 0x8D
    SSD1306_COMMAND(0xAF);
    SSD1306_COMMAND(SSD1306_MEMORYMODE);         // 0x20
    SSD1306_COMMAND(0x00);                    // 0x0 act like ks0108
    SSD1306_COMMAND(SSD1306_SEGREMAP | 0x1);
    SSD1306_COMMAND(SSD1306_COMSCANDEC);
    SSD1306_COMMAND(SSD1306_SETCOMPINS);         // 0xDA
    SSD1306_COMMAND(0x12);
    SSD1306_COMMAND(SSD1306_SETCONTRAST);        // 0x81
    SSD1306_COMMAND(0x8F);
    SSD1306_COMMAND(SSD1306_SETPRECHARGE);       // 0xd9
    SSD1306_COMMAND(0xF1);
    SSD1306_COMMAND(SSD1306_SETVCOMDETECT);      // 0xDB
    SSD1306_COMMAND(0x40);
    SSD1306_COMMAND(SSD1306_DISPLAYALLON_RESUME);// 0xA4
    SSD1306_COMMAND(SSD1306_NORMALDISPLAY);      // 0xA6
    SSD1306_COMMAND(SSD1306_DISPLAYON);          //--turn on oled panel
}


/*******************************************************************************
 * Function:        void drawPixel(int16_t x, int16_t y, uint16_t color) 
 *
 * PreCondition:    Display should have been initialized
 *
 * Input:           X and Y coordinates as well as color
 *
 * Output:          None
 *
 * Overview:        Sets a single pixel to the coordinates and parameters 
 *                  specified
 * 
 * Usage:           drawPixel(0, 0, WHITE);
 *
 * Note:            None
 ******************************************************************************/
void drawPixel(int16_t x, int16_t y, uint16_t color) 
{
  if ((x < 0) || (x >= SSD1306_LCDWIDTH) || (y < 0) || (y >= SSD1306_LCDHEIGHT))
    return;

  // check rotation, move pixel around if necessary
  switch (getRotation()) {
  case 1:
    ssd1306_swap(x, y);
    x = SSD1306_LCDWIDTH - x - 1;
    break;
  case 2:
    x = SSD1306_LCDWIDTH - x - 1;
    y = SSD1306_LCDHEIGHT - y - 1;
    break;
  case 3:
    ssd1306_swap(x, y);
    y = SSD1306_LCDHEIGHT - y - 1;
    break;
  }
  
  // x is which column
    switch (color)
    {
      case WHITE:   buffer[x+ (y/8)*SSD1306_LCDWIDTH] |=  (1 << (y&7)); break;
      case BLACK:   buffer[x+ (y/8)*SSD1306_LCDWIDTH] &= ~(1 << (y&7)); break;
      case INVERSE: buffer[x+ (y/8)*SSD1306_LCDWIDTH] ^=  (1 << (y&7)); break;
    }

}

/*******************************************************************************
 * Function:        void SSD1306_Write_Buffer(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Writes the buffer to the OLED
 * 
 * Usage:           None
 *
 * Note:            None
 ******************************************************************************/
void SSD1306_Write_Buffer(void) {
  SSD1306_COMMAND(SSD1306_COLUMNADDR);
  SSD1306_COMMAND(0);   // Column start address (0 = reset)
  SSD1306_COMMAND(SSD1306_LCDWIDTH-1); // Column end address (127 = reset)
  SSD1306_COMMAND(SSD1306_PAGEADDR);
  SSD1306_COMMAND(0); // Page start address (0 = reset)
  SSD1306_COMMAND(7); // Page end address
  
   // Variable for buffer loop
   uint16_t i;
   
   for(i = 0; i < (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT/ 8); i++){
       I2C1_IDLE();
       I2C1CON1bits.SEN = 1;
       while (I2C1CON1bits.SEN);
       IFS1bits.MI2C1IF = 0;
       MasterWriteI2C1(0x3C<<1|0);
       MasterWriteI2C1(0x40&0x00FF);
       
       // Variable for write loop
       uint16_t x;
     
       // Write a chunk of data 
       for (x=0; x<128; x++) {
           MasterWriteI2C1(buffer[i]);
           i++;
       }
       i--;
       
       I2C1CON1bits.PEN = 1;
       while(I2C1CON1bits.PEN);                     
       IFS1bits.MI2C1IF = 0;   
  }
    
}


/*******************************************************************************
 * Function:        void SSD1306_Clear_Display(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Clears the OLED
 * 
 * Usage:           None
 *
 * Note:            None
 ******************************************************************************/
void SSD1306_Clear_Display(void) {
  memset(buffer, 0, (SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8));
}

/*******************************************************************************
 * Function:        void SSD1306_Write_Text ( int x, int y, char* textptr, 
 *                  int size, char color )
 *
 * PreCondition:    None
 *
 * Input:           X and Y coordinates, text to be written and color
 *
 * Output:          None
 *
 * Overview:        Writes text to the OLED with specified parameters 
 * 
 * Usage:           SSD1306_Write_Text(0, 0, "Hello World!", 1, WHITE);
 *
 * Note:            None
 ******************************************************************************/
void SSD1306_Write_Text ( int x, int y, char* textptr, int size, char color )
{
	unsigned char i, j, k, l, m;						// Loop counters
	unsigned char pixelData [ 5 ];						// Stores character data

	for ( i = 0; textptr [ i ] != 0x00; ++i, ++x )		// Loop through the passed string
	{
		if ( textptr [ i ] < 'S') // Checks if the letter is in the first text array
			memcpy ( pixelData, TEXT [ textptr [ i ] - ' '], 5 );
		
		else if(textptr[i] <= '~') // Check if the letter is in the second array
		{
			if ( ( textptr[i] >= 'a' ) && ( textptr[i] <= 'z' ) )
				memcpy ( pixelData, TEXT2 [ textptr [ i ] - 'S' - 1 ], 5 );
			
			else
				memcpy ( pixelData, TEXT2 [ textptr [ i ] - 'S' ], 5 );

			}
		
		else
			memcpy ( pixelData, TEXT [ 0 ], 5 );		// Default to space

		if ( x + 5 * size >= SSD1306_LCDWIDTH )				// Performs character wrapping
		{	
			x = 0;										// Set x at far left position
			y += 7*size + 1;							// Set y at next position down
      		}
      
		for ( j = 0; j < 5; ++j, x += size )			// Loop through character byte data
		{
			for ( k = 0; k <7 *size; ++k )				// Loop through the vertical pixels
			{
				if ( bit_test ( pixelData [ j ], k ) )	// Check if the pixel should be set
				{
					for ( l = 0; l < size; ++l )		// The next two loops change the
					{									// character's size
						for ( m = 0; m < size; ++m )
						{
							drawPixel ( x + m, y + k * size + l, color ); // Draws the pixel
							}
						}
					}
				}
			}
		}
	}

/*******************************************************************************
 * Function:        void SSD1306_Draw_Line ( unsigned char x1, unsigned char y1, 
 *                  unsigned char x2, unsigned char y2, char color )
 *
 * PreCondition:    None
 *
 * Input:           X and Y coordinates and color
 *
 * Output:          None
 *
 * Overview:        Draws a line to the OLED with specified parameters 
 * 
 * Usage:           SSD1306_Write_Text(0, 0, "Hello World!", 1, WHITE);
 *
 * Note:            None
 ******************************************************************************/
void SSD1306_Draw_Line ( unsigned char x1, unsigned char y1, unsigned char x2, 
                         unsigned char y2, char color )
{
	int  x, y, addx, addy, dx, dy;
	int P;
	int i;

	dx = abs ( ( int ) ( x2 - x1 ) );
	dy = abs ( ( int ) ( y2 - y1 ) );
	x = x1;
	y = y1;

	if ( x1 > x2 )
		addx = -1;
	else
		addx = 1;
	
	if ( y1 > y2 )
		addy = -1;
	else
		addy = 1;

	if ( dx >= dy )
	{
		P = 2 * dy - dx;

		for ( i = 0; i <= dx; ++i )
		{
			drawPixel ( x, y, color );

			if ( P < 0 )
			{
				P += 2 * dy;
				x += addx;
				}
			else
			{
				P += 2 * dy - 2 * dx;
				x += addx;
				y += addy;
				}
			}
		}
	else
	{
		P = 2 * dx - dy;

		for ( i = 0; i <= dy; ++i )
		{
			drawPixel ( x, y, color );

			if ( P < 0 )
			{
				P += 2 * dx;
				y += addy;
				}
			else
			{
				P += 2 * dx - 2 * dy;
				x += addx;
				y += addy;
				}
			}
		}
}

/*******************************************************************************
 * Function:        void SSD1306_Draw_Circle ( int x, int y, int radius, 
 *                  char fill, char color )
 *
 * PreCondition:    None
 *
 * Input:           X and Y coordinates, radius, fill and color
 *
 * Output:          None
 *
 * Overview:        Draws a circle to the OLED with specified parameters 
 * 
 * Usage:           SSD1306_Draw_Circle(50, 30, 10, NO, WHITE);
 *
 * Note:            None
 ******************************************************************************/
void SSD1306_Draw_Circle ( int x, int y, int radius, char fill, char color )
{
	int a, b, P;
	a = 0x00;
	b = radius;
	P = 0x01 - radius;
	
	do
	{
		if( fill )
		{
			SSD1306_Draw_Line ( x - a, y + b, x + a, y + b, color );
			SSD1306_Draw_Line ( x - a, y - b, x + a, y - b, color );
			SSD1306_Draw_Line ( x - b, y + a, x + b, y + a, color );
			SSD1306_Draw_Line ( x - b, y - a, x + b, y - a, color );
			}
		

        else
        {
			drawPixel ( a + x, b + y, color );
			drawPixel ( b + x, a + y, color );
			drawPixel ( x - a, b + y, color );
			drawPixel ( x - b, a + y, color );
			drawPixel ( b + x, y - a, color );
			drawPixel ( a + x, y - b, color );
			drawPixel ( x - a, y - b, color );
			drawPixel ( x - b, y - a, color );
      		}

		if ( P < 0 )
			P += 3 + 2 * a++;
		else
			P += 5 + 2 * ( a++ - b-- );
		
		} while ( a <= b );
}


/*******************************************************************************
 * Function:        void SSD1306_Draw_Rectangle ( unsigned char x1, unsigned char y1,
 *                  unsigned char x2, unsigned char y2, unsigned char fill, char color )
 *
 * PreCondition:    None
 *
 * Input:           X and Y coordinates, radius, fill and color
 *
 * Output:          None
 *
 * Overview:        Draws a rectangle to the OLED with specified parameters 
 * 
 * Usage:           SSD1306_Draw_Rectangle ( 42, 40, 60, 52, 0, WHITE);
 *
 * Note:            None
 ******************************************************************************/
void SSD1306_Draw_Rectangle ( unsigned char x1, unsigned char y1, unsigned char x2, 
                              unsigned char y2, unsigned char fill, char color )
{
	if ( fill )
	{
		unsigned char y, ymax;                          // Find the y min and max
		
		if ( y1 < y2 )
		{
			y = y1;
			ymax = y2;
			}
		else
		{
			y = y2;
			ymax = y1;
			}

		for ( ; y <= ymax; ++y )                    // Draw lines to fill the rectangle
			SSD1306_Draw_Line ( x1, y, x2, y, color );
           
		}
	else
	{
		SSD1306_Draw_Line ( x1, y1, x2, y1, color );      // Draw the 4 sides
		SSD1306_Draw_Line ( x1, y2, x2, y2, color );
		SSD1306_Draw_Line ( x1, y1, x1, y2, color );
		SSD1306_Draw_Line ( x2, y1, x2, y2, color );
		}
	}


/*******************************************************************************
 * Function:        void SSD1306_Draw_Button(unsigned char recx1, unsigned char recy1, 
 *                  unsigned char recx2, unsigned char recy2,  char* text, unsigned char fill)
 *
 * PreCondition:    None
 *
 * Input:           X and Y coordinates, text and fill
 *
 * Output:          None
 *
 * Overview:        Draws a button to the OLED with specified parameters 
 * 
 * Usage:           SSD1306_Draw_Button ( 42, 40, 60, 52, "Hello" , WHITE);
 *
 * Note:            None
 ******************************************************************************/
 void SSD1306_Draw_Button(unsigned char recx1, unsigned char recy1, unsigned char recx2, 
                          unsigned char recy2,  char* text, unsigned char fill)
 {
     if (fill == 0){
         SSD1306_Draw_Rectangle ( recx1,  recy1,  recx2,  recy2, NO, WHITE);
         SSD1306_Write_Text        ( recx1 + 5,  recy1 + 8, text, 1, WHITE);   
     }
     
     else if (fill == 1)
     {
         SSD1306_Draw_Rectangle ( recx1,  recy1,  recx2,  recy2, YES, WHITE);
         SSD1306_Write_Text        ( recx1 + 5,  recy1 + 8, text, 1, BLACK);   
     }
 }
   
 /*******************************************************************************
 * Function:       SSD1306_Write_Integer(uint8_t x, uint8_t y, uint8_t i, 
 *                 uint8_t size)
 *
 * PreCondition:    None
 *
 * Input:           X and Y coordinates, integer and size
 *
 * Output:          None
 *
 * Overview:        Writes an integer to the OLED with specified parameters 
 * 
 * Usage:           SSD1306_Write_Integer ( 0, 0, 10, 2);
 *
 * Note:            None
 ******************************************************************************/
 void SSD1306_Write_Integer(uint8_t x, uint8_t y, uint64_t i, uint8_t size)
 {
      char buff[50];
      sprintf( buff,"%llu",i);
      SSD1306_Write_Text(x, y, buff, size, WHITE );
 }
 
 
 /******************************************************************************
 * Function:       SSD1306_Write_Float(uint8_t x, uint8_t y, float i, uint8_t size)
 *
 * PreCondition:    None
 *
 * Input:           X and Y coordinates, float and size
 *
 * Output:          None
 *
 * Overview:        Writes a float to the OLED with specified parameters 
 * 
 * Usage:           SSD1306_Write_Float ( 0, 0, 3.45, 2);
 *
 * Note:            None
 ******************************************************************************/
 void SSD1306_Write_Float(uint8_t x, uint8_t y, float i, uint8_t size)
 {
      char buff[20];
      sprintf( buff,"%.2f",(double) i);
      SSD1306_Write_Text(x, y, buff, size, WHITE );
 }

/*******************************************************************************
 * Other Adafruit functions 
 ******************************************************************************/
void invertDisplay(uint8_t i) {
  if (i) {
    SSD1306_COMMAND(SSD1306_INVERTDISPLAY);
  } else {
    SSD1306_COMMAND(SSD1306_NORMALDISPLAY);
  }
}

// startscrollright
// Activate a right handed scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F)
void startscrollright(uint8_t start, uint8_t stop){
  SSD1306_COMMAND(SSD1306_RIGHT_HORIZONTAL_SCROLL);
  SSD1306_COMMAND(0X00);
  SSD1306_COMMAND(start);
  SSD1306_COMMAND(0X00);
  SSD1306_COMMAND(stop);
  SSD1306_COMMAND(0X00);
  SSD1306_COMMAND(0XFF);
  SSD1306_COMMAND(SSD1306_ACTIVATE_SCROLL);
}

// startscrollleft
// Activate a right handed scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F)
void startscrollleft(uint8_t start, uint8_t stop){
  SSD1306_COMMAND(SSD1306_LEFT_HORIZONTAL_SCROLL);
  SSD1306_COMMAND(0X00);
  SSD1306_COMMAND(start);
  SSD1306_COMMAND(0X00);
  SSD1306_COMMAND(stop);
  SSD1306_COMMAND(0X00);
  SSD1306_COMMAND(0XFF);
  SSD1306_COMMAND(SSD1306_ACTIVATE_SCROLL);
}

// startscrolldiagright
// Activate a diagonal scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F)
void startscrolldiagright(uint8_t start, uint8_t stop){
  SSD1306_COMMAND(SSD1306_SET_VERTICAL_SCROLL_AREA);
  SSD1306_COMMAND(0X00);
  SSD1306_COMMAND(SSD1306_LCDHEIGHT);
  SSD1306_COMMAND(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
  SSD1306_COMMAND(0X00);
  SSD1306_COMMAND(start);
  SSD1306_COMMAND(0X00);
  SSD1306_COMMAND(stop);
  SSD1306_COMMAND(0X01);
  SSD1306_COMMAND(SSD1306_ACTIVATE_SCROLL);
}

// startscrolldiagleft
// Activate a diagonal scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F)
void startscrolldiagleft(uint8_t start, uint8_t stop){
  SSD1306_COMMAND(SSD1306_SET_VERTICAL_SCROLL_AREA);
  SSD1306_COMMAND(0X00);
  SSD1306_COMMAND(SSD1306_LCDHEIGHT);
  SSD1306_COMMAND(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
  SSD1306_COMMAND(0X00);
  SSD1306_COMMAND(start);
  SSD1306_COMMAND(0X00);
  SSD1306_COMMAND(stop);
  SSD1306_COMMAND(0X01);
  SSD1306_COMMAND(SSD1306_ACTIVATE_SCROLL);
}

void stopscroll(void){
  SSD1306_COMMAND(SSD1306_DEACTIVATE_SCROLL);
}

// Dim the display
// dim = true: display is dimmed
// dim = false: display is normal
void dim(bool dim) {
  uint8_t contrast;

  if (dim) {
    contrast = 0; // Dimmed display
  } else {
   
   
      contrast = 0xCF;
    
  }
  // the range of contrast to too small to be really useful
  // it is useful to dim the display
  SSD1306_COMMAND(SSD1306_SETCONTRAST);
  SSD1306_COMMAND(contrast);
}


void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
  bool bSwap = false;
  switch(rotation) {
    case 0:
      // 0 degree rotation, do nothing
      break;
    case 1:
      // 90 degree rotation, swap x & y for rotation, then invert x
      bSwap = true;
      ssd1306_swap(x, y);
      x = SSD1306_LCDWIDTH - x - 1;
      break;
    case 2:
      // 180 degree rotation, invert x and y - then shift y around for height.
      x = SSD1306_LCDWIDTH - x - 1;
      y = SSD1306_LCDHEIGHT - y - 1;
      x -= (w-1);
      break;
    case 3:
      // 270 degree rotation, swap x & y for rotation, then invert y  and adjust y for w (not to become h)
      bSwap = true;
      ssd1306_swap(x, y);
      y = SSD1306_LCDHEIGHT - y - 1;
      y -= (w-1);
      break;
  }

  if(bSwap) {
    drawFastVLineInternal(x, y, w, color);
  } else {
    drawFastHLineInternal(x, y, w, color);
  }
}

void drawFastHLineInternal(int16_t x, int16_t y, int16_t w, uint16_t color) {
  // Do bounds/limit checks
  if(y < 0 || y >= SSD1306_LCDHEIGHT) { return; }

  // make sure we don't try to draw below 0
  if(x < 0) {
    w += x;
    x = 0;
  }

  // make sure we don't go off the edge of the display
  if( (x + w) > SSD1306_LCDWIDTH) {
    w = (SSD1306_LCDWIDTH - x);
  }

  // if our SSD1306_LCDWIDTH is now negative, punt
  if(w <= 0) { return; }

  // set up the pointer for  movement through the buffer
  register uint8_t *pBuf = buffer;
  // adjust the buffer pointer for the current row
  pBuf += ((y/8) * SSD1306_LCDWIDTH);
  // and offset x columns in
  pBuf += x;

  register uint8_t mask = 1 << (y&7);

  switch (color)
  {
  case WHITE:         while(w--) { *pBuf++ |= mask; }; break;
    case BLACK: mask = ~mask;   while(w--) { *pBuf++ &= mask; }; break;
  case INVERSE:         while(w--) { *pBuf++ ^= mask; }; break;
  }
}

void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
  bool bSwap = false;
  switch(rotation) {
    case 0:
      break;
    case 1:
      // 90 degree rotation, swap x & y for rotation, then invert x and adjust x for h (now to become w)
      bSwap = true;
      ssd1306_swap(x, y);
      x = SSD1306_LCDWIDTH - x - 1;
      x -= (h-1);
      break;
    case 2:
      // 180 degree rotation, invert x and y - then shift y around for height.
      x = SSD1306_LCDWIDTH - x - 1;
      y = SSD1306_LCDHEIGHT - y - 1;
      y -= (h-1);
      break;
    case 3:
      // 270 degree rotation, swap x & y for rotation, then invert y
      bSwap = true;
      ssd1306_swap(x, y);
      y = SSD1306_LCDHEIGHT - y - 1;
      break;
  }

  if(bSwap) {
    drawFastHLineInternal(x, y, h, color);
  } else {
    drawFastVLineInternal(x, y, h, color);
  }
}


void drawFastVLineInternal(int16_t x, int16_t __y, int16_t __h, uint16_t color) {

  // do nothing if we're off the left or right side of the screen
  if(x < 0 || x >= SSD1306_LCDWIDTH) { return; }

  // make sure we don't try to draw below 0
  if(__y < 0) {
    // __y is negative, this will subtract enough from __h to account for __y being 0
    __h += __y;
    __y = 0;

  }

  // make sure we don't go past the height of the display
  if( (__y + __h) > SSD1306_LCDHEIGHT) {
    __h = (SSD1306_LCDHEIGHT - __y);
  }

  // if our height is now negative, punt
  if(__h <= 0) {
    return;
  }

  // this display doesn't need ints for coordinates, use local byte registers for faster juggling
  register uint8_t y = __y;
  register uint8_t h = __h;


  // set up the pointer for fast movement through the buffer
  register uint8_t *pBuf = buffer;
  // adjust the buffer pointer for the current row
  pBuf += ((y/8) * SSD1306_LCDWIDTH);
  // and offset x columns in
  pBuf += x;

  // do the first partial byte, if necessary - this requires some masking
  register uint8_t mod = (y&7);
  if(mod) {
    // mask off the high n bits we want to set
    mod = 8-mod;

    // note - lookup table results in a nearly 10% performance improvement in fill* functions
    // register uint8_t mask = ~(0xFF >> (mod));
    static uint8_t premask[8] = {0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE };
    register uint8_t mask = premask[mod];

    // adjust the mask if we're not going to reach the end of this byte
    if( h < mod) {
      mask &= (0XFF >> (mod-h));
    }

  switch (color)
    {
    case WHITE:   *pBuf |=  mask;  break;
    case BLACK:   *pBuf &= ~mask;  break;
    case INVERSE: *pBuf ^=  mask;  break;
    }

    // fast exit if we're done here!
    if(h<mod) { return; }

    h -= mod;

    pBuf += SSD1306_LCDWIDTH;
  }


  // write solid bytes while we can - effectively doing 8 rows at a time
  if(h >= 8) {
    if (color == INVERSE)  {          // separate copy of the code so we don't impact performance of the black/white write version with an extra comparison per loop
      do  {
      *pBuf=~(*pBuf);

        // adjust the buffer forward 8 rows worth of data
        pBuf += SSD1306_LCDWIDTH;

        // adjust h & y (there's got to be a faster way for me to do this, but this should still help a fair bit for now)
        h -= 8;
      } while(h >= 8);
      }
    else {
      // store a local value to work with
      register uint8_t val = (color == WHITE) ? 255 : 0;

      do  {
        // write our value in
      *pBuf = val;

        // adjust the buffer forward 8 rows worth of data
        pBuf += SSD1306_LCDWIDTH;

        // adjust h & y (there's got to be a faster way for me to do this, but this should still help a fair bit for now)
        h -= 8;
      } while(h >= 8);
      }
    }

  // now do the final partial byte, if necessary
  if(h) {
    mod = h & 7;
    // this time we want to mask the low bits of the byte, vs the high bits we did above
    // register uint8_t mask = (1 << mod) - 1;
    // note - lookup table results in a nearly 10% performance improvement in fill* functions
    static uint8_t postmask[8] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F };
    register uint8_t mask = postmask[mod];
    switch (color)
    {
      case WHITE:   *pBuf |=  mask;  break;
      case BLACK:   *pBuf &= ~mask;  break;
      case INVERSE: *pBuf ^=  mask;  break;
    }
  }
}



