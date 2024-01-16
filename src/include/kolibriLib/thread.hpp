#ifndef __THREAD_H__
#define __THREAD_H__

#include <stdio.h>
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
        /// @paragraph Сколько нужно выделять памяти для стека потока? Я не знаю
        unsigned CreateThread(void *ThreadEntry, unsigned ThreadStackSize = 2048)
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

        /// @brief Завершить процесс/поток
        /// @param PID ID Процесса/потока
        /// @return true если успешно, иначе false
        /// @paragraph Нельзя завершить поток операционной системы OS/IDLE (номер слота 1), можно завершить любой обычный поток/процесс
        bool TerminateThread(int PID)
        {
            int a;
            asm_inline(
                "int $0x40"
                :"=a"(a)
                :"a"(18), "b"(18), "c"(PID)
            );
            return !a;
        }

        /*Потом когданибудь это быдет доделанно
        template <class BuffType>
        class futex
        {
        private:
            uint32_t _discriptor;
            BuffType buffer;
        public:
            futex();
            ~futex();
            BuffType GetBuffer();
            void SetBuffer(BuffType buff);
        };
        
        futex::futex()
        {
            void *a = malloc(4);
            asm_inline(
                "int $0x40"
                :"=a"(_discriptor)
                :"a"(77), "b"(0)
            );
            free(a);
        }
        
        futex::~futex()
        {
            int a;
            asm_inline(
                "int $0x40"
                :"=a"(a)
                :"a"(77), "b"(1)
            );
        }*/
        
    } // namespace Thread
    
} // namespace KolibriLib


#endif // __THREAD_H__