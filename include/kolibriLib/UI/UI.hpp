#ifndef __UI_HPP__
#define __UI_HPP__

#include <sys/ksys.h>

#include <vector>

#include <kolibriLib/types.hpp>
#include <kolibriLib/system/os.hpp>
#include <kolibriLib/color.hpp>
#include <input.hpp>
#include <kolibriLib/window/windowBase.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/graphic/screen.hpp>

namespace KolibriLib
{
    // Элементы UI
    namespace UI
    {

        /// @brief Координаты/Размеры для элементов UI
        struct UIDim
        {
            /// @brief Абсолютные значения
            Coord Offset;

            /// @brief Относительно размеров окна
            Coord Scale;

            /// @brief 
            /// @param p 
            UIDim(const point &p);
        };

        /// @brief Отступы поумолчанию
        const unsigned DefaultMargin = 4;

        /// @brief Элемент интерфейса
        /// @note Используется как шаблон для других классов
        class UIElement
        {
        protected:
        
            /// @brief Координаты
            CoordA _coord;

            /// @brief Размер
            Size _size;

            Colors::Color _MainColor;

            /// @brief Отступы
            unsigned _Margin;

            /// @brief Оносительны ли координаты
            bool _relative;

        public:
            
            /// @brief Конструктор
            /// @param coord координаты
            /// @param size размер
            /// @param MainColor основной цвет
            /// @param Margin отступы
            /// @param relative отностельность
            UIElement(const Coord& coord = Coord(0,0), const Size& size = Size(32,32), const Colors::Color& MainColor = OS::GetSystemColors().work_graph, const unsigned& Margin = DefaultMargin, bool relative = false);
            
            /// @brief Получить размер элемента
            /// @return Функция возвращает _size
            Size GetSize() const;

            /// @brief Изменить размер элемента
            /// @param NewSize новый размер
            void SetSize(const Size& NewSize);

            /// @brief Получить отступы
            /// @return Функция возвращает _Margin
            unsigned GetMargin() const;

            /// @brief Получить осносной цвет элемента
            /// @return Функция возвращает _MainColor
            Colors::Color GetColor() const;

            /// @brief Изменить цвет
            /// @param NewColor новый цвет
            void SetColor(const Colors::Color& NewColor);

            /// @brief изменить координаты
            /// @param NewCoord новые координаты
            void SetCoord(const Coord& NewCoord);

            /// @brief Получить координаты элемента
            /// @return Функция возвращает _coord
            Coord GetCoord() const;

            /// @brief Повернуть элемент
            /// @param NewAngle Новый угол наклона
            void Rotate(unsigned NewAngle);

            /// @brief Получить угол наклона элемента
            /// @return Функция возвращает _angle
            unsigned GetRotate() const;

            /// @brief Проверить лежит ли курсор мыши над элементом
            /// @return true если курсор мыши находится в этом элементе, иначе false
            bool Hover() const;

            /// @brief отрисовать элемент
            virtual void Render();

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