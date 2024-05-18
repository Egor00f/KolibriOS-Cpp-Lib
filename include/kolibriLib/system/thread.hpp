#ifndef __THREAD_H__
#define __THREAD_H__

#include <stdlib.h>
#include <sys/ksys.h>

namespace KolibriLib
{
    /// \brief Подождать
    /// \param time время задержки(в 1/100 секунды)
    inline void Wait(const uint32_t &time)
    {
        _ksys_delay(time);
    }

    /// \brief Подождать, минимальное кол-во времени
    /// @details Функция передаёт управление другим процессам
    inline void Wait()
    {
        _ksys_thread_yield();
    }

    /// \brief Работа с потоками
    namespace Thread
    {
        /// @brief Слот окна
        typedef int Slot;

        /// @brief ID процесса
        typedef int PID;

        /// @brief Информация о потоке
        typedef ksys_thread_t ThreadInfo;

        /// \brief Создать поток
        /// \param ThreadEntry Имя функции которую нужно запустить в новом потоке
        /// @param ThreadStackSize Размер стека нового потока в байтах
        /// \return ID потока
        /// @note Используйте лучше std::thread, а то есть шанс проебаться с размером стека
        PID CreateThread(void(*ThreadEntry)(void*), unsigned ThreadStackSize = 2048);
        

        /// @brief Завершить процесс/поток
        /// @param PID ID Процесса/потока
        /// @return true если успешно, инач false
        /// @note Нельзя завершить поток операционной системы OS/IDLE (номер слота 1), можно завершить любой обычный поток/процесс
        inline bool TerminateThread(PID pid)
        {
            int a;
            asm_inline(
                "int $0x40"
                : "=a"(a)
                : "a"(18), "b"(18), "c"(pid));
            return !a;
        }

        /// @brief Получить слот потока
        /// @param pid поток
        /// @return Слот потока pid
        inline Slot GetThreadSlot(const PID& pid)
        {
            return _ksys_get_thread_slot(pid);
        }

        /// @brief Поличть информацию о потоке
        /// @param thread слот потока
        /// @return информация о потоке
        /// @details по умолчанию возвращается информация о текущем потоке
        ThreadInfo GetThreadInfo(const Slot &thread = -1);

    } // namespace Thread
    
} // namespace KolibriLib


#endif // __THREAD_H__