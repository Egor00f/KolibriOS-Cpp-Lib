#include <kolibriLib/filesystem/file_status.hpp>

using namespace KolibriLib;
using namespace filesystem;

file_type KolibriLib::filesystem::file_status::type() const noexcept
{
	return _type;
}

void KolibriLib::filesystem::file_status::type(filesystem::file_type type) noexcept
{
	_type = type;
}