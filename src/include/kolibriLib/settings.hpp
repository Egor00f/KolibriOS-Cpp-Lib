#ifndef __SETTINGS_H__
#define __SETTINGS_H__


#include <fstream>
#include "filesystem.hpp"
#include "base.hpp"

namespace KolibriLib
{
    namespace Settings
    {
        /// @brief Загрузить настройки приложения
        /// @param AppName Имя приложения
        /// @return удалось ли загрузить настройти приложения
        bool LoadSettings(std::string AppName);

        /// @brief Сохранить настройки приложения
        /// @param AppName Имя приложения
        /// @return удалось ли сохранить настройти приложения
        bool SaveSettings(std::string AppName);

    } // namespace Settings
    
}

#endif // __SETTINGS_H__