#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <unordered_map>
#include <string>

#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/UI/text.hpp>
#include <kolibriLib/UI/image.hpp>
#include <kolibriLib/color.hpp>

namespace KolibriLib
{
    namespace UI
    {
        /// @brief Работа с кнопками
        namespace buttons
        {
            /// @brief Id кнопки
            typedef unsigned int ButtonID;

            // Коды кнопок начинаются с этого числа
            const ButtonID StartButtonId = 100;

            /// @brief Список idшников кнопок
            std::unordered_map<ButtonID, bool> ButtonsIdList;    // "Я надею что это был великий сарказм"
                                                //      

            /// \brief Получить свободный номер id кнопки из списка
            /// \paragraph Эта функция может выполнятся очень долго, если вы уже создали довольно много кнопок. Это становится действительно важно когда у вас объявленно более 2000 кнопок
            /// \return номер кнопки из списка @link ButtonsIdList
            ButtonID GetFreeButtonId()
            {
                for (unsigned i = 0; i < ButtonsIdList.size(); i++)
                {
                    if (ButtonsIdList.count(i) == 0)
                    {
                        return i + StartButtonId;
                    }
                }
            }

            /// \brief Освободить номер кнопки
            /// \param id номер номер кнопки из списка @link ButtonsIdList
            inline void FreeButtonId(ButtonID id)
            {
                ButtonsIdList.erase(id);
            }

            /// \brief Создать кнопку, автоматически присвоить ей id
            /// \param coords координаты
            /// \param size размер
            /// \param color цвет
            /// \return id созданной кнопки
            inline ButtonID autoDefineButton(const Coord &coords, const Size &size, const Colors::Color &color = OS::sys_color_table.work_button)
            {
                ButtonID id = GetFreeButtonId(); // Автоматически получаем id для кнопки
                _ksys_define_button(coords.x, coords.y, size.x, size.y, id, color.val);
                return id;
            }

            /// \brief Создать кнопку, вручную
            /// \param coords координаты
            /// \param size размер
            /// \param id idшник кнопки
            /// \param color цвет
            inline void DefineButton(const Coord &coord, const Size &size, const ButtonID &id, Colors::Color color = OS::sys_color_table.work_button)
            {
                _ksys_define_button(coord.x, coord.y, size.x, size.y, id, color.val);
            }

            /// \brief Удалить кнопу
            /// \param id id удаляемой кнопки
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

            //=============================================================================================================================================================
            

            /// \brief Класс для работы с кнопками
            class Button: public text::TextLabel
            {
            private:

                /// @brief Id кнопки
                ButtonID _id;

                /// @brief Состояние кнопки(Нажата/Ненажата)
                mutable bool _status;

                /// @brief Активна(работает) ли сейчас кнопка
                /// @paragraph Занчение необходимо для того чтобы функция render не пыталась создать кнопку, так как в неактивном состоянии #_id освобождается и его может занять другая кнопка
                bool _active;

            public:

                /// \brief Это конструктор
                /// \param coord координата
                /// \param size размер
                /// \param text текст
                /// \param Margin отступы текста от границ
                /// \param ButtonColor цвет кнопки
                /// \param TextColor цвет текста
                Button(const Coord &coord = {0, 0}, const Size &size = {20, 20}, unsigned Margin = UI::DefaultMargin, const Colors::Color& ButtonColor = OS::sys_color_table.work_button);
                
                /// @brief Отрисовать кнопку
                void Render() const;

                /// @brief Обработчик кнопки
                /// @return Состояние кнопки(Нажата/Ненажата)
                /// @paragraph устанавливает переменную @link _status в true если эта кнопка нажата, иначе false
                /// @paragraph Эту функцию нужно вызывать в цикле, чтобы кнопка работала
                bool Handler() const;

                /// @brief Получить сосояние кнопки на момент последней обработки
                /// @return @link _status
                bool GetStatus() const;

                /// @brief Получить номер кнопки
                /// @return @link _id
                ButtonID GetId() const;

                /// @brief Деактивировать кнопку
                /// @paragraph Эта функция устанавливает переменную @link _active в false
                /// @paragraph В Деактивированном состоянии кнопка "Не нажимается", а её @link _id становится не действительным
                void Deactivate();

                /// @brief Активировать кнопку
                /// @paragraph Противоположна функции @link Deactivate, возвращает кнопку в рабочее состояние
                void Activate();

                /// @brief Декструктор
                ~Button();

                Button &operator=(const Button &element);

                bool operator ==(const Button& element) const;
            };

        buttons::Button::Button(const Coord &coord, const Size &size, unsigned Margin, const Colors::Color &ButtonColor) : TextLabel(coord, size, "Button", 16, true, OS::sys_color_table.work_text, Margin)
        {
            _id = GetFreeButtonId();
        }

        void buttons::Button::Deactivate()
        {
            if (_active)
            {
                DeleteButton(_id);
                _active = false;
            }
        }

        void buttons::Button::Activate()
        {
            if (!_active)
            {
                _id = GetFreeButtonId();
                _active = true;
            }
        }

        buttons::Button::~Button()
        {
            DeleteButton(_id);
        }

        buttons::Button &KolibriLib::UI::buttons::Button::operator=(const buttons::Button &element)
        {
            _coord = element._coord;
            _size = element._size;
            _MainColor = element._MainColor;
            _Margin = element._Margin;
            _id = element._id;
            _active = element._active;
            _data = element._data;

            return *this;
        }

        bool KolibriLib::UI::buttons::Button::operator==(const Button &element) const
        {

            return (_data == element._data) &&
                   (_coord == element._coord) &&
                   (_size == element._size) &&
                   (_angle == element._angle);
        }

        bool buttons::Button::Handler() const
        {
            _status = GetPressedButton() == _id; // Если id нажатой кнопки совпадает к id этой кнопки
            return _status;
        }

        bool buttons::Button::GetStatus() const
        {
            return _status;
        }

        void buttons::Button::Render() const
        {
            if (_active)
            {
                buttons::DefineButton(_coord, _size, _id, _MainColor);

                Print({_coord.x + ((int)_size.x / 2), _coord.y + ((int)_size.y / 2)});
            }
        }

        buttons::ButtonID buttons::Button::GetId() const
        {
            return _id;
        }
        } // namespace buttons

        
    } // namespace UI
    
} // namespace KolibriLib


#endif // __BUTTON_H__