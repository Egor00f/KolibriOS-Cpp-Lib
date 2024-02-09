#include "thread.hpp"



int KolibriLib::Thread::CreateThread(void(* ThreadEntry)(void *), unsigned ThreadStackSize)
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

bool KolibriLib::Thread::TerminateThread(int PID)
{
    int a;
    asm_inline(
        "int $0x40"
        : "=a"(a)
        : "a"(18), "b"(18), "c"(PID));
    return !a;
}
