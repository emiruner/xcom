/**
 * File    : Portability.hpp
 * Author  : Emir Uner
 * Summary : The functions and wrapper classes needed by XCOM core.
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

#ifndef XCOM_INTERNAL_RUNTIME_HPP_INCLUDED
#define XCOM_INTERNAL_RUNTIME_HPP_INCLUDED

#ifndef XCOM_TYPES_HPP_INCLUDED
#include <xcom/Types.hpp>
#endif

extern "C"
{

// --- Atomic Integer Inc/Dec Operations --    
/**
 * Increment the given 32-bit integer in a thread safe manner.
 */
xcom::Int xcomInterlockedIncrement(xcom::Int* num);

/**
 * Decrement the given 32-bit integer in a thread safe manner.
 */
xcom::Int xcomInterlockedDecrement(xcom::Int* num);

// --- Shared Library Access Operations ---
/**
 * Open the given shared library given full path.
 * In case of an error, return null and set errorMsg to point explanation
 * string. The returned string must be freed by xcomMemFree.
 * If no error occurs errorMsg is not touched.
 */
void* xcomLoadSharedLibrary(xcom::Char const* fullPath, xcom::Char** errorMsg);

/**
 * Resolve the named symbol from the given library.
 * Return the value of the given symbol. In case not found or
 * the actual value is null, null returned. In case of an error errorMsg
 * is set otherwise errorMsg is set to null.
 */
void* xcomResolveSymbol(void* library, xcom::Char const* sym,
                        xcom::Char** errorMsg);

/**
 * Close the previously opened shared library.
 */
void xcomUnloadSharedLibrary(void* library, xcom::Char** errorMsg);

// --- Filesystem Operations ---
/**
 * Transform the given path into an absolute one.
 * If the path is already absolute duplicates it and return.
 * If it is a relative path, transforms into absolute using working
 * directory information.
 * In case of any failure returns null.
 */
xcom::Char* xcomMakePathAbsolute(xcom::Char const* relativePath);

/**
 * Transform libraryName into a filename considering the platform issues.
 */
xcom::Char* xcomMakeLibraryFilename(xcom::Char const* libraryName);

/**
 * Generate library name from library path name.
 * The path can be either relative or absolute.
 */
xcom::Char* xcomMakeLibraryName(xcom::Char const* pathName);
    
/**
 * Return the absolute path of the configuration file for the current
 * executable. This function only works before any call to directory
 * changing functions.
 */
xcom::Char* xcomConfigFileForApplication();

/**
 * Returns true if the specified file exists.
 */
xcom::Int xcomFileExists(xcom::Char const* file);

/**
 * Combines given path with the filename.
 */
xcom::Char* xcomCombinePathWithFile(xcom::Char const* path,
                                    xcom::Char const* filename);
    
// --- GUID Generation Operations ---
bool xcomGenerateGUID(xcom::GUID* guid);

// --- Mutex Operations ---    
// +--------------------------------------------------------------------------+
// |WARNING!!!: Bad usage of mutexes lead to errors that are silently ignored.|
// +--------------------------------------------------------------------------+

/**
 * Create a non-recursive mutex and return it.
 */
void* xcomCreateMutex();

/**
 * Lock mutex.
 */
void xcomLockMutex(void* mutex);

/**
 * Unlock mutex.
 */
void xcomUnlockMutex(void* mutex);

/**
 * Destroy the mutex.
 */
void xcomDestroyMutex(void* mutex);
    
} // extern "C"

namespace xcom
{
    namespace internal
    {
        /**
         * Wrapper for mutex functions.
         */
        class Mutex
        {
        public:
            /**
             * Initialize.
             */
            inline Mutex()
            : mutex_(xcomCreateMutex())
            {
            }
            
            /**
             * Destroy.
             */
            inline ~Mutex()
            {
                xcomDestroyMutex(mutex_);
            }
            
            /**
             * Lock mutex.
             */
            inline void lock()
            {
                xcomLockMutex(mutex_);
            }
            
            /**
             * Unlock mutex.
             */
            inline void unlock()
            {
                xcomUnlockMutex(mutex_);
            }
            
            /**
             * Scoped locking.
             */
            struct ScopedLock
            {
                inline ScopedLock(Mutex& mutex)
                : mutex_(mutex)
                {
                    mutex_.lock();
                }
                
                inline ~ScopedLock()
                {
                    mutex_.unlock();
                }

            private:
                Mutex& mutex_;
            };
            
        private:
            void* mutex_;
        };
        
        /**
         * Atomic counter.
         */
        struct AtomicCount
        {
            /**
             * Initializes to zero.
             */
            inline AtomicCount()
            : count_(0)
            {
            }
            
            /**
             * Increment.
             */
            inline xcom::Int operator++()
            {
                return xcomInterlockedIncrement(&count_);
            }

            /**
             * Decrement.
             */
            inline xcom::Int operator--()
            {
                return xcomInterlockedDecrement(&count_);
            }
            
        private:
            Int count_;
        };

        /**
         * Shared library functions wrapper.
         * All functions throw xcom::String in case of an error.
         */
        struct SharedLibrary
        {
            /**
             * Opens the library.
             */
            inline SharedLibrary(xcom::Char const* path)
            {
                xcom::Char* err;
                
                if((handle_ = xcomLoadSharedLibrary(path, &err)) == 0)
                {
                    throw xcom::String::adopt(err);
                }
            }
            
            /**
             * Get the symbols value.
             */
            inline void* resolve(xcom::Char const* symbolName)
            {
                xcom::Char* err;
                void* symbol;
                
                symbol = xcomResolveSymbol(handle_, symbolName, &err);
                if(err != 0)
                {
                    throw xcom::String::adopt(err);
                }
                
                return symbol;
            }
                
            /**
             * Closes the library.
             * Do not throw in case of error.
             */
            inline ~SharedLibrary()
            {
                xcom::Char* err;

                xcomUnloadSharedLibrary(handle_, &err);
                if(err != 0)
                {
                    xcomMemFree(err);
                }
            }
            
        private:
            void* handle_;
        };

        /**
         * Wrapper for SharedLibrary::resolve to simplify it's usage.
         */
        template <typename T>
        inline T resolve(SharedLibrary& lib, Char const* symbolName)
        {
            return (T)(lib.resolve(symbolName));
        }

        /**
         * Wrapper.
         */
        inline String makeLibraryName(Char const* pathName)
        {
            return String::adopt(xcomMakeLibraryName(pathName));
        }    

        inline String makeLibraryFilename(Char const* libraryName)
        {
            return String::adopt(xcomMakeLibraryFilename(libraryName));
        }

        inline String combinePathWithFile(Char const* path,Char const*filename)
        {
            return String::adopt(xcomCombinePathWithFile(path, filename));
        }
        

    } // namespace internal
} // namespace xcom


#endif
