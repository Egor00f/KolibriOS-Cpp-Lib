#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <map>
#include <string>

#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/UI/text/textlabel.hpp>
#include <kolibriLib/color.hpp>

#include "buttonsBase.hpp"

namespace KolibriLib
{
    namespace UI
    {
        /// @brief Работа с кнопками
        namespace buttons
        {
            

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
                /// @details Занчение необходимо для того чтобы функция render не пыталась создать кнопку, так как в неактивном состоянии #_id освобождается и его может занять другая кнопка
                bool _active = true;

            public:

                std::string ClassName = "Button";
                bool RenderOnEverythingRedraw = true;

                /// \brief Это конструктор
                /// \param coord координата
                /// \param size размер
                /// \param text текст
                /// \param Margin отступы текста от границ
                /// \param ButtonColor цвет кнопки
                /// \param TextColor цвет текста
                Button(const UDim &coord = point(0), const UDim &size = DefaultSize, unsigned Margin = UI::DefaultMargin, const Colors::Color &ButtonColor = OS::GetSystemColors().btn_face);

                /// \brief Это конструктор
                /// \param coord координата
                /// \param size размер
                /// \param text текст
                /// \param Margin отступы текста от границ
                /// \param ButtonColor цвет кнопки
                /// \param TextColor цвет текста
                Button(const Txt &text, const UDim &coord = point(0), const UDim &size = DefaultSize, unsigned Margin = UI::DefaultMargin, const Colors::Color &ButtonColor = OS::GetSystemColors().btn_face);

                /// @brief Конструктор копирования
                /// @param copy Кнопка которую будут копировать
                Button(const Button &copy);

                /// @brief Отрисовать кнопку
                void Render() const;

                /// @brief Обработчик кнопки
                /// @return Состояние кнопки(Нажата/Ненажата)
                /// @details устанавливает переменную _status в true если эта кнопка нажата, иначе false
                /// @note Эту функцию нужно вызывать в цикле, чтобы кнопка работала
                int Handler();

                /// @brief Получить сосояние кнопки на момент последней обработки
                /// @return _status
                bool GetStatus() const;

                /// @brief Получить номер кнопки
                /// @return @link _id
                ButtonID GetId() const;

                /// @brief Деактивировать кнопку
                /// @details Эта функция устанавливает переменную _active в false
                /// @details В Деактивированном состоянии кнопка "Не нажимается", а её _id становится не действительным
                void Deactivate();

                /// @brief Активировать кнопку
                /// @details Противоположна функции Deactivate, возвращает кнопку в рабочее состояние
                void Activate();

                /// @brief Декструктор
                ~Button();

                Button &operator=(const Button &element);

                bool operator ==(const Button& element) const;
            };

           

        } // namespace buttons

        
    } // namespace UI
    
} // namespace KolibriLib


#endif // __BUTTON_H__