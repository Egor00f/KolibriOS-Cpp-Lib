#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <map>
#include <string>

#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/UI/text/textlabel.hpp>
#include <kolibriLib/UI/image.hpp>
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
                Button(const Coord &coord = Coord(0,0), const Size &size = Size(20,20), unsigned Margin = UI::DefaultMargin, const Colors::Color& ButtonColor = OS::GetSystemColors().work_button);
                
                /// @brief Отрисовать кнопку
                void Render() const;

                /// @brief Обработчик кнопки
                /// @return Состояние кнопки(Нажата/Ненажата)
                /// @paragraph устанавливает переменную _status в true если эта кнопка нажата, иначе false
                /// @paragraph Эту функцию нужно вызывать в цикле, чтобы кнопка работала
                bool Handler() const;

                /// @brief Получить сосояние кнопки на момент последней обработки
                /// @return @link _status
                bool GetStatus() const;

                /// @brief Получить номер кнопки
                /// @return @link _id
                ButtonID GetId() const;

                /// @brief Деактивировать кнопку
                /// @paragraph Эта функция устанавливает переменную _active в false
                /// @paragraph В Деактивированном состоянии кнопка "Не нажимается", а её _id становится не действительным
                void Deactivate();

                /// @brief Активировать кнопку
                /// @paragraph Противоположна функции Deactivate, возвращает кнопку в рабочее состояние
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