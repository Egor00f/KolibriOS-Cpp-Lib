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
        /// @paragraph Используется как шиблон для других классов
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
            UIElement(const Coord& coord = {0, 0}, const Size& size = {16, 16}, const Colors::Color& MainColor = OS::sys_color_table.work_graph, const unsigned& Margin = DefaultMargin, bool relative = false);
            
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

        //=============================================================================================================================================================

        /// \brief
        /// \param coord
        /// \param size
        /// \param color
        inline void DrawBar(const Coord& coord, const Size& size, const Colors::Color& color = OS::sys_color_table.work_graph)
        {
            _ksys_draw_bar(coord.x, coord.y, size.x, size.y, color.val);
        }

        KolibriLib::UI::UIElement::UIElement(const Coord &coord, const Size &size, const Colors::Color &MainColor, const unsigned &Margin, bool relative)
        {
#if DEBUG == true
            _ksys_debug_puts("UIElement:");
#endif
            _coord = (Coord){coord.x, coord.y + (int)window::GetSkinHeight()};
            _size = size;
            _MainColor = MainColor;
            _Margin = Margin;
            _relative = relative;
        }

        const Size &KolibriLib::UI::UIElement::GetSize() const
        {
            return _size;
        }

        void KolibriLib::UI::UIElement::SetSize(const Size &NewSize)
        {
            _size = NewSize;
        }

        unsigned KolibriLib::UI::UIElement::GetMargin() const
        {
            return _Margin;
        }

        const Colors::Color &KolibriLib::UI::UIElement::GetColor() const
        {
            return _MainColor;
        }

        void KolibriLib::UI::UIElement::SetColor(const Colors::Color &NewColor)
        {
            _MainColor = NewColor;
        }

        void KolibriLib::UI::UIElement::SetCoord(const Coord &NewCoord)
        {
            _coord = NewCoord;
        }

        const Coord &KolibriLib::UI::UIElement::GetCoord() const
        {
            return _coord;
        }

        void KolibriLib::UI::UIElement::Rotate(unsigned NewAngle)
        {
            _angle = NewAngle;
        }

        unsigned KolibriLib::UI::UIElement::GetRotate() const
        {
            return _angle;
        }

        bool KolibriLib::UI::UIElement::Hover() const
        {
            Coord Mouse = mouse::GetMousePositionInWindow();

            return ((_coord.x < Mouse.x) && (_coord.y < Mouse.y) && (Mouse.x < (_coord.x + _size.x)) && (Mouse.y < (_coord.y + _size.y))) && (ScreenPointAffiliation(Mouse) == Thread::GetThreadSlot(Thread::GetThreadInfo(-1).pid));
        }

        UIElement &KolibriLib::UI::UIElement::operator=(const UIElement &Element)
        {
            _coord = Element._coord;
            _size = Element._size;
            _MainColor = Element._MainColor;
            _Margin = Element._Margin;
            _angle = Element._angle;
            return *this;
        }

        bool KolibriLib::UI::UIElement::operator==(const UIElement &Element) const
        {
            return (_coord == Element._coord) && (_size == Element._size) && (_MainColor == Element._MainColor) && (_angle == Element._angle);
        }

        bool KolibriLib::UI::UIElement::operator!=(const UIElement &Element) const
        {
            return (_coord != Element._coord) || (_size != Element._size) || (_MainColor != Element._MainColor) || (_angle != Element._angle);
        }
    }
}

#endif // __UI_H__