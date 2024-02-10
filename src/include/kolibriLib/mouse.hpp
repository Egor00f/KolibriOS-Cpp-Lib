#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <sys/ksys.h>
#include "small.hpp"
#include "filesystem.hpp"
#include "color.hpp"

namespace KolibriLib
{
    /// @brief Работа с мышью
    namespace mouse
    {

        /// @brief Получить позицияю курсора на экране
        /// @return (point) позиция курсора абсолютно
        inline point<int> GetMousePositionOnSreen();

        /// @brief Получить позицияю курсора внутри окна
        /// @return (point) позиция курсора относительно окна
        inline point<int> GetMousePositionInWindow();

        /// @brief Проверить какие кнопки мыши нажаты
        /// @return
        inline uint32_t GetMouseButtons();

        /// @brief колёсико мыши
        /// @return
        inline uint32_t GetMouseWheels();

        enum MouseButtons
		{
            LeftButton	= 0x1,
            RightButton	= 0x10,
            CenterBtton	= 0x100,
            FourButton	= 0x1000,
            FiveButton	= 0x10000
        };

        /// @brief Эмулировать нажатия кнопок мыши
        /// @param m 
		/// @paragraph Использование: EmulateMouse(EmulateMouse::LeftButton + EmulateMouse::RightButton) //Эмулирует нажатие правой и левой кнопок мыши
        inline void EmulateMouse(uint8_t m);

		typedef void* CursorHandle;

		enum LoadCursor
		{
			FromFile = 0,
			FromMem,
			Indirect
		};

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

		/// @brief Загрузить курсор мыши
		/// @param cur путь до файла с курсором
		/// @return Хендл загруженного курсора
		/// @paragraph Файл курсора должен быть в формате .cur, стандартном для MS Windows, причём размером 32*32 пиксел
		inline CursorHandle LoadCursor(Colors::ARGB[] cur);

		/// @brief Установить курсор
		/// @param handle хендл устанавливаемого курсора
		/// @return хендл предыдушего курсора
		inline CursorHandle SetCursor(CursorHandle handle);

		inline void DeleteCursor(CursorHandle handle);
    }
} // namespace KolibriLib


#endif // __MOUSE_H__