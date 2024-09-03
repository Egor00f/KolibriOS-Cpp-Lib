#ifndef __CLIPBOARD_HPP__
#define __CLIPBOARD_HPP__

#include <sys/ksys.h>
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

		typedef int Slot;

		
		/// @brief структура буфера обмена
		struct clipboard_struct
		{

			typedef enum Encodings
			{
				UTF8 = 0,
				CP866 = 1,
				CP1251 = 2
			} Encoding;

			typedef enum Types
			{
				/// @brief Текст
				Text = 0,

				/// @brief Изображние
				Image = 1,

				/// @brief Любые данные
				Raw = 2,

				/// @brief Путь
				Filepath = 3
			} Type;

			/// @brief Размер структуры
			uint32_t size;

			/// @brief Тип структуры
			uint32_t type;


			union 
			{
				/// @brief Кодировка (если текст)
				uint32_t encoding;

				/// @brief изображение
				struct
				{
					/// @brief Ширина изображения
					uint32_t X;

					/// @brief Высота изображения
					uint32_t Y;

					/// @brief Глубина цвета (8, 16, 24, 32, 48, 64)
					uint32_t depht;

					/// @brief Указатель на палитру (смещение от начала файла)
					/// @details Если палитры нет то значение 0
					void* pallete;

					/// @brief Размер области палитры, максимальное значение 256*4=1024байт.
					/// @details Если палитры нет то значение 0
					uint32_t palleteSize;

					/// @brief Указатель на данные пикселей для R, G, B.
					rgb_t* image;

					/// @brief Размер области данных для пикселей
					uint32_t imageSize;
				};

				struct
				{
					uint16_t res;
					char filepath[0];
				};
			};
		};

		class clipboard
		{
		public:

			clipboard(){};

			clipboard(const std::string& text, bool filepath = false);

			clipboard(const UI::Images::img &image);

			/// @brief Конструктор, для любых данных
			/// @tparam T тип данных которй будет скопирован
			/// @param data перемнная что будет скопированна
			/// @note Не пихайте лучше сюда типы имеющи указатели, потому что будт скопирован только указатель
			template <class T>
			clipboard(T data);

			/// @brief деструктор
			~clipboard();

			clipboard_struct::Type GetType();
			

			/// @details Просто возращает указатель
			operator clipboard_struct*() const;

			clipboard_struct* _struct = nullptr;
		};
		
		/// @brief Список ошибок
		typedef enum Errors
		{
			/// @brief Всё ок
			ok = 0,

			/// @brief ошибка
			err = 1,

			/// @brief отсутствует область главного списка
			NotareOfMainEnum = -1
		} Error;

		/// @brief считать данные из буфера обмена
		inline clipboard Get(Slot slot)
		{
			clipboard ret;

			ret._struct = (clipboard_struct*)_ksys_clip_get(slot);

			return ret;
		}

		/// @brief
		/// @return Clipboard::Error
		inline Error Put(clipboard c)
		{
			return static_cast<Error>(_ksys_clip_set(c.operator KolibriLib::Clipboard::clipboard_struct *()->size, (char*)c.operator KolibriLib::Clipboard::clipboard_struct *()));
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
	_struct = (KolibriLib::Clipboard::clipboard_struct *)malloc(4 + 4 + sizeof(T));
	_struct->size = 4 + 4 + sizeof(T);
	_struct->type = KolibriLib::Clipboard::clipboard_struct::Type::Raw;
	
	std::memcpy(_struct+8, data, 4 + 4 + sizeof(T));
}

#endif


#endif