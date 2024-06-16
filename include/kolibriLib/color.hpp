#ifndef __COLOR_H__
#define __COLOR_H__

#include <sys/ksys.h>

namespace KolibriLib
{
    /// @brief Набор функций для работы с цветом
    namespace Colors
    {        
        /// @brief Цвет
        union Color
        {
            ksys_color_t val;
            struct
            {
                /// @brief Альфа канал
                uint8_t _a;
                uint8_t blue;
                uint8_t green;
                uint8_t red;
            };

            Color():val(0xFFFFFFFF){};

            /// @brief Конструктор
            /// @param a 
            Color(const ksys_color_t& a);
            Color(const Color *a);
            Color(const Color &a);
            Color(const rgb_t &color);

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
        struct ColorsTable
        {
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
            Color win_text;
            Color panel_frame;
            Color win_face;
            Color win_inface;
            Color win_frame;
            Color win_inframe;
            Color win_border;
            Color win_inborder;
            Color win_graytext;
            Color menu_frame;
            Color menu_text;
            Color panel_body;
            Color panel_text;
            Color hint_frame;
            Color hint_body;
            Color hint_text;
            Color btn_inface;
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

            // ksys_color_t frame_area;
            // ksys_color_t grab_bar;
            // ksys_color_t grab_bar_button;
            // ksys_color_t grab_button_text;
            // ksys_color_t grab_text;
            // ksys_color_t work_area;
            // ksys_color_t work_button;
            // ksys_color_t work_button_text;
            // ksys_color_t work_text;
            // ksys_color_t work_graph;


            ColorsTable(const ColorsTable &table);
            ColorsTable(const ksys_colors_table_t &table);
        };
    }
} // namespace KolibriLib


#endif // __COLOR_H__