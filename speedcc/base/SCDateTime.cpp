/****************************************************************************
 
 Copyright (c) 2017-2020 Kevin Wu (Wu Feng)
 
 github: http://github.com/kevinwu1024
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

#include <cstdlib>
#include <climits>

#ifdef WIN32
#include "../platform/win32/SCWinTime.h"
#else
#include <sys/time.h>
#endif


#include "SCDateTime.h"
#include "SCString.h"
#include "../system/SCSystem.h"

#include "../platform/SCOSSystem.h"

NAMESPACE_SPEEDCC_BEGIN

enum
{
    SECS_PER_DAY = 86400,
    MSECS_PER_DAY = 86400000,
    SECS_PER_HOUR = 3600,
    MSECS_PER_HOUR = 3600000,
    SECS_PER_MIN = 60,
    MSECS_PER_MIN = 60000,
    TIME_T_MAX = 2145916799,  // int maximum 2037-12-31T23:59:59 UTC
    JULIAN_DAY_FOR_EPOCH = 2440588 // result of julianDayFromDate(1970, 1, 1)
};
    
static const char s_MonthDays[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
bool SCDateTime::Date::isValid() const
{
    return (nYear == 0) ?  false : (nDay > 0 && nMonth > 0 && nMonth <= 12) &&
    (nDay <= s_MonthDays[nMonth] || (nDay == 29 && nMonth == 2 && SCDateTime::isLeapYear(nYear)));
}
    
int SCDateTime::Date::getWeekCountOfYear() const
{
	SC_RETURN_IF(!this->isValid(), -1);

	int year = nYear;
	int yday = nMonth;
	int wday = nDay;

	int week = (yday - wday + 10) / 7;

	if (week == 0)
	{
		// last week of previous year
		--year;
		week = (yday + 365 + (SCDateTime::isLeapYear(year) ? 1 : 0) - wday + 10) / 7;
		SCASSERT(week == 52 || week == 53);
	}
	else if (week == 53)
	{
		// maybe first week of next year
		int w = (yday - 365 - (SCDateTime::isLeapYear(year) ? 1 : 0) - wday + 10) / 7;
		if (w > 0) {
			++year;
			week = w;
		}
		SCASSERT(week == 53 || week == 1);
	}

	return week;
}

int SCDateTime::Date::getDayCountOfMonth() const
{
	SC_RETURN_IF(!this->isValid(), -1);
	return (nMonth == 2 && SCDateTime::isLeapYear(nYear)) ? 29 : s_MonthDays[nMonth];
}

int SCDateTime::Date::getDayCountOfYear() const
{
	SC_RETURN_IF(!this->isValid(), -1);
	return SCDateTime::isLeapYear(nYear) ? 366 : 365;
}

SCDateTime::SCDateTime()
{
    this->createInstance();
    this->now();
}
    
SCDateTime::SCDateTime(const SCString& strDateTime,const SCString& strFormat)
{
    this->createInstance();
    struct tm tb;
        
    struct timeval tv;
    gettimeofday(&tv, NULL);
        
    ::memset(&tb, 0, sizeof(struct tm));
    if(strptime(strDateTime, strFormat, &tb))
    {
        Date d = {tb.tm_year+1900,tb.tm_mon+1,tb.tm_mday};
        Time t1 = {tb.tm_hour,tb.tm_min,tb.tm_sec,(int)(tv.tv_usec/1000)};
            
        auto pStub = this->getStub();
        pStub->jd = SCDateTime::convertDate2JD(d);
        pStub->nMillSecOfDay = t1.getMillSecOfDay();
#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
        pStub->nOffsetSecUTC = (int)tb.tm_gmtoff;
#endif
            
        if(tb.tm_isdst>0)
        {
            pStub->dstStatus = DST_YES;
        }
        else if(tb.tm_isdst==0)
        {
            pStub->dstStatus = DST_NO;
        }
        else
        {
            pStub->dstStatus = DST_UNKNOWN;
        }
    }
    else
    {
        SCLog("datetime '%s' or format '%s' incorrect",strDateTime.c_str(),strFormat.c_str());
        this->now();
    }
}
    
SCDateTime::SCDateTime(const SCDateTime::Date& d,const SCDateTime::Time& t)
{
    this->createInstance();
    this->now();
        
    if(d.isValid())
    {
        auto pStub = this->getStub();
        pStub->jd = SCDateTime::convertDate2JD(d);
        pStub->nMillSecOfDay = t.getMillSecOfDay();
        this->fixedTime();
    }
}
    
SCDateTime::SCDateTime(const SCDateTime& dt)
//    _jd(dt._jd),
//    _nMillSecOfDay(dt._nMillSecOfDay),
//    _nOffsetSecUTC(dt._nOffsetSecUTC),
//    _dstStatus(dt._dstStatus)
{
    this->createInstance();
    auto pStub = this->getStub();
        
    *pStub = *(dt.getStub());
}
    
SCDateTime::SCDateTime(const time_t& t)
{
    this->createInstance();
    this->setDatetime(t);
}
    
SCDateTime::~SCDateTime()
{
        
}
    
void SCDateTime::now()
{
    this->clone4Write();
    time_t t = ::time(NULL);
        
    this->setDatetime(t);
}
    
SCDateTime& SCDateTime::operator=(const SCDateTime& dt)
{
    this->clone4Write();
    auto pStub = this->getStub();
        
    *pStub = *(dt.getStub());
        
    return *this;
}
    
bool SCDateTime::setDatetime(const time_t& t)
{
    this->clone4Write();
        
    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm* tb = ::localtime(&t);
        
    Date d = {tb->tm_year+1900,tb->tm_mon+1,tb->tm_mday};
    Time t1 = {tb->tm_hour,tb->tm_min,tb->tm_sec,(int)(tv.tv_usec/1000)};
        
    auto pStub = this->getStub();
    pStub->jd = SCDateTime::convertDate2JD(d);
    pStub->nMillSecOfDay = t1.getMillSecOfDay();

#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    pStub->nOffsetSecUTC = (int)tb->tm_gmtoff;
#endif
        
    if(tb->tm_isdst>0)
    {
        pStub->dstStatus = DST_YES;
    }
    else if(tb->tm_isdst==0)
    {
        pStub->dstStatus = DST_NO;
    }
    else
    {
        pStub->dstStatus = DST_UNKNOWN;
    }
        
    return true;
}
    
bool SCDateTime::setMilliSeconds(const int nMillSec)
{
    SCASSERT(nMillSec>=0 && nMillSec<1000);
        
    bool bRet = false;
        
    if(nMillSec>=0 && nMillSec<1000)
    {
        this->clone4Write();
        auto pStub = this->getStub();
        Time t(pStub->nMillSecOfDay);
        t.nMillSeconds = nMillSec;
            
        pStub->nMillSecOfDay = t.getMillSecOfDay();
            
        bRet = true;
    }
        
    return bRet;
}
    
    
bool SCDateTime::setSeconds(const int nSeconds)
{
    SCASSERT(nSeconds>=0 && nSeconds<60);
        
    bool bRet = false;
        
    if(nSeconds>=0 && nSeconds<60)
    {
        this->clone4Write();
        auto pStub = this->getStub();
        Time t(pStub->nMillSecOfDay);
        t.nSeconds = nSeconds;
            
        pStub->nMillSecOfDay = t.getMillSecOfDay();
            
        bRet = true;
    }
        
    return bRet;
}
    
bool SCDateTime::setMinute(const int nMinute)
{
    SCASSERT(nMinute>=0 && nMinute<60);
        
    bool bRet = false;
        
    if(nMinute>=0 && nMinute<60)
    {
        this->clone4Write();
        auto pStub = this->getStub();
        Time t(pStub->nMillSecOfDay);
        t.nMinute = nMinute;
            
        pStub->nMillSecOfDay = t.getMillSecOfDay();
            
        bRet = true;
    }
        
    return bRet;
}
    
bool SCDateTime::setHour(const int nHour)
{
    SCASSERT(nHour>=0 && nHour<24);
        
    bool bRet = false;
        
    if(nHour>=0 && nHour<24)
    {
        this->clone4Write();
        auto pStub = this->getStub();
        Time t(pStub->nMillSecOfDay);
        t.nHour = nHour;
            
        pStub->nMillSecOfDay = t.getMillSecOfDay();
            
        bRet = true;
    }
        
    return bRet;
}
    
bool SCDateTime::setDayOfMonth(const int nDay)
{
    SCASSERT(nDay>0 && nDay<32);
        
    bool bRet = false;
        
    if(nDay>0 && nDay<32)
    {
        this->clone4Write();
        auto pStub = this->getStub();
        Date d(pStub->jd);
            
        d.nDay = nDay;
            
        if(d.isValid())
        {
            pStub->jd = SCDateTime::convertDate2JD(d);
            bRet = true;
        }
    }
        
    return bRet;
}
    
bool SCDateTime::setMonth(const int nMonth)
{
    SCASSERT(nMonth>0 && nMonth<13);
        
    bool bRet = false;
        
    if(nMonth>0 && nMonth<13)
    {
        this->clone4Write();
        auto pStub = this->getStub();
        Date d(pStub->jd);
            
        d.nMonth = nMonth;
            
        if(d.isValid())
        {
            pStub->jd = SCDateTime::convertDate2JD(d);
            bRet = true;
        }
    }
        
    return bRet;
}
    
bool SCDateTime::setYear(const int nYear)
{
    bool bRet = false;
        
    this->clone4Write();
    auto pStub = this->getStub();
        
    Date d(pStub->jd);
        
    d.nYear = nYear;
        
    if(d.isValid())
    {
        pStub->jd = SCDateTime::convertDate2JD(d);
        bRet = true;
    }
        
    return bRet;
}
    
// fixedTime() already cloned before it is called
void SCDateTime::fixedTime()
{
    auto pStub = this->getStub();
        
    if(pStub->nMillSecOfDay<0)
    {
        int nRemainMSec = MSECS_PER_DAY + (pStub->nMillSecOfDay % MSECS_PER_DAY);
        int nDays = ::abs(pStub->nMillSecOfDay / MSECS_PER_DAY);
            
        pStub->nMillSecOfDay = nRemainMSec;
        pStub->jd -= nDays + 1;
    }
    else if(pStub->nMillSecOfDay>MSECS_PER_DAY)
    {
        int nRemainMSec = pStub->nMillSecOfDay % MSECS_PER_DAY;
        int nDays = pStub->nMillSecOfDay / MSECS_PER_DAY;
            
        pStub->nMillSecOfDay = nRemainMSec;
        pStub->jd += nDays;
    }
}
    
SCDateTime SCDateTime::addMilliSeconds(const int nMillSecond)
{
    if(nMillSecond)
    {
        this->clone4Write();
        auto pStub = this->getStub();
            
        pStub->nMillSecOfDay += nMillSecond;
        this->fixedTime();
    }
        
    return *this;
}
    
SCDateTime SCDateTime::addSeconds(const int nSeconds)
{
    return this->addMilliSeconds(nSeconds*1000);
}
    
SCDateTime SCDateTime::addMinute(const int nMinute)
{
    return this->addMilliSeconds(nMinute*60*1000);
}
    
SCDateTime SCDateTime::addHour(const int nHour)
{
    return this->addMilliSeconds(nHour*60*60*1000);
}
    
SCDateTime SCDateTime::addDay(const int nDay)
{
    return this->addMilliSeconds(nDay*24*60*60*1000);
}
    
SCDateTime SCDateTime::addMonth(int nMonth)
{
    if(nMonth>0)
    {
        this->clone4Write();
        auto pStub = this->getStub();
            
        Date dt(pStub->jd);
        int y = dt.nYear;
        int m = dt.nMonth;
        int d = dt.nDay;
            
        int old_y = y;
            
        bool increasing = nMonth > 0;
            
        while (nMonth != 0) {
            if (nMonth < 0 && nMonth + 12 <= 0)
            {
                y--;
                nMonth+=12;
            }
            else if (nMonth < 0)
            {
                m+= nMonth;
                nMonth = 0;
                if (m <= 0)
                {
                    --y;
                    m += 12;
                }
            }
            else if (nMonth - 12 >= 0)
            {
                y++;
                nMonth -= 12;
            }
            else if (m == 12)
            {
                y++;
                m = 0;
            }
            else
            {
                m += nMonth;
                nMonth = 0;
                if (m > 12) {
                    ++y;
                    m -= 12;
                }
            }
        }
            
        // was there a sign change?
        if ((old_y > 0 && y <= 0) ||
            (old_y < 0 && y >= 0))
        {
            // yes, adjust the date by +1 or -1 years
            y += increasing ? +1 : -1;
        }
            
        pStub->jd = SCDateTime::convertDate2JD(SCDateTime::fixedDate(y,m,d));
    }
        
    return *this;
}
    
SCDateTime SCDateTime::addYear(const int nYear)
{
    this->clone4Write();
    auto pStub = this->getStub();
        
    Date pd = SCDateTime::convertJD2Date(pStub->jd);
        
    int old_y = pd.nYear;
    pd.nYear += nYear;
        
    // was there a sign change?
    if ((old_y > 0 && pd.nYear <= 0) ||
        (old_y < 0 && pd.nYear >= 0))
    {
        // yes, adjust the date by +1 or -1 years
        pd.nYear += nYear > 0 ? +1 : -1;
    }
        
    auto d = SCDateTime::fixedDate(pd.nYear, pd.nMonth, pd.nDay);
    pStub->jd = SCDateTime::convertDate2JD(d);
        
    return *this;
}
    
int SCDateTime::getYear() const
{
    auto pStub = this->getStub();
    return SCDateTime::convertJD2Date(pStub->jd).nYear;
}
    
int SCDateTime::getMonth() const
{
    auto pStub = this->getStub();
    return SCDateTime::convertJD2Date(pStub->jd).nMonth;
}
    
int SCDateTime::getHour() const
{
    auto pStub = this->getStub();
    return Time(pStub->nMillSecOfDay).nHour;
        
}
    
int SCDateTime::getMinute() const
{
    auto pStub = this->getStub();
    return Time(pStub->nMillSecOfDay).nMinute;
}
    
int SCDateTime::getSeconds() const
{
    auto pStub = this->getStub();
    return Time(pStub->nMillSecOfDay).nSeconds;
}
    
int SCDateTime::getMilleSeconds() const
{
    auto pStub = this->getStub();
    return pStub->nMillSecOfDay % 1000;
}
    
// Returns the week number (1 to 53)
int SCDateTime::getWeekCountOfYear() const
{
	return this->getDate().getWeekCountOfYear();
}
    
// Returns the number of days in the month (28 to 31)
int SCDateTime::getDayCountOfMonth() const
{
	return this->getDate().getDayCountOfMonth();
}
    
// Returns the number of days in the year (365 or 366)
int SCDateTime::getDayCountOfYear() const
{
	return this->getDate().getWeekCountOfYear();
}
    
int SCDateTime::getDayOfWeek() const
{
    auto pStub = this->getStub();
    return (((pStub->jd >= 0) ? ((pStub->jd % 7) + 1) : (((pStub->jd + 1) % 7) + 7)) % 7 + 1);
}
    
SCString SCDateTime::getMonthName(int nMonth,const bool bShort) const
{
    if(nMonth<0 || nMonth>12)
    {
        nMonth = 0;
    }
        
    char buf[128] = {0};
    const int m = (nMonth==0 ? this->getMonth() : nMonth);
        
    ::scGetMonthName(buf,SC_ARRAY_LENGTH(buf),m,bShort);
        
    return buf;
}
    
SCString SCDateTime::getWeekName(int nWeek,const bool bShort) const
{
    if(nWeek<0 || nWeek>7)
    {
        nWeek = 0;
    }
        
    char buf[128] = {0};
    const int w = nWeek==0 ? this->getDayOfWeek() : nWeek;
        
    ::scGetWeekName(buf,SC_ARRAY_LENGTH(buf),w,bShort);
        
    return buf;
}
    
int SCDateTime::getDayOfMonth() const
{
    auto pStub = this->getStub();
    return SCDateTime::convertJD2Date(pStub->jd).nDay;
}
    
int SCDateTime::getDayOfYear() const
{
    auto pStub = this->getStub();
    return (int)(pStub->jd - SCDateTime::convertDate2JD(Date(this->getYear(), 1, 1)) + 1);
}
    
SCDateTime SCDateTime::toUTC()
{
    auto pStub = this->getStub();
    if(pStub->nOffsetSecUTC)
    {
        // because addSeconds() will clone, so no clone here
        this->addSeconds(pStub->nOffsetSecUTC);
        pStub = this->getStub();
        pStub->nOffsetSecUTC = 0;
    }
        
    return *this;
}
    
SCDateTime SCDateTime::toLocal()
{
    time_t t  = ::time(NULL);
    struct tm* tb = ::localtime(&t);
        
    auto pStub = this->getStub();
#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    if(tb->tm_gmtoff!=pStub->nOffsetSecUTC)
    {
        this->addSeconds((int)(tb->tm_gmtoff-pStub->nOffsetSecUTC));
        pStub = this->getStub();
        pStub->nOffsetSecUTC = (int)tb->tm_gmtoff;
    }
#endif
        
    return *this;
}
    
SCDateTimeSpan SCDateTime::operator-(const SCDateTime& dt) const
{
    auto pStub = this->getStub();
    const int nDiffDay = (int)(pStub->jd - dt.getStub()->jd);
    int nDiffSec = (pStub->nMillSecOfDay - dt.getStub()->nMillSecOfDay)/1000;
    nDiffSec += pStub->nOffsetSecUTC - dt.getStub()->nOffsetSecUTC;
        
    return (nDiffDay*24*60*60 + nDiffSec);
}
    
SCDateTime::Date SCDateTime::getDate() const
{
    auto pStub = this->getStub();
    return SCDateTime::convertJD2Date(pStub->jd);
}
    
SCDateTime::Time SCDateTime::getTime() const
{
    auto pStub = this->getStub();
    return SCDateTime::Time(pStub->nMillSecOfDay);
}

bool SCDateTime::setDate(const SCDateTime::Date& date)
{
	SC_RETURN_IF(false,!date.isValid());
	this->clone4Write();
	auto pStub = this->getStub();
	pStub->jd = SCDateTime::convertDate2JD(date);
	return true;
}

bool SCDateTime::setTime(const SCDateTime::Time& time)
{
	SC_RETURN_IF(false, !time.isValid());
	this->clone4Write();
	auto pStub = this->getStub();
	pStub->nMillSecOfDay = time.getMillSecOfDay();
	return true;
}
    
INT64 SCDateTime::getStamp() const
{
    if(this->getDate().isValid() && this->getTime().isValid())
    {
        auto pStub = this->getStub();
        return (((INT64)pStub->jd)*24*60*60 + this->getHour()*60*60 + this->getMinute()*60 + this->getSeconds());
    }
        
    return NullTime;
}

INT64 SCDateTime::getStampInMilleSec() const
{
    if(this->getDate().isValid() && this->getTime().isValid())
    {
        auto pStub = this->getStub();
        return (((INT64)pStub->jd)*24*60*60*1000 + this->getHour()*60*60*1000 + this->getMinute()*60*1000 + this->getSeconds()*1000 + this->getMilleSeconds());
    }
    
    return NullTime;
}
    
SCString SCDateTime::getFormatString(SCString strFormat) const
{
    if(strFormat.isEmpty())
    {
        strFormat = "%Y-%m-%d %H:%M:%S";
    }
    struct tm tb;
        
    Date date = this->getDate();
    Time time = this->getTime();
        
    tb.tm_year = date.nYear - 1900;
    tb.tm_mon = date.nMonth;
    tb.tm_mday = date.nDay;
        
    tb.tm_hour = time.nHour;
    tb.tm_min = time.nMinute;
    tb.tm_sec = time.nSeconds;
        
    auto pStub = this->getStub();

#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    tb.tm_gmtoff = pStub->nOffsetSecUTC;
#endif
        
    char szBuf[256+1] = {0};
        
    if(::strftime(szBuf, SC_ARRAY_LENGTH(szBuf), strFormat.c_str(), &tb))
    {
        return szBuf;
    }
        
    return "";
}
    
////-----
    
SCDateTime::Date SCDateTime::fixedDate(const int y, const int m, const int d)
{
    Date da(y, m, 1);
    Time t(0,0,0,0);
    SCDateTime dt(da,t);
        
    return Date(y,m,MIN(d,dt.getDayCountOfMonth()));
}
    
SCDateTime::Date SCDateTime::convertJD2Date(INT64 julianDay)
{
    /*
        * Math from The Calendar FAQ at http://www.tondering.dk/claus/cal/julperiod.php
        * This formula is correct for all julian days, when using mathematical integer
        * division (round to negative infinity), not c++11 integer division (round to zero)
        */
    INT64 a = julianDay + 32044;
    INT64 b = floordiv(4 * a + 3, 146097);
    INT64    c = a - floordiv(146097 * b, 4);
        
    INT64    d = floordiv(4 * c + 3, 1461);
    INT64    e = c - floordiv(1461 * d, 4);
    INT64    m = floordiv(5 * e + 2, 153);
        
    int    day = (int)(e - floordiv(153 * m + 2, 5) + 1);
    int    month = (int)(m + 3 - 12 * floordiv(m, 10));
    int    year = (int)(100 * b + d - 4800 + floordiv(m, 10));
        
    // Adjust for no year 0
    if (year <= 0)
    {
        --year;
    }
        
    const Date result = { year, month, day };
        
    return result;
}
    
INT64 SCDateTime::convertDate2JD(SCDateTime::Date date)
{
    // Adjust for no year 0
    if (date.nYear < 0)
    {
        ++date.nYear;
    }
        
    /*
        * Math from The Calendar FAQ at http://www.tondering.dk/claus/cal/julperiod.php
        * This formula is correct for all julian days, when using mathematical integer
        * division (round to negative infinity), not c++11 integer division (round to zero)
        */
    int    a = floordiv(14 - date.nMonth, 12);
    INT64 y = (INT64)date.nYear + 4800 - a;
    int    m = date.nMonth + 12 * a - 3;
        
    return date.nDay + floordiv(153 * m + 2, 5) + 365 * y + floordiv(y, 4) - floordiv(y, 100) + floordiv(y, 400) - 32045;
}
    
NAMESPACE_SPEEDCC_END

