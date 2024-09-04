#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <sys/ksys.h>
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
        struct ColorsTable : ksys_colors_table_t
        {
            /*
            /// @brief цвет фона системного меню
            Color menu_body;

            /// @brief цвет фона для придания 3D эффекта
            Color face_3d;

            /// @brief цвет темной обводки для придания 3D эффекта
            Color dark_3d;

            /// @brief цвет светлой обводки для придания 3D эффекта
            Color light_3d;

            /// @brief цвет текста в заголовке окна приложения
            Color win_title;

            /// @brief цвет фона окна
            Color win_body;

            /// @brief цвет активной кнопки
            Color btn_face;

            /// @brief цвет текста активной кнопки
            Color btn_text;

            /// @brief цвет текста в рабочей области окна
            Color win_text;

            /// @brief цвет рамки области панели
            Color panel_frame;

            /// @brief цвет бордюра окна между внешней и внутренней рамкой
            Color win_face;

            /// @brief цвет внешней рамки "неактивного" окна
            Color win_inface;

            /// @brief цвет внешней рамки окна
            Color win_frame;

            /// @brief цвет внешней рамки "неактивного" окна
            Color win_inframe;

            /// @brief цвет внутренней рамки окна
            Color win_border;

            /// @brief цвет внутренней рамки "неактивного" окна
            Color win_inborder;

            /// @brief цвет в оттенках серого в рабочей области окна.
            Color win_graytext;

            /// @brief цвет рамки системного меню
            Color menu_frame;

            /// @brief цвет текста системного меню
            Color menu_text;

            /// @brief цвет фона области панели
            Color panel_body;

            /// @brief цвет текста области панели
            Color panel_text;

            /// @brief цвет рамки всплывающей подсказки
            Color hint_frame;

            /// @brief цвет фона всплывающей подсказки
            Color hint_body;

            /// @brief цвет текста всплывающей подсказки
            Color hint_text;

            /// @brief цвет фона "неактивной" кнопки
            Color btn_inface;

            /// @brief цвет фона кнопки при наведении курсора (focus)
            Color btn_fcface;
            Color btn_frame;
            Color btn_inframe;
            Color btn_fcframe;
            Color btn_intext;
            Color btn_fctex;
            Color gui_shadow;
            Color gui_face;
            Color gui_inface;
            Color gui_fcface;
            Color gui_frame;
            Color gui_inframe;
            Color gui_fcframe;
            Color gui_text;
            Color gui_intex;
            Color gui_fctext;
            Color gui_select;
            
            unsigned int reserved_a;
            unsigned int reserved_b;
            unsigned int reserved_c;
            unsigned int reserved_d;
            unsigned int reserved_e;
            unsigned int reserved_f;

            

            ColorsTable(const ColorsTable &table);
            ColorsTable(const ksys_colors_table_t &table);

            */
        };
    }

    void PrintDebug(Colors::Color out);


    void PrintDebug(Colors::ColorsTable out);
    
} // namespace KolibriLib


#endif // __COLOR_H__