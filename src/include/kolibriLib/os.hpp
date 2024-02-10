#ifndef __OS_H__
#define __OS_H__

#include "small.hpp"
#include "filesystem.hpp"
#include "color.hpp"

namespace KolibriLib
{
    /// @brief Работа с системой
    namespace OS
    {

        /// @brief Таблица стандартных(системных) цветов
        Colors::ColorsTable sys_color_table;

        /// @brief Получить системные цвета
        /// @paragraph Функция изменяет переменную @link sys_color_table
        /// @return Таблица системных цветов
        Colors::ColorsTable GetSystemColors();

        /// @brief Ивент
        typedef unsigned int Event;

        enum Events
        {
            /// @brief Ивента небыло
            None    = KSYS_EVENT_NONE,
            /// @brief Перересовка окна
            Redraw  = KSYS_EVENT_REDRAW,
            /// @brief Нажата кнопка
            Button  = KSYS_EVENT_BUTTON,
            /// @brief Активность мыши
            Mouse   = KSYS_EVENT_MOUSE,
            /// @brief Активность со стороны клавиатуры
            Key     = KSYS_EVENT_KEY,
            /// @brief 
            Desktop = KSYS_EVENT_DESKTOP,
            Debug   = KSYS_EVENT_DEBUG,
            Exit
        };

        /// \brief Ждать ивента
        /// \return Ивент
        inline Event WaitEvent();

        /// \brief Ждать ивента
        /// \param Таймаут (в 1/100 секунды)
        /// \return Ивент
        inline Event WaitEvent(uint32_t TimeOut);

        /// \brief Проверить пришёл ли ли ивент
        /// \return Ивент
        inline Event CheckEvent();

        /// \brief Запустить программу
        /// \param AppName путь до программы + имя
        /// \param args аргументы
        /// \return то что возвращает сама программа, -1 если исполняемы файл не найден
        inline int Exec(const filesystem::Path& AppName, const std::string& args);

        /// @brief Получить системное время
        /// @return
        inline ksys_time_t GetTime();

        /// @brief Получить состояние спикера(Вкл/выкл)
        /// @return true если спикер разрешён, иначе false
        inline bool SpeakerStatus();

        /// @brief Переключить состояние спикера 
        inline void SpeakerSwitch();

        /// @brief получить кол-во свободной памяти
        /// @return размер свободной памяти в килобайтах
        inline unsigned FreeMem();

        inline unsigned AllMem();

        enum lang
        {
            Eng = 0,
            Fi,
            Ger,
            Rus
        };

        inline int GetLang();

    } // namespace OS

    /// \brief Подождать
    /// \param time время задержки(в 1/100 секунды)
    inline void Wait(unsigned time);

} // namespace KolibriLib


#endif // __OS_H__