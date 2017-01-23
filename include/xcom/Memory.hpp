/**
 * File    : Memory.hpp
 * Author  : Emir Uner
 * Summary : Common memory (de)allocation functions.
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

#ifndef XCOM_MEMORY_HPP_INCLUDED
#define XCOM_MEMORY_HPP_INCLUDED

#ifndef XCOM_INTEGRAL_HPP_INCLUDED
#include <xcom/Integral.hpp>
#endif

#include <new>

/**
 * Allocate given number of bytes.
 */
extern "C" void* xcomMemAlloc(xcom::SizeT size);

/**
 * Free memory allocated by xcomMemAlloc
 */
extern "C" void xcomMemFree(void* buf);

namespace xcom
{
    /**
     * Allocates memory for an array of T with given size.
     * No initialization is done on the allocated memory.
     * T must be a POD.
     */
    template <typename T>
    inline T* allocArray(SizeT count)
    {
        return static_cast<T*>(xcomMemAlloc(sizeof(T) * count));
    }

    /**
     * xcomMemAlloc'ing new.
     */
    template <typename T>
    inline T* allocNew()
    {
        return new (xcomMemAlloc(sizeof(T))) T;
    }
}

#endif
