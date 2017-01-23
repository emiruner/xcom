/**
 * File    : Sequence.hpp
 * Author  : Emir Uner
 * Summary : Sequence class definitions.
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

#ifndef XCOM_METADATA_SEQUENCE_HPP_INCLUDED
#define XCOM_METADATA_SEQUENCE_HPP_INCLUDED

#ifndef XCOM_METADATA_DECLARED_HPP_INCLUDED
#include <xcom/metadata/Declared.hpp>
#endif

#ifndef XCOM_IMPLHELPER_HPP_INCLUDED
#include <xcom/ImplHelper.hpp>
#endif

namespace xcom { namespace metadata {

class Sequence : public Supports<Sequence, ISequence>,
                 public RefCounted<Sequence>,
                 public DeclaredImpl
{
public:
    /**
     * Assumes that elementType is not destroyed before this instance.
     */
    inline Sequence(char const* name, IType const& elementType)
    : DeclaredImpl(TypeKind::Sequence, name), elementType_(elementType)
    {
    }

    /**
     * My element type.
     */
    inline IType getElementType() const
    {
        return elementType_;
    }
    
private:
    IType elementType_;
};

} } // namespace

#endif
