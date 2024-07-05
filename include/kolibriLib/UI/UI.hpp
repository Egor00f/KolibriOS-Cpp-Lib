#ifndef __UI_HPP__
#define __UI_HPP__

#include <sys/ksys.h>

#include <vector>
#include <memory>

#include <kolibriLib/types.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/system/thread.hpp>
#include <kolibriLib/system/os.hpp>

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

                /// @brief Конструктор
                /// @param scale 
                /// @param offset 
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

        /// @brief Интерфейс для всех Объектов Gui
        class GuiObject
        {
            public:
                
                virtual ~GuiObject() = default;

                /// @brief Получить размер элемента
                /// @return Функция возвращает _size
                virtual UDim GetSize() const = 0;

                /// @brief Изменить размер элемента
                /// @param NewSize новый размер
                virtual void SetSize(const UDim &NewSize) = 0;

                /// @brief изменить координаты
                /// @param NewCoord новые координаты
                virtual void SetCoord(const UDim &NewCoord) = 0;

                /// @brief Получить координаты элемента
                /// @return Функция возвращает _coord
                virtual UDim GetCoord() const = 0;


                /// @brief Изменить размер элемента
                /// @param NewSize новый размер
                virtual void SetSize(const Size &NewSize) = 0;

                /// @brief изменить координаты
                /// @param NewCoord новые координаты
                virtual void SetCoord(const Coord &NewCoord) = 0;


                virtual Size GetAbsoluteSize() const = 0;
                virtual Size GetAbsoluteCoord() const = 0;

        };


        /// @brief Отступы поумолчанию
        const unsigned DefaultMargin = 4;
        const Size DefaultSize = {200, 100};

        /// @brief Элемент интерфейса
        /// @note Используется как шаблон для других классов
        class UIElement: virtual public GuiObject
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
            std::shared_ptr<GuiObject> Parent {nullptr};
           
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

            /// @brief 
            /// @param Parent 
            void SetParent(const GuiObject* Parent);

            /// @brief 
            /// @return 
            const GuiObject* GetParent() const;

			/// @brief Получить размер элемента
            /// @return Функция возвращает _size
            UDim GetSize() const override;

            /// @brief Изменить размер элемента
            /// @param NewSize новый размер
            void SetSize(const UDim& NewSize) override;

            /// @brief изменить координаты
            /// @param NewCoord новые координаты
            void SetCoord(const UDim &NewCoord) override;

            /// @brief Изменить размер элемента
            /// @param NewSize новый размер
            void SetSize(const Size &NewSize) override;

            void SetCoord(const Coord &NewCoord) override;

            /// @brief Получить абсолютный размер элемента
            /// @return размер
            Size GetAbsoluteSize() const override;

            /// @brief Получить абсолютные координаты элемента
            /// @return
            Coord GetAbsoluteCoord() const override;

            /// @brief Получить координаты элемента
            /// @return Функция возвращает _coord
            UDim GetCoord() const override;

            /// @brief Получить отступы
            /// @return Функция возвращает _Margin
            unsigned GetMargin() const;

            /// @brief Получить осносной цвет элемента
            /// @return Функция возвращает _MainColor
            Colors::Color GetColor() const;

            /// @brief Изменить цвет
            /// @param NewColor новый цвет
            void SetColor(const Colors::Color& NewColor);

            /// @brief Повернуть элемент
            /// @param NewAngle Новый угол наклона
            void Rotate(unsigned NewAngle);

            /// @brief Получить угол наклона элемента
            /// @return Функция возвращает _angle
            unsigned GetRotate() const;

            /// @brief Проверить лежит ли курсор мыши над элементом
            /// @return true если курсор мыши находится в этом элементе, иначе false
            bool Hover() const;

            int Handler();

            /// @brief отрисовать элемент
            void Render() const;

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