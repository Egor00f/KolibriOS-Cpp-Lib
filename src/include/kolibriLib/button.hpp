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

            /// @brief Служебная структура, нигде не использется кроме @link ButtonsIdList
            struct ButtonsIdData
            {
                bool use = false;
            };

            /// @brief Список idшников кнопок
            std::vector<ButtonsIdData> ButtonsIdList;

            /// \brief Получить свободный номер id кнопки из списка
            /// \paragraph Эта функция может выполнятся очень долго, если вы уже создали довольно много кнопок. Это становится действительно важно когда у вас объявленно более 2000 кнопок
            /// \return номер кнопки из списка @link ButtonsIdList
            unsigned GetFreeButtonId()
            {
                for (unsigned i = 0; i < ButtonsIdList.size(); i++) // Проходим по всему массиву
                {                                                   // Если встречается свободный элемент,
                    if (!ButtonsIdList[i].use)                      // То используем его
                    {                                               // Иначе создаём новый и использем тоже новый
                        ButtonsIdList[i].use = true;
                        return i;
                    }
                }
                ButtonsIdData a;
                a.use = true;
                ButtonsIdList.push_back(a);
                return ButtonsIdList.size() - 1; //-1 потому что обращение к элементам массива идёт с 0
            }

            /// \brief Освободить номер кнопки
            /// \param id номер номер кнопки из списка @link ButtonsIdList
            inline void FreeButtonId(unsigned id)
            {
                ButtonsIdList[id].use = false; // Этот элемент теперь не используется
            }

            /// \brief Получить id кнопки
            /// \param id номер кнопки
            /// @paragraph id кнопки выдаваемый системой
            /// \return ButtonsIdList[id].ID
            inline ButtonID GetButtonId(unsigned id)
            {
                return StartButtonId + id;
            }

            /// \brief Создать кнопку, автоматически присвоить ей id
            /// \param coords координаты
            /// \param size размер
            /// \param color цвет
            /// \return id созданной кнопки
            inline unsigned autoDefineButton(const point<int> coords, const Size &size, ksys_color_t color = OS::sys_color_table.work_button)
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
            inline void DefineButton(const point<int> &coord, const Size &size, const ButtonID &id, ksys_color_t color = OS::sys_color_table.work_button)
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

            /// @brief проверить какая кнопка нажата
            /// @return id нажатой кнопки
            inline unsigned GetPressedButton()
            {
                return _ksys_get_button();
            }

            //=============================================================================================================================================================

            struct Content
            {
                /// @brief Тип данных внутри кнопки
                enum class Type
                {
                    /// @brief Изображение
                    Image,
                    /// @brief Текст
                    Text
                };
                Images::image _img;
                text::TextLabel _text;
                Type _type;

                Content(Type t = Type::Text)
                {
                    _type = t;
                }
                ~Content()
                {
                    switch (_type)
                    {
                    case Type::Text:
                        _text.~TextLabel();
                        break;
                    case Type::Image:
                        _img.~image();
                    default:
                        break;
                    }
                }
            };

            

            /// \brief Класс для работы с кнопками
            class Button : public UIElement
            {
            private:
                Content c;


                /// @brief Id кнопки
                ButtonID _id;

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
                /// \param ButtonColor цвет кнопки
                /// \param TextColor цвет текста
                Button(const Coord &coord = {0, 0}, const Size &size = {20, 20}, unsigned Margin = UI::DefaultMargin, ksys_color_t ButtonColor = OS::sys_color_table.work_button);

                /// \brief инициализировать параметры
                /// \param coord координата
                /// \param size размер
                /// \param Content текст
                /// \param Margin отступы текста от границ
                /// \param BackgroundColor цвет кнопки
                /// \param TextColor цвет текста
                void init(const Coord &coord = {0, 0}, const Size &size = {0, 0}, const std::string &text = "button", const unsigned &Margin = UI::DefaultMargin, const Color::Color &ButtonColor = OS::sys_color_table.work_button);

                /// \brief инициализировать параметры
                /// \param coord координата
                /// \param size размер
                /// \param Content текст
                /// \param Margin отступы текста от границ
                /// \param BackgroundColor цвет кнопки
                /// \param TextColor цвет текста
                void init(const Coord &coord = {0, 0}, const Size &size = {0, 0}, const Images::image &image = Images::image(), const unsigned &Margin = DefaultMargin, const Color::Color &ButtonColor = OS::sys_color_table.work_button);

                /// @brief Отрисовать кнопку
                void Render();

                /// \brief Обработчик кнопки
                /// \return Состояние кнопки(Нажата/Ненажата)
                /// @paragraph устанавливает переменную @link _status в true если эта кнопка нажата, иначе false
                /// @paragraph Эту функцию нужно вызывать в цикле, чтобы кнопка работала
                bool Handler();

                /// \brief Получить сосояние кнопки на момент последней обработки
                /// \return @link _status
                bool GetStatus();

                /// \brief Получить номер кнопки
                /// \return @link _id
                ButtonID GetId();

                /// @brief Деактивировать кнопку
                /// @paragraph Эта функция устанавливает переменную @link _active в false
                /// @paragraph В Деактивированном состоянии кнопка "Не нажимается", а её @link _id становится не действительным
                void Deactivate();

                /// @brief Активировать кнопку
                /// @paragraph Противоположна функции @link Deactivate, возвращает кнопку в рабочее состояние
                void Activate();

                /// @brief Возвращает тип данных используемых в кнопке @link _type
                /// @return Функция возвращает @link ContentType :: <Тип Данных>
                Content::Type GetType();

                /// @brief Возвращает текст кнопки
                /// @return std::string
                std::string GetTextLabel();

                /// @brief Получить изображение кнопки
                /// @return
                Images::image GetImage();

                /// @brief Изменить текст кнопки
                /// @param Новый текст кнопки
                void SetText(std::string NewText);

                /// @brief Декструктор
                ~Button();
            };

            Button::Button(const Coord &coord, const Size &size, unsigned Margin, Color::Color ButtonColor) : UIElement(coord, size, ButtonColor, Margin)
            {
                _id = GetButtonId(GetFreeButtonId());
            }

            void Button::Deactivate()
            {
                if (_active)
                {
                    DeleteButton(_id);
                    _active = false;
                }
            }

            void Button::Activate()
            {
                if (!_active)
                {
                    _id = GetButtonId(GetFreeButtonId());
                    _active = true;
                }
            }

            Content::Type Button::GetType()
            {
                return c._type;
            }

            std::string Button::GetTextLabel()
            {
                if (c._type == Content::Type::Text)
                {
                    return c._text.GetText();
                }
            }

            Images::image Button::GetImage()
            {
                return c._img;
            }

            void Button::SetText(std::string NewText)
            {
                if (c._type == Content::Type::Text)
                {
                    return c._text.SetText(NewText);
                }
            }

            Button::~Button()
            {
                DeleteButton(_id);
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

            void UI::buttons::Button::init(const Coord &coord, const Size &size, const std::string &text, const unsigned &Margin, const Color::Color &ButtonColor)
            {
                _coord = coord;
                _size = size;
                _Margin = Margin;

                c._text.SetText(text);
                c._type = Content::Type::Text;

                c._text.SetCoord(coord);
                c._text.SetSize(size);
                c._text.SetScale(true);

                _MainColor = ButtonColor;

                if (!_active) // Если кнопка была неактивна, то нужно её активировать
                {
                    Activate();
                }
            }

            void UI::buttons::Button::init(const Coord &coord, const Size &size, const Images::image &image, const unsigned &Margin, const Color::Color &ButtonColor)
            {
                _coord = coord;
                _size = size;
                _Margin = Margin;

                c._img = image;
                c._type = Content::Type::Image;

                c._img.SetCoord(coord);
                c._img.SetSize(size);

                _MainColor = ButtonColor;

                if (!_active) // Если кнопка была неактивна, то нужно её активировать
                {
                    Activate();
                }
            }

            void Button::Render()
            {
                if (_active)
                {
                    DefineButton(_coord, _size, _id, _MainColor);

                    switch (c._type)
                    {
                    case Content::Type::Image:
                        c._img.Render();
                        break;
                    case Content::Type::Text:
                        c._text.Render();
                        break;
                    default:
                        break;
                    }
                }
            }

            ButtonID Button::GetId()
            {
                return _id;
            }
        } // namespace buttons
    } // namespace UI
    
} // namespace KolibriLib


#endif // __BUTTON_H__