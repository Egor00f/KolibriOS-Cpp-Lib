#ifndef __LIBINI_H__
#define __LIBINI_H__

extern "C"
{
#include <kolibri_libini.h>
}
#include "filesystem.hpp"

#include <functional>
#include <iostream>


namespace KolibriLib
{
    namespace LibIni
    {
        
        bool EnumSections(const filesystem::Path &path, std::function<bool(const filesystem::Path&, std::string SectionName)>& func)
        {
            LIBINI_enum_sections(path.GetChars(), &func);
            return true;
        }

    } // namespace LibIni
    
} // namespace KolibriLib


#endif // __LIBINI_H__