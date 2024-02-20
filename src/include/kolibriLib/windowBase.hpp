#ifndef __WINDOWBASE_H__
#define __WINDOWBASE_H__

/*
    Тут тип базовый функционал работы с окном
*/

#include <sys/ksys.h>
#include <string>

#include "types.hpp"
#include "thread.hpp"
#include "color.hpp"
#include "os.hpp"
#include "mouse.hpp"

namespace KolibriLib
{

    /// @brief Работа с окном
    namespace window
    {
        
        /// @brief Размер окна поумолчанию
        const UI::Size DefaultWindowSize = {400, 400};

        /// @brief Соординаты окна по умолчанию
        const UI::Coord DefaultWindowCoord = {100, 100};

        enum WindowStyle
        {
            /// @brief окно фиксированных размеров
            FixSize = 0,
            /// @brief только определить область окна, ничего не рисовать
            NoDraw = 1,
            /// @brief окно изменяемых размеров
            CanResize = 2,
            /// @brief окно со скином
            withSkin = 3,
            /// @brief окно со скином фиксированных размеров
            FixSizewithSkin = 4,
            /// @brief не закрашивать рабочую область при отрисовке окна
            NoDrawWorkspace = 0b01000000,
            /// @brief нормальная заливка рабочей области
            NormalDraw = 0b00000000,
            /// @brief градиентная заливка рабочей области
            GradientDraw = 0b10000000
        };

        /// @brief 
        /// @param coord Координаты окна(его левого верхнего угола) на экране
        /// @param size Размеры окна
        /// @param title Заголовок окна
        /// @param WorkColor цвет рабочей области окна
        /// @param TitleColor Цвет текста заголовка
        /// @param style Стиль
        inline void CreateWindow(const UI::Coord coord, const UI::Size size, const std::string& title, const Colors::Color WorkColor = OS::sys_color_table.frame_area, const Colors::Color TitleColor = OS::sys_color_table.work_text, const uint32_t style = WindowStyle::CanResize + WindowStyle::NormalDraw)
        {
            const char* t = title.c_str();
            asm_inline(
                "int $0x40"
                :
                : "a"(0),
                  "b"((coord.x << 16) | ((size.x - 1) & 0xFFFF)),
                  "c"((coord.y << 16) | ((size.y - 1) & 0xFFFF)),
                  "d"((style << 24) | (WorkColor.val & 0xFFFFFF)),
                  "D"(t),
                  "S"(TitleColor.val)
                );
            
        }


        /// @brief Снять фокус с окна
        /// @param slot слот окна
        inline void UnfocusWindow(Thread::Slot slot)
        {
            _ksys_unfocus_window(slot);
        }

        /// @brief Поставить фокус на окно
        /// @param slot слот окна
        inline void FocusWindow(Thread::Slot slot)
        {
            _ksys_focus_window(slot);
        }

        /// @brief Получить слот активного окна
        /// @return Слот активного в данный момент окна
        inline Thread::Slot GetActiveWindow()
        {
            Thread::Slot s;
            asm_inline(
                "int $0x40"
                : "=a"(s)
                : "a"(18), "b"(7)
            );
            return s;
        }

        /// @brief Свернуть окно
        inline void MinimizeWindow()
        {
            asm_inline(
                "int $0x40" ::"a"(18), "b"(10)
            );
        }

        /// @brief Свернуть все окна
        inline void MinimizeAllWindows()
        {
            asm_inline(
                "int $0x40" ::"a"(18), "b"(23)
            );
        }

        UI::Coord GetWindowCoord();

        /// @brief Список констант положения окна относительно других окон:
        enum Pos{
            BackGround = -2,
            AlwaysBack = -1,
            Normal = 0,
            AlwaysTop = 1
        };

        /// @brief Получить положение окна относительно других окон
        /// @return одна из констант из списка @link Pos
        inline int GetWindowPos()
        {
            int a;
            asm_inline(
                "int $0x40"
                : "=a"(a)
                : "a"(18), "b"(25), "c"(1));
            return a;
        }

        /// @brief Изменить положение окна относительно дроугих окон
        /// @param pos 
        /// @param pid процесс
        /// @return false если ошибка
        inline bool SetWindowPos(int pos, Thread::PID pid = -1)
        {
            bool a;
            asm_inline(
                "int $0x40"
                : "=a"(a)
                : "a"(18), "b"(25), "c"(2), "d"(pid), "S"(pos));
            return a;
        }

        /// @brief Получить высоту скина(заголовка окна)
        /// @return высота скина
        inline unsigned GetSkinHeight()
        {
            return _ksys_get_skin_height();
        }

    } // namespace window
    

} // namespace KolibriLib


#endif // __WINDOWBASE_H__