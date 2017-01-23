/**
 * File    : GUID.cpp
 * Author  : Emir Uner
 * Summary : GUID generation function.
 */

/**
 * This file is part of XCOM.
 *
 * Copyright (C) 2003 Emir Uner
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <xcom/GUID.hpp>
#include <cstdio>

extern "C"
bool xcomGenerateGUID(xcom::GUID* guid)
{
    xcom::GUID result;
    FILE* pipe = popen("uuidgen", "r");

    if(pipe == 0)
    {
        return false;
    }
    
    char guidbuf[37];
    
    for(int i = 0; i < 37; ++i)
    {
        guidbuf[i] = '\0';
    }
    
    if(fread(guidbuf, 36, 1, pipe) != 1)
    {
        pclose(pipe);
        return false;
    }
    
    pclose(pipe);
    
    if(!xcomParseGUID(guidbuf, &result))
    {
        return false;
    }

    *guid = result;
    return true;
}
