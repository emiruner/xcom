/**
 * File    : Loader.hpp
 * Author  : Emir Uner
 * Summary : Component loader functions.
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

#ifndef XCOM_LOADER_HPP_INCLUDED
#define XCOM_LOADER_HPP_INCLUDED

#include <xcom/GUID.hpp>
#include <xcom/ILibrary.hpp>
#include <xcom/metadata/MDTypes.hpp>
#include <stdexcept>

extern "C"
{

/**
 * Search for the specified library and return a handle to it.
 * User can freely release the interface returned, system
 * holds the library until it can be unloaded safely.
 */    
xcom::ILibraryRaw* xcomLoad(xcom::Char const* name);

/**
 * Load a library from the specified location. This function
 * loads the given library without any version checks.
 */
xcom::ILibraryRaw* xcomLoadFrom(xcom::Char const* path);

/**
 * Same as xcomLoad, but this time add the classes that contained
 * in this library to globally accessible classes.
 */
xcom::ILibraryRaw* xcomLoadAsBuiltin(xcom::Char const* name);

/**
 * Same as xcomLoadFrom and xcomLoadAsBuiltin.
 */
xcom::ILibraryRaw* xcomLoadFromAsBuiltin(xcom::Char const* path);
    
/**
 * Create an instance of the named class. Searches only libraries
 * loaded as builtin.
 */
xcom::IUnknownRaw* xcomCreateObject(xcom::Char const* classname);

/**
 * Add a path to the component search path. If none has given only
 * machine wide component repository is consulted.
 */
void xcomAddLibrarySearchPath(xcom::Char const* fullPath);
    
/**
 * Get the metadata for the specified interface.
 */
xcom::metadata::IInterfaceRaw* xcomGetMetadata(xcom::GUID const* guid);    

} // extern "C"

namespace xcom
{
    
    inline ILibrary load(xcom::Char const* name)
    {
        return xcomLoad(name);
    }

    inline ILibrary loadFrom(xcom::Char const* path)
    {
        return xcomLoadFrom(path);
    }

    inline ILibrary loadAsBuiltin(xcom::Char const* name)
    {
        return xcomLoadAsBuiltin(name);
    }
    
    inline ILibrary loadFromAsBuiltin(xcom::Char const* path)
    {
        return xcomLoadFromAsBuiltin(path);
    }

    inline IUnknown createObject(xcom::Char const* classname)
    {
        return xcomCreateObject(classname);
    }

    inline void addLibrarySearchPath(xcom::Char const* fullPath)
    {
        xcomAddLibrarySearchPath(fullPath);
    }

    template <typename Itf>
    inline Itf createObjectAs(xcom::Char const* classname)
    {
        IUnknown obj(xcomCreateObject(classname));
        
        if(obj.isNil())
        {
            throw std::runtime_error("Object creation failed.");
        }

        return xcom::cast<Itf>(obj);
    }

    inline metadata::IInterface getMetadata(xcom::Char const* guidStr)
    {
        GUID guid;
        
        xcomParseGUID(guidStr, &guid);
        
        return metadata::IInterface(xcomGetMetadata(&guid));
    }
    
    inline metadata::IInterface getMetadata(xcom::GUID const& guid)
    {
        return metadata::IInterface(xcomGetMetadata(&guid));
    }

} // namespace xcom

#endif
