#ifndef __MOUSE_H__
#define __MOUSE_H__


#include <sys/ksys.h>
#include "small.hpp"

namespace KolibriLib
{
    /// @brief Работа с мышью
    namespace mouse
    {
        /// @brief Хендл курсора мыши
        typedef void *CursorHandle;

        /// @brief Структура хранящая все виды курсора
        struct cursor
        {
            mouse::CursorHandle pointer;    //Обычный курсор
            mouse::CursorHandle dgn1;       //
            mouse::CursorHandle dgn2;
            mouse::CursorHandle link;
            mouse::CursorHandle horz;
            mouse::CursorHandle vert;
            mouse::CursorHandle beam;       //Ввод текста
            mouse::CursorHandle busy;       //Загрузка
        };
        
        cursor Cursor;

        /// @brief Получить позицияю курсора на экране
        /// @return (point) позиция курсора
        inline point<unsigned> GetMousePositionOnSreen()
        {
            ksys_pos_t a = _ksys_get_mouse_pos(KSYS_MOUSE_SCREEN_POS);

            return {a.x, a.y};
        }

        /// @brief Получить позицияю курсора внутри окна
        /// @return (point) позиция курсора
        inline point<int> GetMousePositionInWindow()
        {
            ksys_pos_t a = _ksys_get_mouse_pos(KSYS_MOUSE_WINDOW_POS);

            return {a.x, a.y};
        }

        /// @brief Проверить какие кнопки мыши нажаты
        /// @return 
        inline uint32_t GetMouseButtons()
        {
            return _ksys_get_mouse_buttons();
        }

        /// @brief колёсико мыши
        /// @return 
        inline uint32_t GetMouseWheels()
        {
            return _ksys_get_mouse_wheels();
        }

        

        /// @brief Загрузить курсор мыши из файла
        /// @brief Путь до файла
        /// @return Функция возвращает CursorHandle загруженного курсора
        CursorHandle LoadCursor(const std::string& Path)
        {
            return _ksys_load_cursor((void*)Path.c_str(), 0);
        }

        /// @brief Изменить курсор мыши
        /// @param cursor Изображение курсора
        /// @return true если удачно, иначе false
        /// @paragraph Изображение должно обязательно быть 
        inline CursorHandle SetCursor(CursorHandle handler)
        {
            _ksys_set_cursor(handler);
        }

        inline void DeleteCursor(CursorHandle handle)
        {
            _ksys_delete_cursor(handle);
        }

    }
}


#endif // __MOUSE_H__