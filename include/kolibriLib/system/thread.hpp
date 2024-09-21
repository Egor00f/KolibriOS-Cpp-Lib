#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include <include_ksys.h>
#include <kolibriLib/debug.hpp>
#include <kolibriLib/input/keyboard.hpp>
#include <type_traits>

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
        /// @details Слоты нумеруются с 1.
        using Slot = std::uint16_t;

        /// @brief ID процесса
        using PID = int;

        /// @brief Информация о потоке
        union ThreadInfo
        {
            enum class SlotState : std::uint16_t
            {
                /// @brief поток выполняется
                Running = 0,

                /// @brief поток приостановлен
                Suspended = 1,

                /// @brief поток приостановлен в момент ожидания события
                SuspendedWaitEvent = 2,

                /// @brief поток завершается в результате вызова функции -1 или насильственно как следствие вызова подфункции 2 функции 18 или завершения работы системы
                Term = 3,

                /// @brief поток завершается в результате исключения
                ExeptionTerm = 4,

                /// @brief поток ожидает события
                Waitevent = 5,

                /// @brief запрошенный слот свободен, вся остальная информация о слоте не имеет смысла
                Free = 9
            };

            /// @brief Состояние окна
            /// @details Битовое поле
            enum class WindowStatus : std::uint8_t
            {
                /// @brief Окно маскимизированно
                Maximized = 1,

                /// @brief Окно минимизировано в панель задач
                Minimized = 2,

                /// @brief Окно свёрнуто в заголовок
                CollapsedToTitle = 4
            };

            struct
            {
                /// @brief Использование Процессора
                uint32_t cpu_usage;

                /// @brief Позиция окна в оконном стеке
                uint16_t pos_in_window_stack;

                /// @brief Слот окна
                Slot slot_num_window_stack;

                /// @brief Зарезервированно
                uint16_t __reserved1;

                /// @brief имя процесса
                /// @details имя запущенного файла - исполняемый файл без расширения
                char name[12];

                /// @brief адрес процесса в памяти
                uint32_t memstart;

                /// @brief размер используемой памяти 
                uint32_t memused;
                
                /// @brief идентификатор (PID/TID)
                PID pid;

                /// @brief Координата окна потока по оси x
                /// @note Если поток еще не определил свое окно вызовом функции 0, то положение и размеры этого окна полагаются нулями
                int winx_start;

                /// @note Если поток еще не определил свое окно вызовом функции 0, то положение и размеры этого окна полагаются нулями
                int winy_start;

                /// @note Если поток еще не определил свое окно вызовом функции 0, то положение и размеры этого окна полагаются нулями
                int winx_size;

                /// @note Если поток еще не определил свое окно вызовом функции 0, то положение и размеры этого окна полагаются нулями
                int winy_size;

                SlotState slot_state;           // thread slot state
                uint16_t __reserved2;           // reserved
                
                /// @brief координата начала клиентской областипо оси x 
                int clientx;

                /// @brief координата начала клиентской областипо оси y
                int clienty;

                /// @brief ширина клиентской области
                int clientwidth;

                /// @brief Длинна клиентской области
                int clientheight;

                /// @brief Состояние окна
                WindowStatus window_state;
                uint8_t event_mask;             // event mask

                /// @brief Режим ввода клавиатуры
                keyboard::InputMode key_input_mode;
            };

            uint8_t __reserved3[KSYS_THREAD_INFO_SIZE];

            ThreadInfo& operator=(const ThreadInfo&) = default;

            /// @brief 
            operator ksys_thread_t() const;
        };

        /// @brief Значение PID текущего процесса.
        /// @details Нужно для функций
        const PID ThisThread = KSYS_THIS_SLOT;

        /// \brief Создать поток
        /// \param ThreadEntry указатель на функцию которую нужно запустить в новом потоке
        /// @param ThreadStackSize Размер стека нового потока в байтах
        /// \return ID потока
        /// @note есть немалый шанс проебаться с размером стека
        PID CreateThread_(void *ThreadEntry, std::size_t ThreadStackSize = 4096);

        template <class T>
        /// \brief Создать поток
        /// \param ThreadEntry указатель на функцию которую нужно запустить в новом потоке
        /// @param ThreadStackSize Размер стека нового потока в байтах
        /// \return ID потока
        /// @note есть шанс проебаться с размером стека
        /// @note Пихать сюда ТОЛЬКО указатели на функции, иначе ваще хз че поизойдёт
        inline PID CreateThread(T ThreadEntry, std::size_t ThreadStackSize = 4096)
        {
            static_assert(::std::is_pointer<T>::value, "Only pointers to function!");
            return CreateThread_(reinterpret_cast<void*>(ThreadEntry), ThreadStackSize);
        }

        /// @brief Завершить процесс/поток
        /// @param PID ID Процесса/потока
        /// @return false если произошла ошибка
        /// @note Нельзя завершить поток операционной системы OS/IDLE (номер слота 1), можно завершить любой обычный поток/процесс
        inline bool TerminateThread(PID pid)
        {
            int ret;

            asm_inline (
                "int $0x40"
                : "=a"(ret)
                : "a"(18), "b"(18), "c"(pid));

            return ret;
        }

        inline bool TerminateThread()
        {
            _ksys_exit();
            return false; // 'no return statement in function returning non-void [-Wreturn-type]' очень бесит
        }

        
        /// @brief Поличть информацию о потоке
        /// @param thread слот потока
        /// @return информация о потоке
        /// @details по умолчанию возвращается информация о текущем потоке
        ThreadInfo GetThreadInfo(const Slot &thread = ThisThread);

        /// @brief Получить PID текущего процесса(тот в котором была вызваенна эта функция)
        /// @return PID текщего процесса
        inline PID GetThisThreadPID()
        {
            return GetThreadInfo().pid;
        }

        /// @brief Поличть указатель информацию о потоке
        /// @param thread слот потока
        /// @return указатель информация о потоке
        /// @details по умолчанию возвращается информация о текущем потоке
        /// @note Не забудьте освободить память!
        ThreadInfo *GetPointerThreadInfo(const Slot &thread = ThisThread);

        /// @brief Получить слот потока
        /// @param pid поток, по умолчанию поток который вызывает эту функцию
        /// @return Слот потока pid
        inline Slot GetThreadSlot(const PID& pid)
        {
            return _ksys_get_thread_slot(pid);
        }

        /// @brief Получить слот потока
        /// @return Слот потока pid
        inline Slot GetThreadSlot()
        {
            return GetThreadInfo().slot_num_window_stack;
        }

        /// @brief Кривой всратый и тупящий мьютекс, который существует только потому что я не разобрался в фьютексах
        /// @details Реально лучше не используйте это убожество. оно сильно тормозит систему
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