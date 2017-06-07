/*******************************************************************************
 * File: SSD1306_OLED.h
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
 * Program Description: This Program allows setup for SSD1306 based OLEDs using
 *                      I2C
 * 
 * Hardware Description: Standard connections as per MCC or PPS
 *                      
 * Created May 9th, 2017, 7:00 PM
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

// General defines
#define BLACK 0
#define WHITE 1
#define INVERSE 2
#define NO 0
#define YES 1

// Display address
#define SSD1306_I2C_ADDRESS   0x3C  

// Define OLED dimensions
#define SSD1306_LCDWIDTH 128
#define SSD1306_LCDHEIGHT 64

// Rotation commands
#define getRotation() 0
#define rotation 0

// Define command macros
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

// Define scrolling commands
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

// Define basic function macros
#define bit_test(D,i) (D & (0x01 << i))
#define ssd1306_swap(a, b) { int16_t t = a; a = b; b = t; }

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/

// Basic Commands
void SSD1306_INIT(void); 
void SSD1306_COMMAND(uint8_t command);
void SSD1306_Clear_Display(void);
void SSD1306_Write_Buffer(); 

// Graphics functions
void SSD1306_Draw_Button    (unsigned char recx1, unsigned char recy1, unsigned char recx2, 
                              unsigned char recy2,  char* text, unsigned char fill);
void SSD1306_Write_Text     ( int x, int y, char* textptr, int size, 
                              char color );
void SSD1306_Draw_Rectangle ( unsigned char x1, unsigned char y1, unsigned char x2, 
                              unsigned char y2, unsigned char fill, char color );
void SSD1306_Draw_Circle    ( int x, int y, int radius, char fill, char color );
void SSD1306_Draw_Line      ( unsigned char x1, unsigned char y1, unsigned char x2, 
                              unsigned char y2, char color );
void SSD1306_Write_Integer  (uint8_t x, uint8_t y, uint64_t i, uint8_t size);
void SSD1306_Write_Float    (uint8_t x, uint8_t y, float i, uint8_t size);

// Adafruit library core functions
void invertDisplay(uint8_t i);
void startscrollright(uint8_t start, uint8_t stop);
void startscrollleft(uint8_t start, uint8_t stop);
void startscrolldiagright(uint8_t start, uint8_t stop);
void startscrolldiagleft(uint8_t start, uint8_t stop);
void stopscroll(void);
void dim(bool dim);
void drawPixel(int16_t x, int16_t y, uint16_t color);
void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
inline void drawFastVLineInternal (int16_t x, int16_t y, int16_t h, uint16_t color) 
                                   __attribute__((always_inline));
inline void drawFastHLineInternal(int16_t x, int16_t y, int16_t w, uint16_t color) 
                                   __attribute__((always_inline));


