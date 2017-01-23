/**
 * File    : Exception.hpp
 * Author  : Emir Uner
 * Summary : Exception class definitions.
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

#ifndef XCOM_METADATA_EXCEPTION_HPP_INCLUDED
#define XCOM_METADATA_EXCEPTION_HPP_INCLUDED

#ifndef XCOM_METADATA_STRUCTBASE_HPP_INCLUDED
#include <xcom/metadata/StructBase.hpp>
#endif

#ifndef XCOM_IMPLHELPER_HPP_INCLUDED
#include <xcom/ImplHelper.hpp>
#endif

namespace xcom { namespace metadata {

/**
 * Represents an Exception.
 */
class Exception : public Supports<Exception, IException>,
                  public RefCounted<Exception>,
                  public StructBase
{
public:
    /**
     * An Exception with given name and base.
     */
    inline Exception(char const* name, IException const& base, int size)
    : StructBase(TypeKind::Exception, name, size), base_(base)
    {
    }

    /**
     * Get base exception for this exception.
     * If no bases is present nil returned.
     */
    inline IException getBase() const
    {
        return base_;
    }
    
private:
    IException base_;
};

} } // namespace

#endif
