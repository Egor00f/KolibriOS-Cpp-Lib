#ifndef KOLIBRI_OPENDIALOG_H
#define KOLIBRI_OPENDIALOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

const char sz_com_area_name[]    = "FFFFFFFF_open_dialog";
const char sz_dir_default_path[] = "/sys";
const char sz_start_path[]       = "/sys/File managers/opendial";

/// @brief режим окртытия диалога
typedef enum open_dialog_mode
{
	/// @brief Открыть файл
	OPEN = 0,

	/// @brief Сохранить файл
	SAVE = 1,

	/// @brief Выбрать папку
	SELECT = 2
} open_dialog_mode;

/// @brief Структура для фильтра расширений
/// @details имеет непостоянный размер
typedef struct __attribute__ ((__packed__)) {
	
	/// @brief Размер структуры в байтах

	unsigned int size;

	/// @brief конец фильра
	/// @details должен быть 0
	unsigned char end;
} od_filter;


/// @brief Структура
typedef struct __attribute__ ((__packed__)) {
	open_dialog_mode mode;
	char* procinfo;
    char* com_area_name;
    unsigned int com_area;
    char* opendir_path;

	/// @brief директория, которая открывается по умолчанию (если путь в .openfile_path пустой).
	char* dir_default_path;

	/// @brief путь к opendial (по-умолчанию это /sys/File managers/opendial).
	char* start_path;
    void (*draw_window)();
    unsigned int status;
    char* openfile_path;
    char* filename_area;

    /// @brief указатель на фильтр
    od_filter* filter_area;
    unsigned short x_size;
    unsigned short x_start;
    unsigned short y_size;
    unsigned short y_start;
} open_dialog;

void fake_on_redraw(void)
#ifdef __MakeStaticLib__
;
#else
{}
#endif

/// @brief создать структуру
/// @param mode режим
/// @param tlx 
/// @param tly 
/// @param x_size 
/// @param y_size 
/// @return указатель на созданную структуру
open_dialog* kolibri_new_open_dialog(unsigned int mode, unsigned short tlx, unsigned short tly, unsigned short x_size, unsigned short y_size);


/// @brief инициализировать proclib
extern void kolibri_proclib_init();

extern void (*OpenDialog_init)(open_dialog *) __attribute__((__stdcall__));

extern void (*OpenDialog_start)(open_dialog *) __attribute__((__stdcall__));

#ifdef __cplusplus
}
#endif

#endif // KOLIBRI_OPENDIALOG_H
