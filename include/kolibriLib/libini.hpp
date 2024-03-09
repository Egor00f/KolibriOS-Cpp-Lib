#ifndef __LIBINI_H__
#define __LIBINI_H__


#include <kolibri_libini.h>

#include <kolibriLib/system/filesystem.hpp>

#include <functional>
#include <iostream>


namespace KolibriLib
{
    namespace LibIni
    {
        
        bool EnumSections(const filesystem::Path &path, std::function<bool(const filesystem::Path&, const std::string&)>& func)
        {
            LIBINI_enum_sections(path.GetChars(), &func);
            return true;
        }

    } // namespace LibIni
    
} // namespace KolibriLib


#endif // __LIBINI_H__