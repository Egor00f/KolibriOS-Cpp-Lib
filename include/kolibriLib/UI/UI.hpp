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
        struct UDim
        {
            struct Axis
            {
                /// @brief Относительно размера окна
                float Scale;
                /// @brief В пикселях
                int Offset;

                Axis(float scale = 0, int offset = 0);
                bool operator == (const Axis& axis) const;
                bool operator !=(const Axis &axis) const;
            };

            UDim::Axis X, Y;

            /// @brief Конструктор
            /// @param p
            UDim(const point &p);

            /// @brief 
            /// @param XScale 
            /// @param XOffset 
            /// @param YScale 
            /// @param YOffset 
            UDim(float XScale, int XOffset, float YScale, int YOffset);

			/// @brief получить абсолютные значения(в пикселях)
			/// @return 
			point GetAbsolute() const;

            bool operator == (const UDim &obj) const;
            bool operator != (const UDim &obj) const;

        };

        /// @brief Отступы поумолчанию
        const unsigned DefaultMargin = 4;
        const Size DefaultSize = {200, 100};

        /// @brief Элемент интерфейса
        /// @note Используется как шаблон для других классов
        class UIElement
        {
        protected:
        
            /// @brief Координаты
            UDim _coord;

			int _rotation;

            /// @brief Размер
            UDim _size;

            Colors::Color _MainColor;

            /// @brief Отступы
            unsigned _Margin;
        public:
            
            /// @brief Конструктор
            /// @param UDim координаты
            /// @param size размер
            /// @param MainColor основной цвет
            /// @param Margin отступы
            /// @param relative отностельность
			UIElement(const UDim &coord = point(0), const UDim &size = point(0), const Colors::Color &MainColor = OS::GetSystemColors().gui_frame, const unsigned &Margin = DefaultMargin, bool relative = false);

			/// @brief Получить размер элемента
            /// @return Функция возвращает _size
            UDim GetSize() const;

            /// @brief Изменить размер элемента
            /// @param NewSize новый размер
            void SetSize(const UDim& NewSize);

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
            void SetCoord(const UDim& NewCoord);

            /// @brief Получить координаты элемента
            /// @return Функция возвращает _coord
            UDim GetCoord() const;

            /// @brief Повернуть элемент
            /// @param NewAngle Новый угол наклона
            void Rotate(unsigned NewAngle);

            /// @brief Получить угол наклона элемента
            /// @return Функция возвращает _angle
            unsigned GetRotate() const;

            /// @brief Проверить лежит ли курсор мыши над элементом
            /// @return true если курсор мыши находится в этом элементе, иначе false
            bool Hover() const;

            /// @brief Получить абсолютный размер элемента
            /// @return размер
            Size GetAbsoluteSize() const;

            /// @brief Получить абсолютные координаты элемента
            /// @return 
            Coord GetAbsolutePos() const;

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