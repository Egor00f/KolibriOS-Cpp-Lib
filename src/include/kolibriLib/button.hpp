#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <vector>
#include <string>

#include "UI.hpp"
#include "text.hpp"
#include "image.hpp"
#include "color.hpp"

namespace KolibriLib
{
    namespace UI
    {
        /// @brief Работа с кнопками
        namespace buttons
        {
            typedef unsigned int ButtonID;

            // Коды кнопок начинаются с этого числа
            const ButtonID StartButtonId = 100;

            /// @brief Список idшников кнопок
            std::vector<bool> ButtonsIdList;

            /// \brief Получить свободный номер id кнопки из списка
            /// \paragraph Эта функция может выполнятся очень долго, если вы уже создали довольно много кнопок. Это становится действительно важно когда у вас объявленно более 2000 кнопок
            /// \return номер кнопки из списка @link ButtonsIdList
            unsigned GetFreeButtonId();

            /// \brief Освободить номер кнопки
            /// \param id номер номер кнопки из списка @link ButtonsIdList
            inline void FreeButtonId(unsigned id);

            /// \brief Получить id кнопки
            /// \param id номер кнопки
            /// @paragraph id кнопки выдаваемый системой
            /// \return ButtonsIdList[id].ID
            inline ButtonID GetButtonId(unsigned id);

            /// @brief Обрезать список @link ButtonsIdList
            void CutList();

            /// \brief Создать кнопку, автоматически присвоить ей id
            /// \param coords координаты
            /// \param size размер
            /// \param color цвет
            /// \return id созданной кнопки
            inline ButtonID autoDefineButton(const Coord& coords, const Size &size, const Color::Color& color = OS::sys_color_table.work_button);

            /// \brief Создать кнопку, вручную
            /// \param coords координаты
            /// \param size размер
            /// \param id idшник кнопки
            /// \param color цвет
            inline void DefineButton(const Coord &coord, const Size &size, const ButtonID &id, Color::Color color = OS::sys_color_table.work_button);

            /// \brief Удалить кнопу
            /// \param id id удаляемой кнопки
            inline void DeleteButton(unsigned id);

            /// @brief проверить какая кнопка нажата
            /// @return id нажатой кнопки
            inline ButtonID GetPressedButton();

            //=============================================================================================================================================================
            

            /// \brief Класс для работы с кнопками
            class Button : public UIElement
            {
            private:
                Images::Image _img;
                text::TextLabel _text;

                /// @brief Id кнопки
                ButtonID _id;

                unsigned _type;

                /// @brief Состояние кнопки(Нажата/Ненажата)
                bool _status;

                /// @brief Активна(работает) ли сейчас кнопка
                /// @paragraph Занчение необходимо для того чтобы функция render не пыталась создать кнопку, так как в неактивном состоянии #_id освобождается и его может занять другая кнопка
                bool _active;

            public:
                enum Type
                {
                    Image = 0,
                    Text
                };

                /// \brief Это конструктор
                /// \param coord координата
                /// \param size размер
                /// \param text текст
                /// \param Margin отступы текста от границ
                /// \param ButtonColor цвет кнопки
                /// \param TextColor цвет текста
                Button(const Coord &coord = {0, 0}, const Size &size = {20, 20}, unsigned Margin = UI::DefaultMargin, Color::Color ButtonColor = OS::sys_color_table.work_button);

                /// \brief инициализировать параметры
                /// \param coord координата
                /// \param size размер
                /// \param text текст
                /// \param Margin отступы текста от границ
                /// \param BackgroundColor цвет кнопки
                /// \param TextColor цвет текста
                void init(const Coord &coord = {0, 0}, const Size &size = {0, 0}, const std::string &text = "button", const unsigned &Margin = UI::DefaultMargin, const Color::Color &ButtonColor = OS::sys_color_table.work_button);

                /// \brief инициализировать параметры
                /// \param coord координата
                /// \param size размер
                /// \param image Изображение
                /// \param Margin отступы текста от границ
                /// \param BackgroundColor цвет кнопки
                /// \param TextColor цвет текста
                void init(const Coord &coord = {0, 0}, const Size &size = {0, 0}, const Images::Image &image = Images::Image(), const unsigned &Margin = DefaultMargin, const Color::Color &ButtonColor = OS::sys_color_table.work_button);

                /// \brief инициализировать параметры 
                /// \param coord координата
                /// \param size размер
                /// \param Path Путь до изображения
                /// \param Margin отступы текста от границ
                /// \param BackgroundColor цвет кнопки
                /// \param TextColor цвет текста
                void init(const Coord &coord = {0, 0}, const Size &size = {0, 0}, std::string Path = DefaultImage);

                /// @brief Отрисовать кнопку
                void Render();

                /// \brief Обработчик кнопки
                /// \return Состояние кнопки(Нажата/Ненажата)
                /// @paragraph устанавливает переменную @link _status в true если эта кнопка нажата, иначе false
                /// @paragraph Эту функцию нужно вызывать в цикле, чтобы кнопка работала
                bool Handler();

                /// \brief Получить сосояние кнопки на момент последней обработки
                /// \return @link _status
                bool GetStatus() const;

                /// \brief Получить номер кнопки
                /// \return @link _id
                ButtonID GetId() const;

                /// @brief Деактивировать кнопку
                /// @paragraph Эта функция устанавливает переменную @link _active в false
                /// @paragraph В Деактивированном состоянии кнопка "Не нажимается", а её @link _id становится не действительным
                void Deactivate();

                /// @brief Активировать кнопку
                /// @paragraph Противоположна функции @link Deactivate, возвращает кнопку в рабочее состояние
                void Activate();

                /// @brief Возвращает тип данных используемых в кнопке @link _type
                /// @return Функция возвращает @link ContentType :: <Тип Данных>
                unsigned GetType() const;

                /// @brief Возвращает текст кнопки
                /// @return std::string
                std::string GetTextLabel() const;

                /// @brief Получить изображение кнопки
                /// @return
                Images::Image GetImage() const;

                /// @brief Изменить текст кнопки
                /// @param Новый текст кнопки
                void SetText(std::string NewText);

                /// @brief Декструктор
                ~Button();

                Button &operator=(const Button &element)
                {
                    _coord      = element._coord;
                    _size       = element._size;
                    _MainColor  = element._MainColor;
                    _Margin     = element._Margin;
                    _id         = element._id;
                    _type       = element._type;
                    _active     = element._active;

                    switch (element._type)
                    {
                    case Type::Text:
                        _text = element._text;
                        break;
                    case Type::Image:
                        _img = element._img;
                        break;
                    default:
                        break;
                    }
                    return *this;
                }

                
            };
        } // namespace buttons
        unsigned buttons::GetFreeButtonId()
        {
            for (unsigned i = 0; i < ButtonsIdList.size(); i++) // Проходим по всему массиву
            {                                                   // Если встречается свободный элемент,
                if (!ButtonsIdList[i])                          // То используем его
                {                                               // Иначе создаём новый и использем тоже новый
                    ButtonsIdList[i] = true;
                    return i;
                }
            }

            ButtonsIdList.push_back(true);
            return ButtonsIdList.size() - 1; //-1 потому что обращение к элементам массива идёт с 0
        }

        void buttons::FreeButtonId(unsigned id)
        {
            ButtonsIdList[id] = false; // Этот элемент теперь не используется
        }

        buttons::ButtonID buttons::GetButtonId(unsigned id)
        {
            return StartButtonId + id;
        }

        void buttons::CutList()
        {
            unsigned a = ButtonsIdList.size();
            for (unsigned i = a; i < 0; i++)
            {
                if (ButtonsIdList[i])
                {
                    a = i;
                }
                else
                {
                    break;
                }
            }
            ButtonsIdList.erase(ButtonsIdList.begin() + a, ButtonsIdList.end());
        }

        buttons::ButtonID buttons::autoDefineButton(const Coord &coords, const Size &size, const Color::Color &color)
        {
            unsigned id = GetButtonId(GetFreeButtonId()); // Автоматически получаем id для кнопки
            _ksys_define_button(coords.x, coords.y, size.x, size.y, id, color.val);
            return id;
        }

        void buttons::DefineButton(const Coord &coord, const Size &size, const ButtonID &id, Color::Color color)
        {
            _ksys_define_button(coord.x, coord.y, size.x, size.y, id, color.val);
        }

        void buttons::DeleteButton(unsigned id)
        {
            _ksys_delete_button(id);
            FreeButtonId(id); // Кнопка удалена, теперь этот id не использется
        }

        buttons::ButtonID buttons::GetPressedButton()
        {
            return _ksys_get_button();
        }

        buttons::Button::Button(const Coord &coord, const Size &size, unsigned Margin, Color::Color ButtonColor) : UIElement(coord, size, ButtonColor, Margin)
        {
            _id = GetButtonId(GetFreeButtonId());
            _img.SetCoord(coord);
            _img.SetSize(size);
            _text.SetCoord(coord);
            _text.SetSize(size);
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
                _id = GetButtonId(GetFreeButtonId());
                _active = true;
            }
        }

        unsigned buttons::Button::GetType() const
        {
            return _type;
        }

        std::string buttons::Button::GetTextLabel() const
        {
            if (_type == Type::Text)
            {
                return _text.GetText();
            }
        }

        Images::Image buttons::Button::GetImage() const
        {
            return _img;
        }

        void buttons::Button::SetText(std::string NewText)
        {
            if (_type == Type::Text)
            {
                return _text.SetText(NewText);
            }
        }

        buttons::Button::~Button()
        {
            DeleteButton(_id);
        }

        bool buttons::Button::Handler()
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

        bool buttons::Button::GetStatus() const
        {
            return _status;
        }

        void buttons::Button::init(const Coord &coord, const Size &size, const std::string &text, const unsigned &Margin, const Color::Color &ButtonColor)
        {
            _coord = coord;
            _size = size;
            _Margin = Margin;

            _text.SetText(text);
            _type = Type::Text;

            _text.SetCoord(coord);
            _text.SetSize(size);
            _text.SetScale(true);

            _MainColor = ButtonColor;

            if (!_active) // Если кнопка была неактивна, то нужно её активировать
            {
                Activate();
            }
        }

        void buttons::Button::init(const Coord &coord, const Size &size, const Images::Image &image, const unsigned &Margin, const Color::Color &ButtonColor)
        {
            _coord = coord;
            _size = size;
            _Margin = Margin;

            _img = image;
            _type = Type::Image;
            _img.SetCoord(coord);
            _img.SetSize(size);

            _MainColor = ButtonColor;

            if (!_active) // Если кнопка была неактивна, то нужно её активировать
            {
                Activate();
            }
        }

        void buttons::Button::init(const Coord &coord, const Size &size, std::string Path)
        {
            _coord = coord;
            _size = size;

            _img.LoadImage(Path);
            _type = Type::Image;
            _img.SetCoord(coord);
            _img.SetSize(size);

            if (!_active) // Если кнопка была неактивна, то нужно её активировать
            {
                Activate();
            }
        }

        void buttons::Button::Render()
        {
            if (_active)
            {
                DefineButton(_coord, _size, _id, _MainColor);

                switch (_type)
                {
                case Type::Image:
                    _img.Render();
                    break;
                case Type::Text:
                    _text.Render();
                    break;
                default:
                    break;
                }
            }
        }

        buttons::ButtonID buttons::Button::GetId() const
        {
            return _id;
        }
    } // namespace UI
    
} // namespace KolibriLib


#endif // __BUTTON_H__