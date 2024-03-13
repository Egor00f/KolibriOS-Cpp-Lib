#ifndef __MENU_H__
#define __MENU_H__

#include <vector>
#include <string>

#include <kolibriLib/types.hpp>
#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/system/os.hpp>
#include <kolibriLib/color.hpp>
#include "button.hpp"
#include <kolibriLib/graphic/graphic.hpp>

namespace KolibriLib
{
    namespace UI
    {
        /// @brief Выпадающее менб список
        class Menu : public UIElement
        {
        private:
            std::vector<buttons::Button> _Buttons;
        public:
            Menu(const Coord &coord = {0, 0}, const Size &size = {0, 0}, const std::vector<std::string> &li = {"menu", "menu"}, const unsigned &Margin = DefaultMargin, const Colors::Color &color = OS::GetSystemColors().work_area);
            ~Menu();

            /// @brief Отрисовать меню
            void Render();

            /// @brief Обработчик
            /// @return Номер нажатого элемента
            int Handler();

            /// @brief Добавить элемент в список
            /// @param item текст элемента
            /// @param i номер элемента в списке
            /// @return номер элемента в списке, или 0
            /// @paragraph Если i = -1, то элемент вставляется в конец, иначе вставляется на место под номером i. При этом номера всех элементов с номером больше i, нужно увеличить на 1.
            int AddItem(const std::string &item, int i = -1);

            void SetItem(const std::string& NewText, int i);

            /// @brief Удалить элемент
            /// @param i номер удаляемого элемента
            /// @return true если удачно, иначе false
            bool DeleteItem(unsigned i);
        };

        
        
Menu::Menu(const Coord &coord, const Size &size, const std::vector<std::string> &li, const unsigned &Margin, const Colors::Color &color) : UIElement(coord, size, color, Margin)
{
    for (int i = 0; i < li.size(); i++)
    {
        buttons::Button btn({coord.x, coord.y + ((int)(size.y / li.size()) * i)}, {size.x, size.y / li.size()}, Margin, color);
        btn.insert(li[i], 0);
        _Buttons.push_back(btn);
    }
}

Menu::~Menu()
{
}
void Menu::Render()
{
    for (int i = 0; i < _Buttons.size(); i++)
    {
        _Buttons[i].Render();
    }
}

int KolibriLib::UI::Menu::Handler()
{
    for(int i = 0; i < _Buttons.size(); i++)
    {
        if(_Buttons[i].Handler())
        {
            return i;
        }
    }
    return -1;
}

int KolibriLib::UI::Menu::AddItem(const std::string &item, int i)
{
    buttons::Button btn ({_coord.x, _coord.y + ((int)(_size.y / _Buttons.size()) * i)}, {_size.x}, _Margin, _MainColor);
    btn.insert(item, 0);
    if(i == -1)
    {
        _Buttons.push_back(btn);
        return _Buttons.size() - 1;
    }
    
    _Buttons.insert(_Buttons.begin() + i, btn);
    return 0;
}

void Menu::SetItem(const std::string &NewText, int i)
{
    _Buttons[i].SetText(NewText);
}

bool KolibriLib::UI::Menu::DeleteItem(unsigned i)
{
    if(_Buttons.size() <= i || i < 0)
    {
        return false;
    }

    _Buttons.erase(_Buttons.begin() + i);

    return true;
}

    } // namespace UI

} // namespace KolibriLib

#endif // __MENU_H__