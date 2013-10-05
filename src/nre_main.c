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

#include "nre_main.h"

//-----------------------------------------------------------------------------
// load_data:
//-----------------------------------------------------------------------------

int load_data (PLIST list) {

    ELEM e;
    int i;

    while(1) {

        e.line = NULL;
        if(getline(&e.line, &e.size, stdin) < 0) break;
        for(i=0; i<e.size; i++) if(e.line[i] == '\n') e.line[i] = '\0';
        if(nre_list_insert(e, list) < 0) MyDBG(end0);
    }

    // Return on success:
    return 0;

    // Return on error:
    end0: free(e.line);
    return -1;
}

//-----------------------------------------------------------------------------
// Entry point:
//-----------------------------------------------------------------------------

int main(void)

{
    // Variables:
    PLIST list;
    WINDOW *win_iput, *win_oput;

    // Initialize list structure:
    if((list = nre_list_new()) == NULL) MyDBG(end0);
    if(load_data(list) < 0) MyDBG(end1);

    // Ncurses:
    if(init_ncurses() < 0) MyDBG(end1);
    if((win_iput=create_newwin(3,70,(LINES - 3)/10,(COLS - 70)/2)) == NULL) MyDBG(end1);
    if((win_oput=create_newwin(20,70,8,(COLS - 70)/2)) == NULL) MyDBG(end1);

    getch();
    destroy_win(win_iput);
    destroy_win(win_oput);
    endwin();

    // Return on success:
    nre_list_destroy(list);
    return 0;

    // Return on error:
    end1: nre_list_destroy(list);
    end0: return -1;
}
