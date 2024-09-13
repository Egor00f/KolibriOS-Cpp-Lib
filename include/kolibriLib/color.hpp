#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <include_ksys.h>
#include <kolibriLib/debug.hpp>

namespace KolibriLib
{
    /// @brief Набор функций для работы с цветом
    namespace Colors
    {        
        /// @brief Цвет
        union Color
        {
            Color():val(0xFFFFFFFF){};

            /// @brief Конструктор
            /// @param a 
            Color(const ksys_color_t& a);
            //Color(const Color *a);
            Color(const Color &a);
            Color(const rgb_t &color);

            /// @brief Конструктор
            /// @param R Красная состовляющаяя цвета
            /// @param G Красная состовляющаяя цвета
            /// @param B Красная состовляющаяя цвета
            /// @param A Прозрачность
            Color(uint8_t R, uint8_t G, uint8_t B, uint8_t A = 0xFF);

            operator rgb_t() const;
            operator ksys_color_t() const;

            /// @brief Получить rgb_t
            /// @return 
            rgb_t GetRGB() const;

            Color& operator = (const Color& a);

            Color& operator = (const uint32_t& color);

            /// @brief Смешивает два цвета (среднее занчение)
            /// @param a второй цвет
            /// @return 
            Color &operator + (const Color &a);

            bool operator == (const Color& a) const;

            bool operator != (const Color& a) const;


            ksys_color_t val;

            struct
            {
                uint8_t blue;
                uint8_t green;
                uint8_t red;

                /// @brief Альфа канал
                uint8_t _a;
            };
        };

        /// @brief Конвертирует rgb_t в ksys_color_t
        /// @param color 
        /// @return 
        ksys_color_t RGBtoINT(const rgb_t &color);
        
        /// @brief 
        /// @param color 
        /// @return 
        rgb_t UINT32toRGB(const uint32_t &color);

        /// @brief Смешать два цвета
        /// @param a Первый цвет
        /// @param b Второй цвет
        /// @param k Коофициент, чем он больше, тем больше цвета a, чем меньше, тем больше цвета b
        /// @return получившийся в итоге цвет
        Color BlendColors(const Color &a, const Color &b, float k = 0.5f);

        /// @brief Таблица цветов по умолчанию
        const ksys_colors_table_t DefaultColorTable = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        /// @brief Таблица системных цветов
        using ColorsTable = ksys_colors_table_t;
    }

    void PrintDebug(Colors::Color out);


    void PrintDebug(Colors::ColorsTable out);
    
} // namespace KolibriLib


#endif // __COLOR_H__