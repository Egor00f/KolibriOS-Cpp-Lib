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
        public:

            typedef int ElementNumber;

            std::string ClassName = "Frame";
            bool RenderOnEverythingRedraw = false;

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
            ElementNumber AddElement(const T &element);

            template <class T>
            /// @brief Изменить элемент
            /// tparam T
            /// @param i номер элемента
            /// @param element
            void SetElement(ElementNumber i, const T &element);

            /// @brief Полчить элемент
            /// @param i номер элемента
            /// @return
            UIElement* GetElement(ElementNumber i) const;

            /// @brief Удалить элемент из фрейма
            /// @param i Номер элемента
            void DeleteElement(ElementNumber i);

        private:
            std::map<ElementNumber, UIElement *> _Elements;
            bool _scroll;
        };


        

        Frame::Frame(const UDim &coord, const UDim &size, const Colors::Color &Color, const unsigned &Margin) 
            : UIElement(coord, size, Color, Margin)
        {
            #if DEBUG == true
            _ksys_debug_puts("Frame constructor\n");
            #endif
        }

        void UI::Frame::Render()
        {
            graphic::DrawRectangleFill(_coord.GetAbsolute(), _size.GetAbsolute(), _MainColor);

            for (const auto &n : _Elements)
            {
               n.second->Render();
            }
        }

        void UI::Frame::Handler()
        {
            if (Hover())
            {
            }
        }

        template <class T>
        Frame::ElementNumber UI::Frame::AddElement(const T &element)
        {
            for (ElementNumber i = 0; i < _Elements.max_size(); i++)
            {
                if (_Elements.count(i) == 0)
                {
                    _Elements.emplace(i, new T(element));

                    return i;
                }
            }
            return -1;
        }
        
        template <class T>
        void UI::Frame::SetElement(ElementNumber i, const T &element)
        {
            if (_Elements.count(i))
            {
                delete _Elements[i];
                _Elements[i] = new T(element);
                return;
            }
            _ksys_debug_puts("KolibriLib::UI::Frame::Element::SetElement: i >= _Elements.size(), return\n");
        }

        UIElement *UI::Frame::GetElement(ElementNumber i) const
        {
            if (_Elements.count(i))
            {
                return _Elements.at(i);
            }
            _ksys_debug_puts("KolibriLib::UI::Frame::Element::SetElement: i >= _Elements.size(), return\n");
        }

        void KolibriLib::UI::Frame::DeleteElement(ElementNumber i)
        {
            if (_Elements.count(i))
            {
                delete _Elements[i];
                _Elements.erase(_Elements.find(i));
                return;
            }
            _ksys_debug_puts("element with this id not found\n");
        }
    } // namespace UI
} // namespace KolibriLib


#endif // __FRAME_H__