#include <kolibriLib/system/thread.hpp>

using namespace KolibriLib;
using namespace Thread;

PID KolibriLib::Thread::CreateThread(void(* ThreadEntry)(void *), unsigned ThreadStackSize)
{
    void *th_stack = malloc(ThreadStackSize);
    if (!th_stack) //    Если памяти не было выделенно
    {
        _ksys_debug_puts("Memory allocation error for thread!");
        return -1;
    }
    int TID = _ksys_create_thread((void*)ThreadEntry, th_stack + ThreadStackSize);
    if (TID == -1) //   Если поток не был создан
    {
        _ksys_debug_puts("Unable to create a new thread!");
        return TID;
    }
    return TID;
}



KolibriLib::Thread::ThreadInfo KolibriLib::Thread::GetThreadInfo(const Slot& thread)
{
    ThreadInfo *buff = new ThreadInfo;

    _ksys_thread_info(buff, thread);

    ThreadInfo r = *buff;

    for (int i = 0; i < KSYS_THREAD_INFO_SIZE; i++)
    {
        r.__reserved3[i] = buff->__reserved3[i];
    }

    free(buff); // Возвращается копия так как указатель нужно будет удалять
                //  но в какой то момент точно об этом забудешь...

    return r;
}
