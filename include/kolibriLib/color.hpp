#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <include_ksys.h>
#include <kolibriLib/debug.hpp>

namespace KolibriLib
{
    /// @brief Набор функций для работы с цветом
    namespace Colors
    {        

        struct rgb: public rgb_t
        {
            rgb(rgb_t val);

            rgb(ksys_color_t val);

            rgb(std::uint8_t r, std::uint8_t g, std::uint8_t b);

            rgb() = default;
            rgb(const rgb&) = default;

            rgb& operator=(const rgb&) = default;

            operator ksys_color_t() const;

            std::uint32_t BBGGRR() const;

            std::uint32_t BBGGRR00() const;
        };

        /// @brief Цвет
        union Color
        {
            Color():val(0xFFFFFFFF){};

            /// @brief Конструктор
            /// @param a 
            Color(const ksys_color_t& a);
            //Color(const Color *a);
            Color(const Color &a) = default;
            Color(const rgb_t &color);

            /// @brief Конструктор
            /// @param R Красная состовляющаяя цвета
            /// @param G Красная состовляющаяя цвета
            /// @param B Красная состовляющаяя цвета
            /// @param A Прозрачность
            Color(std::uint8_t R, std::uint8_t G, std::uint8_t B, std::uint8_t A = 0xFF);

            operator rgb_t() const;
            operator ksys_color_t() const;
            operator rgb() const;

            /// @brief Получить rgb_t
            /// @return 
            rgb_t GetRGB() const;

            Color& operator = (const Color& a) = default;

            Color& operator = (const std::uint32_t& color);

            /// @brief Смешивает два цвета (среднее занчение)
            /// @param a второй цвет
            /// @return 
            Color &operator + (const Color &a);

            bool operator == (const Color& a) const;

            bool operator != (const Color& a) const;


            ksys_color_t val;

            struct
            {
                std::uint8_t blue;
                std::uint8_t green;
                std::uint8_t red;

                /// @brief Альфа канал
                std::uint8_t _a;
            };
        };

        /// @brief Конвертирует rgb_t в ksys_color_t
        /// @param color 
        /// @return 
        ksys_color_t RGBtoINT(const rgb_t &color);
        
        /// @brief 
        /// @param color 
        /// @return 
        rgb_t UINT32toRGB(const std::uint32_t &color);

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