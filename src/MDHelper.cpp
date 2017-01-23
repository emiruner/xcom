/**
 * File    : MDHelper.cpp
 * Author  : Emir Uner
 * Summary : Implementation file for MDHelper.hpp.
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

#include <xcom/metadata/MDTypesTie.hpp>
#include <xcom/ImplHelper.hpp>

#include <xcom/metadata/Struct.hpp>
#include <xcom/metadata/Exception.hpp>
#include <xcom/metadata/Array.hpp>
#include <xcom/metadata/Sequence.hpp>
#include <xcom/metadata/Enum.hpp>
#include <xcom/metadata/Interface.hpp>
#include <xcom/metadata/Delegate.hpp>

#include <cassert>
#include <string>
#include <vector>

using namespace xcom;
using namespace xcom::metadata;

namespace
{

    inline bool nameMatches(IType const& type, char const* name)
    {
        if(!isBuiltin(type.getKind()))
        {
            return strcmp(xcom::cast<IDeclared>(type).getName().c_str(),
                          name) == 0;
        }
        
        if(strcmp(kindAsString(type.getKind()), name) == 0)
        {
            return true;
        }
        
        return false;
    }
    
    typedef std::vector<IType> TypeVec;
    
    template <typename To, typename FromRaw>
    To assumeAs(FromRaw from)
    {
        return To::adopt((typename To::RawType)from);
    }

    xcom::SizeT calculateSize(IType const& md)
    {
        switch(md.getKind())
        {
        case TypeKind::Void: assert("void is not possible" == ""); return 0;
        case TypeKind::Bool: return 1;
        case TypeKind::Octet: return 1;
        case TypeKind::Short: return 2;
        case TypeKind::Int: return 4;
        case TypeKind::Long: return 8;
        case TypeKind::Float: return 4;
        case TypeKind::Double: return 8;
        case TypeKind::Char: return 1;
        case TypeKind::WChar: return 4;
        case TypeKind::Enum: return 4;
        case TypeKind::String: return 4;
        case TypeKind::WString: return 4;
        case TypeKind::Sequence: return sizeof(xcom::SequenceData);
        case TypeKind::Struct: return xcom::cast<IException>(md).getSize();
        case TypeKind::Interface: return sizeof(void*);
        case TypeKind::Exception: return xcom::cast<IException>(md).getSize();
            
        case TypeKind::Array:
        {
            IArray arr(xcom::cast<IArray>(md));    
            return calculateSize(arr.getElementType()) * arr.getSize();
        }
        
        case TypeKind::Any:
            assert(false);
            break;
        }
        
        return 0;
    }
}

extern "C"
{

IUnknownRaw* xcomCreateArrayMD(Char const* name, IUnknownRaw* elt, Int size)
{
    return new Array(name, assumeAs<IType>(elt), size);
}

IUnknownRaw* xcomCreateSequenceMD(Char const* name, IUnknownRaw* elt)
{
    return new Sequence(name, assumeAs<IType>(elt));
}

IUnknownRaw* xcomCreateStructMD(Char const* name, Int size, Int elementCount,
                                IUnknownRaw** types, Char const** names,
                                Int* offsets)
{
    Struct* s = new Struct(name, size);
    
    for(Int i = 0; i < elementCount; ++i)
    {
        s->addMember(names[i], (ITypeRaw*)types[i], offsets[i]);
    }
    
    return s;
}

IUnknownRaw* xcomCreateExceptionMD(Char const* name, IUnknownRaw* base,
                                   Int size, Int elementCount,
                                   IUnknownRaw** types, Char const** names,
                                   Int* offsets)
{
    Exception* e = new Exception(name, (IExceptionRaw*)base, size);
    
    for(Int i = 0; i < elementCount; ++i)
    {
        e->addMember((char const*)names[i], (ITypeRaw*)types[i], offsets[i]);
    }
    
    return e;
}

xcom::Int xcomTypeExists(xcom::IUnknownSeq::RawType* typesRaw,
                         xcom::Char const* name)
{
    IUnknownSeq const& types = *(IUnknownSeq*)(typesRaw);
    IUnknownSeq::const_iterator i = types.begin(), end = types.end();
    
    while(i != end)
    {
        IType type((ITypeRaw*)IUnknown(*i).detach());

        if(nameMatches(type, name))
        {   
            return 1;
        }
        
        ++i;
    }
    
    return 0;
}

void xcomAddType(xcom::IUnknownSeq::RawType* typesRaw, xcom::IUnknownRaw* type)
{
    IUnknownSeq& types = *(IUnknownSeq*)(typesRaw);
    types.push_back(type);
}

IUnknownRaw* xcomFindMetadata(IUnknownSeq::RawType const* typesRaw,
                              Char const* name)
{
    IUnknownSeq const& types = *(IUnknownSeq*)(typesRaw);
    IUnknownSeq::const_iterator i = types.begin(), end = types.end();
    
    while(i != end)
    {
        IType type((ITypeRaw*)IUnknown(*i).detach());

        if(nameMatches(type, name))
        {            
            return type.detach();
        }
        
        ++i;
    }
    
    return 0;
}

IUnknownRaw* xcomCreateEnumMD(Char const* name, Char const** elems,
                              Int elemCount)
{
    Enum* e = new Enum(name);
    
    for(Int i = 0; i < elemCount; ++i)
    {
        e->addElement(elems[i]);
    }
    
    return e;
}

xcom::IUnknownRaw* xcomCreateInterfaceMD(Char const* name, GUID const* iid,
                                         IUnknownRaw* base, void** cookie)
{
    Interface* itf = new Interface(name, *iid, (IInterfaceRaw*) base);
    *cookie = itf;
    return itf;
}

IUnknownRaw* xcomCreateDelegateMD(Char const* name,
                                  IUnknownRaw* ret,
                                  Int paramCount,
                                  Int* modes,
                                  IUnknownRaw** types,
                                  Char const** names)
{
    ParamInfoSeq params;
    ParamInfo pi;

    pi.mode = 3;
    pi.type = (ITypeRaw*) ret;
    pi.name = "<return>";
    params.push_back(pi);
    
    for(Int i = 0; i < paramCount; ++i)
    {    
        pi.mode = modes[i];
        pi.type = (ITypeRaw*)types[i];
        pi.name = names[i];

        params.push_back(pi);
    }

    return new metadata::Delegate(name, params);    
}


void xcomAddMethodToItf(void* cookie, Char const* name, IUnknownRaw* ret,
                        Int paramCount, Int* modes, IUnknownRaw** types,
                        Char const** names)
{
    Interface* itf = (Interface*) cookie;
    ParamInfoSeq params;
    ParamInfo pi;

    pi.mode = 3;
    pi.type = (ITypeRaw*) ret;
    pi.name = "<return>";
    params.push_back(pi);
    
    for(Int i = 0; i < paramCount; ++i)
    {    
        pi.mode = modes[i];
        pi.type = (ITypeRaw*)types[i];
        pi.name = names[i];

        params.push_back(pi);
    }
    
    itf->addMethod(name, params);
}

void xcomPopulateBuiltin(IUnknownSeq::RawType* ptypes)
{
    IUnknownSeq& types = *(IUnknownSeq*)ptypes;
    
    types.push_back(new Type(TypeKind::Void));
    types.push_back(new Type(TypeKind::Bool));
    types.push_back(new Type(TypeKind::Octet));
    types.push_back(new Type(TypeKind::Short));
    types.push_back(new Type(TypeKind::Int));
    types.push_back(new Type(TypeKind::Long));
    types.push_back(new Type(TypeKind::Float));
    types.push_back(new Type(TypeKind::Double));
    types.push_back(new Type(TypeKind::Char));
    types.push_back(new Type(TypeKind::WChar));
    types.push_back(new Type(TypeKind::String));
    types.push_back(new Type(TypeKind::WString));
    types.push_back(new Type(TypeKind::Any));
}
 
/**
 * Destroy the contents of the data according to the rules of XCOM.
 * The md parameter is the metadata about the data.
 */
void xcomGenericDestroy(void* data, IUnknownRaw* pdesc)
{
    IType md(assumeAs<IType>(pdesc));
    
    switch(md.getKind())
    {
    case TypeKind::Void: assert("void is not possible" == ""); break;
    case TypeKind::Bool:
    case TypeKind::Octet:
    case TypeKind::Short:
    case TypeKind::Int:
    case TypeKind::Long:
    case TypeKind::Float:
    case TypeKind::Double:
    case TypeKind::Char:
    case TypeKind::WChar:
    case TypeKind::Enum:
        // Do nothing.
        break;
        
    case TypeKind::String:
    case TypeKind::WString:
    {
        void* embPtr = *(void**)data;
        if(embPtr != 0)
        {
            xcomMemFree(embPtr);
        }
    }
    break;

    case TypeKind::Array:
    {
        IArray arr(cast<IArray>(md));
        IType elementType(arr.getElementType());
        
        const Int elementSize = calculateSize(elementType);
        const Int count = arr.getSize();
        char* it = (char*)data;
        
        for(Int i = 0; i < count; ++i)
        {
            xcomGenericDestroy(it, elementType.ptr_);
            it += elementSize;
        }
    }
    break;
        
    case TypeKind::Sequence:
    {
        ISequence seq(cast<ISequence>(md));
        IType elementType(seq.getElementType());
        
        const Int elementSize = calculateSize(elementType);
        SequenceData* sd = (SequenceData*)data;
        char* it = (char*)sd->data;
        
        for(SizeT i = 0; i < sd->size; ++i)
        {
            xcomGenericDestroy(it, elementType.ptr_);
            it += elementSize;
        }
        
        xcomMemFree(sd->data);
    }
    break;
    
    case TypeKind::Struct:
    {
        IStruct type(cast<IStruct>(md));
        char* ptr = (char*)data;
        const Int count = type.getMemberCount();
        
        for(Int i = 0; i < count; ++i)
        {
            xcomGenericDestroy(ptr + type.getMemberOffset(i),
                               type.getMemberType(i).ptr_);
        }
    }
    break;
        
    case TypeKind::Exception:
    {
        IException exc(cast<IException>(md));
        char* ptr = (char*)data;
        
        while(!exc.isNil())
        {
            const Int count = exc.getMemberCount();
        
            for(Int i = 0; i < count; ++i)
            {
                xcomGenericDestroy(ptr + exc.getMemberOffset(i),
                                   exc.getMemberType(i).ptr_);
            }

            exc = exc.getBase();
        }
    }
    break;
        
    case TypeKind::Interface:
    {
        IUnknown& unk = *(IUnknown*)data;        
        unk.release();
    }
    break;
        
    case TypeKind::Any:
        assert(false);
        break;
    }
}

} // extern "C"
