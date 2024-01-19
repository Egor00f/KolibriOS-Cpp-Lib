#ifndef __UI_HPP__
#define __UI_HPP__

#include <sys/ksys.h>

#include <vector>

#include "base.hpp"
#include "color.hpp"

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

        public:
            UIElement(Coord coord = {0, 0}, Size size = {16, 16}, Color::Color MainColor = 0, unsigned Margin = DefaultMargin)
            {
                _coord = coord;
                _size = size;
                _MainColor = MainColor;
                _Margin = Margin;
            }
            Size GetSize()
            {
                return _size;
            }

            void SetSize(Size NewSize)
            {
                _size = NewSize;
            }

            unsigned GetMargin()
            {
                return _Margin;
            }

            /// @brief Получить осносной цвет элемента
            /// @return Функция возвращает @link _MainColor
            Color::Color GetColor()
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
            Coord GetCoord()
            {
                return _coord;
            }
        };

        //=============================================================================================================================================================

        /// \brief
        /// \param coord
        /// \param size
        /// \param color
        inline void DrawBar(point<int> coord, point<unsigned> size, ksys_color_t color = OS::sys_color_table.work_graph)
        {
            _ksys_draw_bar(coord.x, coord.y, size.x, size.y, color);
        }

        
    }
}

#endif // __UI_H__