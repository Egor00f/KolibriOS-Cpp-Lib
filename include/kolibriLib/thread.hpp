#ifndef __THREAD_H__
#define __THREAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/ksys.h>

namespace KolibriLib
{
    namespace Thread
    {
        const unsigned ThreadStackSize = 1024;


        /// @brief Создать поток
        /// @param ThreadEntry Просто напиши сюда имя функции которую нужно запустить в новом потоке
        /// @return tid потока
        unsigned CreateThread(void* ThreadEntry)
        {
            void* th_stack = malloc(ThreadStackSize);
            if (!th_stack) //    Если памяти не было выделенно
            {
                _ksys_debug_puts("Memory allocation error for thread!");
                return -1;
            }
            unsigned tid = _ksys_create_thread(ThreadEntry, th_stack + ThreadStackSize);
            if (tid == -1) //   Если поток небыл создан
            {
                _ksys_debug_puts("Unable to create a new thread!");
                return tid;
            }
            return tid;
        }
    } // namespace Thread
    
} // namespace KolibriLib


#endif // __THREAD_H__