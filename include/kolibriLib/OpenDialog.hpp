#ifndef __OPENDIALOG_HPP__
#define __OPENDIALOG_HPP__

#include <kolibriLib/system/filesystem.hpp>
#include <kolibriLib/types.hpp>
#include <kolibriLib/window/windowBase.hpp>

namespace KolibriLib
{
	
	#include <C_Layer/INCLUDE/kolibri_opendialog.h>

		
	/// @brief Диалог выбора файлов
	/// @details это отдельная программа (если что)
	/// Памяти требует эта штука много (около 9500 байт)
	class OpenDialog
	{	
	public:

		/// @brief Режим открытия OpenDialogа
		typedef enum Modes
		{
			/// @brief Открыть файл
			/// @image OpenD1.png
			Open = open_dialog_mode::OPEN,

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

		struct OpenDialogStruct
		{
			unsigned int mode;
			char *procinfo;
			char *com_area_name;
			unsigned int com_area;
			char *opendir_path;

			/// @brief директория, которая открывается по умолчанию (если путь в .openfile_path пустой).
			char *dir_default_path;

			/// @brief путь к opendial (по-умолчанию это /sys/File managers/opendial).
			char *start_path;
			void (*draw_window)();
			unsigned int status;
			char *openfile_path;
			char *filename_area;
			FilterArea filter_area;
			unsigned short x_size;
			unsigned short x_start;
			unsigned short y_size;
			unsigned short y_start;
		};
		
		/// @brief Указатель на то что путь не указан, нужен только для GetPath
		const filesystem::Path PathNotSet = "/";

		OpenDialog(Modes mode, Size winSize = window::DefaultWindowSize, Coord winCoord = window::DefaultWindowCoord, FilterArea filter = FilterArea(), const filesystem::Path &defaultPath = sz_dir_default_path);

		/// @brief Открыть OpenDialog
		/// @return Путь который выбрал пользователь
		Status Open();

		filesystem::Path GetPath() const;

		/// @brief Добавить еще фильров
		void SetFilter(const std::vector<FilterElement> &f);

		~OpenDialog();

	private:
		OpenDialogStruct* _opendialog;

	};

	
} // namespace KolibriLib


#endif