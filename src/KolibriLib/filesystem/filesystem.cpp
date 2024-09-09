#include <kolibriLib/system/filesystem/filesystem.hpp>
#include <stdio.h>
#include <kolibriLib/time.hpp>

using namespace KolibriLib;

KolibriLib::filesystem::Path::Path(const std::string &path)
{
    _string = path;
}

KolibriLib::filesystem::Path::Path(const char *path)
{
    _string = std::string(path);
}

KolibriLib::filesystem::Path &KolibriLib::filesystem::Path::operator/(const KolibriLib::filesystem::Path &a)
{
    _string += a._string;

    return *this;
}

filesystem::Path &KolibriLib::filesystem::Path::operator/(const std::string &a)
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

std::size_t KolibriLib::filesystem::Path::length() const
{
    return _string.length();
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

KolibriLib::filesystem::Path::operator std::string() const
{
    return _string;
}

KolibriLib::filesystem::Path::operator const char*() const
{
    return _string.c_str();
}

filesystem::filesystem_error &KolibriLib::filesystem::filesystem_error::operator=(const filesystem_error &other)
{
    _code = other._code;
    return *this;
}

filesystem::filesystem_error &KolibriLib::filesystem::filesystem_error::operator=(const int &other)
{
    _code = other;
    return *this;
}

const int &KolibriLib::filesystem::filesystem_error::code() const
{
    return _code;
}

KolibriLib::filesystem::directory_entry::directory_entry(const filesystem::path &p, filesystem::FilesystemErrors &ec)
    :   _path(p)
{
    refresh(ec);
}

void KolibriLib::filesystem::directory_entry::assign(const filesystem::path &p, filesystem::FilesystemErrors &ec)
{
    _path = p;
    refresh(ec);
}

void KolibriLib::filesystem::directory_entry::refresh(filesystem::FilesystemErrors &ec) noexcept
{
    _last_mod_time = filesystem::last_write_time(_path, ec);
    if(ec != FilesystemErrors::Successfully)
        goto epic_fail;
    file_size = filesystem::file_size(_path, ec);
    if (ec != FilesystemErrors::Successfully)
        goto epic_fail;

epic_fail:
    return;
}



std::uintmax_t KolibriLib::filesystem::file_size(const Path &p)
{

    filesystem::FilesystemErrors ec;

    std::uintmax_t ret = filesystem::file_size(p, ec);

    if (ec != FilesystemErrors::Successfully)
        throw ec;

    return ret;
}

std::uintmax_t KolibriLib::filesystem::file_size(const Path &p, filesystem::FilesystemErrors &ec) noexcept
{
    int err;
    std::uintmax_t size = _ksys_file_get_size(p, &err);

    ec = (filesystem::FilesystemErrors)err;

    if (ec != FilesystemErrors::Successfully)
    {
        return static_cast<std::uintmax_t>(-1);
    }
    else
    {
        return size;
    }
}

void KolibriLib::filesystem::resize_file(const path &p, std::uintmax_t new_size)
{
    filesystem::FilesystemErrors ec;

    resize_file(p, new_size, ec);

    if (ec != FilesystemErrors::Successfully)
        throw ec;
}

void KolibriLib::filesystem::resize_file(const filesystem::path &p, std::uintmax_t new_size, filesystem::FilesystemErrors &ec) noexcept
{
    ec = (filesystem::FilesystemErrors)_ksys_file_set_size(p, new_size);
}

bool KolibriLib::filesystem::exists(const Path &p)
{
    filesystem::FilesystemErrors ec;

    bool ret = KolibriLib::filesystem::exists(p, ec);

    if (ec != filesystem::FilesystemErrors::Successfully)
        throw ec;

    return ret;
}

bool KolibriLib::filesystem::exists(const filesystem::path &p, filesystem::FilesystemErrors &ec) noexcept
{
    ksys_file_info_t *buff = new ksys_file_info_t;

    ec = static_cast<filesystem::FilesystemErrors>(_ksys_file_info(p, buff));

    delete buff;

    return static_cast<bool>(ec);
}


bool KolibriLib::filesystem::copy_file(const filesystem::path &from, const filesystem::path &to)
{
    return filesystem::copy_file(from, to, filesystem::copy_options::none);
}

bool KolibriLib::filesystem::copy_file(const filesystem::path &from, const filesystem::path &to, filesystem::copy_options options)
{
    filesystem::FilesystemErrors ec;

    bool ret = filesystem::copy_file(from, to, options, ec);

    if (ec != FilesystemErrors::Successfully)
        throw ec;

    return ret;
}

bool KolibriLib::filesystem::copy_file(const filesystem::path &from, const filesystem::path &to, filesystem::copy_options options, filesystem::FilesystemErrors &ec)
{
    if(from == to)
        return false;

    size_t file_size = 0;

    const size_t BLOCK_SIZE = 256;

    unsigned char buffer[BLOCK_SIZE];

    FILE *fin = NULL;
    FILE *fout = NULL;

    if ((fin = fopen(from, "rb")) == NULL )
    {
        ec = filesystem::FilesystemErrors::NotFound;
    }

    if ((fout = fopen(to, "wb")) == NULL)
    {
        throw;
    }

    fseek(fin, 0, SEEK_END);
    file_size = ftell(fin);
    rewind(fin);

    size_t i = 0;

    for (i = 0; i < file_size / BLOCK_SIZE; ++i)
    {
        if (fread(buffer, sizeof(unsigned char), BLOCK_SIZE, fin) != BLOCK_SIZE)
        {
            throw;
        }
        if (fwrite(buffer, sizeof(unsigned char), BLOCK_SIZE, fout) != BLOCK_SIZE)
        {
            throw;
        }
    }

    if ((file_size %= BLOCK_SIZE))
    {
        if (fread(buffer, sizeof(unsigned char), file_size, fin) != file_size)
        {
            throw;
        }
        if (fwrite(buffer, sizeof(unsigned char), file_size, fout) != file_size)
        {
            throw;
        }
    }

    fclose(fin);
    fclose(fout);

epic_fail:
    return 1;
}

void filesystem::rename(const filesystem::path &old_p, const filesystem::path &new_p)
{
    filesystem::FilesystemErrors ec;
    filesystem::rename(old_p, new_p, ec);

    if (ec != FilesystemErrors::Successfully)
        throw ec;
}

void filesystem::rename(const filesystem::path &old_p, const filesystem::path &new_p, filesystem::FilesystemErrors &ec) noexcept
{
    ec = (FilesystemErrors)_ksys_file_rename(old_p, new_p);
}

bool filesystem::is_directory(filesystem::file_status s) noexcept
{
    return s.type() == filesystem::file_type::directory;
}

bool filesystem::is_directory(const filesystem::path &p)
{
    filesystem::FilesystemErrors ec;
    bool ret = filesystem::is_directory(p, ec);

    if (ec != FilesystemErrors::Successfully)
        throw ec;
    
    return ret;
}

bool filesystem::is_directory(const filesystem::path &p, filesystem::FilesystemErrors &ec) noexcept
{
    ksys_file_info_t ret;
    ec = (filesystem::FilesystemErrors)_ksys_file_info(p, &ret);

    return ret.attr & (unsigned)filesystem::AttributeMasks::Dir;
}

filesystem::file_time_type KolibriLib::filesystem::last_write_time(const filesystem::path &p, filesystem::FilesystemErrors &ec) noexcept
{
    ksys_file_info_t info;
    ec = (filesystem::FilesystemErrors)_ksys_file_info(p, &info);

    return to_tm(info.mtime, info.mdate);
}

filesystem::file_time_type KolibriLib::filesystem::last_write_time(const filesystem::path &p)
{
    filesystem::FilesystemErrors ec;
    KolibriLib::filesystem::file_time_type ret = last_write_time(p, ec);

    if (ec != FilesystemErrors::Successfully)
        throw ec;

    return ret;
}

filesystem::file_time_type KolibriLib::filesystem::create_time(const filesystem::path &p, filesystem::FilesystemErrors &ec) noexcept
{
    ksys_file_info_t info;
    ec = (filesystem::FilesystemErrors)_ksys_file_info(p, &info);

    return to_tm(info.ctime, info.cdate);
}

filesystem::file_time_type KolibriLib::filesystem::create_time(const filesystem::path &p)
{
    filesystem::FilesystemErrors ec;
    KolibriLib::filesystem::file_time_type ret = create_time(p, ec);

    if (ec != FilesystemErrors::Successfully)
        throw ec;

    return ret;
}

filesystem::file_time_type KolibriLib::filesystem::last_acess_time(const filesystem::path &p, filesystem::FilesystemErrors &ec) noexcept
{
    ksys_file_info_t info;
    ec = (filesystem::FilesystemErrors)_ksys_file_info(p, &info);

    return to_tm(info.atime, info.adate);
}

filesystem::file_time_type KolibriLib::filesystem::last_acess_time(const filesystem::path &p)
{
    filesystem::FilesystemErrors ec;
    KolibriLib::filesystem::file_time_type ret = last_acess_time(p, ec);

    if (ec != FilesystemErrors::Successfully)
        throw ec;

    return ret;
}

KolibriLib::filesystem::AttributeMasks KolibriLib::filesystem::get_attr(const KolibriLib::filesystem::path &p)
{
    filesystem::FilesystemErrors ec;
    KolibriLib::filesystem::AttributeMasks ret = get_attr(p, ec);

    if (ec != FilesystemErrors::Successfully)
        throw ec;

    return ret;
}

KolibriLib::filesystem::AttributeMasks KolibriLib::filesystem::get_attr(const KolibriLib::filesystem::path &p, KolibriLib::filesystem::FilesystemErrors &ec)
{
    ksys_file_info_t info;
    ec = (filesystem::FilesystemErrors) _ksys_file_info(p, &info);

    return (KolibriLib::filesystem::AttributeMasks)info.attr;
}

void KolibriLib::filesystem::delete_file(const path &p, FilesystemErrors &ec)
{
    ec = (KolibriLib::filesystem::FilesystemErrors)_ksys_file_delete(p);
}

void KolibriLib::filesystem::delete_file(const path &p)
{
    filesystem::FilesystemErrors ec;
    delete_file(p, ec);

    if (ec != FilesystemErrors::Successfully)
        throw ec;
}