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

KolibriLib::Time::operator std::tm() const
{
	std::tm ret;

	ret.tm_hour = hour();
	ret.tm_min = min();
	ret.tm_sec = sec();

	return ret;
}

KolibriLib::Time::operator std::time_t() const
{
	std::tm r = this->operator std::tm();
	return std::mktime(&r);
}

KolibriLib::FileTimeAndDate::FileTimeAndDate(ksys_ftime_t time, ksys_fdate_t date)
	:	_time(time),
		_date(date)
{
}