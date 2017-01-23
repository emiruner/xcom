/**
 * File    : Declared.hpp
 * Author  : Emir Uner
 * Summary : Declared class definitions.
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

#ifndef XCOM_METADATA_DECLARED_HPP_INCLUDED
#define XCOM_METADATA_DECLARED_HPP_INCLUDED

#ifndef XCOM_METADATA_TYPE_HPP_INCLUDED
#include <xcom/metadata/Type.hpp>
#endif

#include <string>

namespace xcom { namespace metadata {

/**
 * Base type for user defined types.
 */
class DeclaredImpl : public TypeImpl
{
public:
    /**
     * Declared  with given name and type.
     */
    DeclaredImpl(int kind, char const* name)
    : TypeImpl(kind), name_(name)
    {
    }

    /**
     * My name. This name includes the scope.
     * For example for the type referred as xcom::IUnknown
     * xcom.IUnknown is returned.
     */
    inline String getName() const
    {
        return String(name_.c_str());
    }
    
private:
    std::string name_;
};

} } // namespace

#endif
