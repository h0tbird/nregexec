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
// Include guard:
//-----------------------------------------------------------------------------

#ifndef _NRE_LIST_
#define _NRE_LIST_

//-----------------------------------------------------------------------------
// Includes:
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include "nre_common.h"

//-----------------------------------------------------------------------------
// Typedefs:
//-----------------------------------------------------------------------------

typedef struct _ELEM {

    char *line; // This is the raw line of text.
    int  len;   // Total length of the raw line.
    int  mask;  // Binary mask of metadata.

} ELEM, *PELEM;

typedef struct _NODE {

    ELEM         e;
    struct _NODE *pre;
    struct _NODE *nxt;

} NODE, *PNODE;

typedef struct _LIST {

   PNODE start; // Pointer to the start of the list.
   PNODE focus; // Pointer to the focused element of the list.
   int   count; // Total number of elements in the list.
   int   mxlen; // Length of the longest string on the list.

} LIST, *PLIST;

//-----------------------------------------------------------------------------
// Prototypes:
//-----------------------------------------------------------------------------

PLIST nre_list_new(void);
int nre_list_empty(PLIST list);
int nre_list_end(PLIST list);
void nre_list_gostart(PLIST list);
int nre_list_advance(PLIST list);
int nre_list_insert(ELEM e, PLIST list);
int nre_list_delete(PLIST list);
void nre_list_destroy(PLIST list);

//-----------------------------------------------------------------------------
// End of include guard:
//-----------------------------------------------------------------------------

#endif
