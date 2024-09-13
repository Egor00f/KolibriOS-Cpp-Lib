#include <kolibriLib/time.hpp>

using namespace KolibriLib;

std::tm KolibriLib::to_tm(ksys_ftime_t t, ksys_fdate_t d)
{
	std::tm ret;

	ret.tm_hour	= t.hour;
	ret.tm_min	= t.min;
	ret.tm_sec	= t.sec;

	ret.tm_mday	= d.day;
	ret.tm_mon	= d.month;
	ret.tm_year	= d.year;

	return ret;
}

std::tm KolibriLib::to_tm(ksys_time_bcd_t t, ksys_date_bcd_t d)
{
	std::tm ret;

	ret.tm_hour	= t.hour;
	ret.tm_min	= t.min;
	ret.tm_sec	= t.sec;

	ret.tm_mday	= d.day;
	ret.tm_mon	= d.month;
	ret.tm_year	= d.year;

	return ret;
}