/**
 * File    : Loader.cpp
 * Author  : Emir Uner
 * Summary : Loader.hpp implementation.
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

#include <xcom/GUID.hpp>
#include <xcom/Loader.hpp>
#include <xcom/Portability.hpp>
#include <xcom/ILibraryTie.hpp>
#include <xcom/ImplHelper.hpp>
#include <xcom/metadata/MDTypes.hpp>

#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace xcom;
using namespace internal;

namespace
{

    /**
     * Version equality operator.
     */
    inline bool operator==(Version const& lhs, Version const& rhs)
    {
        return ::memcmp(&lhs, &rhs, sizeof(Version)) == 0;
    }
    
    /**
     * Checks whether GUID is null.
     */
    inline bool isNullGUID(GUID const& guid)
    {
        GUID nullGUID = XCOM_NULL_GUID_INITIALIZER;
        return nullGUID == guid;
    }
    
    /**
     * Checks the presence of the endChar in the string and
     * converts the integer beginning at the string.
     * In case endChar not found return null
     * otherwise return the position of the end char. 
     */
    Char const* checkAndConvert(Char const* str, int endChar, int& result)
    {
        Char const* endPos;
        
        if((endPos = strchr(str, endChar)) > str)
        {
            result = atoi(str);
        }
        
        return endPos;
    }

    /**
     * Check Version= presence.
     * Return the end of the version string if successfull,
     * null otherwise.
     */
    Char const* parseVersion(Char const* str, Version& version)
    {
        // Version= must be present at the beginning of the string.
        if(strstr(str, "Version=") != str)
        {
            return 0;
        }
        
        str += 8;
        
        Version tmp;
        int converted;
        
        if((str = checkAndConvert(str, '.', converted)))
        {
            ++str;
            tmp.major = converted;
            
            if((str = checkAndConvert(str, '.', converted)))
            {
                ++str;
                tmp.minor = converted;
                
                if((str = checkAndConvert(str, '.', converted)))
                {
                    ++str;
                    tmp.build = converted;
                    
                    str = checkAndConvert(str, ' ', converted);
                    tmp.revision = converted;

                    version = tmp;
                    
                    return str;
                }
            }
        }
        
        return 0;
    }

    /**
     * Parse vendor part, the last part, and return true on success.
     */
    bool parseVendor(Char const* str,  GUID& vendor)
    {
        // Version= must be present at the beginning of the string.
        if(strstr(str, "Vendor=") != str)
        {
            return false;
        }
        
        str += 7;
        
        return xcomParseGUID(str, &vendor);
    }

    bool parseSpec(Char const* spec, String& name, Version& ver, GUID& ven)
    {
        Char const* comma;
        
        if((comma = strchr(spec, ',')) == 0)
        {
            Version nver = XCOM_NULL_VERSION_INITIALIZER;
            GUID nven = XCOM_NULL_GUID_INITIALIZER;

            name = spec;
            ver = nver;
            ven = nven;
        
            return true;
        }

        String tmpName(spec, comma);
        spec = comma + 1;
    
        // If a comma seen before then there must exist another one
        if(strchr(spec, ',') == 0)
        {
            return false;
        }
        
        Version tmpVersion;
        while(*spec != '\0' && *spec != 'V')
        {
            ++spec;
        }
        
        if((spec = parseVersion(spec, tmpVersion)) == 0)
        {
            return false;
        }
        
        ++spec;
        
        GUID tmpVendor;
        while(*spec != '\0' && *spec != 'V')
        {
            ++spec;
        }
        if(!parseVendor(spec, tmpVendor))
        {
            return false;
        }
        
        name = tmpName;
        ver = tmpVersion;
        ven = tmpVendor;
        
        return true;
    }

    // Prototypes for exported DLL functions.
    typedef IUnknownRaw* (*CreateObjectFn)(Char const* classname);
    typedef void (*GetVersionFn)(Version* version, GUID* vendor);
    typedef StringSeq::RawType (*GetClassNamesFn)();
    typedef IUnknownSeq::RawType (*GetMetadataFn)();
    
    /**
     * Very simple ILibrary implementation storing only the
     * creation function.
     */
    struct ILibraryImpl : public Supports<ILibraryImpl, ILibrary>, public RefCounted<ILibraryImpl>
    {
        ILibraryImpl(SharedLibrary* lib)
        : creator_(resolve<CreateObjectFn>(*lib, "dllCreateObject"))
        {
        }
        
        IUnknown createObject(Char const* classname)
        {
            return creator_(classname);
        }

    private:
        CreateObjectFn creator_;
    };
    
    /**
     * Information about a loaded shared library.
     */
    struct SharedLibInfo
    {
        String fullPath;
        Version version;
        GUID vendor;
        SharedLibrary* lib;

        SharedLibInfo(Char const* fp, SharedLibrary* lb)
        {
            GetVersionFn gvf = resolve<GetVersionFn>(*lb, "dllGetVersion");

            fullPath = fp;
            gvf(&version, &vendor);
            lib = lb;
        }        

        SharedLibrary* detach()
        {
            SharedLibrary* ret = lib;
            lib = 0;
            return ret;
        }
    };

    /**
     * Resolve and call the "dllGetClassNames" function from the given library.
     */
    inline StringSeq getClassNames(SharedLibrary& lib)
    {
        GetClassNamesFn fn(resolve<GetClassNamesFn>(lib, "dllGetClassNames"));
        return StringSeq::adopt(fn());
    }

    /**
     * Resolve and call the "dllGetMetadata" function from the given library.
     */
    inline IUnknownSeq getMetadata(SharedLibrary& lib)
    {
        GetMetadataFn fn(resolve<GetMetadataFn>(lib, "dllGetMetadata"));
        return IUnknownSeq::adopt(fn());
    }
    
    /**
     * Information about the libraries loaded for the builtin class search.
     */
    struct BuiltinInfo
    {
        ILibrary lib;
        StringSeq classes;
        IUnknownSeq metadata;
        
        BuiltinInfo(SharedLibrary* lb)
        : lib(new ILibraryImpl(lb)), classes(getClassNames(*lb)), metadata(getMetadata(*lb))
        {
        }        
    };

    // Sequences
    typedef SequenceBase<BuiltinInfo, BuiltinInfo> BuiltinSeq;

    struct LibrarySeq : public SequenceBase<SharedLibInfo, SharedLibInfo>
    {
        ~LibrarySeq()
        {
            iterator lib, libend = end();
            
            for(lib = begin(); lib != libend; ++lib)
            {
                delete lib->detach();
            }
        }
    };
    

    /**
     * Check whether a library specified by it's full path loaded before and
     * return handle of it if successfull.
     */
    SharedLibrary* isLoadedBefore(LibrarySeq const& libs, Char const* f)
    {
        for(LibrarySeq::const_iterator i = libs.begin(); i != libs.end(); ++i)
        {
            if(i->fullPath == f)
            {
                return i->lib;
            }
        }
        
        return 0;
    }

    /**
     * Returns true if the version and name of the library specified
     * in library info is same with the parameters.
     */
    bool libraryMatches(SharedLibInfo const& sli, Char const* name, GUID const& vendor, Version const& version)
    {
        return makeLibraryName(sli.fullPath.c_str()) == name && sli.vendor == vendor && sli.version == version;
    }

    /**
     * Checks whether the library specified by the version is loaded before.
     */
    SharedLibrary* isLoadedBefore(LibrarySeq const& libs, Char const* name, GUID const& vendor, Version const& version)
    {
        for(LibrarySeq::const_iterator i = libs.begin(); i != libs.end(); ++i)
        {
            if(libraryMatches(*i, name, vendor, version))
            {
                return i->lib;
            }
        }
        
        return 0;
    }
    
    // Configuration
    LibrarySeq libraries;
    Mutex libMutex;

    BuiltinSeq builtins;
    Mutex builtinMutex;

    StringSeq searchPath;
    Mutex pathMutex;
    
    SharedLibrary* findExistingOrLoad(Char const* path)
    {
        String fullPath;
        SharedLibrary* lib;
    
        fullPath = String::adopt(xcomMakePathAbsolute(path));
        Mutex::ScopedLock libLock(libMutex);
        
        if((lib = isLoadedBefore(libraries, fullPath.c_str())))
        {
            return lib;
        }
        
        try
        {
            lib = new SharedLibrary(fullPath.c_str());
        }
        catch(String& cause)
        {
            return 0;
        }
            
        if(lib->resolve("dllGetVersion"))
        {
            SharedLibInfo libInfo(fullPath.c_str(), lib);
            libraries.push_back(libInfo);
            return lib;
        }
            
        delete lib;

        return 0;
    }

    struct XCOMInitializer
    {
        XCOMInitializer()
        {
            String configFile(String::adopt(xcomConfigFileForApplication()));
            std::ifstream config(configFile.c_str());

            if(config.is_open())
            {
                char line[4096];
                
                config.getline(line, 4095, '\n');
                while(!config.fail())
                {
                    if(line[0] != '\0')
                    {
                        xcomAddLibrarySearchPath(line);
                    }
                    
                    config.getline(line, 4095, '\n');
                }
            }
        }
    } theInitializer;
    
}

extern "C"
{

void xcomAddLibrarySearchPath(Char const* fullPath)
{
    Mutex::ScopedLock lock(pathMutex);
    searchPath.push_back(fullPath);
}    

ILibraryRaw* xcomLoad(Char const* spec)
{   
    Mutex::ScopedLock libLock(libMutex);
    Mutex::ScopedLock pathLock(pathMutex);
    
    GUID vendor;
    Version version;
    String name;
    
    if(!parseSpec(spec, name, version, vendor))
    {
        return 0;
    }
    
    if(!isNullGUID(vendor))
    {
        SharedLibrary* lib;
        
        if((lib = isLoadedBefore(libraries, name.c_str(), vendor, version)))
        {
            return new ILibraryImpl(lib);
        }

        StringSeq::const_iterator dir, end = searchPath.end();
        
        for(dir = searchPath.begin(); dir != end; ++dir)
        {
            String completePath = combinePathWithFile((*dir).c_str(), xcomMakeLibraryFilename(name.c_str()));
            
            if(xcomFileExists(completePath.c_str()))
            {
                try
                {
                    lib = new SharedLibrary(completePath.c_str());
                    SharedLibInfo sli(completePath.c_str(), lib);

                    if(libraryMatches(sli, name.c_str(), vendor, version))
                    {
                        libraries.push_back(sli);
                        return new ILibraryImpl(lib);
                    }
                }
                catch(...)
                {
                    // Do nothing.
                }
                
                delete lib;
            }       
        }        
    }
    else
    {
        SharedLibrary* lib;
        StringSeq::const_iterator dir, end = searchPath.end();
        
        for(dir = searchPath.begin(); dir != end; ++dir)
        {
            String completePath = combinePathWithFile((*dir).c_str(), xcomMakeLibraryFilename(name.c_str()));
            
            if(xcomFileExists(completePath.c_str()))
            {
                if((lib = isLoadedBefore(libraries, completePath.c_str())))
                {
                    return new ILibraryImpl(lib);
                }
                
                try
                {
                    lib = new SharedLibrary(completePath.c_str());
                    SharedLibInfo sli(completePath.c_str(), lib);

                    libraries.push_back(sli);
                    return new ILibraryImpl(lib);
                }
                catch(...)
                {
                    // Do nothing.
                }
                
                delete lib;
            }       
        }        
    }
    
    return 0;
}

ILibraryRaw* xcomLoadFrom(Char const* path)
{
    SharedLibrary* lib = findExistingOrLoad(path);
    
    if(lib != 0)
    {
        return new ILibraryImpl(lib);
    }
    
    return 0;
}

ILibraryRaw* xcomLoadAsBuiltin(Char const* spec)
{   
    Mutex::ScopedLock libLock(libMutex);
    Mutex::ScopedLock pathLock(pathMutex);

    GUID vendor;
    Version version;
    String name;
    
    if(!parseSpec(spec, name, version, vendor))
    {
        return 0;
    }
    
    if(!isNullGUID(vendor))
    {
        SharedLibrary* lib;
        
        if((lib = isLoadedBefore(libraries, name.c_str(), vendor, version)))
        {
            builtins.push_back(BuiltinInfo(lib));
            return new ILibraryImpl(lib);
        }

        StringSeq::const_iterator dir, end = searchPath.end();
        
        for(dir = searchPath.begin(); dir != end; ++dir)
        {
            String completePath = combinePathWithFile((*dir).c_str(), xcomMakeLibraryFilename(name.c_str()));
            
            if(xcomFileExists(completePath.c_str()))
            {
                try
                {
                    lib = new SharedLibrary(completePath.c_str());
                    SharedLibInfo sli(completePath.c_str(), lib);

                    if(libraryMatches(sli, name.c_str(), vendor, version))
                    {
                        libraries.push_back(sli);
                        builtins.push_back(BuiltinInfo(lib));
                        return new ILibraryImpl(lib);
                    }
                }
                catch(...)
                {
                    // Do nothing.
                }
                
                delete lib;
            }       
        }        
    }
    else
    {
        SharedLibrary* lib;
        StringSeq::const_iterator dir, end = searchPath.end();
        
        for(dir = searchPath.begin(); dir != end; ++dir)
        {
            String completePath = combinePathWithFile((*dir).c_str(),
                                      String::adopt(xcomMakeLibraryFilename(name.c_str())).c_str());
            
            if(xcomFileExists(completePath.c_str()))
            {
                if((lib = isLoadedBefore(libraries, completePath.c_str())))
                {
                    builtins.push_back(BuiltinInfo(lib));
                    return new ILibraryImpl(lib);
                }
                
                try
                {
                    lib = new SharedLibrary(completePath.c_str());
                    SharedLibInfo sli(completePath.c_str(), lib);

                    libraries.push_back(sli);
                    builtins.push_back(BuiltinInfo(lib));
                    return new ILibraryImpl(lib);
                }
                catch(...)
                {
                    // Do nothing.
                }
                
                delete lib;
            }       
        }        
    }
    
    return 0;
}

ILibraryRaw* xcomLoadFromAsBuiltin(Char const* path)
{
    SharedLibrary* lib;
    Mutex::ScopedLock builtinsLock(builtinMutex);
    
    if((lib = findExistingOrLoad(path)))
    {
        builtins.push_back(BuiltinInfo(lib));
        return new ILibraryImpl(lib);
    }

    return 0;
}

IUnknownRaw* xcomCreateObject(Char const* classname)
{
    BuiltinSeq::const_iterator bil, builtinsEnd = builtins.end();
    Mutex::ScopedLock builtinsLock(builtinMutex);
    
    for(bil = builtins.begin(); bil != builtinsEnd; ++bil)
    {
        StringSeq::const_iterator cls, classesEnd = bil->classes.end();
        
        for(cls = bil->classes.begin(); cls != classesEnd; ++cls)
        {
            if(*cls == classname)
            {
                return bil->lib.createObject(classname).detach();
            }
        }
    }
    
    return 0;
}

xcom::metadata::IInterfaceRaw* xcomGetMetadata(GUID const* guid)
{
    BuiltinSeq::const_iterator bil, builtinsEnd = builtins.end();
    Mutex::ScopedLock builtinsLock(builtinMutex);
    
    for(bil = builtins.begin(); bil != builtinsEnd; ++bil)
    {
        IUnknownSeq::const_iterator mdIt, mdEnd = bil->metadata.end();
        
        for(mdIt = bil->metadata.begin(); mdIt != mdEnd; ++mdIt)
        {
            xcom::metadata::IInterface itf = xcom::cast<xcom::metadata::IInterface>(*mdIt);
            
            if(itf.getId() == *guid)
            {
                return itf.detach();
            }
        }
    }
    
    return 0;
}

} // extern "C"
