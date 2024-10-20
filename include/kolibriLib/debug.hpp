#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#include <microlog/microlog.hpp>
#include <kolibriLib/system/thread.hpp>

namespace KolibriLib
{

	const std::string LogFileName(Thread::GetThreadInfo().name + "-debug.log");

	/**
	 * @brief Логер
	 * @details Используется для вывода отладочной информации. 
	 */
	extern microlog::logger logger;
} // namespace KolibriLib

#endif // __DEBUG_HPP__
