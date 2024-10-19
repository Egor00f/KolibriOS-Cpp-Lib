#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#ifdef DEBUG


#include <include_ksys.h>
#include <string>
#include <fstream>
#include <microlog/microlog.hpp>

namespace KolibriLib
{
	/**
	 * @brief Логер
	 * @details Используется для вывода отладочной информации. 
	 */
	extern microlog::logger logger;
} // namespace KolibriLib

#endif // DEBUG

#endif // __DEBUG_HPP__
