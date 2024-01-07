#ifndef __UI_HPP__
#define __UI_HPP__

#include <sys/ksys.h>

#include <vector>

#include "base.hpp"
#include "windowBase.hpp"
#include "graphic.hpp"

namespace KolibriLib
{
    // Элементы UI
    namespace UI
    {
        /// @brief Отступы поумолчанию
        const unsigned DefaultMargin = 4;

        /// @brief Элемент интерфейса
        /// @paragraph Используется как шиблон для других классов
        class UIElement
        {
        protected:
        
            /// @brief Координаты
            KolibriLib::point _coord;

            /// @brief Размер
            KolibriLib::point _size;

            /// @brief Отступы
            unsigned _Margin;

        public:
            UIElement(KolibriLib::point coord = {0,0}, KolibriLib::point size = {16, 16}, unsigned Margin = DefaultMargin)
            {
                _coord = coord;
                _size = size;
                _Margin = Margin;
            }
        };

        //=============================================================================================================================================================

        /// \brief
        /// \param coord
        /// \param size
        /// \param color
        inline void DrawBar(KolibriLib::point coord, KolibriLib::point size, ksys_color_t color = OS::sys_color_table.work_graph)
        {
            _ksys_draw_bar(coord.x * KolibriLib::AAANUMBER, coord.y * KolibriLib::AAANUMBER, size.x, size.y, color);
        }

        namespace text
        {
            /// \brief Получить размер текста
            /// \return текущая высота текста
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

            /// \brief Изменить размер текста
            /// \param newSize высота текста в px
            void SetTextSize(unsigned int newSize)
            {
                asm_inline(
                    "int $0x40" ::"a"(48), "b"(12), "c"(newSize)
                );
            }


            /// \brief Вывести текст
            /// \param text текст
            /// \param coord координаты
            /// \param color цвет текста
            inline void DrawText(std::string text, KolibriLib::point coord, unsigned size = 9, ksys_color_t color = OS::sys_color_table.work_text)
            {
                SetTextSize(size);
                _ksys_draw_text(text.c_str(), coord.x, coord.y, text.length(), color);
            }

            /// \brief Вывести текст
            /// \param text текст
            /// \param coord координаты
            /// \param color цвет текста
            inline void DrawText(const char *text, KolibriLib::point coord, unsigned size = 9, ksys_color_t color = OS::sys_color_table.work_text)
            {
                SetTextSize(size);
                _ksys_draw_text(text, coord.x, coord.y, strlen(text), color);
            }

            

            /// @brief Класс для работы с текстом
            class TextLabel: public UIElement
            {
            private:
                /// @brief Сам текст
                std::string _text;

                /// @brief Размер текста(высота)
                unsigned _FontSize;

                /// @brief Подстраивать @link _FontSize, чтобы размер текст соответствовал размеру элемента( @link _size)
                bool _TextScale;
            public:
                /// @brief Конструктор
                /// @param coord координата
                /// @param size Рамер элемента, игнорируется если TextScale = false
                /// @param text Текст текста
                /// @param FontSize Размер текста
                /// @param TextScale Маштабировать текст, чтобы он не выходил за границы элемента
                /// @param Margin не нужный параметр, необходим для конструктора класса @link UIElement
                TextLabel(point coord = {0, 0}, point size = {0, 0}, std::string text = "Text", unsigned FontSize = 9, bool TextScale = true, unsigned Margin = 0);
                ~TextLabel();

                /// @brief Отрисовать текст
                void render();

                /// @brief Получить текст
                /// @return @link _text
                std::string GetText();

                /// @brief Получить Размер шрифта
                /// @return @link _FontSize
                unsigned GetFontSize();
            };

            TextLabel::TextLabel(point coord, point size, std::string text, unsigned FontSize, bool TextScale, unsigned Margin) : UIElement(coord, size, Margin)
            {
                _text       = text;
                _FontSize   = FontSize;
                _TextScale  = TextScale;
            }
            
            TextLabel::~TextLabel()
            {
                
            }
            
            void TextLabel::render()
            {
                if(_TextScale)
                {
                    _FontSize = _size.x / _text.length();
                }
                SetTextSize(_FontSize);
                DrawText(_text, _coord);
            }

            std::string TextLabel::GetText()
            {
                return _text;
            }
            unsigned TextLabel::GetFontSize()
            {
                return _FontSize;
            }
        }

        //=============================================================================================================================================================

        // Работа с кнопками
        namespace buttons
        {
            // Коды кнопок начинаются с этого числа
            const unsigned StartButtonId = 100;

            /// @brief Служебная структура, нигде не использется кроме @link ButtonsIdList
            struct ButtonsIdData
            {
                unsigned data;
                bool use = false;
            };

            /// @brief Список idшников кнопок
            std::vector<ButtonsIdData> ButtonsIdList;

            /// \brief Получить свободный номер id кнопки из списка
            /// \paragraph Эта функция может выполнятся очень долго, если вы уже создали довольно много кнопок. Это становится действительно важно когда у вас объявленно более 2000 кнопок
            /// \return номер кнопки из списка @link ButtonsIdList
            unsigned GetFreeButtonId()
            {
                for (unsigned i = 0; i < ButtonsIdList.size(); i++)         // Проходим по всему массиву
                {                                                           // Если встречается свободный элемент,
                    if (!ButtonsIdList[i].use)                              // То используем его
                    {                                                       // Иначе создаём новый и использем тоже новый
                        ButtonsIdList[i].use = true;
                        return i;

                    }
                }
                ButtonsIdData a;
                a.data  = StartButtonId + ButtonsIdList.size();
                a.use   = true;
                ButtonsIdList.push_back(a);
                return ButtonsIdList.size() - 1; //-1 потому что обращение к элементам массива идёт с 0
            }

            /// \brief Освободить номер кнопки
            /// \param id номер номер кнопки из списка @link ButtonsIdList
            void FreeButtonId(unsigned id)
            {
                ButtonsIdList[id].use = false; // Этот элемент теперь не используется
            }

            /// \brief Получить id кнопки
            /// \param id номер кнопки
            /// @paragraph id кнопки выдаваемый системой
            /// \return ButtonsIdList[id].ID
            unsigned GetButtonId(unsigned id)
            {
                return ButtonsIdList[id].data;
            }

            /// \brief Создать кнопку, автоматически присвоить ей id
            /// \param coords координаты
            /// \param size размер
            /// \param color цвет
            /// \return id созданной кнопки
            inline unsigned autoDefineButton(point coords, point size, ksys_color_t color = OS::sys_color_table.work_button)
            {
                unsigned id = GetButtonId(GetFreeButtonId()); // Автоматически получаем id для кнопки
                _ksys_define_button(coords.x, coords.y, size.x, size.y, id, color);
                return id;
            }

            /// \brief Создать кнопку, вручную
            /// \param coords координаты
            /// \param size размер
            /// \param id idшник кнопки
            /// \param color цвет
            inline void DefineButton(point coord, point size, unsigned id, ksys_color_t color = OS::sys_color_table.work_button)
            {
                _ksys_define_button(coord.x, coord.y, size.x, size.y, id, color);
            }

            /// \brief Удалить кнопу
            /// \param id id удаляемой кнопки
            inline void DeleteButton(unsigned id)
            {
                _ksys_delete_button(id);
                FreeButtonId(id); // Кнопка удалена, теперь этот id не использется
            }

            /// \brief проверить какая кнопка нажата
            /// \return id нажатой кнопки
            inline unsigned GetPressedButton()
            {
                return _ksys_get_button();
            }

            

            /// \brief Класс для работы с кнопками
            class Button : public UIElement
            {
            private:
                /// @brief текст кноки
                std::string _text;

                /// @brief Цвет кноки
                ksys_color_t _BackgroundColor;

                /// @brief Цвет текста кнопки
                ksys_color_t _TextColor;

                /// @brief Номер id кнопки в списке idшников
                unsigned _id;

                /// @brief Состояние кнопки(Нажата/Ненажата)
                bool _status;

                /// @brief Активна(работает) ли сейчас кнопка
                /// @paragraph Занчение необходимо для того чтобы функция render не пыталась создать кнопку, так как в неактивном состоянии #_id освобождается и его может занять другая кнопка
                bool _active;
            public:
                /// \brief Это конструктор
                /// \param coord координата
                /// \param size размер
                /// \param text текст
                /// \param Margin отступы текста от границ
                /// \param BackgroundColor цвет кнопки
                /// \param TextColor цвет текста
                Button(point coord = {0, 0}, point size = {20, 20}, std::string text = "Button", unsigned Margin = DefaultMargin, ksys_color_t BackgroundColor = OS::sys_color_table.work_button, ksys_color_t TextColor = OS::sys_color_table.work_text);

                /// \brief инициализировать параметры
                /// \param coord координата
                /// \param size размер
                /// \param text текст
                /// \param Margin отступы текста от границ
                /// \param BackgroundColor цвет кнопки
                /// \param TextColor цвет текста
                void init(point coord, point size, std::string text, unsigned Margin = DefaultMargin, ksys_color_t BackgroundColor = OS::sys_color_table.work_button, ksys_color_t TextColor = OS::sys_color_table.work_text);

                /// \brief Отрисовать кнопку
                void render();

                /// \brief Обработчик кнопки
                /// \return Состояние кнопки(Нажата/Ненажата)
                /// @paragraph устанавливает переменную #_status в true если эта кнопка нажата, иначе false
                bool Handler();

                /// \brief Получить сосояние кнопки на момент последней обработки
                /// \return @link _status
                bool GetStatus();

                /// \brief Получить номер кнопки
                /// \return @link _id
                unsigned GetId();

                /// @brief Деактивировать кнопку
                /// @paragraph Эта функция устанавливает переменную @link _active в false
                /// @paragraph В Деактивированном состоянии кнопка "Не нажимается", а её @link _id становится не действительным
                void Deactivate();

                /// @brief Активировать кнопку
                /// @paragraph Противоположна функции @link Deactivate, возвращает кнопку в рабочее состояние 
                void Activate();

                ~Button();
            };

            Button::Button(point coord, point size, std::string text, unsigned Margin, ksys_color_t BackgroundColor, ksys_color_t TextColor) : UIElement(coord, size, Margin)
            {
                init(coord, size, text, Margin, BackgroundColor, TextColor);
            }

            void Button::Deactivate()
            {
                if(_active)
                {
                    DeleteButton(_id);
                    _active = false;
                }
            }

            inline void Button::Activate()
            {
                if(!_active)
                {
                    _id = GetFreeButtonId();
                    _active = true;
                }
            }

            Button::~Button()
            {
                DeleteButton(_id);
            }

            void Button::render()
            {
                if(_active)
                {
                    DefineButton(_coord, _size, GetButtonId(_id), _BackgroundColor);
                }
                else
                {
                    graphic::DrawRectangleLines(_coord, {_coord.x + _size.x, _coord.y + _size.y});
                }
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
                _text = text;
                _BackgroundColor = BackgroundColor;
                _TextColor = TextColor;
                if (!_active)                   //Если кнопка была неактивна, то нужно её активировать
                {
                    Activate();
                }
                else
                {
                    _id = GetFreeButtonId();
                }
                
                render();
            }

            unsigned Button::GetId()
            {
                return _id;
            }


        }

        //=============================================================================================================================================================

        /// \brief Форма для ввода текста
        class Form : public UIElement
        {
        private:
            std::string _BackgroundText;

            /// @brief Введённый пользователем текст
            std::string _inputText;

            /// @brief Цвет рамки формы
            ksys_color_t _FormColor;
            ksys_color_t _BackgroundTextColor;
            KolibriLib::UI::buttons::Button _butt;
            bool _active;

        public:
            /// \brief конструктор
            /// \param coord позиция в коне
            /// \param size размеры
            /// \param BackgroundText фоновый текст(проподает когда вводится текст)
            /// \param FormColor цвет рамки формы
            /// \param BackgroundTextColor цвет фонового текста
            /// \param Margin отступы рамки от текста
            Form(point coord = {0,0}, KolibriLib::point size = {32, 16}, std::string BackgroundText = " ", ksys_color_t FormColor = OS::sys_color_table.work_text, ksys_color_t BackgroundTextColor = OS::sys_color_table.work_button_text, unsigned Margin = DefaultMargin);

            /// \brief Отрисовать форму
            void render();
            /// \brief Обработчик
            void Handler();

            /// \brief Получить введённый текст
            /// \return @link _inputText (текст который ввели в форму)
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
        }

        std::string Form::GetInput()
        {
            return _inputText;
        }

        void Form::Handler()
        {

            if (_butt.Handler())
            {
                _active = true;
            }
            else
            {
                _active = false;
            }
        }
    }
}

#endif // __UI_H__