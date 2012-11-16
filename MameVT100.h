/*************************************************************************/
/* XMAME VT100 MENU                                                      */
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

#ifndef __MameVT100_H
#define __MameVT100_H


#define ARG_COUNT		2
#define ARG_EXE			0
#define ARG_FILTER		1

#define TRUE			-1
#define FALSE			0
#define BUFF_SIZE		1024
#define MAX_ROMS		8192
#define BORDER_TOP		1
#define BORDER_LEFT		2
#define ITEM_WIDTH		26
#define ITEM_HEIGHT		2


void Timer(int signum);
void DisplayError(char* Error);
int GetKeys(char* Buffer, char FromChar, char ToChar);
void GetRomInfo(char** ROM, char** ROM_Name, char** ROM_Status, int* ROM_Filtered, char* Filter);
void UpdateDisplay(char** ROM, char** ROM_Name, char** ROM_Status, int* ROM_Filtered, int Cols, int Rows, int Offset, int Index);


#endif

