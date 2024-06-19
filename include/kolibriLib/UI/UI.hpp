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

			/// @brief получить абсолютные значения(в пикселях) относительно окна
			/// @return 
			point GetAbsolute(const point &Parent = {Thread::GetThreadInfo().winx_size, Thread::GetThreadInfo().winy_size}) const;


            bool operator == (const UDim &obj) const;
            bool operator != (const UDim &obj) const;

        };


        class GuiObject
        {
            public:
                /// @brief Получить размер элемента
                /// @return Функция возвращает _size
                virtual UDim GetSize() const;

                /// @brief Изменить размер элемента
                /// @param NewSize новый размер
                virtual void SetSize(const UDim &NewSize);

                /// @brief изменить координаты
                /// @param NewCoord новые координаты
                virtual void SetCoord(const UDim &NewCoord);

                /// @brief Получить координаты элемента
                /// @return Функция возвращает _coord
                virtual UDim GetCoord() const;


                /// @brief Изменить размер элемента
                /// @param NewSize новый размер
                virtual void SetSize(const Size &NewSize);

                /// @brief изменить координаты
                /// @param NewCoord новые координаты
                virtual void SetCoord(const Coord &NewCoord);


                virtual Size GetAbsoluteSize() const;
                virtual Size GetAbsoluteCoord() const;

        };


        /// @brief Отступы поумолчанию
        const unsigned DefaultMargin = 4;
        const Size DefaultSize = {200, 100};

        /// @brief Элемент интерфейса
        /// @note Используется как шаблон для других классов
        class UIElement: public GuiObject
        {
        protected:
        
            /// @brief Координаты
            UDim _coord;

            /// @brief Размер
            UDim _size;

            /// @brief Основной цвет элемента
            Colors::Color _MainColor;

            /// @brief Отступы
            unsigned _Margin;

			int _rotation;

            /// @brief Элемент gui относительно которого просиходят расчёты относительного размера
            GuiObject *Parent = nullptr;
           
        public:
            /// @brief Имя класса, (для наследуемых классов)
            std::string ClassName = "UIElement";

            /// @brief Флаг того нужно ли отрисовывать этот элемент при каждой перерисовке окна
            bool RenderOnEverythingRedraw;

            /// @brief Конструктор
            /// @param UDim координаты
            /// @param size размер
            /// @param MainColor основной цвет
            /// @param Margin отступы
            /// @param relative отностельность
			UIElement(const UDim &coord = point(0), const UDim &size = point(0), const Colors::Color &MainColor = OS::GetSystemColors().gui_frame, const unsigned &Margin = DefaultMargin);

            /// @brief 
            /// @param cp 
            UIElement(const UIElement &cp);

            virtual ~UIElement() = default;

            /// @brief 
            /// @param Parent 
            void SetParent(const GuiObject* Parent);

            /// @brief 
            /// @return 
            const GuiObject* GetParent() const;

			/// @brief Получить размер элемента
            /// @return Функция возвращает _size
            virtual UDim GetSize() const;

            /// @brief Изменить размер элемента
            /// @param NewSize новый размер
            virtual void SetSize(const UDim& NewSize);

            /// @brief Получить отступы
            /// @return Функция возвращает _Margin
            virtual unsigned GetMargin() const;

            /// @brief Получить осносной цвет элемента
            /// @return Функция возвращает _MainColor
            virtual Colors::Color GetColor() const;

            /// @brief Изменить цвет
            /// @param NewColor новый цвет
            virtual void SetColor(const Colors::Color& NewColor);

            /// @brief Повернуть элемент
            /// @param NewAngle Новый угол наклона
            virtual void Rotate(unsigned NewAngle);

            /// @brief Получить угол наклона элемента
            /// @return Функция возвращает _angle
            virtual unsigned GetRotate() const;

            /// @brief изменить координаты
            /// @param NewCoord новые координаты
            virtual void SetCoord(const UDim &NewCoord);

            /// @brief Получить координаты элемента
            /// @return Функция возвращает _coord
            virtual UDim GetCoord() const;

            /// @brief Проверить лежит ли курсор мыши над элементом
            /// @return true если курсор мыши находится в этом элементе, иначе false
            virtual bool Hover() const;

            Size GetAbsoluteSize() const;

            virtual int Handler();

            /// @brief Получить абсолютный размер элемента
            /// @return размер
            virtual Size GetAbsoluteSize() const;

            /// @brief Получить абсолютные координаты элемента
            /// @return 
            virtual Coord GetAbsolutePos() const;

            /// @brief отрисовать элемент
            virtual void Render() const;

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