#ifndef __SETTINGS_H__
#define __SETTINGS_H__


#include <fstream>
#include <vector>

#include "filesystem.hpp"
#include "base.hpp"
#include "childWindow.hpp"

namespace KolibriLib
{
    /// @brief Работа с настройками
    namespace Settings
    {
        struct SettingsParam
        {
            std::string Group;
            std::string Name;
            std::string Data;
        };
        
        std::vector<SettingsParam> Settings;

        /// @brief Загрузить настройки приложения
        /// @param AppName Имя приложения
        /// @return удалось ли загрузить настройти приложения
        bool LoadSettings(std::string AppName)
        {
            std::string path = KolibriLib::ConfigFolder + AppName + "conf.ini";
            std::ifstream file(path.c_str());

            if(file.is_open())
            {

            }
            else
            {

                return 0;
            }
        }

        /// @brief Сохранить настройки приложения
        /// @param AppName Имя приложения
        /// @return удалось ли сохранить настройти приложения
        bool SaveSettings(std::string AppName)
        {
            std::string path = KolibriLib::ConfigFolder + AppName + "conf.ini";
            std::ofstream file(path.c_str());

            if (file.is_open())
            {
                for(unsigned i = 0; i < Settings.size(); i++)
                {

                }
                
            }
            else
            {

                return 0;
            }
            file.close();
        }

    } // namespace Settings
    
}

#endif // __SETTINGS_H__