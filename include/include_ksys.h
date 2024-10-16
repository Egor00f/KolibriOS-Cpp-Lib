#ifndef __INCLUDE_KSYS_H_H__
#define __INCLUDE_KSYS_H_H__

/*
	Почему?
	С включеным флагами для с++ компилятор выдаёт тонну предупреждений
*/

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wcast-qual"
#pragma GCC diagnostic ignored "-Wsign-conversion"

#include <sys/ksys.h>

#pragma GCC diagnostic pop

#endif // __INCLUDE_KSYS_H_H__