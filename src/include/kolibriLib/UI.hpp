#ifndef __UI_HPP__
#define __UI_HPP__

#include <sys/ksys.h>

#include <vector>

#include "small.hpp"
#include "os.hpp"
#include "color.hpp"
#include "input.hpp"

namespace KolibriLib
{
    // Элементы UI
    namespace UI
    {

        /// @brief Размер
        typedef point<unsigned> Size;
        typedef point<int>  Coord;

        

        /// @brief Отступы поумолчанию
        const unsigned DefaultMargin = 4;

        /// @brief Элемент интерфейса
        /// @paragraph Используется как шиблон для других классов
        class UIElement
        {
        protected:
        
            /// @brief Координаты
            Coord _coord;

            /// @brief Размер
            Size _size;

            Color::Color _MainColor;

            /// @brief Отступы
            unsigned _Margin;

            /// @brief Угол наклона
            unsigned _angle;

            /// @brief Оносительн
            bool _relative;

        public:
            /// @brief конструктор
            /// @param coord
            /// @param size
            /// @param MainColor
            /// @param Margin
            /// @param relative
            UIElement(const Coord& coord = {0, 0}, const Size& size = {16, 16}, const Color::Color& MainColor = OS::sys_color_table.work_graph, const unsigned& Margin = DefaultMargin, bool relative = false)
            {
                #if DEBUG == true
                _ksys_debug_puts("UIElement:");
                #endif
                _coord      = coord;
                _size       = size;
                _MainColor  = MainColor;
                _Margin     = Margin;
                _relative   = relative;
            }
            /// @brief Получить размер элемента
            /// @return Функция возвращает @link _size
            Size GetSize() const
            {
                return _size;
            }

            void SetSize(Size NewSize)
            {
                _size = NewSize;
            }

            unsigned GetMargin() const
            {
                return _Margin;
            }

            /// @brief Получить осносной цвет элемента
            /// @return Функция возвращает @link _MainColor
            Color::Color GetColor() const
            {
                return _MainColor;
            }

            void SetColor(Color::Color NewColor)
            {
                _MainColor = NewColor;
            }

            void SetCoord(Coord NewCoord) 
            {
                _coord = NewCoord;
            }
            Coord GetCoord() const
            {
                return _coord;
            }

            /// @brief Повернуть элемент
            void Rotate(unsigned NewAngle)
            {
                _angle = NewAngle;
            }

            unsigned GetRotate() const
            {
                return _angle;
            }

            bool Hover()
            {
                Coord mouse = mouse::GetMousePositionInWindow();
                if(_coord.x < mouse.x && _coord.y < mouse.y && mouse.x < _coord.x + _size.x && mouse.y < _coord.y + _size.y)
                {
                    return true;
                }
                return false;
            }

            UIElement& operator = (const UIElement& Element) const = default;
            bool operator == (const UIElement& Element) const = default;
            bool operator !=(const UIElement &Element) const = default;
        };

        //=============================================================================================================================================================

        /// \brief
        /// \param coord
        /// \param size
        /// \param color
        inline void DrawBar(Coord coord, Size size, Color::Color color = OS::sys_color_table.work_graph)
        {
            _ksys_draw_bar(coord.x, coord.y, size.x, size.y, color.val);
        }

        
    }
}

#endif // __UI_H__