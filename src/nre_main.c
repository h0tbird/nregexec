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

void load_data (PLIST list) {

    char *line = NULL;
    size_t size;

    while(1) {

        if(getline(&line, &size, stdin) == -1) break;
        printf("LOAD: %s", line);
    }

    free(line);
}

//-----------------------------------------------------------------------------
// Entry point:
//-----------------------------------------------------------------------------

int main(int argc, char *argv[])

{
    // Variables:
    PLIST list = nre_list_new();

    // Load data from stdin to list:
    load_data(list);

    // Return:
    nre_list_destroy(list);
    return 0;
}
