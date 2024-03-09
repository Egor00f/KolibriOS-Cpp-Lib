#include <kolibriLib/system/filesystem.hpp>

using namespace KolibriLib;
using namespace filesystem;

KolibriLib::filesystem::Path::Path(const std::string &path)
{
    _string = path;
}

const char *KolibriLib::filesystem::Path::GetChars() const
{
    return _string.c_str();
}

const std::string &KolibriLib::filesystem::Path::GetString() const
{
    return _string;
}

KolibriLib::filesystem::Path &KolibriLib::filesystem::Path::operator/(const KolibriLib::filesystem::Path &a)
{
    _string += a._string;

    return *this;
}

Path &KolibriLib::filesystem::Path::operator/(const std::string &a)
{
    _string += a;
    return *this;
}

KolibriLib::filesystem::Path &KolibriLib::filesystem::Path::operator+(const KolibriLib::filesystem::Path &a)
{
    _string += a._string;

    return *this;
}

KolibriLib::filesystem::Path &KolibriLib::filesystem::Path::operator+(const std::string &a)
{
    _string += a;
    return *this;
}

KolibriLib::filesystem::Path &KolibriLib::filesystem::Path::operator=(const KolibriLib::filesystem::Path &a)
{
    _string = a._string;
    return *this;
}

KolibriLib::filesystem::Path &KolibriLib::filesystem::Path::operator=(const std::string &a)
{
    _string = a;
    return *this;
}

bool KolibriLib::filesystem::Path::operator==(const KolibriLib::filesystem::Path &a) const
{
    return _string == a._string;
}

bool KolibriLib::filesystem::Path::operator!=(const KolibriLib::filesystem::Path &a) const
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
