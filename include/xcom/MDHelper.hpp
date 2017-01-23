/**
 * File    : MDHelper.hpp
 * Author  : Emir Uner
 * Summary : Metadata registration helpers called by TypeDesc::addSelf methods.
 * WARNING : DO NOT INCLUDE THIS FILE DIRECTLY
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

#ifndef XCOM_MDHELPER_HPP_INCLUDED
#define XCOM_MDHELPER_HPP_INCLUDED

// The following functions assume the following:
//
// * The xcom::IUnknownRaw** arrays actually contain xcom::metadata::ITypeRaw's
// * The returned xcom::IUnknownRaw* are accually consistens with the function
//   names, so can be cast directly.
// * All passed interface pointer are adopted by the called function.

extern "C"
{

/**
 * Create array metadata object.
 */
xcom::IUnknownRaw* xcomCreateArrayMD(xcom::Char const* name,
                                     xcom::IUnknownRaw* elt,
                                     xcom::Int size);

/**
 * Create sequence metadata object.
 */
xcom::IUnknownRaw* xcomCreateSequenceMD(xcom::Char const* name,
                                        xcom::IUnknownRaw* elt);

/**
 * Create array struct object.
 */
xcom::IUnknownRaw* xcomCreateStructMD(xcom::Char const* name,
                                      xcom::Int size,
                                      xcom::Int elementCount,
                                      xcom::IUnknownRaw** types,
                                      xcom::Char const** names,
                                      xcom::Int* offsets);

/**
 * Create exception metadata object.
 */
xcom::IUnknownRaw* xcomCreateExceptionMD(xcom::Char const* name,
                                         xcom::IUnknownRaw* base,
                                         xcom::Int size,
                                         xcom::Int elementCount,
                                         xcom::IUnknownRaw** types,
                                         xcom::Char const** names,
                                         xcom::Int* offsets);

/**
 * Create enum metadata object.
 */
xcom::IUnknownRaw* xcomCreateEnumMD(xcom::Char const* name,
                                    xcom::Char const** elems,
                                    xcom::Int elemCount);

/**
 * Create interface metadata object.
 * Method info is filled with xcomAddMethodToItf function using
 * the returned cookie.
 */
xcom::IUnknownRaw* xcomCreateInterfaceMD(xcom::Char const* name,
                                         xcom::GUID const* iid,
                                         xcom::IUnknownRaw* base,
                                         void** cookie);

/**
 * Add a method to interface metadata.
 */
void xcomAddMethodToItf(void* cookie,
                        xcom::Char const* name,
                        xcom::IUnknownRaw* ret,
                        xcom::Int paramCount,
                        xcom::Int* modes,
                        xcom::IUnknownRaw** types,
                        xcom::Char const** names);


/**
 * Create a delegate descriptor.
 */
xcom::IUnknownRaw* xcomCreateDelegateMD(xcom::Char const* name,
                                    xcom::IUnknownRaw* ret,
                                    xcom::Int paramCount,
                                    xcom::Int* modes,
                                    xcom::IUnknownRaw** types,
                                    xcom::Char const** names);
    
/**
 * Add metadata objects for builtin types to the sequence.
 */
void xcomPopulateBuiltin(xcom::IUnknownSeq::RawType* types);

/**
 * Searches the given sequence of interfaces for the given type specified by
 * the name. Returns nil if search fails.
 */
xcom::IUnknownRaw* xcomFindMetadata(xcom::IUnknownSeq::RawType const* types,
                                    xcom::Char const* name);

/**
 * Adds given type to the type list.
 */
void xcomAddType(xcom::IUnknownSeq::RawType* types, xcom::IUnknownRaw* type);

/**
 * Returns 1 if the given type found in the type sequence,
 * 0 if not found.
 */
xcom::Int xcomTypeExists(xcom::IUnknownSeq::RawType* types, xcom::Char const* name);

/**
 * Destroy the given object using the metadata.
 * Does not release matadata interface.
 */
void xcomGenericDestroy(void* data, xcom::IUnknownRaw* desc);
    

} // extern "C"

namespace xcom
{
    /**
     * Wrapper for xcomFindMetadata.
     * Warning: Returns a raw pointer, must be adopted to be released.
     */
    inline IUnknownRaw* rawFindMetadata(IUnknownSeq const& types, Char const* name)
    {
        return xcomFindMetadata((IUnknownSeq::RawType*)&types, name);
    }
    
    /**
     * Searches the type sequence using findMetadata function then if fails
     * calls the type description registeration function method to register
     * the given type and returns the metadata associated with the given type.
     * Warning: Returns a raw pointer, must be adopted to be released.
     */
    inline IUnknownRaw* rawFindOrReg(IUnknownSeq& types, Char const* name, void (*adder)(IUnknownSeq&))
    {
        IUnknownRaw* found = rawFindMetadata(types, name);
            
        if(found == 0)
        {
            adder(types);
            return rawFindMetadata(types, name);
        }
        
        return found;
    }

    /**
     * Automatically adopting version of rawFindOrReg.
     */
    inline IUnknown findOrRegister(IUnknownSeq& types, Char const* name, void (*adder)(IUnknownSeq&))
    {
        return rawFindOrReg(types, name, adder);
    }

    /**
     * Wrapper for xcomAddType.
     */
    inline void addType(IUnknownSeq& types, IUnknownRaw* type)
    {
        xcomAddType((IUnknownSeq::RawType*) &types, type);
    }

    /**
     * Wrapper for xcomTypeExists.
     */
    inline bool typeExists(IUnknownSeq& types, Char const* name)
    {
        return xcomTypeExists((xcom::IUnknownSeq::RawType*) &types, name);
    }    

    /**
     * Wrapper for xcomGenericDestroy.
     * Assumes that desc is a xcom::metadata::IType in reality or derived.
     */
    inline void genericDestroy(void* data, IUnknown const& desc)
    {
        xcomGenericDestroy(data, desc.ptr_);
    }

    /**
     * Wrapper for xcomPopulateBuiltin.
     */
    inline void populateBuiltin(IUnknownSeq& types)
    {
        xcomPopulateBuiltin((IUnknownSeq::RawType*)&types);
    }
    
}

#endif
