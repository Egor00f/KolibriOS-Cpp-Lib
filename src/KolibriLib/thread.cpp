#include <kolibriLib/system/thread.hpp>
#include <cstdlib>

using namespace KolibriLib;
using namespace Thread;

PID KolibriLib::Thread::CreateThread_(void *ThreadEntry, unsigned ThreadStackSize)
{
    void *th_stack = std::malloc(ThreadStackSize);

    if (!th_stack) //    Если памяти не было выделенно
    {
        PrintDebug("Memory allocation error for thread!\n");
        return -1;
    }

    PID TID = _ksys_create_thread(ThreadEntry, ((uint8_t*) th_stack) + ThreadStackSize);

    if (TID == -1) //   Если поток не был создан
    {
        PrintDebug("Unable to create a new thread!\n");
    }

    return TID;
}

KolibriLib::Thread::ThreadInfo KolibriLib::Thread::GetThreadInfo(const Slot& thread)
{
    ThreadInfo ret;

    _ksys_thread_info((ksys_thread_t*)&ret, thread);

    return ret;
}

KolibriLib::Thread::ThreadInfo* KolibriLib::Thread::GetPointerThreadInfo(const Slot& thread)
{
    ThreadInfo *buff = new ThreadInfo;

    _ksys_thread_info((ksys_thread_t*)buff, thread);

    return buff; 
}




KolibriLib::Thread::ThreadInfo::operator ksys_thread_t() const
{
    return *this;
}