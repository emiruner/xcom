#ifndef INC_ILIBRARY_HPP_3332C439_1E27_4E07_9D53_1DAA4B372070
#define INC_ILIBRARY_HPP_3332C439_1E27_4E07_9D53_1DAA4B372070

#include <xcom/Types.hpp>

#include <xcom/IUnknown.hpp>
namespace xcom
{
    struct ILibraryRaw : public xcom::IUnknownRaw
    {
    };
    struct ILibraryVtbl
    {
        xcom::IUnknownRaw* (*queryInterface)(void*, xcom::Environment*, xcom::GUID const* iid);
        xcom::GUID (*getInterfaceId)(void*, xcom::Environment*);
        xcom::Int (*addRef)(void*, xcom::Environment*);
        xcom::Int (*release)(void*, xcom::Environment*);
        xcom::IUnknownRaw* (*createObject)(void*, xcom::Environment*, const xcom::Char* name);
        
    };
    template<typename Impl> class ILibraryTie;
    class ILibrary : public xcom::IUnknown
    {
    public:
        typedef ILibraryRaw* RawType;
        typedef xcom::IUnknown ParentClass;
        template<typename T>
        struct Tie { typedef ILibraryTie<T> type; };
        ILibrary() {}
        ILibrary(ILibraryRaw* ptr) : xcom::IUnknown((xcom::IUnknownRaw*)ptr) {}
        xcom::IUnknown createObject(const xcom::Char* name) const;
        
        static ILibrary adopt(ILibraryRaw* src)
        {
            return ILibrary(src);
        }
        
        ILibraryRaw* detach()
        {
            ILibraryRaw* result = (ILibraryRaw*)ptr_;
            ptr_ = 0;
            return result;
        }
        
        static inline xcom::GUID const& thisInterfaceId()
        {
            static const xcom::GUID id =
            {
                1694264368, 15080, 17082,
                {0xba, 0xdb, 0x2d, 0xb8, 0xb9, 0xb3, 0x71, 0x3b}
            };
            
            return id;
        }
        
    };
    
}
namespace xcom
{
    inline xcom::IUnknown ILibrary::createObject(const xcom::Char* name) const
    {
        xcom::Environment __exc_info;
        xcom::IUnknown result(xcom::IUnknown::adopt(static_cast<ILibraryVtbl*>(static_cast<ILibraryRaw*>(ptr_)->vptr_)->createObject(ptr_, &__exc_info, name)));
        if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
        
        return result;
    }
    
}
#include <xcom/MDHelper.hpp>
namespace xcom
{

    template<> struct TypeDesc<xcom::ILibrary>
    {
        static void addSelf(IUnknownSeq& types);
    };
    
    inline void TypeDesc<xcom::ILibrary>::addSelf(IUnknownSeq& types)
    {
        if(!typeExists(types, "xcom.ILibrary"))
        {
            void* cookie;
            IUnknown base(findOrRegister(types, "xcom.IUnknown", &TypeDesc<xcom::IUnknown>::addSelf));
            Char const* pnames[2];
            IUnknownRaw* ptypes[2];
            Int pmodes[2];
            types.push_back(xcomCreateInterfaceMD("xcom.ILibrary", &xcom::ILibrary::thisInterfaceId(), base.detach(), &cookie));
            
            pnames[0] = "name";
            
            ptypes[0] = rawFindMetadata(types, "string");
            
            pmodes[0] = 0;
            
            xcomAddMethodToItf(cookie, "createObject", rawFindOrReg(types, "xcom.IUnknown", &TypeDesc<xcom::IUnknown>::addSelf), 1, pmodes, ptypes, pnames);
            
        }
    }
    
} // namespace xcom

#include <xcom/ExcHelper.hpp>

namespace xcom
{

}

#endif
