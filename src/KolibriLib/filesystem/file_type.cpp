#include <kolibriLib/system/filesystem/file_status.hpp>

using namespace KolibriLib;
using namespace filesystem;

file_type KolibriLib::filesystem::file_status::type() const noexcept
{
	return _type;
}