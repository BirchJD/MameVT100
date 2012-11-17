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

/*************************************************************************/
/* MameVT100   Copyright (C)   Jason Birch   2012-11-15   V1.00          */
/*                                                                       */
/* Compile this file with the following command:                         */
/* make clean                                                            */
/* make                                                                  */
/*                                                                       */
/* Keys defined within this application when in use, chosen to be        */
/* convienient when used with the XMAME application:                     */
/* Cursor keys to move the ROM selection.                                */
/* '1' to select the ROM and start XMAME.                                */
/* '0' to exit the application.                                          */
/*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/time.h>
#include "VT100.h"
#include "MameVT100.h"


int main(int argc, char* argv[])
{
	int Count;
	int Size;
	int Index;
	int Offset;
	int Refresh;
	int DisplayWidth;
	int DisplayHeight;
	int Cols;
	int Rows;
	char Buffer[BUFF_SIZE + 1];
	char Execute[BUFF_SIZE + 1];
	char* ROM[MAX_ROMS];
	char* ROM_Name[MAX_ROMS];
	char* ROM_Status[MAX_ROMS];
	int ROM_Filtered[MAX_ROMS];
	struct termios RestoreTermIOs;
	struct termios NewTermIOs;
	struct itimerval NewTimer;

	if (argc != ARG_COUNT)
	{
		printf("Copyright Jason Birch   2012-11-17   V1.01\n");
		printf("%s [ROM_PATH] \"[FILTER]\"\n", argv[ARG_EXE]);
		printf("Where:\n");
		printf("[ROM_PATH]         - /root/.xmame/roms/\n");
		printf("\"[FILTER]\"       - Which ROM statuses to display seperated by '|'\n");
		printf("\n");
		printf("Examples:\n");
		printf("%s /root/.xmame/roms/ \"|correct|best available|\"\n", argv[ARG_EXE]);
		printf("%s /root/.xmame/roms/ \"|correct|best available|incorrect|\"\n", argv[ARG_EXE]);
		printf("%s /root/.xmame/roms/ \"|correct|best available|incorrect|not found|\"\n", argv[ARG_EXE]);
	}
	else
	{
  /****************/
 /* CooCooCaChoo */
/****************/
		tcgetattr(fileno(stdin), &RestoreTermIOs);
		memcpy(&NewTermIOs, &RestoreTermIOs, sizeof(struct termios));
		NewTermIOs.c_lflag &= ~(ECHO|ICANON);
		NewTermIOs.c_cc[VTIME] = 0;
		NewTermIOs.c_cc[VMIN] = 0;
		tcsetattr(fileno(stdin), TCSANOW, &NewTermIOs);

  /********************************************/
 /* Ensure all pointers are NULL by default. */
/********************************************/
		memset(ROM, '\0', MAX_ROMS * sizeof(char*));
		memset(ROM_Name, '\0', MAX_ROMS * sizeof(char*));
		memset(ROM_Status, '\0', MAX_ROMS * sizeof(char*));
		memset(ROM_Filtered, (int)-1, MAX_ROMS * sizeof(int));

  /*******************************/
 /* Generate and load ROM data. */
/*******************************/
		GetRomInfo(ROM, ROM_Name, ROM_Status, ROM_Filtered, argv[ARG_FILTER], argv[ARG_ROM_PATH]);

  /******************************/
 /* Clear the terminal window. */
/******************************/
		printf(VT100_RESET);
		printf(VT100_LINE_WRAP_OFF);
		printf(VT100_CURSOR_OFF);
		GetSizeVT100(&DisplayWidth, &DisplayHeight);
		Rows = (DisplayHeight - BORDER_TOP) / ITEM_HEIGHT;
		Cols = (DisplayWidth - BORDER_LEFT) / ITEM_WIDTH;

  /***************************/
 /* Generate a frame timer. */
/***************************/
		signal(SIGALRM, Timer);
		NewTimer.it_interval.tv_usec = 50000;
		NewTimer.it_interval.tv_sec = 0;
		NewTimer.it_value.tv_usec = 50000;
		NewTimer.it_value.tv_sec = 0;
		if (setitimer(ITIMER_REAL, &NewTimer, NULL))
			DisplayError("Failed to start timer.");

  /****************************/
 /* Handle user key presses. */
/****************************/
		Index = 0;
		Offset = 0;
		Refresh = TRUE;
		do
		{
  /**********/
 /* Yeald. */
/**********/
			pause();

  /*********************************/
 /* Update display when required. */
/*********************************/
			if (Refresh)
			{
				Refresh = FALSE;
				UpdateDisplay(ROM, ROM_Name, ROM_Status, ROM_Filtered, Cols, Rows, Offset, Index);
			}

  /*************************/
 /* Get user key presses. */
/*************************/
			GetKeys(Buffer, '\0', '\0');
			Size = strlen(Buffer);

  /***********************/
 /* Start selected ROM. */
/***********************/
			if (Buffer[0] == '1')
			{
				sprintf(Execute, "./xmame.SDL -ef 2 -afs -fsr 0 -rp %s -fullscreen %s", argv[ARG_ROM_PATH], ROM[ROM_Filtered[Index]]);
				system(Execute);
				Refresh = TRUE;
			}
  /*****************/
 /* Cursor right. */
/*****************/
			else if (Buffer[0] == 0x1B && Buffer[1] == 0x4F && Buffer[2] == 0x43)
			{
				Index += Rows;
				while (ROM_Filtered[Index] == -1 && Index > 0)
				{
					--Index;
				};
				if (Index >= Offset + Cols * Rows)
					Offset += Rows;
				Refresh = TRUE;
			}
  /****************/
 /* Cursor left. */
/****************/
			else if (Buffer[0] == 0x1B && Buffer[1] == 0x4F && Buffer[2] == 0x44)
			{
				Index -= Rows;
				if (Index < 0)
					Index = 0;
				if (Index < Offset)
					Offset -= Rows;
				if (Offset < 0)
					Offset = 0;
				Refresh = TRUE;
			}
  /**************/
 /* Cursor up. */
/**************/
			else if (Buffer[0] == 0x1B && Buffer[1] == 0x4F && Buffer[2] == 0x41)
			{
				if (--Index < 0)
					Index = 0;
				if (Index < Offset)
					--Offset;
				Refresh = TRUE;
			}
  /****************/
 /* Cursor down. */
/****************/
			else if (Buffer[0] == 0x1B && Buffer[1] == 0x4F && Buffer[2] == 0x42)
			{
				if (ROM_Filtered[++Index] == -1)
					--Index;
				if (Index >= Offset + Cols * Rows)
					++Offset;
				Refresh = TRUE;
			}
  /*****************************************/
 /* Exit application when '0' is pressed. */
/*****************************************/
		} while (Buffer[0] != '0');

  /*******************/
 /* Stop the timer. */
/*******************/
		signal(SIGALRM, SIG_IGN);

  /******************************/
 /* Clear the terminal window. */
/******************************/
		printf(VT100_RESET);

  /****************/
 /* Free memory. */
/****************/
		for (Index = 0; Index < MAX_ROMS; ++Index)
		{
			if (ROM[Index])
				free(ROM[Index]);
			if (ROM_Name[Index])
				free(ROM_Name[Index]);
			if (ROM_Status[Index])
				free(ROM_Status[Index]);
		}

  /***************/
 /* CooCooUnDoo */
/***************/
    		tcsetattr(fileno(stdin), TCSANOW, &RestoreTermIOs);
	}

	return 0;
}


void Timer(int signum)
{
}


void UpdateDisplay(char** ROM, char** ROM_Name, char** ROM_Status, int* ROM_Filtered, int Cols, int Rows, int Offset, int Index)
{
	int Count;
	int Row;
	int Col;
	int Display;
	char Buffer[BUFF_SIZE + 1];

  /**************************/
 /* Set background colour. */
/**************************/
	printf(VT100_SET_ATTRIB, VT100_ATTRIB_BG_BLUE);
	printf(VT100_ERASE_DISPLAY);

	Count = Offset;
	Row = 0;
	Col = 0;
	while (ROM_Filtered[Count] != -1)
	{
  /********************/
 /* Display an item. */
/********************/
		Display = FALSE;
		if (!strcmp(ROM_Status[ROM_Filtered[Count]], "correct"))
		{
			Display = TRUE;
			printf(VT100_SET_ATTRIB, VT100_ATTRIB_BOLD);
			printf(VT100_SET_ATTRIB, VT100_ATTRIB_FG_WHITE);
			printf(VT100_SET_ATTRIB, VT100_ATTRIB_BG_GREEN);
		}
		else if (!strcmp(ROM_Status[ROM_Filtered[Count]], "best available"))
		{
			Display = TRUE;
			printf(VT100_SET_ATTRIB, VT100_ATTRIB_BOLD);
			printf(VT100_SET_ATTRIB, VT100_ATTRIB_FG_BLACK);
			printf(VT100_SET_ATTRIB, VT100_ATTRIB_BG_GREEN);
		}
		else if (!strcmp(ROM_Status[ROM_Filtered[Count]], "incorrect"))
		{
			Display = TRUE;
			printf(VT100_SET_ATTRIB, VT100_ATTRIB_RESET);
			printf(VT100_SET_ATTRIB, VT100_ATTRIB_FG_WHITE);
			printf(VT100_SET_ATTRIB, VT100_ATTRIB_BG_MAGENTA);
		}
		else
		{
			Display = TRUE;
			printf(VT100_SET_ATTRIB, VT100_ATTRIB_RESET);
			printf(VT100_SET_ATTRIB, VT100_ATTRIB_FG_WHITE);
			printf(VT100_SET_ATTRIB, VT100_ATTRIB_BG_RED);
		}

		if (Display == TRUE)
		{
			printf(VT100_CURSOR_Y_X, 1 + BORDER_TOP + Row * ITEM_HEIGHT, 1 + BORDER_LEFT + Col * ITEM_WIDTH);
			memset(Buffer, ' ', ITEM_WIDTH);
			strcpy(Buffer, ROM_Name[ROM_Filtered[Count]]);
			Buffer[strlen(Buffer)] = ' ';
			Buffer[ITEM_WIDTH - 2] = '\0';
			printf(Buffer);

  /****************************/
 /* Highlight selected item. */
/****************************/
			if (Count == Index)
			{
				memset(Buffer, ' ', ITEM_WIDTH);
				Buffer[ITEM_WIDTH] = '\0';

				printf(VT100_SET_ATTRIB, VT100_ATTRIB_BG_BLACK);
				printf(VT100_CURSOR_Y_X, BORDER_TOP + Row * ITEM_HEIGHT, BORDER_LEFT + Col * ITEM_WIDTH);
				printf(Buffer);
				printf(VT100_CURSOR_Y_X, 2 + BORDER_TOP + Row * ITEM_HEIGHT, BORDER_LEFT + Col * ITEM_WIDTH);
				printf(Buffer);
				Buffer[1] = '\0';
				printf(VT100_CURSOR_Y_X, 1 + BORDER_TOP + Row * ITEM_HEIGHT, BORDER_LEFT + Col * ITEM_WIDTH);
				printf(Buffer);
				printf(VT100_CURSOR_Y_X, 1 + BORDER_TOP + Row * ITEM_HEIGHT, ITEM_WIDTH - 1 + BORDER_LEFT + Col * ITEM_WIDTH);
				printf(Buffer);
			}

  /**************************************/
 /* Set location to display next item. */
/**************************************/
			if (++Row >= Rows)
			{
				Row = 0;
				if (++Col >= Cols)
					break;
			}
		}

		++Count;
	}
  /*********************/
 /* Move cursor home. */
/*********************/
	printf(VT100_CURSOR_HOME);
}


void DisplayError(char* Error)
{
	printf(VT100_ATTRIB_SAVE);

  /******************************/
 /* Set the text style to use. */
/******************************/
        printf(VT100_SET_ATTRIB, VT100_ATTRIB_BOLD);
        printf(VT100_SET_ATTRIB, VT100_ATTRIB_FG_WHITE);
        printf(VT100_SET_ATTRIB, VT100_ATTRIB_BG_RED);

  /**********************/
 /* Display the error. */
/**********************/
	printf("%s\n", Error);

	printf(VT100_ATTRIB_RESTORE);
}


void GetRomInfo(char** ROM, char** ROM_Name, char** ROM_Status, int* ROM_Filtered, char* Filter, char* RomPath)
{
	FILE* File;
	int Index;
	int Size;
	int FilterCount;
	char* Pos1;
	char* Pos2;
	char Buffer[BUFF_SIZE + 1];
	char Temp[BUFF_SIZE + 1];

  /***************************************************************/
 /* Generate information about the Mame ROMs which are present. */
/***************************************************************/
   sprintf(Buffer, "./xmame.SDL -rp %s -srtn -lf > MameGameList.txt 2>/dev/null", RomPath);
	system(Buffer);
   sprintf(Buffer, "./xmame.SDL -rp %s -srtn -vrs > MameGameValid.txt 2>/dev/null", RomPath);
	system(Buffer);

  /*******************************************/
 /* Read the game data for use in the menu. */
/*******************************************/
	if (!(File = fopen("MameGameList.txt", "r")))
		DisplayError("Failed to open file: MameGameList.txt");
	else
	{
		Index = 0;
		while (!feof(File))
		{
			fgets(Buffer, BUFF_SIZE, File);

			if ((Pos1 = strchr(Buffer, ' ')) && (Pos2 = strchr(Buffer, '\"')))
			{
  /*************************/
 /* Get the ROM filename. */
/*************************/
				Size = Pos1 - Buffer;
				ROM[Index] = malloc(Size + 1);
				strncpy(ROM[Index], Buffer, Size);
				ROM[Index][Size] = '\0';

  /*********************/
 /* Get the ROM name. */
/*********************/
				Pos1 = strchr(Pos2 + 1, '\"');
				if (Pos1 && Pos2)
				{
					Size = Pos1 - Pos2 - 1;
					ROM_Name[Index] = malloc(Size + 1);
					strncpy(ROM_Name[Index], Pos2 + 1, Size);
					ROM_Name[Index][Size] = '\0';
				}

				++Index;
			}
		};
		fclose(File);
	}

  /**************************************************/
 /* Read the game status data for use in the menu. */
/**************************************************/
	if (!(File = fopen("MameGameValid.txt", "r")))
		DisplayError("Failed to open file: MameGameValid.txt");
	else
	{
		FilterCount = 0;
		Index = 0;
		while (!feof(File))
		{
			fgets(Buffer, BUFF_SIZE, File);

			if ((Pos1 = strchr(Buffer, ' ')))
			{
  /*************************/
 /* Get the ROM filename. */
/*************************/
				Size = Pos1 - Buffer;
				strncpy(Temp, Buffer, Size);
				Temp[Size] = '\0';

  /***************************************************************************/
 /* XMame has a bug which outputs a fault in the log, this is a workaround. */
/***************************************************************************/
				if (ROM[Index + 1] && !strcmp(Temp, ROM[Index + 1]))
               ++Index;

				if (ROM[Index] && !strcmp(Temp, ROM[Index]))
				{
  /***********************/
 /* Get the ROM status. */
/***********************/
					Pos2 = Pos1;
					while ((++Pos2)[0] == ' ');

					Size = strlen(Pos2) - 1;
					ROM_Status[Index] = malloc(Size + 1);
					strncpy(ROM_Status[Index], Pos2, Size);
					ROM_Status[Index][Size] = '\0';

  /*******************************************/
 /* Generate a filter to the required ROMs. */
/*******************************************/
					if (strstr(Filter, ROM_Status[Index]))
						ROM_Filtered[FilterCount++] = Index;

					++Index;
				}
			}
		};
		fclose(File);
	}
}


int GetKeys(char* Buffer, char FromChar, char ToChar)
{
	int Count;
	char Char;

	Count = 0;
	if (FromChar != '\0')
	{
		do
		{
			Char = fgetc(stdin);
		} while (Char != FromChar);
		Buffer[Count++] = Char;
	}
	do
	{
		Char = fgetc(stdin);
		if (Char != 255)
			Buffer[Count++] = Char;
	} while ((ToChar == '\0' && Char != 255) || (ToChar != '\0' && Char != ToChar));
	Buffer[Count] = '\0';

	return Count;
}

