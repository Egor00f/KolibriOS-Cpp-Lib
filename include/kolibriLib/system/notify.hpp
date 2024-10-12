#ifndef __SYSTEM_NOTIFY_HPP__
#define __SYSTEM_NOTIFY_HPP__

#include <string>

namespace KolibriLib
{
	namespace OS
	{
		/// @brief Иконки в сообщениях
		/// @image notify.orig.png
		enum class notifyIcon : char
		{
			
			/**
			 * @brief Приложение (шестерёнка)
			 */
			Application = 'A',

			/**
			 * @brief Иконка ошибки
			 */
			Error = 'E',

			/**
			 * @brief Иконка предупреждения
			 */
			Warning = 'W',

			/**
			 * @brief Иконка 
			 */
			Ok = 'O',

			/**
			 * @brief Иконка сети
			 */
			Network = 'N',

			/**
			 * @brief Значок Info
			 */
			Info = 'I',

			Folder = 'F',

			Component = 'C',

			/**
			 * @brief Иконка почты
			 */
			Mail = 'M',

			/**
			 * @brief Иконка загрузки
			 */
			Download = 'D',

			/**
			 * @brief 
			 */
			Sound = 'S'
		};

		/// @brief Ключи для уведомлений
		enum class notifyKey : char
		{
			/// @brief Ключа нет
			NotSet,

			/// @brief не закрывать автоматически
			NoAutoClose = 'd',

			/// @brief не закрываеть по клику
			NoClose = 'c',

			/// @brief Есть заголовок
			Title = 't',

			/**
			 * @brief 
			 */
			ProgressBar = 'p'
		};

		/// @brief Уведмление
		/// @param Title Заголовок, может быть пустым если заголовок не нужен
		/// @param Text текст после заголовка
		/// @param icon иконка
		/// @param keys ключи
		void Notify(const std::string &Text, notifyIcon icon = notifyIcon::Info, const notifyKey (&keys)[4] = {notifyKey::NotSet, notifyKey::NotSet, notifyKey::NotSet, notifyKey::NotSet});
	} // namespace OS
	
} // namespace KolibriLib


#endif // __SYSTEM_NOTIFY_HPP__