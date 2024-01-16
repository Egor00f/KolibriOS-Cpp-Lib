#ifndef __UI_HPP__
#define __UI_HPP__

#include <sys/ksys.h>

#include <vector>

#include "small.hpp"
#include "windowBase.hpp"
#include "graphic.hpp"
#include "mouse.hpp"

//=============================================================================================================================================================

namespace KolibriLib
{
    /// @brief Класс-шаблон, от которого наследуются все остальные UI элементы
    namespace UI
    {
        /// @brief Отступы поумолчанию
        const unsigned DefaultMargin = 4;

        /// @brief Элемент интерфейса
        /// @paragraph Используется как шиблон для других классов
        class UIElement
        {
        protected:
        
            /// @brief Координаты
            point<int> _coord;

            /// @brief Размер
            point<unsigned> _size;

            ksys_color_t _MainColor;

            /// @brief Отступы
            unsigned _Margin;

            

        public:
            UIElement(point<int> coord = {0,0}, point<unsigned> size = {16, 16}, ksys_color_t MainColor = OS::sys_color_table.frame_area, unsigned Margin = DefaultMargin)
            {
                _coord = coord;
                _size = size;
                _MainColor = MainColor;
                _Margin = Margin;
            }

            /// @brief Проверяет находится ли курсор мыши на этом элементе
            /// @return truе если да, иначе false
            bool Hover()
            {
                point<int> mouse = mouse::GetMousePositionInWindow();
                if ((mouse.x > _coord.x && mouse.x < _coord.x + _size.x) && (mouse.y > _coord.y && mouse.y < _coord.y + _size.y))
                {
                    return true;
                }
                return false;
            }

            /// @brief Изменить цвет элемента
            /// @param Цвет
            /// @paragraph Функция изменяет занчение переменной @link _MainColor
            void SetColor(ksys_color_t color)
            {
                _MainColor = color;
            }

            /// @brief Получить цвет элемента
            /// @return Цвет, @link _MainColor
            ksys_color_t GetColor()
            {
                return _MainColor;
            }

            /// @brief Изменить размер текстовой метки
            /// @param NewSize Новый рамер текстовой метки
            void SetSize(const point<unsigned> &NewSize)
            {
                _size = NewSize;
            }

            /// @brief Изменить координаты текстовой метки
            /// @param NewCoords новые координаты(относительно окна)
            void SetCoord(const point<int> &NewCoords)
            {
                _coord = NewCoords;
            }

            /// @brief Получить размер элемента
            /// @return Функция возвращает @link _size
            point<unsigned> GetSize()
            {
                return _size;
            }
            /// @brief Получить координаты элемента
            /// @return Функция возвращает @link _coord
            point<int> GetCoord()
            {
                return _coord;
            }
        };

        //=============================================================================================================================================================

        /// \brief
        /// \param coord
        /// \param size
        /// \param color
        inline void DrawBar(point<unsigned> coord, point<unsigned> size, ksys_color_t color = OS::sys_color_table.work_graph)
        {
            _ksys_draw_bar(coord.x, coord.y, size.x, size.y, color);
        }

        

    }
        
}

#endif // __UI_H__