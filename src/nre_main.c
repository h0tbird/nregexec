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
// input: This function prints the interactive user input buffer in the center
//        of the screen. It also moves the cursor to the 'p' position and
//        handles cursor movementis as well as text insertion and deletion.
//-----------------------------------------------------------------------------

int input(char *s, int *p) {

    int c, i, l = strlen(s);

    // Print the current buffer (centered):
    mvprintw(1, (COLS-l)/2, "%s", s);
    move(1,((COLS+l)/2)-*p);

    // Get one key (blocking):
    switch (c = getch()) {

        // Handle cursor movement:
        case KEY_LEFT:  if(*p != l) (*p)++; break;
        case KEY_RIGHT: if(*p != 0) (*p)--; break;
        case CTRL_A:    *p=l; break;
        case CTRL_E:    *p=0; break;
        case KEY_DOWN:  break;
        case KEY_UP:    break;

        // Handle deletion:
        case KEY_BACKSPACE:
            move(1,0); clrtoeol();
            for(i=*p; i!=0 && i!=l; i--) s[l-1-i] = s[l-i];
            if(i!=l) s[l-1] = '\0';
            break;

        // Handle insertion:
        default:
            if(l==MAXLEN-1) break;
            for(i=0; i<=*p; i++) s[l-i+1] = s[l-i];
            s[l-*p] = c; s[l+1] = '\0';
            break;
    }

    // Return the key code:
    return c;
}

//-----------------------------------------------------------------------------
// list2scr: This function creates one new pad, big enough to hold all the
//           data in the list. It feeds the new pad with filtered information
//           and displays a chunk of it in the screen.
//-----------------------------------------------------------------------------

WINDOW* list2scr(PLIST l) {

    WINDOW* p;
    int i = 0;
    int smincol = (COLS-l->mxlen)/2;

    // Create one pad as big as the list:
    if((p = newpad(l->count,l->mxlen)) == NULL) { MyDBG(end0); } nre_list_gostart(l);

    // Poppulate the new pad:
    do { mvwprintw(p, i, 0, "[x] %s", l->focus->nxt->e.line); wrefresh(p); i++; }
    while(nre_list_advance(l));

    // Copy a chunk from the pad and display it on the screen:
    if(prefresh(p,0,0,4,smincol,LINES-2,l->mxlen + smincol) == ERR) MyDBG(end1);

    // Return on success:
    return p;

    // Return on error:
    end1: destroy_win(p);
    end0: return NULL;
}

//-----------------------------------------------------------------------------
// load_data: This function reads from 'stdin' one line at a time. It removes
//            any newline character before storing the string and its length
//            into the dynamic list structure.
//-----------------------------------------------------------------------------

int load_data (PLIST list) {

    ELEM e;
    size_t i;

    while(1) {

        // Load from 'stdin':
        e.line = NULL;
        if(getline(&e.line, &i, stdin) < 0) break;

        // Find and replace '\n' newline character:
        for(i=0, e.len=strlen(e.line); i<e.len; i++) {
            if(e.line[i] == '\n') {
                e.line[i] = '\0';
                e.len-=1;
            }
        }

        // Insert the new element into the list:
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
    PLIST list;     // List of input strings and its metadata.
    WINDOW *pad;    // Non-visible ncurses virtual screen.
    int pos = 0;    // Cursor position on input 's' string.
    int key = 0;    // Last key pressed on keyboard.
    char s[MAXLEN]; // Current regex input string.

    // Initialize and feed the list structure from 'stdin':
    if((list = nre_list_new()) == NULL) MyDBG(end0);
    if(load_data(list) < 0) MyDBG(end1);

    // Initialize ncurses:
    if(init_ncurses() < 0) MyDBG(end1);

    // Loop until enter is pressed:
    s[0] = '\0'; while((key = input(&s[0], &pos)) != '\n') {

        // For every pressed key:
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
