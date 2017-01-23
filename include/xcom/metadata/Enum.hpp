/**
 * File    : Enum.hpp
 * Author  : Emir Uner
 * Summary : Enum class definitions.
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

#ifndef XCOM_METADATA_ENUM_HPP_INCLUDED
#define XCOM_METADATA_ENUM_HPP_INCLUDED

#ifndef XCOM_METADATA_DECLARED_HPP_INCLUDED
#include <xcom/metadata/Declared.hpp>
#endif

#ifndef XCOM_IMPLHELPER_HPP_INCLUDED
#include <xcom/ImplHelper.hpp>
#endif

#include <vector>
#include <string>

namespace xcom { namespace metadata {

/**
 * All information about an enum.
 */
class Enum : public Supports<Enum, IEnum>,
             public RefCounted<Enum>,
             public DeclaredImpl
{
public:
    /**
     * An enum with the given name.
     */
    inline Enum(char const* name)
    : DeclaredImpl(TypeKind::Enum, name)
    {
    }

    // IEnum method implementations
    inline int getElementCount() const
    {
        return elements_.size();
    }
    
    inline String getElement(int idx) const
    {
        return String(elements_[idx].c_str());
    }
    
    /**
     * Append an element to enumerations list.
     */
    void addElement(char const* elem)
    {
        elements_.push_back(elem);
    }
    
private:
    std::vector<std::string> elements_;
};
    
} } // namespace

#endif
