#ifndef __FILESYSTEM_TYPES_HPP__
#define __FILESYSTEM_TYPES_HPP__

#include <sys/ksys.h>

namespace KolibriLib
{

	class Time
	{
	public:
		virtual ~Time() = default;

		virtual uint8_t sec() const;
		virtual void sec(uint8_t NewSec);

		virtual uint8_t min() const;
		virtual void min(uint8_t NewMin);

		virtual uint8_t hour() const;
		virtual void hour(uint8_t NewHour);
	};


	/// @brief Время
	class Time_bcd : public Time
	{
	public:
		uint8_t sec() const override;
		void sec(uint8_t NewSec) override;

		uint8_t min() const override;
		void min(uint8_t NewMin) override;

		uint8_t hour() const override;
		void hour(uint8_t NewHour) override;

	private:
		ksys_time_bcd_t time;
	};

	/// @brief Дата
	class Date
	{
	public:

	private:
		ksys_date_bcd_t date;
	};

	/// @brief Время для файлов
	class FileTime : public Time
	{
	public:
		FileTime() = default;
		FileTime(ksys_ftime_t t);
		FileTime(const FileTime &f) = default;
		~FileTime() = default;

		/// @brief
		/// @param b
		/// @return
		bool operator==(const FileTime &b) const;
		bool operator<(const FileTime &b) const;
		bool operator>(const FileTime &b) const;

		operator ksys_ftime_t() const;

		FileTime& operator=(const FileTime &b) = default;
		FileTime& operator+=(const FileTime &b);

		uint8_t sec() const override;
		void sec(uint8_t NewSec) override;

		uint8_t min() const override;
		void min(uint8_t NewMin) override;

		uint8_t hour() const override;
		void hour(uint8_t NewHour) override;

		void swap(FileTime &b);

	private:
		ksys_ftime_t time;
	};

	/// @brief Дата для файлов
	class FileDate
	{
	public:
		FileDate() {}
		FileDate(ksys_fdate_t t);
		FileDate(const FileDate &f) = default;
		~FileDate() = default;

		/// @brief
		/// @param b
		/// @return
		bool operator==(const FileDate &b) const;
		bool operator<(const FileDate &b) const;
		bool operator>(const FileDate &b) const;

		operator ksys_fdate_t() const;

		FileDate& operator=(const FileDate &b);
		FileDate& operator+=(const FileDate &b);
		FileDate &operator-=(const FileDate &b);
		FileDate operator+(const FileDate &b);
		FileDate& operator-(const FileDate &b);

		void swap(FileTime &b);

	private:
		ksys_fdate_t date;
	};

	class FileTimeAndDate: public Time
	{
	public:
		FileTimeAndDate() = default;
		FileTimeAndDate(const FileTimeAndDate& c) = default;
		FileTimeAndDate(const FileTime &time);
		FileTimeAndDate(const FileDate &date);
		FileTimeAndDate(const FileTime &time, const FileDate &date);
		~FileTimeAndDate() = default;

		bool operator==(const FileTime &b) const;
		bool operator<(const FileTime &b) const;
		bool operator>(const FileTime &b) const;

		operator ksys_ftime_t() const;

		FileTimeAndDate &operator=(const FileTimeAndDate &b) = default;
		FileTimeAndDate &operator+=(const FileTimeAndDate &b);
		FileTimeAndDate &operator=(const FileTime &b);
		FileTimeAndDate &operator+=(const FileTime &b);

		uint8_t sec() const override;
		void sec(uint8_t NewSec) override;

		uint8_t min() const override;
		void min(uint8_t NewMin) override;

		uint8_t hour() const override;
		void hour(uint8_t NewHour) override;

		void swap(FileTimeAndDate &b);

	private:
		FileTime _time;
		FileDate _date;
	};
	
	
	
} // namespace KolibriLib



#endif
