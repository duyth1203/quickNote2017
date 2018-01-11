#include "stdafx.h"
#include "datetime.h"

datetime::datetime()
{
	this->setSecond(0);
	this->setMinute(0);
	this->setHour(0);
	this->setDay(1);
	this->setMonth(1);
	this->setYear(1753);
}

datetime::~datetime()
{
}

unsigned char datetime::getSecond()
{
	return this->second;
}

unsigned char datetime::getMinute()
{
	return this->minute;
}

unsigned char datetime::getHour()
{
	return this->hour;
}

unsigned char datetime::getDay()
{
	return this->day;
}

unsigned char datetime::getMonth()
{
	return this->month;
}

unsigned char datetime::getYear()
{
	return this->year;
}

void datetime::setSecond(const unsigned char & sc)
{
	this->second = sc;
}

void datetime::setMinute(const unsigned char & mi)
{
	this->minute = mi;
}

void datetime::setHour(const unsigned char & hr)
{
	this->hour = hr;
}

void datetime::setDay(const unsigned char & dd)
{
	this->day = dd;
}

void datetime::setMonth(const unsigned char & mm)
{
	this->month = mm;
}

void datetime::setYear(const unsigned char & yyyy)
{
	this->year = yyyy;
}

bool datetime::operator>(datetime dt)
{
	return (this->getYear() > dt.getYear()
		|| (this->getYear() == dt.getYear() && (this->getMonth() > dt.getMonth()
			|| (this->getMonth() == dt.getMonth() && this->getDay() > dt.getDay()
				|| (this->getDay() == dt.getDay() && this->getHour() > dt.getHour()
					|| (this->getHour() == dt.getHour() && this->getMinute() > dt.getMinute()
						|| (this->getMinute() == dt.getMinute() && this->getSecond() > dt.getSecond())))))));
}

bool datetime::operator>=(datetime dt)
{
	return (*this > dt || *this == dt);
}

bool datetime::operator<(datetime dt)
{
	return (this->getYear() < dt.getYear()
		|| (this->getYear() == dt.getYear() && (this->getMonth() < dt.getMonth()
			|| (this->getMonth() == dt.getMonth() && this->getDay() < dt.getDay()
				|| (this->getDay() == dt.getDay() && this->getHour() < dt.getHour()
					|| (this->getHour() == dt.getHour() && this->getMinute() < dt.getMinute()
						|| (this->getMinute() == dt.getMinute() && this->getSecond() < dt.getSecond())))))));
}

bool datetime::operator<=(datetime dt)
{
	return (*this < dt || *this == dt);
}

bool datetime::operator==(datetime dt)
{
	return (this->getYear() == dt.getYear()
		&& this->getMonth() == dt.getMonth()
		&& this->getDay() == dt.getDay()
		&& this->getHour() == dt.getHour()
		&& this->getMinute() == dt.getMinute()
		&& this->getSecond() == dt.getSecond());
}

datetime & datetime::operator=(datetime dt)
{
	this->setYear(dt.getYear());
	this->setMonth(dt.getMonth());
	this->setDay(dt.getDay());
	this->setHour(dt.getHour());
	this->setMinute(dt.getMinute());
	this->setSecond(dt.getSecond());
}

wistream & operator>>(wistream & wis, datetime & dt)
{
	wstring wsTmp = L"";
	wis >> wsTmp;

	dt.setYear(stoi(wsTmp.substr(0, 4))); // 4 == lengthOf("yyyy")
	dt.setMonth(stoi(wsTmp.substr(wsTmp.find_first_of(L"-") + 1, 2))); // 2 == lengthOf("mm")
	dt.setDay(stoi(wsTmp.substr(wsTmp.find_last_of(L"-"), 2))); // 2 == lengthOf("dd")

	dt.setHour(stoi(wsTmp.substr(wsTmp.find(L",") + 1, 2))); // 2 == lengthOf("hh") == lengthOf(", ");
	dt.setMinute(stoi(wsTmp.substr(wsTmp.find_first_of(L":") + 1, 2))); // 2 == lengthOf("mi");
	dt.setSecond(stoi(wsTmp.substr(wsTmp.find_last_of(L":") + 1)));

	return wis;
}

wostream & operator<<(wostream & wos, datetime dt)
{
	wos << dt.getYear() << L"-";
	if (dt.getMonth() < 10) wos << L"0";
	wos << dt.getMonth() << L"-";
	if (dt.getDay() < 10) wos << L"0" ;
	wos << dt.getDay() << L",";

	if(dt.getHour() < 10) wos << L"0";
	wos << dt.getHour() << L":";
	if (dt.getMinute() < 10) wos << L"0";
	wos << dt.getMinute() << L":";
	if (dt.getSecond() < 10) wos << L"0";
	wos << dt.getSecond();
	
	return wos;
}