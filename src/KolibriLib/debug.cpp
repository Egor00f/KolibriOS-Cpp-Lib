#include <kolibriLib/debug.hpp>
#include <cstdio>


#ifdef DEBUG

#include <kolibriLib/system/thread.hpp>
#include <kolibriLib/filesystem/filesystem.hpp>

using namespace KolibriLib;

microlog::logger KolibriLib::logger(filesystem::temp_directory_path()/ std::string(Thread::GetThreadInfo().name + "-debug.log"));

#endif