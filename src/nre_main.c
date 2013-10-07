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
// list2scr:
//-----------------------------------------------------------------------------

WINDOW* list2scr(PLIST l) {

    WINDOW* p;
    int i = 0;
    int smincol = (COLS-l->mxlen)/2;

    // Populate a new pad:
    if((p = newpad(l->count,l->mxlen)) == NULL) { MyDBG(end0); } nre_list_gostart(l);
    do { mvwprintw(p, i, 0, "[x] %s", l->focus->nxt->e.line); wrefresh(p); i++; }
    while(nre_list_advance(l));

    // Refresh:
    if(prefresh(p,0,0,4,smincol,LINES-2,l->mxlen + smincol) == ERR) MyDBG(end1);

    // Return on success:
    return p;

    // Return on error:
    end1: destroy_win(p);
    end0: return NULL;
}

//-----------------------------------------------------------------------------
// load_data:
//-----------------------------------------------------------------------------

int load_data (PLIST list) {

    ELEM e;
    size_t i;

    while(1) {

        e.line = NULL; if(getline(&e.line, &i, stdin) < 0) break;
        for(i=0, e.len=strlen(e.line); i<e.len; i++) if(e.line[i] == '\n') e.line[i] = '\0';
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
    WINDOW *pad;
    int key;

    // Initialize list structure:
    if((list = nre_list_new()) == NULL) MyDBG(end0);
    if(load_data(list) < 0) MyDBG(end1);

    // Start ncurses:
    if(init_ncurses() < 0) MyDBG(end1);

    while((key = mvgetch(1,COLS/2)) != '\n') {

        if((pad = list2scr(list)) == NULL) MyDBG(end2);
        destroy_win(pad);
    }

    // End ncurses:
    endwin();

    // Return on success:
    nre_list_destroy(list);
    return 0;

    // Return on error:
    end2: endwin();
    end1: nre_list_destroy(list);
    end0: return -1;
}
