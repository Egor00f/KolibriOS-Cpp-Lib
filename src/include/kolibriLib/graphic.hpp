#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__


#include <sys/ksys.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include <fstream>

#include "base.hpp"
#include "filesystem.hpp"

namespace KolibriLib
{
    // Графика
    namespace graphic
    {
        /// @brief Нарисовать линию
        /// @param a точка первая
        /// @param b точка вторая
        inline void DrawLine(const point& a, const point& b, const ksys_color_t color = OS::sys_color_table.work_graph)
        {
            _ksys_draw_line(a.x, a.y, b.x, b.y, color);
        }

        /// @brief Закрасить пиксель точку
        /// @param position координаты
        /// @param color Цвет
        inline void DrawPixel(const point& position, const ksys_color_t color = OS::sys_color_table.work_text)
        {
            _ksys_draw_pixel(position.x, position.y, color);
        }

        /// @brief Нарисовать окружность
        /// @param coord Координаты центра
        /// @param Radius радиус окружности
        /// @param detalization Детализация прорисовки окружности
        /// @paragraph Круг рисуется с помошью линий
        /// @param color Цвет
        void DrawCircle(point coord, unsigned Radius, unsigned detalization = 36, ksys_color_t color = OS::sys_color_table.work_graph)
        {
            point buff;
            unsigned b = Radius;
            unsigned c = 0;
            for (unsigned angle = 1; angle <= detalization * 10; angle += (36 / detalization))
            {
                buff = {coord.x + b, coord.y + c};
                b = Radius * cos(angle);
                c = sqrt((Radius*Radius) - (b*b));
                point n = {coord.x + b, coord.y + c};
                DrawLine(buff, n);
            }
        }

        /// @brief Нарисовать закрашенный прямоугольник
        /// @param position позиция левого верхнего угла
        /// @param size Размеры
        /// @param color Цвет
        void DrawRectangleFill(point position, const point& size, const ksys_color_t color = OS::sys_color_table.work_graph)
        {
            __asm__ __volatile__(
                "int $0x40" 
                ::"a"(13), "b"((position.x << 16) + size.x), "c"((position.y << 16) + size.y), "d"(color));
        }

        /// @brief Нарисовать круг(закрашенный)
        /// @param coord Координаты центра
        /// @param Radius Радиус круга
        /// @param color Цвет
        void DrawCircleFill(point coord, unsigned Radius, ksys_color_t color = OS::sys_color_table.work_graph)
        {
            DrawCircle(coord, Radius, color);
            unsigned b = Radius * cos(90+45);
            unsigned c = sqrt((Radius * Radius) - (b * b));
            point n = {coord.x + b, coord.y + c};
            DrawRectangleFill(n, {(coord.x - n.x) * 2, c * 2}, color);
            for (unsigned i = Radius; i > (Radius -(coord.x - n.x)); i--)//Дозакрашивание пробелов между квадратом и границами груга
            {
                DrawCircle(coord, i, NULL, color);
            }
        }

        /// @brief Нарисовать точку
        /// @param position Координаты
        /// @param size Радиус точки в рx
        /// @param color Цвет
        /// @param fill Закрашенная/Выколотая точка
        /// @paragraph Функция рисует закрашенную точку если fill = true
        void DrawPoint(const point& position, const unsigned& Radius, const ksys_color_t& color = OS::sys_color_table.work_graph, bool fill = false)
        {
            if(Radius < 3)    //Если радиус меньше 3 пикселей, то не смысла его закрашивать
            {
                fill = false;
            }
            if (fill)
            {
                DrawCircleFill(position, Radius, color);
            }
            else
            {
                DrawCircle(position, Radius, color);
                if(Radius < 3)
                {
                    DrawPixel(position, color);
                }
            }
        }


        /// @brief Нарисовать прямоугольник
        /// @param a Точка в левом верхнем углу
        /// @param b Точка в правом нижнем углу
        void DrawRectangleLines(point a, point b, ksys_color_t color = OS::sys_color_table.work_graph)
        {
            DrawLine(a, {b.x, a.y}, color);
            DrawLine(a, {a.x, b.y}, color);
            DrawLine({b.x, a.y}, b, color);
            DrawLine({a.x, b.y}, b, color);
        }

        

        /// @brief Нарисовать треугольник
        /// @param a первая точка
        /// @param b вторая точка
        /// @param c третья точка
        /// @param color цвет линий
        inline void DrawTriangle(point a, point b, point c, ksys_color_t color = OS::sys_color_table.work_graph)
        {
            DrawLine(a, b, color);
            DrawLine(a, c, color);
            DrawLine(b, c, color);
        }

        //=============================================================================================================================================================

        /// @brief Класс для работы с изображениями
        class Image
        {
        private:
            std::vector<rgb_t> _img;
            point _size;
        public:
            Image(std::string Path);
            ~Image();

            /// @brief Загрузить изображение из файла
            /// @param Path Путь до файла с изображением
            /// @return true если удачно, false если неудачно
            bool LoadImage(std::string Path);

            /// @briefВывести изображение
            /// @param coord координаты 
            /// @param size 
            /// @warning Функция пока что очень медленная, может быть когданибудь позже от=птимизирую...
            void DrawImage(point coord = {0,0}, point size = {0,0});
        };
        
        Image::Image(std::string Path)
        {
            LoadImage(Path);
        }
        
        Image::~Image()
        {
        }

        bool Image::LoadImage(std::string Path)
        {
            bool extcode;
            if(filesystem::Exist(Path)) //Если файл с изображением существует
            {
                std::string Type;
                std::ifstream img;

                {
                    unsigned i = Path.length();

                    while (Path[i] != '.')
                    {
                        Type.push_back(Path[i]);
                        i--;
                    }
                }

                if (Type == "png")//Потом канибудь надо допилить открытие png
                {
                    img.open(Path.c_str(), std::ios::binary);

                    char buff[8];

                    for(unsigned i = 0; i < 8; i++)
                    {
                        img >> buff[8];
                    }
                    if(buff[0] == 89)
                    {
                        //тут двльше
                    }
                }
                else if (Type == "jpeg")
                {
                    /* code */
                }
                else
                {
                    extcode = false;
                }
                

                img.close();
            }
            else
            {
                return extcode = false;
            }
            return extcode;
        }

        void Image::DrawImage(point coord, point size)
        {
            if(size.x == 0 && size.y == 0)
            {
                size = _size;
            }

            rgb_t *d = (rgb_t*)malloc(_img.size() * sizeof(rgb_t));

            for(unsigned i = 0; i < _img.size(); i++)
            {
                d[i] = _img[i];
            }

            _ksys_draw_bitmap(d,coord.x, coord.y, size.x, size.y);

            free(d);
        }
        //=============================================================================================================================================================

        
    }
} // namespace KolibriLib


#endif // __GRAPHIC_H__