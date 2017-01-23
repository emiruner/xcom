/**
 * File    : SharedLibrary.cpp
 * Author  : Emir Uner
 * Summary : Shared library access routines for Linux.
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

#include <xcom/Integral.hpp>
#include <dlfcn.h>

extern "C"
xcom::Char* xcomDuplicateString(xcom::Char const* src);

extern "C"
void* xcomLoadSharedLibrary(xcom::Char const* fullPath, xcom::Char** errorMsg)
{
    void* handle;
    
    handle = dlopen(reinterpret_cast<char const*>(fullPath), RTLD_NOW);
    xcom::Char* errstr = reinterpret_cast<xcom::Char*>(dlerror());
    if(handle == 0)
    {
        *errorMsg = xcomDuplicateString(errstr);
    }

    return handle;    
}

extern "C"
void* xcomResolveSymbol(void* library, xcom::Char const* sym,
                        xcom::Char** errorMsg)
{
    void* symbol;
    
    symbol = dlsym(library, reinterpret_cast<char const*>(sym));
    xcom::Char* errstr = reinterpret_cast<xcom::Char*>(dlerror());
    if(errstr)
    {
        *errorMsg = xcomDuplicateString(errstr);
    }
    else
    {
        *errorMsg = 0;
    }
    
    return symbol;
}

extern "C"
void xcomUnloadSharedLibrary(void* library, xcom::Char** errorMsg)
{
    if(dlclose(library) != 0)
    {
        xcom::Char* errstr = reinterpret_cast<xcom::Char*>(dlerror());
        *errorMsg = xcomDuplicateString(errstr);
    }
    else
    {
        *errorMsg = 0;
    }
}
