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

#ifndef __SPEEDCC__SCDATATIME_H__
#define __SPEEDCC__SCDATATIME_H__

#include <time.h>
#include <limits>
#include "SCBaseMacros.h"
#include "SCObjPtrT.h"
#include "SCObject.h"

NAMESPACE_SPEEDCC_BEGIN

class SCString;
class SCDateTimeSpan;
    
struct SCDateTimeStub
{
    int             nMillSecOfDay; // in milliseconds
    INT64           jd;
    int             nOffsetSecUTC;
    int             dstStatus;
};
    
class SCDateTime
:public SCObjRefT<SCDateTimeStub>
,public SCObject
{
public: 
    enum {NullTime = -1};
    enum DSTStatus
    {
        DST_UNKNOWN     = 0,
        DST_YES         = 1,
        DST_NO          = 2,
    };
        
    struct Date
    {
        int nYear;
        int nMonth;
        int nDay;
            
        Date()
        :nYear(0)
        ,nMonth(0)
        ,nDay(0)
        {}
            
        Date(const int y,const int m,const int d)
        :nYear(y)
        ,nMonth(m)
        ,nDay(d)
        {}
            
        Date(const INT64 jd) { *this = SCDateTime::convertJD2Date(jd);}
            
        bool isValid() const;
		int getWeekCountOfYear() const;
        int getDayCountOfMonth() const;
        int getDayCountOfYear() const;
    };
        
    struct Time
    {
        int nHour;
        int nMinute;
        int nSeconds;
        int nMillSeconds;
            
        Time()
        :nHour(0)
        ,nMinute(0)
        ,nSeconds(0)
        ,nMillSeconds(0)
        {}
            
        Time(const int h,const int m,const int s,const int ms)
        :nHour(h)
        ,nMinute(m)
        ,nSeconds(s)
        ,nMillSeconds(ms)
        {}
            
        Time(const int nMillSecOfDay)
        :nHour(nMillSecOfDay/(1000*60*60))
        ,nMinute((nMillSecOfDay/1000)%(60*60)/60)
        ,nSeconds((nMillSecOfDay/1000)%60)
        ,nMillSeconds(nMillSecOfDay%1000)
        {}
            
        inline bool isValid() const {return (nHour<24 && nHour>=0 &&
                                                nMinute<60 && nMinute>=0 &&
                                                nSeconds<60 && nSeconds>=0 &&
                                                nMillSeconds<1000 && nMillSeconds>=0);}
            
        inline int getMillSecOfDay() const
        {
            return this->isValid() ? ((nHour*(60*60) + nMinute*60 + nSeconds)*1000 + nMillSeconds) : NullTime;
        }
            
        inline int getSecOfDay() const
        {
            return this->isValid() ? (nHour*(60*60) + nMinute*60 + nSeconds) : NullTime;
        }
    };
        
public:
	SC_DEFINE_CLASS_PTR(SCDateTime)
    SCDateTime();
        
    // specifier refer to: https://www.gnu.org/software/libc/manual/html_node/Low_002dLevel-Time-String-Parsing.html
    SCDateTime(const SCString& strDateTime,const SCString& strFormat);
    SCDateTime(const SCDateTime& dt);
    SCDateTime(const SCDateTime::Date& d,const SCDateTime::Time& t=Time(0,0,0,0));
    SCDateTime(const time_t& time);
    ~SCDateTime();
        
    SCDateTime& operator=(const SCDateTime& dt);
        
    SCDateTime addMilliSeconds(const int nMillSecond);
    SCDateTime addSeconds(const int nSeconds);
    SCDateTime addMinute(const int nMinute);
    SCDateTime addHour(const int nHour);
    SCDateTime addDay(const int nDay);
    SCDateTime addMonth(int nMonth);
    SCDateTime addYear(const int nYear);
        
    bool setMilliSeconds(const int nMillSec);
    bool setSeconds(const int nSeconds);
    bool setMinute(const int nMinute);
    bool setHour(const int nHour);
    // begin from 1
    bool setDayOfMonth(const int nDay);
    bool setMonth(const int nMonth);
    bool setYear(const int nYear);
        
    int getYear() const;
    int getMonth() const;
        
    int getHour() const;
    int getMinute() const;
    int getSeconds() const;
    int getMilleSeconds() const;
        
    Date getDate() const;
    Time getTime() const;
    bool setDate(const Date& date);
    bool setTime(const Time& time);
        
    SCString getMonthName(int nMonth=0,const bool bShort = true) const;
    SCString getWeekName(int nWeek=0,const bool bShort = true) const;
        
    // base 1, sunday is the first day of week
    int getDayOfWeek() const;
        
    // base 1
    int getDayOfMonth() const;
        
    // base 1
    int getDayOfYear() const;
        
    int getWeekCountOfYear() const;
    int getDayCountOfMonth() const;
    int getDayCountOfYear() const;
        
    bool setDatetime(const time_t& time);
        
    INT64 getStamp() const;
    INT64 getStampInMilleSec() const;
        
    SCDateTime toUTC();
    SCDateTime toLocal();
        
    inline DSTStatus getDSTStatus() const {return (DSTStatus)this->getStub()->dstStatus;}
        
    void now();
    SCDateTimeSpan operator-(const SCDateTime& dt) const;
        
    // specifier refer to: https://www.gnu.org/software/libc/manual/html_node/Low_002dLevel-Time-String-Parsing.html
    // if format string is empty, then set to default format "%Y-%m-%d %H:%M:%S"
    SCString getFormatString(SCString strFormat) const;
        
    static inline bool isLeapYear(int y)
    {
        if ( y < 1) { ++y; }
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }
        
private:
    static inline INT64 getDateNull() { return (std::numeric_limits<INT64>::min)();}
    static inline int getTimeNull() {return -1;}
        
    static Date convertJD2Date(INT64 julianDay);
    static INT64 convertDate2JD(SCDateTime::Date date);
    static Date fixedDate(const int y, const int m, const int d);
        
    static inline INT64 floordiv(INT64 a, int b) {return (a - (a < 0 ? b - 1 : 0)) / b;}
    static inline int floordiv(int a, int b) { return (a - (a < 0 ? b - 1 : 0)) / b;}
        
    void fixedTime();
};
    
class SCDateTimeSpan
{
public:
    SCDateTimeSpan():_nSeconds(0){}
    SCDateTimeSpan(const int nSec):_nSeconds(nSec){}
        
    inline int getDays() const { return _nSeconds/(24*60*60); }
    inline int getHours() const { return (_nSeconds%(24*60*60))/(60*60); }
    inline int getMinutes() const { return _nSeconds%(60*60)/60; }
    inline int getSeconds() const { return _nSeconds%60; }
        
private:
    int     _nSeconds;
};

NAMESPACE_SPEEDCC_END



#endif // __SPEEDCC__SCDATATIME_H__
