#ifndef INC_IUNKNOWN_HPP_FBA137DB_6D5B_42D5_A667_FA3F8DF6B950
#define INC_IUNKNOWN_HPP_FBA137DB_6D5B_42D5_A667_FA3F8DF6B950

#include <xcom/Types.hpp>

namespace xcom
{
    class octet8
     : public xcom::SimpleArrayBase<xcom::Octet, 8, xcom::Octet>
    {
        
    };
    
    #ifndef XCOM_GUID_DEFINED
    #define XCOM_GUID_DEFINED
    struct GUID
    {
        xcom::Int data1;
        xcom::Short data2;
        xcom::Short data3;
        xcom::octet8 data4;
        
    };
    #endif
    
    struct IUnknownRaw
    {
        void* vptr_;
    };
    struct IUnknownVtbl
    {
        xcom::IUnknownRaw* (*queryInterface)(void*, xcom::Environment*, xcom::GUID const* iid);
        xcom::GUID (*getInterfaceId)(void*, xcom::Environment*);
        xcom::Int (*addRef)(void*, xcom::Environment*);
        xcom::Int (*release)(void*, xcom::Environment*);
        
    };
    class IUnknown
    {
    public:
        IUnknownRaw* ptr_;
    public:
        typedef IUnknownRaw* RawType;IUnknown() : ptr_(0) {}
        IUnknown(IUnknownRaw* ptr) : ptr_(ptr) {}
        ~IUnknown() { if(ptr_ != 0) this->release(); }
        
        IUnknown& operator=(IUnknown const& rhs)
        {
            if(this != &rhs)
            {
                if(ptr_ != 0) release();
                ptr_ = rhs.ptr_;
                if(ptr_ != 0) addRef();
            }
            return *this;
        }
        
        IUnknown(IUnknown const& other)
        : ptr_(other.ptr_){
            if(ptr_ != 0)
            {
                addRef();
            }
        }
        
        xcom::IUnknown queryInterface(xcom::GUID const& iid) const;
        xcom::GUID getInterfaceId() const;
        xcom::Int addRef() const;
        xcom::Int release() const;
        
        static IUnknown adopt(IUnknownRaw* src)
        {
            return IUnknown(src);
        }
        
        IUnknownRaw* detach()
        {
            IUnknownRaw* result = (IUnknownRaw*)ptr_;
            ptr_ = 0;
            return result;
        }
        
        static inline xcom::GUID const& thisInterfaceId()
        {
            static const xcom::GUID id =
            {
                -1083449775, -15722, 19831,
                {0xba, 0x36, 0x61, 0xd7, 0x77, 0x5a, 0xe0, 0xa2}
            };
            
            return id;
        }
        
        bool isNil() const { return ptr_ == 0; }
        operator bool() const { return !isNil(); }
        bool operator !() const { return isNil(); }
    };
    
    template <typename To, typename From>
    To cast(From const& from)
    {
        IUnknown unk(from.queryInterface(To::thisInterfaceId()));
        return static_cast<typename To::RawType>(unk.detach());
    }
    
    
    
    struct Version
    {
        xcom::Short major;
        xcom::Short minor;
        xcom::Short build;
        xcom::Short revision;
        
    };
    
    
    class IUnknownSeq : public xcom::SequenceBase<xcom::IUnknown, xcom::IUnknownRaw*>
    {
    public:
        static IUnknownSeq adopt(RawType const& src)
        {
            IUnknownSeq result;
            ::memcpy(&result, &src, sizeof(RawType));
            return result;
        }
        
        IUnknownSeq() {}
        explicit IUnknownSeq(xcom::Int size)
        : xcom::SequenceBase<xcom::IUnknown, xcom::IUnknownRaw*>(size)
        {
        }
    };
    
    class StringSeq : public xcom::SequenceBase<xcom::String, xcom::Char*>
    {
    public:
        static StringSeq adopt(RawType const& src)
        {
            StringSeq result;
            ::memcpy(&result, &src, sizeof(RawType));
            return result;
        }
        
        StringSeq() {}
        explicit StringSeq(xcom::Int size)
        : xcom::SequenceBase<xcom::String, xcom::Char*>(size)
        {
        }
    };
    
}
namespace xcom
{
    inline xcom::IUnknown IUnknown::queryInterface(xcom::GUID const& iid) const
    {
        xcom::Environment __exc_info;
        xcom::IUnknown result(xcom::IUnknown::adopt(static_cast<IUnknownVtbl*>(static_cast<IUnknownRaw*>(ptr_)->vptr_)->queryInterface(ptr_, &__exc_info, (xcom::GUID const*)&iid)));
        if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
        
        return result;
    }
    inline xcom::GUID IUnknown::getInterfaceId() const
    {
        xcom::Environment __exc_info;
        xcom::GUID result(static_cast<IUnknownVtbl*>(static_cast<IUnknownRaw*>(ptr_)->vptr_)->getInterfaceId(ptr_, &__exc_info));
        if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
        
        return result;
    }
    inline xcom::Int IUnknown::addRef() const
    {
        xcom::Environment __exc_info;
        xcom::Int result(static_cast<IUnknownVtbl*>(static_cast<IUnknownRaw*>(ptr_)->vptr_)->addRef(ptr_, &__exc_info));
        if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
        
        return result;
    }
    inline xcom::Int IUnknown::release() const
    {
        xcom::Environment __exc_info;
        xcom::Int result(static_cast<IUnknownVtbl*>(static_cast<IUnknownRaw*>(ptr_)->vptr_)->release(ptr_, &__exc_info));
        if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
        
        return result;
    }
    
}
#include <xcom/MDHelper.hpp>
namespace xcom
{

    template<> struct TypeDesc<xcom::IUnknown>
    {
        static void addSelf(IUnknownSeq& types);
    };
    
    template <>
    struct TypeDesc<xcom::octet8>
    {
        static void addSelf(IUnknownSeq& types)
        {
            if(!typeExists(types, "xcom.octet8"))
            {
                addType(types, xcomCreateArrayMD("xcom.octet8", rawFindMetadata(types, "octet"), 8));
            }
        }
    };
    
    template <>
    struct TypeDesc<xcom::GUID>
    {
        static void addSelf(IUnknownSeq& types)
        {
            if(!typeExists(types, "xcom.GUID"))
            {
                IUnknownRaw* mtypes[4] =
                {
                    rawFindMetadata(types, "int"),
                    rawFindMetadata(types, "short"),
                    rawFindMetadata(types, "short"),
                    rawFindOrReg(types, "xcom.octet8", &TypeDesc<xcom::octet8>::addSelf),
                    
                };
                
                const Char* mnames[4] =
                {
                    "data1",
                    "data2",
                    "data3",
                    "data4",
                    
                };
                
                Int moffsets[4] =
                {
                    offsetof(xcom::GUID, data1),
                    offsetof(xcom::GUID, data2),
                    offsetof(xcom::GUID, data3),
                    offsetof(xcom::GUID, data4),
                    
                };
                
                addType(types, xcomCreateStructMD("xcom.GUID", sizeof(xcom::GUID), 4, mtypes, mnames, moffsets));
            }
        }
    };
    
    inline void TypeDesc<xcom::IUnknown>::addSelf(IUnknownSeq& types)
    {
        if(!typeExists(types, "xcom.IUnknown"))
        {
            void* cookie;
            IUnknown base;
            Char const* pnames[2];
            IUnknownRaw* ptypes[2];
            Int pmodes[2];
            types.push_back(xcomCreateInterfaceMD("xcom.IUnknown", &xcom::IUnknown::thisInterfaceId(), base.detach(), &cookie));
            
            pnames[0] = "iid";
            
            ptypes[0] = rawFindOrReg(types, "xcom.GUID", &TypeDesc<xcom::GUID>::addSelf);
            
            pmodes[0] = 0;
            
            xcomAddMethodToItf(cookie, "queryInterface", rawFindOrReg(types, "xcom.IUnknown", &TypeDesc<xcom::IUnknown>::addSelf), 1, pmodes, ptypes, pnames);
            
            
            
            xcomAddMethodToItf(cookie, "getInterfaceId", rawFindOrReg(types, "xcom.GUID", &TypeDesc<xcom::GUID>::addSelf), 0, pmodes, ptypes, pnames);
            
            
            
            xcomAddMethodToItf(cookie, "addRef", rawFindMetadata(types, "int"), 0, pmodes, ptypes, pnames);
            
            
            
            xcomAddMethodToItf(cookie, "release", rawFindMetadata(types, "int"), 0, pmodes, ptypes, pnames);
            
        }
    }
    
    template <>
    struct TypeDesc<xcom::Version>
    {
        static void addSelf(IUnknownSeq& types)
        {
            if(!typeExists(types, "xcom.Version"))
            {
                IUnknownRaw* mtypes[4] =
                {
                    rawFindMetadata(types, "short"),
                    rawFindMetadata(types, "short"),
                    rawFindMetadata(types, "short"),
                    rawFindMetadata(types, "short"),
                    
                };
                
                const Char* mnames[4] =
                {
                    "major",
                    "minor",
                    "build",
                    "revision",
                    
                };
                
                Int moffsets[4] =
                {
                    offsetof(xcom::Version, major),
                    offsetof(xcom::Version, minor),
                    offsetof(xcom::Version, build),
                    offsetof(xcom::Version, revision),
                    
                };
                
                addType(types, xcomCreateStructMD("xcom.Version", sizeof(xcom::Version), 4, mtypes, mnames, moffsets));
            }
        }
    };
    
    template <>
    struct TypeDesc<xcom::IUnknownSeq>
    {
        static void addSelf(IUnknownSeq& types)
        {
            if(!typeExists(types, "xcom.IUnknownSeq"))
            {
                addType(types, xcomCreateSequenceMD("xcom.IUnknownSeq", rawFindOrReg(types, "xcom.IUnknown", &TypeDesc<xcom::IUnknown>::addSelf)));
            }
        }
    };
    
    template <>
    struct TypeDesc<xcom::StringSeq>
    {
        static void addSelf(IUnknownSeq& types)
        {
            if(!typeExists(types, "xcom.StringSeq"))
            {
                addType(types, xcomCreateSequenceMD("xcom.StringSeq", rawFindMetadata(types, "string")));
            }
        }
    };
    
} // namespace xcom

#include <xcom/ExcHelper.hpp>

namespace xcom
{

}

#endif
