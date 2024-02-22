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
            Menu(const Coord &coord = {0, 0}, const Size &size = {0, 0}, const std::vector<std::string> &li = {"menu", "menu"}, const unsigned &Margin = DefaultMargin, const Colors::Color &color = OS::sys_color_table.work_area);
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

            /// @brief Удалить элемент
            /// @param i номер удаляемого элемента
            /// @return true если удачно, иначе false
            bool DeleteItem(unsigned i);
        };

        

    } // namespace UI

} // namespace KolibriLib

#endif // __MENU_H__