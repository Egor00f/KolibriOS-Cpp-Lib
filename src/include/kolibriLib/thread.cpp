#include "thread.hpp"

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

bool KolibriLib::Thread::TerminateThread(PID pid)
{
    int a;
    asm_inline(
        "int $0x40"
        : "=a"(a)
        : "a"(18), "b"(18), "c"(pid));
    return !a;
}

Slot KolibriLib::Thread::GetThreadSlot(PID pid)
{
    return _ksys_get_thread_slot(pid);
}

KolibriLib::Thread::ThreadInfo KolibriLib::Thread::GetThreadInfo(Slot thread)
{
    ThreadInfo *buff = (ThreadInfo *)malloc(sizeof(ThreadInfo));

    _ksys_thread_info((ksys_thread_t*)buff, thread);

    ThreadInfo r = *buff;

    free(buff);

    return r;
}

ThreadInfo &KolibriLib::Thread::ThreadInfo::operator=(const ksys_thread_t &a)
{
    for(int i = 0; i < KSYS_THREAD_INFO_SIZE; i++)
    {
        __reserved3[i] = a.__reserved3[i];
    }
    return *this;
}
