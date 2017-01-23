/**
 * File    : ExcHelper.hpp
 * Author  : Emir Uner
 * Summary : C++ Exception helpers.
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
#ifndef XCOM_EXCHELPER_HPP_INCLUDED
#define XCOM_EXCHELPER_HPP_INCLUDED

namespace xcom
{
    /**
     * Wrapper around xcomGetExceptionTypes.
     */
    inline IUnknownSeq& getExceptionTypes()
    {
        return *(IUnknownSeq*)xcomGetExceptionTypes();
    }

    template <typename T>
    struct Registrar
    {
        Registrar()
        {
            IUnknownSeq* types = (IUnknownSeq*)xcomGetExceptionTypes();
            
            TypeDesc<T>::addSelf(*types);
            xcomRegisterThrower(&T::excThrower,
               xcomFindMetadata((SequenceData*)types, TypeDesc<T>::getName()));
        }   
    };

    template <typename T>
    struct Registration
    {
        static Registrar<T> reg;
    };
    
    template <typename T>
    Registrar<T> Registration<T>::reg;
    
} // namespace xcom

#endif
