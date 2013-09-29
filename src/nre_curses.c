/******************************************************************************
* Copyright (C) 2013 Marc Villacorta Morera
*
* Authors: Marc Villacorta Morera <marc.villacorta@gmail.com>
*
* This file is part of nregexec (nre).
*
* Nregexec is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Nregexec is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with nregexec. If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

//-----------------------------------------------------------------------------
// Includes:
//-----------------------------------------------------------------------------

#include "nre_curses.h"

//-----------------------------------------------------------------------------
// init_ncurses:
//-----------------------------------------------------------------------------

int init_ncurses(void) {

    if(freopen("/dev/tty", "rw", stdin) == NULL) MyDBG(end0);
    if(initscr() == NULL) MyDBG(end0);
    if(raw() == ERR) MyDBG(end1);
    if(refresh() == ERR) MyDBG(end1);

    // Return on success:
    return 0;

    // Return on error:
    end1: endwin();
    end0: return -1;
}

//-----------------------------------------------------------------------------
// create_newwin:
//-----------------------------------------------------------------------------

WINDOW *create_newwin(int height, int width, int starty, int startx) {

    WINDOW *local_win;

    if((local_win = newwin(height, width, starty, startx)) == NULL) MyDBG(end0);
    box(local_win, 0 , 0); if(wrefresh(local_win) == ERR) MyDBG(end0);

    // Return on success:
    return local_win;

    // Return on error:
    end0: return NULL;
}

//-----------------------------------------------------------------------------
// destroy_win:
//-----------------------------------------------------------------------------

void destroy_win(WINDOW *local_win) {

    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(local_win);
    delwin(local_win);
}
