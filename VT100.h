/*************************************************************************/
/* VT100                                                                 */
/* Copyright (C) 2012 Jason Birch                                        */
/*                                                                       */
/* This program is free software: you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation, either version 3 of the License, or     */
/* (at your option) any later version.                                   */
/*                                                                       */
/* This program is distributed in the hope that it will be useful,       */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/* GNU General Public License for more details.                          */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/*************************************************************************/

#ifndef __VT100_H
#define __VT100_H


#define VT52_IDENTIFY			"%cZ", 0x1B
#define VT52_CURSOR_HOME		"%cH", 0x1B
#define VT52_CURSOR_UP			"%cA", 0x1B
#define VT52_CURSOR_DOWN		"%cB", 0x1B
#define VT52_CURSOR_RIGHT		"%cC", 0x1B
#define VT52_CURSOR_LEFT		"%cD", 0x1B
#define VT52_CURSOR_POSITION_Y_X	"%cY%c%c", 0x1B
#define VT52_CHAR_GRAPHICS		"%cF", 0x1B
#define VT52_CHAR_ASCII			"%cG", 0x1B
#define VT52_LINE_FEED_REVERSE		"%cI", 0x1B
#define VT52_ERASE_DISPLAY_DOWN		"%cJ", 0x1B
#define VT52_ERASE_LINE_END		"%cK", 0x1B
#define VT52_KEYPAD_ON			"%c=", 0x1B
#define VT52_KEYPAD_OFF			"%c>", 0x1B
#define VT52_ANSI			"%c<", 0x1B
#define VT52_GRAPHICS_ON		"%c1", 0x1B
#define VT52_GRAPHICS_OFF		"%c2", 0x1B

#define VT100_RESET			"%cc", 0x1B
#define VT100_DISPLAY_E			"%c#8", 0x1B
#define VT100_TEST_POWERUP		"%c[2;1y", 0x1B
#define VT100_TEST_LOOP_BACK		"%c[2;2y", 0x1B
#define VT100_TEST_LOOP_BACK_ETA        "%c[2;4y", 0x1B

#define VT100_BELL			"%c", 0x07

#define VT100_DEFINE_KEY		"%c[%u;\"%s\"p", 0x1B

#define VT100_CRLF			"%c[20h", 0x1B
#define VT100_LF			"%c[20l", 0x1B
#define VT100_CURSOR_OFF		"%c[?1h", 0x1B
#define VT100_CURSOR_ON			"%c[?1l", 0x1B
#define VT100_VT52			"%c[?2l", 0x1B
#define VT100_COL_132			"%c[?3h", 0x1B
#define VT100_COL_80			"%c[?3l", 0x1B
#define VT100_SCROLL_SMOOTH		"%c[?4h", 0x1B
#define VT100_SCROLL_JUMP		"%c[?4l", 0x1B
#define VT100_DISPLAY_REVERSE		"%c[?5h", 0x1B
#define VT100_DISPLAY_NORMAL		"%c[?5l", 0x1B
#define VT100_ORIGIN_RELATIVE		"%c[?6h", 0x1B
#define VT100_ORIGIN_ABSOLUTE		"%c[?6l", 0x1B
#define VT100_LINE_WRAP_ON		"%c[?7h", 0x1B
#define VT100_LINE_WRAP_OFF		"%c[?7l", 0x1B
#define VT100_KEY_REPEAT_ON		"%c[?8h", 0x1B
#define VT100_KEY_REPEAT_OFF		"%c[?8l", 0x1B
#define VT100_INTERLACE_ON		"%c[?9h", 0x1B
#define VT100_INTERLACE_OFF		"%c[?9l", 0x1B
#define VT100_GRAPHIC_ON		"%c1", 0x1B
#define VT100_GRAPHIC_OFF		"%c2", 0x1B
#define VT100_KEY_NUMERIC_ON		"%c=", 0x1B
#define VT100_KEY_NUMERIC_OFF		"%c>", 0x1B

#define VT100_LED_OFF_ALL		"%c[0q", 0x1B
#define VT100_LED_1_ON			"%c[1q", 0x1B
#define VT100_LED_2_ON                  "%c[2q", 0x1B
#define VT100_LED_3_ON                  "%c[3q", 0x1B
#define VT100_LED_4_ON                  "%c[4q", 0x1B

#define VT100_CURSOR_HOME		"%c[H", 0x1B
#define VT100_CURSOR_Y_X		"%c[%u;%uf", 0x1B
#define VT100_CURSOR_UP_N		"%c[%uA", 0x1B
#define VT100_CURSOR_DOWN_N             "%c[%uB", 0x1B
#define VT100_CURSOR_RIGHT_N            "%c[%uC", 0x1B
#define VT100_CURSOR_LEFT_N             "%c[%uD", 0x1B
#define VT100_CURSOR_STORE		"%c[s", 0x1B
#define VT100_CURSOR_RESTORE		"%c[u", 0x1B

#define VT100_LINE_FEED			"%cE", 0x1B
#define VT100_INDEX			"%cD", 0x1B
#define VT100_INDEX_REVERSE		"%cM", 0x1B

#define VT100_ERASE_LINE_END		"%c[K", 0x1B
#define VT100_ERASE_LINE_START		"%c[1K", 0x1B
#define VT100_ERASE_LINE		"%c[2K", 0x1B
#define VT100_ERASE_DISPLAY_DOWN	"%c[J", 0x1B
#define VT100_ERASE_DISPLAY_UP		"%c[1J", 0x1B
#define VT100_ERASE_DISPLAY		"%c[2J", 0x1B

#define VT100_PRINT_DISPLAY		"%c[i", 0x1B
#define VT100_PRINT_LINE		"%c[1i", 0x1B
#define VT100_PRINT_START		£"%c[5i", 0x1B
#define VT100_PRINT_STOP		"%c[4i", 0x1B

#define VT100_SCROLL_ALL		"%c[r", 0x1B
#define VT100_SCROLL_ROW_TO_ROW		"%c[%u;%ur", 0x1B
#define VT100_SCROLL_DOWN		"%cD", 0x1B
#define VT100_SCROLL_UP			"%cM", 0x1B

#define VT100_TAB_SET			"%cH", 0x1B
#define VT100_TAB_CLEAR			"%c[g", 0x1B
#define VT100_TAB_CLEAR_ALL		"%c[3g", 0x1B

#define VT100_DOUBLE_HEIGHT_TOP		"%c#3", 0x1B
#define VT100_DOUBLE_HEIGHT_BOTTOM	"%c#4", 0x1B
#define VT100_SINGLE_WIDTH		"%c#5", 0x1B
#define VT100_DOUBLE_WIDTH		"%c#6", 0x1B

#define VT100_ATTRIB_SAVE		"%c7", 0x1B
#define VT100_ATTRIB_RESTORE		"%c8", 0x1B
#define VT100_SET_ATTRIB                "%c[%um", 0x1B
#define VT100_ATTRIB_RESET		0
#define VT100_ATTRIB_BOLD		1
#define VT100_ATTRIB_DIM		2
#define VT100_ATTRIB_UNDERLINE		4
#define VT100_ATTRIB_BLINK		5
#define VT100_ATTRIB_REVERSE		7
#define VT100_ATTRIB_INVISIBLE		8
#define VT100_ATTRIB_FG_BLACK		30
#define VT100_ATTRIB_FG_RED		31
#define VT100_ATTRIB_FG_GREEN		32
#define VT100_ATTRIB_FG_YELLOW		33
#define VT100_ATTRIB_FG_BLUE		34
#define VT100_ATTRIB_FG_MAGENTA		35
#define VT100_ATTRIB_FG_CYAN		36
#define VT100_ATTRIB_FG_WHITE		37
#define VT100_ATTRIB_BG_BLACK           40
#define VT100_ATTRIB_BG_RED             41
#define VT100_ATTRIB_BG_GREEN           42
#define VT100_ATTRIB_BG_YELLOW          43
#define VT100_ATTRIB_BG_BLUE            44
#define VT100_ATTRIB_BG_MAGENTA         45
#define VT100_ATTRIB_BG_CYAN            46
#define VT100_ATTRIB_BG_WHITE           47

#define VT100_CHAR_SET_UK_0		"%c(A", 0x1B
#define VT100_CHAR_SET_UK_1             "%c)A", 0x1B
#define VT100_CHAR_SET_US_0             "%c(B", 0x1B
#define VT100_CHAR_SET_US_1             "%c)B", 0x1B
#define VT100_CHAR_SET_LINE_0           "%c(0", 0x1B
#define VT100_CHAR_SET_LINE_1           "%c)0", 0x1B
#define VT100_CHAR_SET_ROM0_0           "%c(1", 0x1B
#define VT100_CHAR_SET_ROM0_1           "%c)1", 0x1B
#define VT100_CHAR_SET_ROM1_0           "%c(2", 0x1B
#define VT100_CHAR_SET_ROM1_1           "%c)2", 0x1B

#define VT100_QUERY_DEVICE_CODE		"%c[c", 0x1B
// ESC[?1;xC
// x=0	Base VT100, no options
// x=1  Processor option (STP)
// x=2  Advanced Video option (AVO)
// x=3  AVO and STP
// x=4  Graphocs processor option (GO)
// x=5  GO and STP
// x=6  GO and AVO
// x=7  GO, STP, and AVO
#define VT100_QUERY_DEVICE_STATUS	"%c[5n", 0x1B
// ESC[0n	OK
// ESC[3n	FAIL
#define VT100_QUERY_CURSOR_POSITION	"%c[6n", 0x1B
// ESC[y;xR


#define BUFF_SIZE 1024


void GetSizeVT100(int* DisplayWidth, int* DisplayHeight);
int GetValueVT100(char* Buffer, char StartChar);


#endif

