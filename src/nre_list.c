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

int nre_list_new(PLIST list)

{
    if((list->start = malloc(sizeof(NODE))) == NULL) return -1;
    list->focus = list->start;
    list->focus->nxt = NULL;
    return 0;
}

//-----------------------------------------------------------------------------
// nre_list_empty:
//-----------------------------------------------------------------------------

int nre_list_empty(PLIST list)

{
    if(list->start->nxt == NULL) return 0;
    return 1;
}

//-----------------------------------------------------------------------------
// nre_list_gostart:
//-----------------------------------------------------------------------------

void nre_list_gostart(PLIST list)

{
    list->focus = list->start;
}
