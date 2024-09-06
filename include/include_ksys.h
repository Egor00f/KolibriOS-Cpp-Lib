#ifndef __INCLUDE_KSYS_H_HPP__
#define __INCLUDE_KSYS_H_HPP__

/*
	Почему?
	с включеным флагом -Wold-style-cast компилятор с++ выдаёт тонну предупреждений
*/

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wcast-qual"

#include <sys/ksys.h>

#pragma GCC diagnostic pop

#endif // __INCLUDE_KSYS_H_HPP__