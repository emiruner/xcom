/**
 * File    : Mutex.cpp
 * Author  : Emir Uner
 * Summary : Mutex functions for linux.
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

#include <xcom/Memory.hpp>

#include <pthread.h>

inline pthread_mutex_t* asMutex(void* mutex)
{
    return static_cast<pthread_mutex_t*>(mutex);
}

extern "C"
void* xcomCreateMutex()
{
    pthread_mutex_t* mutex;

    mutex = asMutex(xcomMemAlloc(sizeof(pthread_mutex_t)));
    pthread_mutex_init(mutex, 0);

    return mutex;
}

extern "C"
void xcomLockMutex(void* mutex)
{
    pthread_mutex_lock(asMutex(mutex));
}

extern "C"
void xcomUnlockMutex(void* mutex)
{
    pthread_mutex_unlock(asMutex(mutex));
}

extern "C"
void xcomDestroyMutex(void* mutex)
{
    pthread_mutex_destroy(asMutex(mutex));
    xcomMemFree(mutex);
}
