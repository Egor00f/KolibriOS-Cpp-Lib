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
            std::vector<bool> ButtonsIdList;    // "Я надею что это был великий сарказм"
                                                //      

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
            inline ButtonID autoDefineButton(const Coord& coords, const Size &size, const Colors::Color& color = OS::sys_color_table.work_button);

            /// \brief Создать кнопку, вручную
            /// \param coords координаты
            /// \param size размер
            /// \param id idшник кнопки
            /// \param color цвет
            inline void DefineButton(const Coord &coord, const Size &size, const ButtonID &id, Colors::Color color = OS::sys_color_table.work_button);

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
                /// @brief Список типов данных которые можно "запихнуть" в кнопку
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
                Button(const Coord &coord = {0, 0}, const Size &size = {20, 20}, const unsigned& Margin = UI::DefaultMargin, const Colors::Color& ButtonColor = OS::sys_color_table.work_button);

                /// \brief инициализировать параметры
                /// \param coord координата
                /// \param size размер
                /// \param text текст
                /// \param Margin отступы текста от границ
                /// \param BackgroundColor цвет кнопки
                /// \param TextColor цвет текста
                void init(const Coord &coord = {0, 0}, const Size &size = {0, 0}, const std::string &text = "button", const unsigned &Margin = UI::DefaultMargin, const Colors::Color &ButtonColor = OS::sys_color_table.work_button);

                /// \brief инициализировать параметры
                /// \param coord координата
                /// \param size размер
                /// \param image Изображение
                /// \param Margin отступы текста от границ
                /// \param BackgroundColor цвет кнопки
                /// \param TextColor цвет текста
                void init(const Coord &coord = {0, 0}, const Size &size = {0, 0}, const Images::Image &image = Images::Image(), const unsigned &Margin = DefaultMargin, const Colors::Color &ButtonColor = OS::sys_color_table.work_button);

                /// \brief инициализировать параметры 
                /// \param coord координата
                /// \param size размер
                /// \param Path Путь до изображения
                /// \param Margin отступы текста от границ
                /// \param BackgroundColor цвет кнопки
                /// \param TextColor цвет текста
                void init(const Coord &coord = {0, 0}, const Size &size = {0, 0}, std::string Path = DefaultImage);

                /// @brief Отрисовать кнопку
                void Render() const;

                /// @brief Обработчик кнопки
                /// @return Состояние кнопки(Нажата/Ненажата)
                /// @paragraph устанавливает переменную @link _status в true если эта кнопка нажата, иначе false
                /// @paragraph Эту функцию нужно вызывать в цикле, чтобы кнопка работала
                bool Handler();

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

                /// @brief Возвращает тип данных используемых в кнопке @link _type
                /// @return Функция возвращает @link ContentType :: <Тип Данных>
                unsigned GetType() const;

                /// @brief Возвращает текст кнопки
                /// @return Функция возвращает @link _text
                std::string GetTextLabel() const;

                /// @brief Получить изображение кнопки
                /// @return Функция возвращает @link _img
                Images::Image GetImage() const;

                /// @brief Изменить текст кнопки
                /// @param Новый текст кнопки
                void SetText(const std::string& NewText);

                /// @brief Изменить изображение в кнопке
                /// @param NewImg Изображение
                void SetImage(const Images::Image& NewImg);

                /// @brief Декструктор
                ~Button();

                Button &operator=(const Button &element);

                bool operator ==(const Button& element) const;
            };
        } // namespace buttons
    } // namespace UI
    
} // namespace KolibriLib


#endif // __BUTTON_H__