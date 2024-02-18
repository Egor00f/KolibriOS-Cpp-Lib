#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <sys/ksys.h>
#include "types.hpp"
#include "filesystem.hpp"
#include "color.hpp"

namespace KolibriLib
{
    /// @brief Работа с мышью
    namespace mouse
    {
		enum MouseButtons
		{
            LeftButton	= 0b1,
            RightButton	= 0b10,
            CenterBtton	= 0b100,
            FourButton	= 0b1000,
            FiveButton	= 0b10000
        };
		
        /// @brief Получить позицияю курсора на экране
        /// @return (point) позиция курсора абсолютно
        inline point<int> GetMousePositionOnSreen();

        /// @brief Получить позицияю курсора внутри окна
        /// @return (point) позиция курсора относительно окна
        inline UI::Coord GetMousePositionInWindow();

        /// @brief Проверить какие кнопки мыши нажаты
        /// @return
        inline uint32_t GetMouseButtons();

        /// @brief колёсико мыши
        /// @return
        inline uint32_t GetMouseWheels();

        /// @brief Эмулировать нажатия кнопок мыши
        /// @param m 
		/// @paragraph Использование: EmulateMouse(EmulateMouse::LeftButton + EmulateMouse::RightButton) //Эмулирует нажатие правой и левой кнопок мыши
        inline void EmulateMouse(uint8_t m);

		/// @brief Центрировать курсор
		/// @paragraph Функция устанавливает курсор в середину экрана
		inline void CenterCursor();

		/// @brief Хендл курсора мыши
		typedef void* CursorHandle;


		


		/// @brief Загрузить курсор мыши
		/// @param path путь до файла с курсором
		/// @return Хендл загруженного курсора
		/// @paragraph Файл курсора должен быть в формате .cur, стандартном для MS Windows, причём размером 32*32 пикселя
		inline CursorHandle LoadCursor(filesystem::Path path);

		/// @brief Загрузить курсор мыши
		/// @param ptr путь до файла с курсором
		/// @return Хендл загруженного курсора
		/// @paragraph Файл курсора должен быть в формате .cur, стандартном для MS Windows, причём размером 32*32 пиксел
		inline CursorHandle LoadCursor(void* ptr);

		// /// @brief Загрузить курсор мыши
		// /// @param cur путь до файла с курсором
		// /// @return Хендл загруженного курсора
		// /// @paragraph Файл курсора должен быть в формате .cur, стандартном для MS Windows, причём размером 32*32 пиксел
		// inline CursorHandle LoadCursor(Colors::ARGB[] cur);

		/// @brief Установить курсор
		/// @param handle хендл устанавливаемого курсора
		/// @return хендл предыдушего курсора
		inline CursorHandle SetCursor(CursorHandle handle);

		inline void DeleteCursor(CursorHandle handle);
    }
} // namespace KolibriLib


#endif // __MOUSE_H__