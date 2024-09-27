#ifndef KOLIBRI_LIBINI_H
#define KOLIBRI_LIBINI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
/// @brief инициализировать libini
/// @param  
/// @return 
extern int kolibri_libini_init(void);

/// @brief
typedef void (*LIBINI_enum_sections_func)(const char *fileName, const char *sectionName);

/// @brief 
typedef void (*LIBINI_enum_keys_func)(const char *fileName, const char *sectionName, const char* keyName, const char* value);

/// @brief Перебрать секции, вызывая пользовательскую функцию для каждого из них.
/// @param FileName ini файл
/// @param func функция что вызывается для каждой секции
/// @return -1 если ошибка
extern uint32_t (*LIBINI_enum_sections)(const char *filename, LIBINI_enum_sections_func func) __attribute__((__stdcall__));

/// @brief Перебрать ключи в секции, вызывая пользовательскую функцию для каждого из них.
/// @param filename путь до ini файла
/// @param sectionName имя секции
/// @param func фунцкия, что вызывается для каждой найденной секции
/// @return -1 если ошибка
extern uint32_t (*LIBINI_enum_keys)(const char *filename, const char *sectionName, LIBINI_enum_keys_func func) __attribute__((__stdcall__));

/// @brief Прочитать строку.
/// @param filename путь до ini файла
/// @param sectionName имя секции
/// @param keyName имя ключа
/// @param buffer буфер для записи полученного значения
/// @param bufferLen размер буфера (максимальное количество байт для чтения)
/// @param defaultValue возвращаемое значение по умолчанию, если ключ, секция или файл не будут найдены
/// @return -1 если ошибка
/// @return если ключ не найден то *buff равен defaultValue
extern uint32_t (*LIBINI_get_str)(const char *filename, const char *sectionName, const char *keyName, char *buffer, uint32_t bufferLen, uint32_t defaultValue) __attribute__((__stdcall__));

/// @brief Записать строку.
/// @param filename путь до ini файла
/// @param sectionName имя секции
/// @param keyName имя ключа
/// @param buffer буфер содержащий значение
/// @param bufferLen размер буфера (максимальное количество байт для чтения)
/// @return -1 если ошибка
extern uint32_t (*LIBINI_set_str)(const char *filename, const char *sectionName, const char *keyName, const char *buffer, uint32_t bufferLen) __attribute__((__stdcall__));

/// @brief Прочитать число.
/// @param filename путь до ini файла
/// @param sectionName имя секции
/// @param keyName имя ключа
/// @param defaultValue возвращаемое значение по умолчанию
/// @return defaultValue возвращаемое значение по умолчанию, если ключ, секция или файл не будут найдены
/// @return найденное значение ключа
extern uint32_t (*LIBINI_get_int)(const char *filename, const char *sectionName, const char *keyName, uint32_t defaultValue) __attribute__((__stdcall__));

/// @brief Прочитать число.
/// @param filename путь до ini файла
/// @param sectionName имя секции
/// @param keyName имя ключа
/// @param value записываемое значение
/// @return -1 если ошибка
extern uint32_t (*LIBINI_set_int)(const char *filename, const char *sectionName, const char *keyName, uint32_t value) __attribute__((__stdcall__));

/// @brief Прочитать число.
/// @param filename путь до ini файла
/// @param sectionName имя секции
/// @param keyName имя ключа
/// @param defaultValue возвращаемое значение по умолчанию
/// @return defaultValue возвращаемое значение по умолчанию, если ключ, секция или файл не будут найдены
/// @return найденное значение ключа
extern uint32_t (*LIBINI_get_color)(const char *filename, const char *sectionName, const char *keyName, uint32_t defaultValue) __attribute__((__stdcall__));

/// @brief Прочитать число.
/// @param filename путь до ini файла
/// @param sectionName имя секции
/// @param keyName имя ключа
/// @param value записываемое значение
/// @return -1 если ошибка
extern uint32_t (*LIBINI_set_color)(const char *filename, const char *sectionName, const char *keyName, uint32_t value) __attribute__((__stdcall__));

/// @brief Прочитать клавишу быстрого доступа.
/// @details Строка для ini_get_shortcut - произвольное количество модификаторов Ctrl/Alt/Shift/LCtrl/LAlt/LShift/RCtrl/RAlt/RShift, после которых следует латинская буква/цифра/имя клавиши (имена собственные имеют Home, End, PgUp, PgDn, Ins=Insert, Del=Delete, Tab, Plus, Esc, Enter, Backspace, Space, Left, Right, Up, Down). Строку можно писать с любым регистром символов. Части пишутся либо слитно, либо разделяются плюсом. Например: Ctrl+Alt+Backspace, RCtrl+RShift, ShiftA, f10, shiftalt5
/// @param filename путь до ini файла
/// @param sectionName имя секции
/// @param keyName имя ключа
/// @param defaultValue возвращаемое значение по умолчанию, если ключ, секция или файл не будут найдены
/// @param modifiers адрес переменной типа dword, получающей значение модификаторов для передачи функции 66.4
/// @return сканкод клавиши быстрого доступа
extern uint32_t (*LIBINI_get_shortcut)(const char *filename, const char *sectionName, const char *keyName, uint32_t defaultValue, const char *modifiers, uint32_t) __attribute__((__stdcall__));

#ifdef __cplusplus
}
#endif

#endif /* KOLIBRI_LIBINI_H */
