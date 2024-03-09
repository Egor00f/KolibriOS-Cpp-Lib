#ifndef __THREAD_H__
#define __THREAD_H__

#include <stdlib.h>
#include <sys/ksys.h>

namespace KolibriLib
{
    /// \brief Подождать
    /// \param time время задержки(в 1/100 секунды)
    inline void Wait(int time)
    {
        _ksys_delay(time);
    }

    /// \brief Подождать, минимальное кол-во времени
    /// @paragraph Функция передаёт управление другим процессам
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
        /// @paragraph Используйте лучше std::thread, а не эту функцию, а то я вот вообще незнаю сколько размер стека сделать
        PID CreateThread(void(*ThreadEntry)(void*), unsigned ThreadStackSize = 2048)
        {
            void *th_stack = malloc(ThreadStackSize);
            if (!th_stack) //    Если памяти не было выделенно
            {
                _ksys_debug_puts("Memory allocation error for thread!");
                return -1;
            }
            int TID = _ksys_create_thread((void *)ThreadEntry, th_stack + ThreadStackSize);
            if (TID == -1) //   Если поток не был создан
            {
                _ksys_debug_puts("Unable to create a new thread!");
                return TID;
            }
            return TID;
        }

        /// @brief Завершить процесс/поток
        /// @param PID ID Процесса/потока
        /// @return true если успешно, инач false
        /// @paragraph Нельзя завершить поток операционной системы OS/IDLE (номер слота 1), можно завершить любой обычный поток/процесс
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
        Slot GetThreadSlot(const PID& pid)
        {
            return _ksys_get_thread_slot(pid);
        }

        /// @brief Поличть информацию о потоке
        /// @param thread слот потока
        /// @return информация о потоке
        /// @paragraph если слот -1 то возвращается информация о текущем потоке
        ThreadInfo GetThreadInfo(const Slot &thread)
        {
            ThreadInfo *buff = new ThreadInfo;

            _ksys_thread_info(buff, thread);

            ThreadInfo r = *buff;

            for (int i = 0; i < KSYS_THREAD_INFO_SIZE; i++)
            {
                r.__reserved3[i] = buff->__reserved3[i];
            }

            free(buff); //Возвращается копия так как указатель нужно будет удалять
                        // но в какой то момент точно об этом забудешь...

            return r;
        }

    } // namespace Thread
    
} // namespace KolibriLib


#endif // __THREAD_H__