#ifndef __THREAD_H__
#define __THREAD_H__

#include <stdlib.h>
#include <sys/ksys.h>
#include <kolibriLib/debug.hpp>

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

        /// @brief Значение PID текущего процесса.
        ///@details Нужно для функций
        const PID ThisThread = -1;

        /// \brief Создать поток
        /// \param ThreadEntry указатель на функцию которую нужно запустить в новом потоке
        /// @param ThreadStackSize Размер стека нового потока в байтах
        /// \return ID потока
        /// @note есть шанс проебаться с размером стека
        PID CreateThread_(void *ThreadEntry, unsigned ThreadStackSize = 2048);

        template <class T>
        /// \brief Создать поток
        /// \param ThreadEntry указатель на функцию которую нужно запустить в новом потоке
        /// @param ThreadStackSize Размер стека нового потока в байтах
        /// \return ID потока
        /// @note есть шанс проебаться с размером стека
        /// @note Пихать сюда ТОЛЬКО указатели на функции, иначе ваще хз че поизойдёт
        inline PID CreateThread(T ThreadEntry, unsigned ThreadStackSize = 2048)
        {
            return CreateThread_((void*)ThreadEntry, ThreadStackSize);
        }

        /// @brief Завершить процесс/поток
        /// @param PID ID Процесса/потока
        /// @return true если успешно, иначе false
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

        /// @brief Поличть информацию о потоке
        /// @param thread слот потока
        /// @return информация о потоке
        /// @details по умолчанию возвращается информация о текущем потоке
        ThreadInfo GetThreadInfo(const Slot &thread = ThisThread);

        /// @brief Поличть указатель информацию о потоке
        /// @param thread слот потока
        /// @return указатель информация о потоке
        /// @details по умолчанию возвращается информация о текущем потоке
        /// @note Не забудьте освободить память!
        ThreadInfo *GetPointerThreadInfo(const Slot &thread = ThisThread);

        /// @brief Получить PID текущего процесса(тот в котором была вызваенна эта функция)
        /// @return PID текщего процесса
        inline PID GetThisThreadPID()
        {
            return GetThreadInfo().pid;
        }

        /// @brief Получить слот потока
        /// @param pid поток, по умолчанию поток который вызывает эту функцию
        /// @return Слот потока pid
        inline Slot GetThreadSlot(const PID& pid = GetThisThreadPID())
        {
            return _ksys_get_thread_slot(pid);
        }

        /// @brief Кривой косячный и тупящий мьютекс, который существует только потому что я не разобрался в фьютексах
        /// @details Реально лучше не используйте это убожество.
        /// @details использует подфункцию 1 функции 68
        class Mutex
        {
        public:
            void lock()
            {
                _locked = true;
            }
            void unlock()
            {
                _locked = false;
            }
            void waitPoint()
            {
                while(_locked)
                {
                    Wait();
                }
            }
        private:
            bool _locked = false;
        };

    } // namespace Thread
    
} // namespace KolibriLib


#endif // __THREAD_H__