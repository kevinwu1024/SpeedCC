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

#include "gtest/gtest.h"
#include "SpeedCC.h"

using namespace SpeedCC;

TEST(TestSCString, Constructor)
{
    // empty string
    SCString str0;
    SCString str1;
    EXPECT_EQ(str1.getLength(),0);
    EXPECT_EQ(str1.getRefCount(),0);
    EXPECT_EQ(str1.c_str(),str0.c_str());
    
    SCString str2('a');
    EXPECT_EQ(str2.getLength(),1);
    EXPECT_EQ(str2.getAt(0),'a');
    EXPECT_EQ(str2.getRefCount(),1);
    
    
    SCString str3("a");
    EXPECT_EQ(str3.getLength(),1);
    EXPECT_EQ(str3.getAt(0),'a');
    EXPECT_EQ(str3.getRefCount(),1);
    
    SCString str4("abc");
    EXPECT_EQ(str4.getLength(),3);
    EXPECT_EQ(str4.getRefCount(),1);
    
    SCString str5(str4);
    EXPECT_EQ(str5.getLength(),3);
    EXPECT_EQ(str5.getRefCount(),2);
    
    SCString str6(1);
    EXPECT_EQ(str6.getLength(),1);
    EXPECT_EQ(str6.getRefCount(),1);
    
    SCString str8(0,"%s%d","abc",123);
    EXPECT_EQ(str8.getLength(),6);
    EXPECT_EQ(str8.getRefCount(),1);
    
    SCString str9(std::string("abc"));
    EXPECT_EQ(str9.getLength(),3);
    EXPECT_EQ(str9.getRefCount(),1);
}


TEST(TestSCString, Assignment)
{
    char temBuf[64] = {0};
    const char* pszTestString1 = "abc";
    const char* pszTestString2 = "123";
    const char cTestChar = 'a';
    const int nTestInt = -7;
    const unsigned uTestUnint = 7;
    const std::string strTestString = "456";
    
    SCString str1 = "";
    
    // normal string 1
    str1 = pszTestString1;
    EXPECT_STREQ(str1.c_str(),pszTestString1);
    
    // normal string 2
    str1 = pszTestString2;
    EXPECT_STREQ(str1.c_str(),pszTestString2);
    
    // char
    str1 = cTestChar;
    EXPECT_EQ(str1.getLength(),1);
    EXPECT_EQ(str1.getAt(0),cTestChar);
    
    // int
    str1 = nTestInt;
    sprintf(temBuf, "%d",nTestInt);
    EXPECT_EQ(str1.getLength(), strlen(temBuf));
    EXPECT_STREQ(str1.c_str(),temBuf);
    
    // unsigned int
    str1 = uTestUnint;
    sprintf(temBuf, "%u",uTestUnint);
    EXPECT_EQ(str1.getLength(),strlen(temBuf));
    EXPECT_STREQ(str1.c_str(),temBuf);
    
    // std::string
    str1 = strTestString;
    EXPECT_EQ(str1.getLength(),strTestString.size());
    EXPECT_STREQ(str1,strTestString.c_str());
}

TEST(TestSCString, Comparation)
{
    const char* pOne = "1";
    const char* pEscap = "abc\r\n";
    const char* pEscapCase = "Abc\r\n";
    const char* pChinese = "今天是星期天，放假啦！";
    const char* pSpecial = "!@#$%^&*()0987654321";
    
    SCString strEmpty;
    SCString strOne = pOne;
    SCString strEscap = pEscap;
    SCString strEscapCase = pEscapCase;
    SCString strChinese = pChinese;
    SCString strSpecial = pSpecial;
    
    EXPECT_EQ(strEmpty.compare(""),0);
    EXPECT_EQ(strEmpty==(""),true);
    EXPECT_EQ(strEmpty!=(""),false);
    EXPECT_EQ(strEmpty.compareNoCase(""),0);
    
    EXPECT_EQ(strEmpty==pOne,false);
    EXPECT_EQ(strEmpty==pOne,false);
    EXPECT_EQ(strEmpty!=pOne,true);
    EXPECT_NE(strEmpty.compareNoCase(pOne),0);
    
    EXPECT_EQ(strOne.compare(pOne),0);
    EXPECT_EQ(strOne==(pOne),true);
    EXPECT_EQ(strOne!=(pOne),false);
    EXPECT_EQ(strOne.compareNoCase(pOne),0);
    
    EXPECT_EQ(strEscap.compare(pEscap),0);
    EXPECT_EQ(strEscap==(pEscap),true);
    EXPECT_EQ(strEscap!=(pEscap),false);
    EXPECT_EQ(strEscap.compareNoCase(pEscap),0);
    
    EXPECT_NE(strEscapCase.compare(pEscap),0);
    EXPECT_EQ(strEscapCase==(pEscap),false);
    EXPECT_EQ(strEscapCase!=(pEscap),true);
    EXPECT_EQ(strEscapCase.compareNoCase(pEscap),0);
    
    EXPECT_EQ(strChinese.compare(pChinese),0);
    EXPECT_EQ(strChinese==(pChinese),true);
    EXPECT_EQ(strChinese!=(pChinese),false);
    EXPECT_EQ(strChinese.compareNoCase(pChinese),0);
    
    EXPECT_EQ(strSpecial.compare(pSpecial),0);
    EXPECT_EQ(strSpecial==(pSpecial),true);
    EXPECT_EQ(strSpecial!=(pSpecial),false);
    EXPECT_EQ(strSpecial.compareNoCase(pSpecial),0);
}

TEST(TestSCString, Find)
{
    const char* pszTest1 = "abcdefgfgc";
    const char* pszWord1 = "bc";
    const char* pszWord2 = "ab";
    const char* pszWord3 = "fg";
    const char* pszWord4 = "g1";
    const char* pszWord5 = "23";
    const char pszChar1 = 'c';
    const char pszChar2 = '1';
    
    SCString strEmpty;
    SCString strTest1 = pszTest1;
    
    EXPECT_EQ(strTest1.find(pszWord1),1);
    EXPECT_EQ(strTest1.find(pszWord2),0);
    EXPECT_EQ(strTest1.find(pszWord3),5);
    EXPECT_EQ(strTest1.find(pszWord4),-1);
    EXPECT_EQ(strTest1.find(pszWord5),-1);
    EXPECT_EQ(strTest1.find(""),0);
    
    EXPECT_EQ(strEmpty.find(pszWord1),-1);
    EXPECT_EQ(strEmpty.find(pszWord2),-1);
    EXPECT_EQ(strEmpty.find(pszWord3),-1);
    EXPECT_EQ(strEmpty.find(pszWord4),-1);
    EXPECT_EQ(strEmpty.find(pszWord5),-1);
    EXPECT_EQ(strEmpty.find(""),0);
    EXPECT_EQ(strEmpty.find(pszChar1),-1);
    EXPECT_EQ(strEmpty.find(pszChar2),-1);
    
    EXPECT_EQ(strTest1.find(pszWord1,1),1);
    EXPECT_EQ(strTest1.find(pszWord2,1),-1);
    EXPECT_EQ(strTest1.find(pszWord3,8),-1);
    EXPECT_EQ(strTest1.find(pszWord4,-1),-1);
    EXPECT_EQ(strTest1.find(pszWord5,-1),-1);
    
    EXPECT_EQ(strTest1.find(pszChar1),2);
    EXPECT_EQ(strTest1.find(pszChar2),-1);
    
//    EXPECT_EQ(strTest1.findOneOf(pszWord1),1);
//    EXPECT_EQ(strTest1.findOneOf(pszWord3),5);
    
    EXPECT_EQ(strEmpty.reverseFind(pszChar1),-1);
    EXPECT_EQ(strEmpty.reverseFind(pszChar2),-1);
    
    EXPECT_EQ(strTest1.reverseFind(pszChar1),9);
    EXPECT_EQ(strTest1.reverseFind(pszChar2),-1);
}


TEST(TestSCString, Extract)
{
    const char* pszTest1 = "abcdefgh";
    
    SCString strEmpty;
    SCString strText1 = pszTest1;
    
    EXPECT_STREQ(strText1.left(3),"abc");
    EXPECT_STREQ(strText1.right(3),"fgh");
    EXPECT_STREQ(strText1.mid(2,4),"cdef");
    
    EXPECT_STREQ(strText1.left(strText1.getLength()),pszTest1);
    EXPECT_STREQ(strText1.right(strText1.getLength()),pszTest1);
    EXPECT_STREQ(strText1.mid(0,strText1.getLength()),pszTest1);
    
    EXPECT_STREQ(strText1.left(0),"");
    EXPECT_STREQ(strText1.left(-1),"");
    EXPECT_STREQ(strText1.right(0),"");
    EXPECT_STREQ(strText1.right(-1),"");
    EXPECT_STREQ(strText1.mid(0,0),"");
    EXPECT_STREQ(strText1.mid(-1,0),"");
    EXPECT_STREQ(strText1.mid(-1,-1),"");
    EXPECT_STREQ(strText1.mid(0,-1),"");
    EXPECT_STREQ(strText1.mid(2,0),"");
    
    EXPECT_STREQ(strText1.left(strText1.getLength()+1),pszTest1);
    EXPECT_STREQ(strText1.right(strText1.getLength()+1),pszTest1);
    EXPECT_STREQ(strText1.mid(0,strText1.getLength()+1),pszTest1);
}

TEST(TestSCString, Split)
{
    const char* pszTest1 = "abc,def,ghi";
    const char* pszTest2 = ",abc,def,ghi,";
    const char* pszTest3 = "[abc]de[fgh]i";
    const char* pszTest4 = "[a[bc]de[fgh]i]";
    
    SCString strEmpty;
    SCString strTest1 = pszTest1;
    SCString strTest2 = pszTest2;
    SCString strTest3 = pszTest3;
    SCString strTest4 = pszTest4;
    
    auto resutl1 = strTest1.split(",");
    ASSERT_EQ(resutl1.size(), 3);
    EXPECT_STREQ(resutl1[0], "abc");
    EXPECT_STREQ(resutl1[1], "def");
    EXPECT_STREQ(resutl1[2], "ghi");
    
    auto resutl2 = strTest1.split("|");
    EXPECT_EQ(resutl2.size(), 1);
    EXPECT_STREQ(resutl2[0], "abc,def,ghi");

    auto resutl3 = strTest2.split(",");
    ASSERT_EQ(resutl3.size(), 5);
    EXPECT_STREQ(resutl3[0], "");
    EXPECT_STREQ(resutl3[1], "abc");
    EXPECT_STREQ(resutl3[2], "def");
    EXPECT_STREQ(resutl3[3], "ghi");
    EXPECT_STREQ(resutl3[4], "");
    
    auto resutl4 = strTest3.extract("[", "]");
    ASSERT_EQ(resutl4.size(), 2);
    EXPECT_STREQ(resutl4[0], "abc");
    EXPECT_STREQ(resutl4[1], "fgh");
    
    auto resutl5 = strTest4.extract("[", "]");
    ASSERT_EQ(resutl5.size(), 2);
    EXPECT_STREQ(resutl5[0], "a[bc");
    EXPECT_STREQ(resutl5[1], "fgh");
}

TEST(TestSCString, Replace)
{
    const char* pszTest1 = "abcdefghcd";
    
    SCString strTest1 = pszTest1;
    auto result1 = strTest1.replace('c', '1');
    EXPECT_STREQ(strTest1.c_str(),"ab1defgh1d");
    EXPECT_EQ(result1, 2);
    
    strTest1 = pszTest1;
    result1 = strTest1.replace('z', '1');
    EXPECT_STREQ(strTest1.c_str(),pszTest1);
    EXPECT_EQ(result1, 0);
    
    strTest1 = pszTest1;
    result1 = strTest1.replace("cd", "12");
    EXPECT_STREQ(strTest1.c_str(),"ab12efgh12");
    EXPECT_EQ(result1, 4);
    
    strTest1 = pszTest1;
    result1 = strTest1.replace("zy", "12");
    EXPECT_STREQ(strTest1.c_str(),pszTest1);
    EXPECT_EQ(result1, 0);
    
    strTest1 = pszTest1;
    result1 = strTest1.replace("", "12");
    EXPECT_STREQ(strTest1.c_str(),pszTest1);
    EXPECT_EQ(result1, 0);
    
    strTest1 = pszTest1;
    result1 = strTest1.replace("cd", "");
    EXPECT_STREQ(strTest1.c_str(),pszTest1);
    EXPECT_EQ(result1, 0);
    
    strTest1 = "";
    result1 = strTest1.replace("cd", "");
    EXPECT_STREQ(strTest1.c_str(),"");
    EXPECT_EQ(result1, 0);
    
    strTest1 = "";
    result1 = strTest1.replace('c', '1');
    EXPECT_STREQ(strTest1.c_str(),"");
    EXPECT_EQ(result1, 0);
    
    strTest1 = "";
    result1 = strTest1.replace("", "12");
    EXPECT_STREQ(strTest1.c_str(),"");
    EXPECT_EQ(result1, 0);
}

TEST(TestSCString, Remove)
{
    const char* pszTest1 = "abcdefgh";
    const char* pszTest2 = "abcdefghcd";
    SCString strTest;
    int result;
    
    strTest = pszTest1;
    result = strTest.remove(0,(int)strlen(pszTest1));
    EXPECT_STREQ(strTest.c_str(),"");
    EXPECT_EQ(result, strlen(pszTest1));
    
    strTest = pszTest1;
    result = strTest.remove(3,2);
    EXPECT_STREQ(strTest.c_str(),"abcfgh");
    EXPECT_EQ(result, 2);
    
    strTest = pszTest1;
    result = strTest.remove((int)strlen(pszTest1));
    EXPECT_STREQ(strTest.c_str(),pszTest1);
    EXPECT_EQ(result, 0);
    
    strTest = pszTest1;
    result = strTest.remove('z');
    EXPECT_STREQ(strTest.c_str(),pszTest1);
    EXPECT_EQ(result, 0);
    
    strTest = pszTest1;
    result = strTest.remove('d');
    EXPECT_STREQ(strTest.c_str(),"abcefgh");
    EXPECT_EQ(result, 1);
    
    strTest = pszTest1;
    result = strTest.remove('a');
    EXPECT_STREQ(strTest.c_str(),"bcdefgh");
    EXPECT_EQ(result, 1);
    
    strTest = pszTest1;
    result = strTest.remove('h');
    EXPECT_STREQ(strTest.c_str(),"abcdefg");
    EXPECT_EQ(result, 1);
    
    strTest = pszTest1;
    result = strTest.remove("cd");
    EXPECT_STREQ(strTest.c_str(),"abefgh");
    EXPECT_EQ(result, 2);
    
    strTest = pszTest2;
    result = strTest.remove("cd");
    EXPECT_STREQ(strTest.c_str(),"abefgh");
    EXPECT_EQ(result, 4);
    
    strTest = "";
    result = strTest.remove("cd");
    EXPECT_STREQ(strTest.c_str(),"");
    EXPECT_EQ(result, 0);
}

TEST(TestSCString, Insert)
{
    const char* pszTest = "abc";
    int result;
    SCString strTest;
    
    strTest = pszTest;
    result = strTest.insert(0, "123");
    EXPECT_STREQ(strTest.c_str(),"123abc");
    EXPECT_EQ(result, 6);
    
    strTest = pszTest;
    result = strTest.insert(1, "123");
    EXPECT_STREQ(strTest.c_str(),"a123bc");
    EXPECT_EQ(result, 6);
    
    strTest = pszTest;
    result = strTest.insert(3, "123");
    EXPECT_STREQ(strTest.c_str(),"abc123");
    EXPECT_EQ(result, 6);
    
    strTest = pszTest;
    result = strTest.insert(-1, "123");
    EXPECT_STREQ(strTest.c_str(),"123abc");
    EXPECT_EQ(result, 6);
    
    strTest = pszTest;
    result = strTest.insert(4, "123");
    EXPECT_STREQ(strTest.c_str(),"abc123");
    EXPECT_EQ(result, 6);
    
    strTest = pszTest;
    result = strTest.insert(0, '1');
    EXPECT_STREQ(strTest.c_str(),"1abc");
    EXPECT_EQ(result, 4);
    
    strTest = pszTest;
    result = strTest.insert(1, '1');
    EXPECT_STREQ(strTest.c_str(),"a1bc");
    EXPECT_EQ(result, 4);
    
    strTest = pszTest;
    result = strTest.insert(3, '1');
    EXPECT_STREQ(strTest.c_str(),"abc1");
    EXPECT_EQ(result, 4);
    
    strTest = pszTest;
    result = strTest.insert(-1, '1');
    EXPECT_STREQ(strTest.c_str(),"1abc");
    EXPECT_EQ(result, 4);
    
    strTest = pszTest;
    result = strTest.insert(5, '1');
    EXPECT_STREQ(strTest.c_str(),"abc1");
    EXPECT_EQ(result, 4);
    
    strTest = "";
    result = strTest.insert(0, '1');
    EXPECT_STREQ(strTest.c_str(),"1");
    EXPECT_EQ(result, 1);
}

TEST(TestSCString, Trim)
{
    const char* pTest1 = "  abc  ";
    const char* pTest2 = "abc123abc";
    SCString strTest;
    int result;
    
    strTest = pTest1;
    result = strTest.trimLeft(' ');
    EXPECT_STREQ(strTest.c_str(),"abc  ");
    EXPECT_EQ(result, 2);
    
    strTest = pTest1;
    result = strTest.trimRight(' ');
    EXPECT_STREQ(strTest.c_str(),"  abc");
    EXPECT_EQ(result, 2);
    
    strTest = pTest1;
    result = strTest.trimLeft('a');
    EXPECT_STREQ(strTest.c_str(),pTest1);
    EXPECT_EQ(result, 0);
    
    strTest = pTest1;
    result = strTest.trimRight('a');
    EXPECT_STREQ(strTest.c_str(),pTest1);
    EXPECT_EQ(result, 0);
    
    strTest = "";
    result = strTest.trimLeft('a');
    EXPECT_STREQ(strTest.c_str(),"");
    EXPECT_EQ(result, 0);
    
    strTest = "";
    result = strTest.trimRight('a');
    EXPECT_STREQ(strTest.c_str(),"");
    EXPECT_EQ(result, 0);
    
    strTest = pTest2;
    result = strTest.trimLeft("abc");
    EXPECT_STREQ(strTest.c_str(),"123abc");
    EXPECT_EQ(result, 3);
    
    strTest = pTest2;
    result = strTest.trimRight("abc");
    EXPECT_STREQ(strTest.c_str(),"abc123");
    EXPECT_EQ(result, 3);
    
    strTest = "";
    result = strTest.trimLeft("abc");
    EXPECT_STREQ(strTest.c_str(),"");
    EXPECT_EQ(result, 0);
    
    strTest = "";
    result = strTest.trimRight("abc");
    EXPECT_STREQ(strTest.c_str(),"");
    EXPECT_EQ(result, 0);
}

TEST(TestSCString, CaseConvert)
{
    const char* pszTest = "abc123ABC";
    SCString strTest;
    
    strTest = pszTest;
    strTest.makeUpper();
    EXPECT_STREQ(strTest,"ABC123ABC");
    
    strTest = pszTest;
    strTest.makeLower();
    EXPECT_STREQ(strTest,"abc123abc");
}

TEST(TestSCString, Connector)
{
    const char* pszTest1 = "abc";
    const char* pszTest2 = "123";
    SCString strTest;
    SCString strTest2;
    SCString strTest3;
    
    strTest = pszTest1;
    strTest += pszTest2;
    EXPECT_STREQ(strTest,"abc123");
    
    strTest = pszTest1;
    strTest = strTest + pszTest2;
    EXPECT_STREQ(strTest,"abc123");
    
    strTest = pszTest1;
    strTest = pszTest2 + strTest;
    EXPECT_STREQ(strTest,"123abc");
    
    strTest = pszTest1;
    strTest += '1';
    EXPECT_STREQ(strTest,"abc1");
    
    strTest = pszTest1;
    strTest = strTest + '1';
    EXPECT_STREQ(strTest,"abc1");
    
    strTest = pszTest1;
    strTest = '1' + strTest;
    EXPECT_STREQ(strTest,"1abc");
    
    strTest = pszTest1;
    strTest2 = pszTest2;
    strTest3 = strTest + strTest2;
    EXPECT_STREQ(strTest3,"abc123");
    
    strTest = pszTest1;
    strTest2 = pszTest2;
    strTest3 = "";
    strTest3 += strTest ;
    strTest3 += strTest2;
    EXPECT_STREQ(strTest3,"abc123");
    
    strTest = pszTest1;
    strTest3 = strTest + pszTest2;
    EXPECT_STREQ(strTest3,"abc123");
    
    strTest = "";
    strTest3 = pszTest1 + strTest + pszTest2;
    EXPECT_STREQ(strTest3,"abc123");
    
}

