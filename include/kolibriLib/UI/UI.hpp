#ifndef __UI_HPP__
#define __UI_HPP__

#include <sys/ksys.h>

#include <vector>

#include <kolibriLib/types.hpp>
#include <kolibriLib/system/os.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/input/input.hpp>
#include <kolibriLib/window/windowBase.hpp>
#include <kolibriLib/graphic/screen.hpp>

namespace KolibriLib
{
    // Элементы UI
    namespace UI
    {

        /// @brief Отступы поумолчанию
        const unsigned DefaultMargin = 4;

        /// @brief Элемент интерфейса
        /// @note Используется как шаблон для других классов
        class UIElement
        {
        protected:
        
            /// @brief Координаты
            Coord _coord;

            /// @brief Размер
            Size _size;

            Colors::Color _MainColor;

            /// @brief Отступы
            unsigned _Margin;

            /// @brief Угол наклона
            unsigned _angle;

            /// @brief Оносительны ли координаты
            bool _relative;

        public:
            
            /// @brief Конструктор
            /// @param coord 
            /// @param size 
            /// @param MainColor 
            /// @param Margin 
            /// @param relative 
            UIElement(const Coord& coord = {0, 0}, const Size& size = {16, 16}, const Colors::Color& MainColor = OS::GetSystemColors().work_graph, const unsigned& Margin = DefaultMargin, bool relative = false);
            
            /// @brief Получить размер элемента
            /// @return Функция возвращает @link _size
            const Size& GetSize() const;

            /// @brief Изменить размер элемента
            /// @param NewSize новый размер
            void SetSize(const Size& NewSize);

            /// @brief Получить отступы
            /// @return Функция возвращает @link _Margin
            unsigned GetMargin() const;

            /// @brief Получить осносной цвет элемента
            /// @return Функция возвращает @link _MainColor
            const Colors::Color& GetColor() const;

            /// @brief 
            /// @param NewColor 
            void SetColor(const Colors::Color& NewColor);

            /// @brief 
            /// @param NewCoord 
            void SetCoord(const Coord& NewCoord);

            /// @brief Получить координаты элемента
            /// @return Функция возвращает _coord
            const Coord& GetCoord() const;

            /// @brief Повернуть элемент
            /// @param NewAngle Новый угол наклона
            void Rotate(unsigned NewAngle);

            /// @brief Получить угол наклона элемента
            /// @return Функция возвращает @link _angle
            unsigned GetRotate() const;

            /// @brief Проверить лежит ли курсор мыши над элементом
            /// @return true если курсор мыши находится в этом эелементе, иначе false
            bool Hover() const;

            /// @brief 
            /// @param Element 
            /// @return 
            UIElement& operator = (const UIElement& Element);

            /// @brief 
            /// @param Element 
            /// @return 
            bool operator == (const UIElement& Element) const;

            /// @brief 
            /// @param Element 
            /// @return 
            bool operator != (const UIElement &Element) const;
        };
    }
}

#endif // __UI_H__