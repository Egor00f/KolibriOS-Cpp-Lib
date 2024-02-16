#include "filesystem.hpp"

using namespace KolibriLib;
using namespace filesystem;


Path::Path(std::string path)
{
    _string = path;
}

const char *Path::GetChars() const
{
    return _string.c_str();
}

std::string KolibriLib::filesystem::Path::GetString() const
{
    return _string;
}

Path &Path::operator/(const Path &a)
{
    _string += a._string;

    return *this;
}

Path &KolibriLib::filesystem::Path::operator/(const std::string &a)
{
    _string += a;
    return *this;
}

Path &KolibriLib::filesystem::Path::operator=(const Path &a)
{
    _string = a._string;
    return *this;
}

Path &KolibriLib::filesystem::Path::operator=(const std::string &a)
{
    _string = a;
    return *this;
}

bool KolibriLib::filesystem::Path::operator==(const Path &a) const
{
    return _string == a._string;
}

bool KolibriLib::filesystem::Path::operator!=(const Path &a) const
{
    return _string != a._string;
}

bool KolibriLib::filesystem::Path::operator==(const std::string &a) const
{
    return _string == a;
}

bool KolibriLib::filesystem::Path::operator!=(const std::string &a) const
{
    return _string != a;
}

int KolibriLib::filesystem::CreateFile(const Path &name)
{
    return _ksys_file_create(name.GetChars());
}

int KolibriLib::filesystem::Delete(const Path &name)
{
    return _ksys_file_delete(name.GetChars());
}

int KolibriLib::filesystem::MakeDirectory(const Path &path)
{
    return _ksys_mkdir(path.GetChars());
}

bool KolibriLib::filesystem::Exist(const Path &Path)
{
    ksys_bdfe_t *buff;
    if (_ksys_file_info(Path.GetChars(), buff) > 0)
    {
        return true;
    }
    return false;
}

int KolibriLib::filesystem::Rename(const Path &OldName, const Path &NewName)
{
    return _ksys_file_rename(OldName.GetChars(), NewName.GetChars());
}