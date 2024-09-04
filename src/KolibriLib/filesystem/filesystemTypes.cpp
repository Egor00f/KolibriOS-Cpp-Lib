#include <kolibriLib/system/filesystem/types.hpp>

using namespace KolibriLib;

KolibriLib::FileTime::FileTime(ksys_ftime_t t)
	:	time(t)
{
}

bool KolibriLib::FileTime::operator==(const FileTime &b) const
{
	return time.hour == b.time.hour &&
		   time.min == b.time.min &&
		   time.sec == b.time.sec;
}

inline bool KolibriLib::FileTime::operator<(const FileTime &b) const
{
	return time.hour < b.time.hour	||
	       (time.hour == b.time.hour && 
		   	(time.min < b.time.min	|| ( time.min == b.time.min && time.sec < b.time.sec)));
}

bool KolibriLib::FileTime::operator>(const FileTime &b) const
{
	return time.hour > b.time.hour	||
	       (time.hour == b.time.hour && 
		   	(time.min > b.time.min	|| ( time.min == b.time.min && time.sec > b.time.sec)));
}

FileTime& KolibriLib::FileTime::operator+=(const FileTime &b)
{

}

void KolibriLib::FileTime::swap(FileTime &b)
{
	FileTime tmp(*this);

	*this = b;

	b = tmp;
}