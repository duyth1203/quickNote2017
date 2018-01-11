#pragma once

#include <iostream>
#include <string>
#include "convertor.h"

using namespace std;

class datetime
{
private:
	unsigned char second;
	unsigned char minute;
	unsigned char hour;
	unsigned char day;
	unsigned char month;
	unsigned char year;
public:
	datetime();
	~datetime();

	unsigned char getSecond();
	unsigned char getMinute();
	unsigned char getHour();
	unsigned char getDay();
	unsigned char getMonth();
	unsigned char getYear();

	void setSecond(const unsigned char & sc);
	void setMinute(const unsigned char & mi);
	void setHour(const unsigned char & hr);
	void setDay(const unsigned char & dd);
	void setMonth(const unsigned char & mm);
	void setYear(const unsigned char & yyyy);

	bool operator>(datetime dt);
	bool operator>=(datetime dt);
	bool operator<(datetime dt);
	bool operator<=(datetime dt);
	bool operator==(datetime dt);
	datetime & operator=(datetime dt);

	// format of datetime: yyyy-mm-dd,hr:mi:sc
	friend wistream & operator>>(wistream & wis, datetime & dt);
	friend wostream & operator<<(wostream & wos, datetime dt);
};