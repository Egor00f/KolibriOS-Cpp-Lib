/*
    Файл с константами
*/
#ifndef __SMALL_H__
#define __SMALL_H__

#include <string>
#include <kolibriLib/types.hpp>

namespace KolibriLib
{
    const std::string ConfigurationDir = "/kolibrios/etc/";

    const std::string ImgDir = ConfigurationDir + "KolibriOS-Cpp-Lib/";

    const std::string DefaultImage = ImgDir + "default.png";

} // namespace KolibriLib

#endif // __SMALL_H__