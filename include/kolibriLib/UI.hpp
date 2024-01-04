#ifndef __UI_HPP__
#define __UI_HPP__

extern "C"{
#include <sys/ksys.h>
}

#include <vector>

#include "base.hpp"
#include "windowBase.hpp"
#include "graphic.hpp"

namespace KolibriLib
{
    // Элементы UI
    namespace UI
    {

        class UIElement
        {
        protected:
        
            KolibriLib::point _coord;
            KolibriLib::point _size;
            unsigned _Margin;

        public:
            UIElement(KolibriLib::point coord, KolibriLib::point size, unsigned Margin)
            {
                _coord = coord;
                _size = size;
                _Margin = Margin;
            }
        };

        //=============================================================================================================================================================

        /// @brief
        /// @param coord
        /// @param size
        /// @param color
        inline void DrawBar(KolibriLib::point coord, KolibriLib::point size, ksys_color_t color = window::colors.work_graph)
        {
            _ksys_draw_bar(coord.x * KolibriLib::AAANUMBER, coord.y * KolibriLib::AAANUMBER, size.x, size.y, color);
        }

        namespace text
        {
            /// @brief Получить размер текста
            /// @return текущая высота текста
            unsigned int GetTextSize()
            {
                unsigned Size;
                asm_inline(
                    "int $0x40"
                    : "=c"(Size)
                    : "a"(48), "b"(11)
                );
                return Size;
            }

            /// @brief Изменить размер текста
            /// @param newSize высота текста в px
            void SetTextSize(unsigned int newSize)
            {
                asm_inline(
                    "int $0x40" ::"a"(48), "b"(12), "c"(newSize)
                );
            }


            /// @brief Вывести текст
            /// @param text текст
            /// @param coord координаты
            /// @param color цвет текста
            inline void DrawText(std::string text, KolibriLib::point coord, unsigned size = 9, ksys_color_t color = window::colors.work_text)
            {
                SetTextSize(size);
                _ksys_draw_text(text.c_str(), coord.x, coord.y, text.length(), color);
            }

            /// @brief Вывести текст
            /// @param text текст
            /// @param coord координаты
            /// @param color цвет текста
            inline void DrawText(const char *text, KolibriLib::point coord, unsigned size = 9, ksys_color_t color = window::colors.work_text)
            {
                SetTextSize(size);
                _ksys_draw_text(text, coord.x, coord.y, strlen(text), color);
            }

            

            /* class Text: public UIElement
            {
            private:
                std::string _text;
                unsigned _FontSize;
            public:
                Text(point coord, point size = {0, 0}, std::string text, unsigned FontSize = 0, unsigned Margin = 0);
                ~Text();
                void render();
            };

            Text::Text(point coord, point size, std::string text, unsigned FontSize = 0, unsigned Margin) : UIElement(coord, size, Margin)
            {
                _text = text;
                _FontSize = FontSize;
            }
            
            Text::~Text()
            {
                
            }
            
            void Text::render()
            {
                if (_size.x == 0 && _size.y == 0)
                {
                    
                }
                else
                {
                    _FontSize = _size.x / _text.length();
                }
                SetTextSize(_FontSize);
                DrawText(_text, _coord);
            }*/


        } 

        //=============================================================================================================================================================

        // Работа с кнопками
        namespace buttons
        {
            // Коды кнопок начинаются с этого числа
            const unsigned StartButtonId = 100;

            // Список idшников кнопок
            std::vector<unsigned> ButtonsIdList;

            /// @brief Получить свободный номер id кнопки из списка
            /// @return номер id
            unsigned GetFreeButtonId()
            {
                ButtonsIdList.push_back(StartButtonId + ButtonsIdList.size());
                return ButtonsIdList.size() - 1; //-1 потому что обращение к элементам массива идёт с 0
            }

            /// @brief Освободить id
            /// @param id номер id
            void FreeButtonId(unsigned id)
            {
                ButtonsIdList.erase(ButtonsIdList.begin() + id, ButtonsIdList.begin() + id);
            }

            /// @brief Получить реальный id кнопки
            /// @param id номер id
            /// @return ButtonsIdList[id].ID
            unsigned GetButtonId(unsigned id)
            {
                return ButtonsIdList[id];
            }

            /// @brief Создать кнопку, автоматически присвоить ей id
            /// @param coords координаты
            /// @param size размер
            /// @param color цвет
            /// @return id созданной кнопки
            inline unsigned autoDefineButton(point coords, point size, ksys_color_t color = OS::sys_color_table.work_button)
            {
                unsigned id = GetButtonId(GetFreeButtonId()); // Автоматически получаем id для кнопки
                _ksys_define_button(coords.x, coords.y, size.x, size.y, id, color);
                return id;
            }

            /// @brief Создать кнопку, вручную
            /// @param coords координаты
            /// @param size размер
            /// @param id idшник кнопки
            /// @param color цвет
            inline void DefineButton(point coord, point size, unsigned id, ksys_color_t color = OS::sys_color_table.work_button)
            {
                _ksys_define_button(coord.x, coord.y, size.x, size.y, id, color);
            }

            /// @brief Удалить кнопу
            /// @param id id удаляемой кнопки
            inline void DeleteButton(unsigned id)
            {
                _ksys_delete_button(id);
                FreeButtonId(id); // Кнопка удалена, теперь этот id не использется
            }

            /// @brief проверить какая кнопка нажата
            /// @return id нажатой кнопки
            inline unsigned GetPressedButton()
            {
                return _ksys_get_button();
            }

            /// @brief кнопка
            class Button : public UIElement
            {
            private:
                std::string _text;
                ksys_color_t _BackgroundColor;
                ksys_color_t _TextColor;
                unsigned _id;
                bool _status;

            public:
                /// @brief
                /// @param coord координата
                /// @param size размер
                /// @param text текст
                /// @param Margin отступы текста от границ
                /// @param BackgroundColor цвет кнопки
                /// @param TextColor цвет текста
                Button(point coord = {0, 0}, point size = {20, 20}, std::string text = "Button", unsigned Margin = window::MARGIN, ksys_color_t BackgroundColor = OS::sys_color_table.work_button, ksys_color_t TextColor = OS::sys_color_table.work_text);

                /// @brief инициализировать параметры
                /// @param coord координата
                /// @param size размер
                /// @param text текст
                /// @param Margin отступы текста от границ
                /// @param BackgroundColor цвет кнопки
                /// @param TextColor цвет текста
                void init(point coord, point size, std::string text, unsigned Margin = window::MARGIN, ksys_color_t BackgroundColor = OS::sys_color_table.work_button, ksys_color_t TextColor = OS::sys_color_table.work_text);

                /// @brief Отрисовать кнопку
                void render();

                /// @brief Обработчик кнопки
                /// @return состояние кнопки
                bool Handler();

                /// @brief Получить сосояние кнопки
                /// @return состояние кноки
                bool GetStatus();

                /// @brief Получить id кнопки
                /// @return _id
                unsigned GetId();

                ~Button();
            };

            Button::Button(point coord, point size, std::string text, unsigned Margin, ksys_color_t BackgroundColor, ksys_color_t TextColor) : UIElement(coord, size, Margin)
            {
                this->_text = text;
                this->_BackgroundColor = BackgroundColor;
                this->_TextColor = TextColor;
                this->_id = GetButtonId(GetFreeButtonId());
            }

            Button::~Button()
            {
                DeleteButton(_id);
            }

            void Button::render()
            {
                DefineButton(_coord, _size, _id, _BackgroundColor);
                unsigned buff = text::GetTextSize();
                text::SetTextSize(_size.y - 2 * _Margin);
                text::DrawText(_text, _coord, _TextColor);
                text::SetTextSize(buff); // Возвращение размера текста обратно
            }

            bool Button::Handler()
            {
                if (GetPressedButton() == _id)
                {
                    _status = true;
                }
                else
                {
                    _status = false;
                }
                return _status;
            }

            bool Button::GetStatus()
            {
                return _status;
            }

            void UI::buttons::Button::init(point coord, point size, std::string text, unsigned Margin, ksys_color_t BackgroundColor, ksys_color_t TextColor)
            {
                _coord = coord;
                _size = size;
                _Margin = Margin;
                this->_text = text;
                this->_BackgroundColor = BackgroundColor;
                this->_TextColor = TextColor;
                this->_id = GetButtonId(GetFreeButtonId());
            }

            unsigned Button::GetId()
            {
                return _id;
            }


        }

        //=============================================================================================================================================================

        /// @brief Форма для ввода текста
        class Form : public UIElement
        {
        private:
            std::string _BackgroundText;
            std::string _inputText;  // Введённый пользователем текст
            ksys_color_t _FormColor; // Цвет рамки формы
            ksys_color_t _BackgroundTextColor;
            KolibriLib::UI::buttons::Button _butt;
            bool _active;

        public:
            /// @brief конструктор
            /// @param coord позиция в коне
            /// @param size размеры
            /// @param BackgroundText фоновый текст(проподает когда вводится текст)
            /// @param FormColor цвет рамки формы
            /// @param BackgroundTextColor цвет фонового текста
            /// @param Margin отступы рамки от текста
            Form(KolibriLib::point coord, KolibriLib::point size, std::string BackgroundText = " ", ksys_color_t FormColor = KolibriLib::OS::sys_color_table.work_text, ksys_color_t BackgroundTextColor = KolibriLib::OS::sys_color_table.work_button_text, unsigned Margin = KolibriLib::window::MARGIN);

            /// @brief Отрисовать форму
            void render();
            /// @brief Обработчик
            void Handler();

            /// @brief Получить введённый текст
            /// @return текст который ввели в форму
            std::string GetInput();
            ~Form();
        };

        Form::Form(KolibriLib::point coord, KolibriLib::point size, std::string BackgroundText, ksys_color_t FormColor, ksys_color_t BackgroundTextColor, unsigned Margin) : UIElement(coord, size, Margin)
        {
            _BackgroundText = BackgroundText;
            _FormColor = FormColor;
            _BackgroundTextColor = BackgroundTextColor;
            _active = false;
            _butt.init(coord, size, " ", 0);
            render();
        }

        Form::~Form()
        {
        }

        void Form::render()
        {
            unsigned TextSizeBuff = text::GetTextSize();

            KolibriLib::graphic::DrawRectangleLines(_coord, {_coord.x + _size.x, _coord.y + _size.y});
            text::SetTextSize(_size.y - (2 * _Margin)); // Подгон размера текста под размеры формы
            if (_inputText == "")
            {
                text::DrawText(
                    _BackgroundText,
                    (KolibriLib::point){_coord.x + _Margin, (_coord.y + _coord.y) - _Margin},
                    _BackgroundTextColor);
            }

            _butt.render();

            text::SetTextSize(TextSizeBuff); // Возвращение размера текста обратно
        }

        std::string Form::GetInput()
        {
            return _inputText;
        }

        void Form::Handler()
        {

            if (_butt.Handler())
            {
                _active = !_active;
            }
        }
    }
}

#endif // __UI_H__