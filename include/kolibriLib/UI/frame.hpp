#ifndef __FRAME_H__
#define __FRAME_H__

#include <map>

#include <kolibriLib/graphic/graphic.hpp>
#include "UI.hpp"
#include "text/textlabel.hpp"
#include "button.hpp"
#include "form.hpp"
#include "image.hpp"
#include "checkbox.hpp"
#include "menu.hpp"
#include <input.hpp>

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

				void *pointer;

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
            std::map<int, Element> _Elements;
            bool _scroll;
        public:
             std::string ClassName = "Frame";

            /// @brief 
            /// @param coord 
            /// @param size 
            /// @param Color 
            /// @param Margin
            Frame(const UDim &coord = point(0), const UDim &size = DefaultSize, const Colors::Color &Color = OS::GetSystemColors().gui_frame, const unsigned &Margin = DefaultMargin);

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

        Frame::Element::Element()
        {
            #ifdef Debug
            _ksys_debug_puts("KolibriLib::Frame::Element constructor\n");
            #endif
            _type = Type::None;
        }

        Frame::Element::~Element()
        {
            #ifdef Debug
            _ksys_debug_puts("KolibriLib::Frame::Element destructor\n");
            #endif
            free();
        }

        void Frame::Element::free()
        {
            switch (_type)
            {
            case Type::Button:
                delete ((buttons::Button*)pointer);
                break;
            case Type::Image:
                delete ((Images::Image*)pointer);
                break;
            case Type::CheckBox:
                delete ((UI::CheckBox*)pointer);
                break;
            case Type::Form:
                delete ((UI::Form*)pointer);
                break;
            case Type::TextLabel:
                delete ((text::TextLabel*)pointer);
                break;
            case Type::Menu:
                delete ((UI::Menu*)pointer);
                break;
            }
        }

        template <class T>
        void Frame::Element::SetElement(const T &elem)
        {
            _ksys_debug_puts("Error in KolibriLib::UI::Frame::Element::SetElement: unklown type");
        }

        //=============================================================================================================================================================
        template <>
        void Frame::Element::SetElement<UI::buttons::Button>(const UI::buttons::Button &elem)
        {
            free();
            pointer = new UI::buttons::Button(elem);
            _type = Type::Button;
        }

        template <>
        void Frame::Element::SetElement<UI::Images::Image>(const UI::Images::Image &elem)
        {
            free();
            pointer = new UI::Images::Image(elem);
            _type = Type::Image;
        }

        template <>
        void Frame::Element::SetElement<UI::CheckBox>(const UI::CheckBox &elem)
        {
            free();
            pointer = new UI::CheckBox(elem);
            _type = Type::CheckBox;
        }

        template <>
        void Frame::Element::SetElement<UI::Form>(const UI::Form &elem)
        {
            free();
            pointer = new UI::Form(elem);
            _type = Type::Form;
        }

        template <>
        void Frame::Element::SetElement<UI::text::TextLabel>(const UI::text::TextLabel &elem)
        {
            free();
            pointer = new UI::text::TextLabel(elem);
            _type = Type::TextLabel;
        }

        template <>
        void Frame::Element::SetElement<UI::Menu>(const UI::Menu &elem)
        {
            free();
            pointer = new UI::Menu(elem);
            _type = Type::Menu;
        }

        Frame::Frame(const UDim &coord, const UDim &size, const Colors::Color &Color, const unsigned &Margin) : UIElement(coord, size, Color, Margin)
        {
            #if DEBUG == true
            _ksys_debug_puts("Frame constructor\n");
            #endif
        }

        void UI::Frame::Render()
        {
            graphic::DrawRectangleFill(_coord.GetAbsolute(), _size.GetAbsolute(), _MainColor);

            for (const std::pair<int, Element> &n : _Elements)
            {
                switch (n.second._type)
                {
                case Element::Type::TextLabel:
                    ((text::TextLabel*)n.second.pointer)->Render();
                    break;
                case Element::Type::Button:
                    ((buttons::Button*)n.second.pointer)->Render();
                    break;
                case Element::Type::Image:
                    ((Images::Image*)n.second.pointer)->Render();
                    break;
                case Element::Type::Form:
                    ((UI::Form*)n.second.pointer)->Render();
                    break;
                case Element::Type::CheckBox:
                    ((UI::CheckBox*)n.second.pointer)->Render();
                    break;
                case Element::Type::Menu:
                    ((UI::Menu*)n.second.pointer)->Render();
                    break;
                default:
                    break;
                }
            }
        }

        void UI::Frame::Handler()
        {
            if (Hover())
            {
            }
        }

        void KolibriLib::UI::Frame::DeleteElement(int i)
        {
            if (_Elements.count(i)) // Проверка что элемент с таким ключом
            {
                _Elements.erase(i);
            }
            _ksys_debug_puts("KolibriLib::UI::Frame::DeleteElement: \n");
        }

        template <class T>
        unsigned UI::Frame::AddElement(const T &element)
        {
            Element a;
            a.SetElement(element);

            auto p = _Elements.emplace(a);
            return p.first;

            _ksys_debug_puts("KolibriLib::UI::Frame::AddElement _Elements is overflow\n");
        }
        template <class T>
        void UI::Frame::SetElement(int i, const T &element)
        {
            if (_Elements.count(i))
            {
                _Elements[i].SetElement(element);
                return;
            }
            _ksys_debug_puts("KolibriLib::UI::Frame::Element::SetElement: i >= _Elements.size(), return\n");
        }

        const Frame::Element &UI::Frame::GetElement(int i) const
        {
            if (_Elements.count(i))
            {
                return _Elements.at(i);
            }
            _ksys_debug_puts("KolibriLib::UI::Frame::Element::SetElement: i >= _Elements.size(), return\n");
        }
    } // namespace UI
} // namespace KolibriLib


#endif // __FRAME_H__