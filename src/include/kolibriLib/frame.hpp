#ifndef __FRAME_H__
#define __FRAME_H__


#include <vector>
#include <type_traits>

#include "graphic.hpp"
#include "UI.hpp"
#include "text.hpp"
#include "button.hpp"
#include "form.hpp"
#include "image.hpp"
#include "checkbox.hpp"
#include "menu.hpp"
#include "input.hpp"

namespace KolibriLib
{
    namespace UI
    {

        class Frame: public UIElement
        {
        private:
            struct Element
            {
                enum Type
				{
					None = 0,
					Button,
					Image,
					CheckBox,
					Form,
					TextLabel,
					Frame,
					Menu
				};

				UI::buttons::Button * btn;
				UI::Images::Image   * img;
				UI::CheckBox        * checkbox;
				UI::Form            * form;
				UI::text::TextLabel * txt;
				UI::Menu            * menu;

				unsigned _type;
				unsigned DrawPrioritet;
				bool use;

				Element();
				~Element();

				template <class T>
				void SetElement(const T& elem);

				void free();
            };
            std::vector<Element> _Elements;
            bool _scroll;
        public:
            Frame(const Coord &coord = {0,0}, const Size &size = {0,0}, const Colors::Color &Color = OS::sys_color_table.work_area, const unsigned &Margin = DefaultMargin);
            

            /// @brief Отрисовать фрейм
            void Render();

            /// @brief 
            void Handler();

            template <class T>
            /// @brief Добавить элемент во фрейм
            /// @param element элемент
            /// @return номер элемента
            unsigned AddElement(const T &element);

            template <class T>
            /// @brief Изменить элемент
            /// tparam T
            /// @param i номер элемента
            /// @param element
            void SetElement(unsigned i, const T &element);

            /// @brief Полчить элемент
            /// @tparam T
            /// @param i номер элемента
            /// @return
            template <class T>
            T GetElement(unsigned i) const;

            /// @brief Удалить элемент из фрейма
            /// @param i Номер элемента
            void DeleteElement(unsigned i);
        };
    } // namespace UI
} // namespace KolibriLib


#endif // __FRAME_H__