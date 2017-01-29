/**
 * File    : Atomic.cpp
 * Author  : Emir Uner
 * Summary : Atomic increment/decrement implementations for Linux.
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

extern "C"
xcom::Int xcomInterlockedIncrement(xcom::Int* num)
{
    xcom::Int newVal = *num + 1;
    __atomic_fetch_add(num, 1, __ATOMIC_SEQ_CST);
    return newVal;
}

extern "C"
xcom::Int xcomInterlockedDecrement(xcom::Int* num)
{
    xcom::Int newVal = *num - 1;
    __atomic_fetch_add(num, -1, __ATOMIC_SEQ_CST);
    return newVal;
}
