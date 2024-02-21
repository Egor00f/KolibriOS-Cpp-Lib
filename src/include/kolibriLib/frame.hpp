#ifndef __FRAME_H__
#define __FRAME_H__

#include <unordered_map>

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

        /// @brief Фрейм
        /// @paragraph Может содержать другие элементы 
        class Frame: public UIElement
        {
        private:
            struct Element
            {
                // Список типов с которыми умеет работать элемент
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

				// хранит тип данных который хранит этот элемент
				unsigned _type;

				/// @brief 
				Element();
				~Element();

				/// @brief 
				/// @tparam T 
				/// @param elem 
				template <class T>
				void SetElement(const T& elem);

				void free();
            };
            std::unordered_map<int, Element> _Elements;
            bool _scroll;
        public:
            /// @brief 
            /// @param coord 
            /// @param size 
            /// @param Color 
            /// @param Margin 
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
            void SetElement(int i, const T &element);

            /// @brief Полчить элемент
            /// @param i номер элемента
            /// @return
            const Element& GetElement(int i) const;

            /// @brief Удалить элемент из фрейма
            /// @param i Номер элемента
            void DeleteElement(int i);
        };
    } // namespace UI
} // namespace KolibriLib


#endif // __FRAME_H__