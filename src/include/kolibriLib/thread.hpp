#ifndef __THREAD_H__
#define __THREAD_H__

#include <stdlib.h>
#include <sys/ksys.h>

namespace KolibriLib
{
    /// \brief Работа с потоками
    namespace Thread
    {

        /// \brief Создать поток
        /// \param ThreadEntry Имя функции которую нужно запустить в новом потоке
        /// @param ThreadStackSize Размер стека нового потока в байтах
        /// \return ID потока
<<<<<<< Updated upstream
        unsigned CreateThread(void *ThreadEntry, unsigned ThreadStackSize = 1024)
        {
            void* th_stack = malloc(ThreadStackSize);
            if (!th_stack) //    Если памяти не было выделенно
            {
                _ksys_debug_puts("Memory allocation error for thread!");
                return -1;
            }
            unsigned TID = _ksys_create_thread(ThreadEntry, th_stack + ThreadStackSize);
            if (TID == -1) //   Если поток небыл создан
            {
                _ksys_debug_puts("Unable to create a new thread!");
                return TID;
            }
            return TID;
        }
=======
        int CreateThread(void(*ThreadEntry)(void*), unsigned ThreadStackSize = 1024);
        
>>>>>>> Stashed changes

        /// @brief Завершить процесс/поток
        /// @param PID ID Процесса/потока
        /// @return true если успешно, инач false
        /// @paragraph Нельзя завершить поток операционной системы OS/IDLE (номер слота 1), можно завершить любой обычный поток/процесс
        bool TerminateThread(int PID);
    } // namespace Thread
    
} // namespace KolibriLib


#endif // __THREAD_H__