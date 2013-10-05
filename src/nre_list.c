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

#include "nre_list.h"

//-----------------------------------------------------------------------------
// nre_list_new:
//-----------------------------------------------------------------------------

PLIST nre_list_new(void)

{
    PLIST pl;

    if((pl = malloc(sizeof(LIST))) == NULL) return NULL;
    if((pl->start = malloc(sizeof(NODE))) == NULL) return NULL;
    pl->focus = pl->start;
    pl->focus->nxt = NULL;
    pl->count = 0;
    return pl;
}

//-----------------------------------------------------------------------------
// nre_list_empty:
//-----------------------------------------------------------------------------

int nre_list_empty(PLIST list)

{
    if(list->start->nxt == NULL) return 1;
    return 0;
}

//-----------------------------------------------------------------------------
// nre_list_end:
//-----------------------------------------------------------------------------

int nre_list_end(PLIST list)

{
    if(list->focus->nxt->nxt == NULL) return 1;
    return 0;
}

//-----------------------------------------------------------------------------
// nre_list_gostart:
//-----------------------------------------------------------------------------

void nre_list_gostart(PLIST list)

{
    list->focus = list->start;
}

//-----------------------------------------------------------------------------
// nre_list_advance:
//-----------------------------------------------------------------------------

int nre_list_advance(PLIST list) {

    if(nre_list_empty(list)) return 0;
    if(nre_list_end(list)) return 0;
    list->focus = list->focus->nxt;
    return 1;
}

//-----------------------------------------------------------------------------
// nre_list_insert:
//-----------------------------------------------------------------------------

int nre_list_insert(ELEM e, PLIST list)

{
    PNODE pn;

    if((pn = malloc(sizeof(NODE))) == NULL) return -1;
    pn->e = e;
    pn->nxt = list->focus->nxt;
    list->focus->nxt = pn;
    list->count++;
    return 1;
}

//-----------------------------------------------------------------------------
// nre_list_delete:
//-----------------------------------------------------------------------------

int nre_list_delete(PLIST list)

{
    PNODE pn;

    if(nre_list_empty(list)) return 0;
    pn = list->focus->nxt;
    list->focus->nxt = pn->nxt;
    free(pn);
    list->count--;
    return 1;
}

//-----------------------------------------------------------------------------
// nre_list_destroy:
//-----------------------------------------------------------------------------

void nre_list_destroy(PLIST list)

{
    nre_list_gostart(list);
    while(nre_list_delete(list));
    free(list->start);
    free(list);
}
