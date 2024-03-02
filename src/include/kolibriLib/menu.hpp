#ifndef __MENU_H__
#define __MENU_H__

#include <vector>

#include "UI.hpp"
#include "os.hpp"
#include "color.hpp"
#include "button.hpp"
#include "graphic.hpp"

namespace KolibriLib
{
    namespace UI
    {
        class Menu: public UIElement
        {
        private:
            std::vector<buttons::Button> _Buttons;
        public:
            Menu(const Coord& coord = {0,0}, const Size& size = {0,0}, const std::vector<std::string>& li, const unsigned& Margin = DefaultMargin, const Color::Color& color = OS::sys_color_table.work_area);
            ~Menu();

            /// @brief Отрисовать меню
            void Render();

            /// @brief Добавить элемент в список 
            unsigned AddItem(const text::TextLabel& item, bool end = true);
            bool DeleteItem(unsigned i);
        };

        Menu::Menu(const Coord &coord, const Size &size, const std::vector<std::string>& li, const unsigned &Margin, const Color::Color &color) : UIElement(coord, size, color, Margin)
        {
            for(int i = 0; i < li.size(); i++)
            {
                buttons::Button btn({coord.x, coord.y + ((int)(size.y / li.size()) * i)}, {size.x, size.y / li.size()}, Margin, color);
                btn.SetText(li[i]);
                _Buttons.push_back(btn);
            }
        }
        
        Menu::~Menu()
        {
        }
        void Menu::Render()
        {
            for(int i = 0; i < _Buttons.size(); i++)
            {
                _Buttons[i].Render();
            }
        }
        
    } // namespace UI
    
} // namespace KolibriLib


#endif // __MENU_H__