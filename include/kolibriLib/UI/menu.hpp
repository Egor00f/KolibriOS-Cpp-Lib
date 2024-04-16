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
        public:

            struct Item: public buttons::Button
            {
                /// @brief Poiter to Menu
                Menu* _undermenu = nullptr;

                /// @brief 
                /// @param text 
                /// @param TextColor 
                /// @param BackgroundColor 
                Item(const text::Txt &text, const Colors::Color &TextColor = OS::GetSystemColors().work_text, const Colors::Color &BackgroundColor = OS::GetSystemColors().work_button, Menu *underMenu = nullptr);
                Item(const Item &copy);
                Item(const buttons::Button &copy);
                ~Item();
            };

            Menu(const Coord &coord = {0, 0}, 
                const Size &size = {0, 0}, 
                const std::vector<Item> &li = { Menu::Item(std::string("menu1")), Menu::Item(std::string("menu2")) }, 
                const unsigned &Margin = DefaultMargin, 
                const Colors::Color &color = OS::GetSystemColors().work_area);

            /// @brief 
            /// @param copy 
            Menu(const Menu &copy);

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

        private:
            std::vector<Item> _Buttons;
        };

    } // namespace UI

} // namespace KolibriLib

#endif // __MENU_H__