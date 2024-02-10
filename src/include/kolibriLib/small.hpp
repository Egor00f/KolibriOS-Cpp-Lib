/*
    Файл с константами и малыми струтурами, которые используются везде
*/
#ifndef __SMALL_H__
#define __SMALL_H__

#include <string>
#include "types.hpp"

#define DEBUG true

namespace KolibriLib
{
    const std::string ConfigurationDir = "/kolibrios/etc/";

    const std::string ImgDir = ConfigurationDir + "images/";

    const std::string DefaultImage = ImgDir + "default.png";

    const std::string CursorsDir = ConfigurationDir + "cursors/"; // Предпологается что в этой папке лежат файлы, они заранее приготовленны



} // namespace KolibriLib

#endif // __SMALL_H__