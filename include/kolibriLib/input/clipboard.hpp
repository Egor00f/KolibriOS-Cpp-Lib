#ifndef __CLIPBOARD_HPP__
#define __CLIPBOARD_HPP__

#include <include_ksys.h>
#include <kolibriLib/img.hpp>
#include <string>
#include <cstring>

namespace KolibriLib
{
	/// @brief Буфер обмена
	namespace Clipboard
	{
		/// @brief Узнать колическтов слотов в буфере обмена
		/// @return количество слотов в буфере
		/// @return -1 если остутсвует область главного списка
		inline int NumOfSlots()
		{
			return _ksys_clip_num();
		}

		using Slot = int;

		
		/// @brief структура буфера обмена
		struct clipboard_struct
		{

			/**
			 * @brief Кодировака для текста
			 */
			enum class Encoding
			{
				UTF8 = 0,
				CP866 = 1,
				CP1251 = 2
			};

			/**
			 * @brief Тип буфера обмена
			 */
			enum class Type : std::uint32_t
			{
				/// @brief Текст
				Text = 0,

				/// @brief Изображние
				Image = 1,

				/// @brief Любые данные
				Raw = 2,

				/// @brief Путь
				Filepath = 3
			};

			// Поля

			/// @brief Размер структуры
			std::int32_t size;

			/// @brief Тип структуры
			Type type;

			union 
			{
				/// @brief Кодировка (если текст)
				std::uint32_t encoding;

				/// @brief изображение
				struct
				{
					/// @brief Ширина изображения
					std::uint32_t X;

					/// @brief Высота изображения
					std::uint32_t Y;

					/// @brief Глубина цвета (8, 16, 24, 32, 48, 64)
					std::uint32_t depht;

					/// @brief Указатель на палитру (смещение от начала файла)
					/// @details Если палитры нет то значение 0
					void* pallete;

					/// @brief Размер области палитры, максимальное значение 256*4=1024байт.
					/// @details Если палитры нет то значение 0
					std::uint32_t palleteSize;

					/// @brief Указатель на данные пикселей для R, G, B.
					rgb_t* image;

					/// @brief Размер области данных для пикселей
					std::uint32_t imageSize;
				};

				struct
				{
					/// @brief Зарезервированно
					std::uint16_t res;

					/// @brief Файловый путь
					char filepath[0];
				};
			};
		};

		/// @brief Буффер обмена
		class clipboard
		{
		public:

			/**
			 * @brief Конструктор по умолчанию
			 */
			clipboard() = default;

			/// @brief Конструктор
			/// @param text текст
			/// @param filepath текст это файловый путь?
			clipboard(const std::string& text, bool filepath = false);

			/**
			 * @brief Конструктор
			 * @param image картинка
			 */
			clipboard(const UI::Images::img &image);

			/// @brief Конструктор, для любых данных
			/// @tparam T тип данных которй будет скопирован
			/// @param data перемнная что будет скопированна
			/// @note Не пихайте лучше сюда типы имеющи указатели, пsотому что будт скопирован только указатель
			template <class T>
			clipboard(T data);

			/// @brief деструктор
			~clipboard();

			/**
			 * @brief Получить тип буфера обмена
			 * @return тип буфера обмена
			 */
			clipboard_struct::Type GetType();
			

			/// @details Просто возращает указатель
			operator clipboard_struct*() const;

			// Поля

			/**
			 * @brief Указатель на структуру
			 */
			clipboard_struct* _struct = nullptr;
		};
		
		/// @brief Список ошибок
		enum class Error
		{
			/// @brief Всё ок
			ok = 0,

			/// @brief ошибка
			err = 1,

			/// @brief отсутствует область главного списка
			NotareOfMainEnum = -1
		};

		/// @brief считать данные из буфера обмена
		inline clipboard Get(Slot slot)
		{
			clipboard ret;

			ret._struct = reinterpret_cast<clipboard_struct*>(_ksys_clip_get(slot));

			return ret;
		}

		/// @brief
		/// @return Clipboard::Error
		inline Error Put(clipboard c)
		{
			return static_cast<Error>(_ksys_clip_set(static_cast<clipboard_struct*>(c)->size, (char*)c.operator KolibriLib::Clipboard::clipboard_struct *()));
		}

		/// @brief удалить последний слот с данными в буфере обмена
		/// @return Clipboard::Error
		inline Error Pop()
		{
			return static_cast<Error>(_ksys_clip_pop());
		}

		/// @brief аварийный сброс блокировки буфера
		/// @details Используется в исключительных случаях, когда зависшее или убитое приложение заблокировало работу с буфером обмена.
		/// @return true если ошибка
		inline bool Unlock()
		{
			return _ksys_clip_unlock();
		}
	} // namespace Clipboard
	
} // namespace KolibriLib

#ifndef __MakeStaticLib__

template <class T>
inline KolibriLib::Clipboard::clipboard::clipboard(T data)
{
	_struct = static_cast<KolibriLib::Clipboard::clipboard_struct *>(malloc(4 + 4 + sizeof(T)));
	_struct->size = 4 + 4 + sizeof(T);
	_struct->type = KolibriLib::Clipboard::clipboard_struct::Type::Raw;
	
	std::memcpy(_struct+8, data, 4 + 4 + sizeof(T));
}

#endif


#endif