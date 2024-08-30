#ifndef __OPENDIALOG_HPP__
#define __OPENDIALOG_HPP__

#include <kolibriLib/system/filesystem.hpp>
#include <kolibriLib/types.hpp>
#include <kolibriLib/window/windowBase.hpp>
#include <C_Layer/INCLUDE/kolibri_opendialog.h>

namespace KolibriLib
{
	

		
	/// @brief Диалог выбора файлов
	/// @details это отдельная программа (если что)
	/// Памяти требует эта штука много (около 9500 байт)
	/// @warning На данный момент не работает
	class OpenDialog
	{	
	public:

		/// @brief Режим открытия OpenDialogа
		typedef enum Modes
		{
			/// @brief Открыть файл
			/// @image OpenD1.png
			OpenFile = open_dialog_mode::OPEN,

			/// @brief Сохранить файл
			/// @image OpenD2.png
			Save = open_dialog_mode::SAVE,

			/// @brief Выбрать папку
			/// @image OpenD3.png
			Select = open_dialog_mode::SELECT
		} Mode;

		typedef enum Status_
		{
			/// @brief Пользователь нажал Cancel
			Cancel = 0,

			/// @brief Пользователь нажал Open
			Opened = 1,

			/// @brief OpenDialog не смог отрыться
			Error = 2
		} Status;

		/// @note должно обязательно заканчиавться на '\0'
		typedef std::string FilterElement;

		/// @brief 
		struct FilterArea
		{
			od_filter* area;

			FilterArea();
			FilterArea(const std::vector<FilterElement> &elements);

			/// @brief Деструктор
			~FilterArea();

			static od_filter* Create(const std::vector<FilterElement> &elements);

			FilterElement & operator[](std::size_t n);
			FilterElement operator[](std::size_t n) const;
		};

		/// @brief Указатель на то что путь не указан, нужен только для GetPath
		const filesystem::Path PathNotSet = "/";

		OpenDialog(Modes mode, Size winSize = window::DefaultWindowSize, Coord winCoord = window::DefaultWindowCoord, const std::vector<FilterElement> &filter = {}, const filesystem::Path &defaultPath = sz_dir_default_path);

		/// @brief Открыть OpenDialog
		/// @return Путь который выбрал пользователь
		Status Open();

		filesystem::Path GetPath() const;

		/// @brief Добавить еще фильров
		void SetFilter(const std::vector<FilterElement> &f);

		/// @brief деструктор
		~OpenDialog();

	private:
		open_dialog* _opendialog;

	};

	
} // namespace KolibriLib


#endif