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

#include <stdio.h>
#include <string.h>
#include "VT100.h"


void GetSizeVT100(int* DisplayWidth, int* DisplayHeight)
{
	char Buffer[BUFF_SIZE + 1];

  /*******************************************/
 /* Get the VT100 display width and height. */
/*******************************************/
	printf(VT100_CURSOR_DOWN_N, 255);
	printf(VT100_CURSOR_RIGHT_N, 255);
	printf(VT100_QUERY_CURSOR_POSITION);
	GetKeys(Buffer, 0x1B, 'R');
	*DisplayHeight = GetValueVT100(Buffer, '[');
	*DisplayWidth = GetValueVT100(Buffer, ';');
	printf(VT100_CURSOR_HOME);
}


int GetValueVT100(char* Buffer, char StartChar)
{
	int Result;
	char* Pos;

	Result = 0;
	if ((Pos = strchr(Buffer, StartChar)))
		Result = atoi(Pos + 1);

	return Result;
}

