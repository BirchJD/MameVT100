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

This software provides a simple menu for selecting a ROM to be used when
starting a game in XMAME. This allows XMAME to run games full screen using
SDL libraries. The application can be used with a keyboard or switches on 
the Raspberry Pi GPIO pins. The the following video on YouTube for a
demonstration on the Raspberry Pi using GPIO pins:
https://www.youtube.com/watch?v=tHjeFawO6u0

The application MameVT100 should be placed in the directory /root/.xmame/
along with the xmame.SDL application. The ROM files should be placed in
/root/.xmame/roms/

Instructions on how to build the xmame.SDL application can be found here:
http://www.newsdownload.co.uk/pages/RPiMameMess.html

The application was originally written for the Raspberry Pi to provide a
cheap and simple MAME emulator for use in home MAME projects.

The application keys have been designed to make use with MAME easy.
Cursor keys are used to select the required ROM. '1' is used to start
the selected game. And '2' is used to exit the application. As the
source code is distributed under the GNU General Public License, the 
source code can be modified to change the colours or keys or enhance the
application. As long as the License is strictly adhered to, and 
preferably the source code checked back into GIT under a new branch of
the original code.

The first time the application is run, the RESCAN option should be
specified to update the menu items with the ROMs in the roms directory.
This should be repeated if the ROMs are changed in the roms directory.
e.g.
./MameVT100 /root/.xmame/ /root/.xmame/roms/ "|correct|best available|" RESCAN

It is possible to configure Linux to auto login, the instructions for
this vary with the distribution of Linux used.

To auto start the application when logging in, do the following at a 
command prompt:
cd ~
nano .bash_profile
modprobe snd-bcm2835
cd /root/.xmame/
./MameVT100 /root/.xmame/ /root/.xmame/roms/ "|correct|best available|"

Then press ^O ENTER ^X, where ^ means hold down the CTRL key while 
pressing the next key.

This will show a menu displaying only valid ROMs which are present and valid.

Other options are:
Display all ROMs whatever their status.
./MameVT100 /root/.xmame/ /root/.xmame/roms/ "|correct|best available|incorrect|not found|"

Display all ROMs present if they are valid or not.
./MameVT100 /root/.xmame/ /root/.xmame/roms/ "|correct|best available|incorrect|"

Display invalid ROMs (ROMs which are missing or invalid).
./MameVT100 /root/.xmame/ /root/.xmame/roms/ "|incorrect|not found|"

