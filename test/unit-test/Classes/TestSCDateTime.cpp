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

#ifdef _WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif


#include "gtest/gtest.h"
#include "SpeedCC.h"

using namespace SpeedCC;

struct STimeInfo
{
    int nYear;
    int nMonth;
    int nDayOfMonth;
    int nDayOfWeek;
    int nDayOfYear;
    int nHour;
    int nMinutes;
    int nSeconds;
    int nMillSeconds;
    time_t time;
};

STimeInfo getTime(int nOffsetSeconds=0)
{
    STimeInfo ti;
    
    time_t t = ::time(NULL) + nOffsetSeconds;
    ti.time = t;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm* tb = ::localtime(&t);
    
    ti.nYear = tb->tm_year+1900;
    ti.nMonth = tb->tm_mon+1;
    ti.nDayOfMonth = tb->tm_mday;
    ti.nDayOfWeek = tb->tm_wday+1;
    ti.nDayOfYear = tb->tm_yday+1;
    
    ti.nHour = tb->tm_hour;
    ti.nMinutes = tb->tm_min;
    ti.nSeconds = tb->tm_sec;
    ti.nMillSeconds = tv.tv_usec/1000;
    
    return ti;
}

TEST(TestSCDateTime, Constructor)
{
    const int offset = 67*60;
    
    STimeInfo tiOffset = getTime(offset);
    STimeInfo tiNow = getTime();
    
    SCDateTime dt1;
    EXPECT_EQ(dt1.getYear(), tiNow.nYear);
    EXPECT_EQ(dt1.getMonth(), tiNow.nMonth);
    EXPECT_EQ(dt1.getDayOfMonth(), tiNow.nDayOfMonth);
    EXPECT_EQ(dt1.getDayOfWeek(), tiNow.nDayOfWeek);
    EXPECT_EQ(dt1.getDayOfYear(), tiNow.nDayOfYear);
    EXPECT_EQ(dt1.getHour(), tiNow.nHour);
    EXPECT_EQ(dt1.getMinute(), tiNow.nMinutes);
//    EXPECT_EQ(dt1.getSeconds(), tiNow.nSeconds);
//    EXPECT_LT(abs(dt1.getMilleSeconds()-tiNow.nMillSeconds), 5);
    
    SCDateTime dt2(dt1);
    EXPECT_EQ(dt2.getYear(), tiNow.nYear);
    EXPECT_EQ(dt2.getMonth(), tiNow.nMonth);
    EXPECT_EQ(dt2.getDayOfMonth(), tiNow.nDayOfMonth);
    EXPECT_EQ(dt2.getDayOfWeek(), tiNow.nDayOfWeek);
    EXPECT_EQ(dt2.getDayOfYear(), tiNow.nDayOfYear);
    EXPECT_EQ(dt2.getHour(), tiNow.nHour);
    EXPECT_EQ(dt2.getMinute(), tiNow.nMinutes);
    EXPECT_EQ(dt2.getSeconds(), tiNow.nSeconds);
//    EXPECT_EQ(dt2.getStamp(),dt1.getStamp());
//    EXPECT_LT(abs(dt2.getMilleSeconds()-tiNow.nMillSeconds), 5);
    
    SCDateTime dt3(tiNow.time);
    EXPECT_EQ(dt3.getYear(), tiNow.nYear);
    EXPECT_EQ(dt3.getMonth(), tiNow.nMonth);
    EXPECT_EQ(dt3.getDayOfMonth(), tiNow.nDayOfMonth);
    EXPECT_EQ(dt3.getDayOfWeek(), tiNow.nDayOfWeek);
    EXPECT_EQ(dt3.getDayOfYear(), tiNow.nDayOfYear);
    EXPECT_EQ(dt3.getHour(), tiNow.nHour);
    EXPECT_EQ(dt3.getMinute(), tiNow.nMinutes);
//    EXPECT_EQ(dt3.getSeconds(), tiNow.nSeconds);
//    EXPECT_LT(abs(dt3.getMilleSeconds()-tiNow.nMillSeconds), 5);
    
    SCDateTime dt4(dt1.getDate(),dt1.getTime());
    EXPECT_EQ(dt4.getYear(), tiNow.nYear);
    EXPECT_EQ(dt4.getMonth(), tiNow.nMonth);
    EXPECT_EQ(dt4.getDayOfMonth(), tiNow.nDayOfMonth);
    EXPECT_EQ(dt4.getDayOfWeek(), tiNow.nDayOfWeek);
    EXPECT_EQ(dt4.getDayOfYear(), tiNow.nDayOfYear);
    EXPECT_EQ(dt4.getHour(), tiNow.nHour);
    EXPECT_EQ(dt4.getMinute(), tiNow.nMinutes);
//    EXPECT_EQ(dt4.getSeconds(), tiNow.nSeconds);
    EXPECT_EQ(dt4.getStamp(),dt1.getStamp());
//    EXPECT_LT(abs(dt4.getMilleSeconds()-tiNow.nMillSeconds), 5);
    
    
    SCDateTime dt5(tiOffset.time);
    EXPECT_EQ(dt5.getYear(), tiOffset.nYear);
    EXPECT_EQ(dt5.getMonth(), tiOffset.nMonth);
    EXPECT_EQ(dt5.getDayOfMonth(), tiOffset.nDayOfMonth);
    EXPECT_EQ(dt5.getDayOfWeek(), tiOffset.nDayOfWeek);
    EXPECT_EQ(dt5.getDayOfYear(), tiOffset.nDayOfYear);
    EXPECT_EQ(dt5.getHour(), tiOffset.nHour);
    EXPECT_EQ(dt5.getMinute(), tiOffset.nMinutes);
//    EXPECT_EQ(dt5.getSeconds(), tiOffset.nSeconds);
//    EXPECT_LT(abs(dt5.getMilleSeconds()-tiOffset.nMillSeconds), 5);
    
    SCDateTime dt6("2017-10-01 12:34:56","%Y-%m-%d %H:%M:%S");
    EXPECT_EQ(dt6.getYear(), 2017);
    EXPECT_EQ(dt6.getMonth(), 10);
    EXPECT_EQ(dt6.getDayOfMonth(), 1);
    EXPECT_EQ(dt6.getHour(), 12);
    EXPECT_EQ(dt6.getMinute(), 34);
    EXPECT_EQ(dt6.getSeconds(), 56);
}

TEST(TestSCDateTime, SetGet)
{
    const int offset = 12345*67*60;
    
    STimeInfo tiOffset = getTime(offset);
    
    SCDateTime dt1;
    dt1.setYear(tiOffset.nYear);
    dt1.setMonth(tiOffset.nMonth);
    dt1.setDayOfMonth(tiOffset.nDayOfMonth);
    dt1.setHour(tiOffset.nHour);
    dt1.setMinute(tiOffset.nMinutes);
    dt1.setSeconds(tiOffset.nSeconds);
    dt1.setMilliSeconds(tiOffset.nMillSeconds);
    
    EXPECT_EQ(dt1.getYear(), tiOffset.nYear);
    EXPECT_EQ(dt1.getMonth(), tiOffset.nMonth);
    EXPECT_EQ(dt1.getDayOfMonth(), tiOffset.nDayOfMonth);
    EXPECT_EQ(dt1.getDayOfWeek(), tiOffset.nDayOfWeek);
    EXPECT_EQ(dt1.getDayOfYear(), tiOffset.nDayOfYear);
    EXPECT_EQ(dt1.getHour(), tiOffset.nHour);
    EXPECT_EQ(dt1.getMinute(), tiOffset.nMinutes);
    EXPECT_EQ(dt1.getSeconds(), tiOffset.nSeconds);
    EXPECT_LT(abs(dt1.getMilleSeconds()-tiOffset.nMillSeconds), 5);
}

TEST(TestSCDateTime, Add)
{
    STimeInfo tiOffset;
    SCDateTime dt1;
    
    tiOffset = getTime(24*60*60);
    dt1.addDay(1);
    EXPECT_EQ(dt1.getYear(), tiOffset.nYear);
    EXPECT_EQ(dt1.getMonth(), tiOffset.nMonth);
    EXPECT_EQ(dt1.getDayOfMonth(), tiOffset.nDayOfMonth);
    EXPECT_EQ(dt1.getDayOfWeek(), tiOffset.nDayOfWeek);
    EXPECT_EQ(dt1.getDayOfYear(), tiOffset.nDayOfYear);
    EXPECT_EQ(dt1.getHour(), tiOffset.nHour);
    EXPECT_EQ(dt1.getMinute(), tiOffset.nMinutes);
    EXPECT_EQ(dt1.getSeconds(), tiOffset.nSeconds);
    EXPECT_LT(abs(dt1.getMilleSeconds()-tiOffset.nMillSeconds), 5);
    
    dt1.now();
    tiOffset = getTime(-24*60*60);
    dt1.addDay(-1);
    EXPECT_EQ(dt1.getYear(), tiOffset.nYear);
    EXPECT_EQ(dt1.getMonth(), tiOffset.nMonth);
    EXPECT_EQ(dt1.getDayOfMonth(), tiOffset.nDayOfMonth);
    EXPECT_EQ(dt1.getDayOfWeek(), tiOffset.nDayOfWeek);
    EXPECT_EQ(dt1.getDayOfYear(), tiOffset.nDayOfYear);
    EXPECT_EQ(dt1.getHour(), tiOffset.nHour);
    EXPECT_EQ(dt1.getMinute(), tiOffset.nMinutes);
    EXPECT_EQ(dt1.getSeconds(), tiOffset.nSeconds);
    EXPECT_LT(abs(dt1.getMilleSeconds()-tiOffset.nMillSeconds), 5);
    
    dt1.now();
    tiOffset = getTime(60*60);
    dt1.addHour(1);
    EXPECT_EQ(dt1.getYear(), tiOffset.nYear);
    EXPECT_EQ(dt1.getMonth(), tiOffset.nMonth);
    EXPECT_EQ(dt1.getDayOfMonth(), tiOffset.nDayOfMonth);
    EXPECT_EQ(dt1.getDayOfWeek(), tiOffset.nDayOfWeek);
    EXPECT_EQ(dt1.getDayOfYear(), tiOffset.nDayOfYear);
    EXPECT_EQ(dt1.getHour(), tiOffset.nHour);
    EXPECT_EQ(dt1.getMinute(), tiOffset.nMinutes);
    EXPECT_EQ(dt1.getSeconds(), tiOffset.nSeconds);
    EXPECT_LT(abs(dt1.getMilleSeconds()-tiOffset.nMillSeconds), 5);
    
    dt1.now();
    tiOffset = getTime(60);
    dt1.addMinute(1);
    EXPECT_EQ(dt1.getYear(), tiOffset.nYear);
    EXPECT_EQ(dt1.getMonth(), tiOffset.nMonth);
    EXPECT_EQ(dt1.getDayOfMonth(), tiOffset.nDayOfMonth);
    EXPECT_EQ(dt1.getDayOfWeek(), tiOffset.nDayOfWeek);
    EXPECT_EQ(dt1.getDayOfYear(), tiOffset.nDayOfYear);
    EXPECT_EQ(dt1.getHour(), tiOffset.nHour);
    EXPECT_EQ(dt1.getMinute(), tiOffset.nMinutes);
    EXPECT_EQ(dt1.getSeconds(), tiOffset.nSeconds);
    EXPECT_LT(abs(dt1.getMilleSeconds()-tiOffset.nMillSeconds), 5);
    
//    dt1.now();
//    tiOffset = getTime();
//    dt1.addMonth(1);
//    EXPECT_EQ(dt1.getYear(), tiOffset.nYear);
//    EXPECT_EQ(dt1.getMonth(), tiOffset.nMonth+1);
//    EXPECT_EQ(dt1.getDayOfMonth(), tiOffset.nDayOfMonth);
//    EXPECT_EQ(dt1.getDayOfWeek(), tiOffset.nDayOfWeek);
//    EXPECT_EQ(dt1.getDayOfYear(), tiOffset.nDayOfYear);
//    EXPECT_EQ(dt1.getHour(), tiOffset.nHour);
//    EXPECT_EQ(dt1.getMinute(), tiOffset.nMinutes);
//    EXPECT_EQ(dt1.getSeconds(), tiOffset.nSeconds);
//    EXPECT_LT(abs(dt1.getMilleSeconds()-tiOffset.nMillSeconds), 5);
    
}

TEST(TestSCDateTime, Name)
{
    
    SCDateTime dt1;
    SCString strResult;
    
    // month name long
    strResult = dt1.getMonthName(1,false);
    EXPECT_STREQ(strResult, "January");
    
    strResult = dt1.getMonthName(2,false);
    EXPECT_STREQ(strResult, "February");
    
    strResult = dt1.getMonthName(3,false);
    EXPECT_STREQ(strResult, "March");
    
    strResult = dt1.getMonthName(4,false);
    EXPECT_STREQ(strResult, "April");
    
    strResult = dt1.getMonthName(5,false);
    EXPECT_STREQ(strResult, "May");
    
    strResult = dt1.getMonthName(6,false);
    EXPECT_STREQ(strResult, "June");
    
    strResult = dt1.getMonthName(7,false);
    EXPECT_STREQ(strResult, "July");
    
    strResult = dt1.getMonthName(8,false);
    EXPECT_STREQ(strResult, "August");
    
    strResult = dt1.getMonthName(9,false);
    EXPECT_STREQ(strResult, "September");
    
    strResult = dt1.getMonthName(10,false);
    EXPECT_STREQ(strResult, "October");
    
    strResult = dt1.getMonthName(11,false);
    EXPECT_STREQ(strResult, "November");
    
    strResult = dt1.getMonthName(12,false);
    EXPECT_STREQ(strResult, "December");
    
    // week name long
    strResult = dt1.getWeekName(1,false);
    EXPECT_STREQ(strResult, "Sunday");
    
    strResult = dt1.getWeekName(2,false);
    EXPECT_STREQ(strResult, "Monday");
    
    strResult = dt1.getWeekName(3,false);
    EXPECT_STREQ(strResult, "Tuesday");
    
    strResult = dt1.getWeekName(4,false);
    EXPECT_STREQ(strResult, "Wednesday");
    
    strResult = dt1.getWeekName(5,false);
    EXPECT_STREQ(strResult, "Thursday");
    
    strResult = dt1.getWeekName(6,false);
    EXPECT_STREQ(strResult, "Friday");
    
    strResult = dt1.getWeekName(7,false);
    EXPECT_STREQ(strResult, "Saturday");
    
    
    // month short name
    strResult = dt1.getMonthName(1,true);
    EXPECT_STREQ(strResult, "Jan");
    
    strResult = dt1.getMonthName(2,true);
    EXPECT_STREQ(strResult, "Feb");
    
    strResult = dt1.getMonthName(3,true);
    EXPECT_STREQ(strResult, "Mar");
    
    strResult = dt1.getMonthName(4,true);
    EXPECT_STREQ(strResult, "Apr");
    
    strResult = dt1.getMonthName(5,true);
    EXPECT_STREQ(strResult, "May");
    
    strResult = dt1.getMonthName(6,true);
    EXPECT_STREQ(strResult, "Jun");
    
    strResult = dt1.getMonthName(7,true);
    EXPECT_STREQ(strResult, "Jul");
    
    strResult = dt1.getMonthName(8,true);
    EXPECT_STREQ(strResult, "Aug");
    
    strResult = dt1.getMonthName(9,true);
    EXPECT_STREQ(strResult, "Sep");
    
    strResult = dt1.getMonthName(10,true);
    EXPECT_STREQ(strResult, "Oct");
    
    strResult = dt1.getMonthName(11,true);
    EXPECT_STREQ(strResult, "Nov");
    
    strResult = dt1.getMonthName(12,true);
    EXPECT_STREQ(strResult, "Dec");
    
    // week short name
    strResult = dt1.getWeekName(1,true);
    EXPECT_STREQ(strResult, "Sun");
    
    strResult = dt1.getWeekName(2,true);
    EXPECT_STREQ(strResult, "Mon");
    
    strResult = dt1.getWeekName(3,true);
    EXPECT_STREQ(strResult, "Tue");
    
    strResult = dt1.getWeekName(4,true);
    EXPECT_STREQ(strResult, "Wed");
    
    strResult = dt1.getWeekName(5,true);
    EXPECT_STREQ(strResult, "Thu");
    
    strResult = dt1.getWeekName(6,true);
    EXPECT_STREQ(strResult, "Fri");
    
    strResult = dt1.getWeekName(7,true);
    EXPECT_STREQ(strResult, "Sat");
    
}




