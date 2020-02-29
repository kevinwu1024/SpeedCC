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

#include "TestHttpFetcherController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestHttpFetcherController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test Http Download");
    TestCaseController::onCreate(parameters);
    
    _ptrCaseBvr->setCase(0, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseText, this)));
    _ptrCaseBvr->setCase(1, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseJson, this)));
    _ptrCaseBvr->setCase(2, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseHttps, this)));
    _ptrCaseBvr->setCase(3, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseParameter, this)));
    _ptrCaseBvr->setCase(4, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseHeader, this)));
    
    _ptrCaseBvr->execute();
}

void TestHttpFetcherController::testCaseText()
{
    (*_ptrWatchDescription) = "(Test Download Text)";
    _pContainerLayer->removeAllChildren();
    
    auto getCall = [](SCDictionary dic)
    {
        SCHttpFetcher::getInstance()->fetchText("http://httpbin.org/get",
                                                    [](bool bSuccess, int nResponseCode,SCString strText)
                                                    {
                                                        if(bSuccess)
                                                        {
                                                            SCLog("Download with GET success! result: %s",strText.c_str());
                                                        }
                                                        else
                                                        {
                                                            SCLog("Download with GET failed!");
                                                        }
                                                        
                                                    });
    };
    
    auto postCall = [](SCDictionary dic)
    {
        SCHttpFetcher::SRequestPara para;
        para.method = SCHttpFetcher::EMethod::POST;
        SCHttpFetcher::getInstance()->fetchText("http://httpbin.org/post",
                                                    [](bool bSuccess, int nResponseCode,SCString strText)
                                                    {
                                                        if(bSuccess)
                                                        {
                                                            SCLog("Download with POST success! result: %s",strText.c_str());
                                                        }
                                                        else
                                                        {
                                                            SCLog("Download with POST failed!");
                                                        }
                                                    },&para);
    };
    
    auto ptrBvrGET = SCBehaviorCallFunc::create(getCall);
    auto ptrBvrPOST = SCBehaviorCallFunc::create(postCall);
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,40,0)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test GET", "", 20, ptrBvrGET)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test POST", "", 20, ptrBvrPOST)
        SC_END_PARENT
    SC_END_PARENT
}

void TestHttpFetcherController::testCaseJson()
{
    (*_ptrWatchDescription) = "(Test Download Json)";
    _pContainerLayer->removeAllChildren();
    
    auto getCall = [](SCDictionary dic)
    {
        SCHttpFetcher::getInstance()->fetchJSON("http://httpbin.org/get",
                                                    [](bool bSuccess, int nResponseCode, SCDictionary dic)
                                                    {
                                                        if(bSuccess)
                                                        {
                                                            SCLog("Download with GET success! result: %s",dic.exportJson().c_str());
                                                        }
                                                        else
                                                        {
                                                            SCLog("Download with GET failed!");
                                                        }
                                                    });
    };
    
    auto postCall = [](SCDictionary dic)
    {
        SCHttpFetcher::SRequestPara para;
        para.method = SCHttpFetcher::EMethod::POST;
        SCHttpFetcher::getInstance()->fetchJSON("http://httpbin.org/post",
                                                    [](bool bSuccess, int nResponseCode, SCDictionary dic)
                                                    {
                                                        if(bSuccess)
                                                        {
                                                            SCLog("Download with POST success! result: %s",dic.exportJson().c_str());
                                                        }
                                                        else
                                                        {
                                                            SCLog("Download with POST failed!");
                                                        }
                                                    },&para);
    };
    
    auto ptrBvrGET = SCBehaviorCallFunc::create(getCall);
    auto ptrBvrPOST = SCBehaviorCallFunc::create(postCall);
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,40,0)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test GET", "", 20, ptrBvrGET)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test POST", "", 20, ptrBvrPOST)
        SC_END_PARENT
    SC_END_PARENT
}

void TestHttpFetcherController::testCaseHttps()
{
    (*_ptrWatchDescription) = "(Test Download with Https)";
    _pContainerLayer->removeAllChildren();
    
    auto getCall = [](SCDictionary dic)
    {
        SCHttpFetcher::getInstance()->fetchJSON("https://httpbin.org/get",
                                                    [](bool bSuccess, int nResponseCode, SCDictionary dic)
                                                    {
                                                        if(bSuccess)
                                                        {
                                                            SCLog("Download with GET success! result: %s",dic.exportJson().c_str());
                                                        }
                                                        else
                                                        {
                                                            SCLog("Download with GET failed!");
                                                        }
                                                        
                                                    });
    };
    
    auto postCall = [](SCDictionary dic)
    {
        SCHttpFetcher::SRequestPara para;
        para.method = SCHttpFetcher::EMethod::POST;
        SCHttpFetcher::getInstance()->fetchJSON("https://httpbin.org/post",
                                                    [](bool bSuccess, int nResponseCode, SCDictionary dic)
                                                    {
                                                        if(bSuccess)
                                                        {
                                                            SCLog("Download with POST success! result: %s",dic.exportJson().c_str());
                                                        }
                                                        else
                                                        {
                                                            SCLog("Download with POST failed!");
                                                        }
                                                    },&para);
    };
    
    auto ptrBvrGET = SCBehaviorCallFunc::create(getCall);
    auto ptrBvrPOST = SCBehaviorCallFunc::create(postCall);
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,40,0)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test GET", "", 20, ptrBvrGET)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test POST", "", 20, ptrBvrPOST)
        SC_END_PARENT
    SC_END_PARENT
}

void TestHttpFetcherController::testCaseParameter()
{
    (*_ptrWatchDescription) = "(Test Download with Parameters)";
    _pContainerLayer->removeAllChildren();
    
    auto getCall = [](SCDictionary dic)
    {
        SCHttpFetcher::SRequestPara para;
        para.method = SCHttpFetcher::EMethod::GET;
        para.paramDic.setValue("arg1", "my-value");
        para.paramDic.setValue("arg2", "123");
        para.paramDic.setValue("arg3", "好天气");
        para.paramDic.setValue("@.arg4", "/0/1/2/3");
        
        SCHttpFetcher::getInstance()->fetchJSON("http://httpbin.org/get",
                                                    [](bool bSuccess, int nResponseCode, SCDictionary dic)
                                                    {
                                                        if(bSuccess)
                                                        {
                                                            SCLog("Download with GET success! result: %s",dic.exportJson().c_str());
                                                        }
                                                        else
                                                        {
                                                            SCLog("Download with GET failed!");
                                                        }
                                                        
                                                    },&para);
    };
    
    auto postCall = [](SCDictionary dic)
    {
        SCHttpFetcher::SRequestPara para;
        para.method = SCHttpFetcher::EMethod::POST;
        para.paramDic.setValue("arg1", "my-value");
        para.paramDic.setValue("arg2", "123");
        para.paramDic.setValue("arg3", "好天气");
        para.paramDic.setValue("@.arg4", "/0/1/2/3");
        
        SCHttpFetcher::getInstance()->fetchJSON("http://httpbin.org/post",
                                                    [](bool bSuccess, int nResponseCode, SCDictionary dic)
                                                    {
                                                        if(bSuccess)
                                                        {
                                                            SCLog("Download with POST success! result: %s",dic.exportJson().c_str());
                                                        }
                                                        else
                                                        {
                                                            SCLog("Download with POST failed!");
                                                        }
                                                    },&para);
    };
    
    auto ptrBvrGET = SCBehaviorCallFunc::create(getCall);
    auto ptrBvrPOST = SCBehaviorCallFunc::create(postCall);
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,40,0)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test GET", "", 20, ptrBvrGET)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test POST", "", 20, ptrBvrPOST)
        SC_END_PARENT
    SC_END_PARENT
}

void TestHttpFetcherController::testCaseHeader()
{
    (*_ptrWatchDescription) = "(Test Download with Header)";
    _pContainerLayer->removeAllChildren();
    
    auto getCall = [](SCDictionary dic)
    {
        SCHttpFetcher::SRequestPara para;
        para.method = SCHttpFetcher::EMethod::GET;
        para.paramDic.setValue("arg1", "my-value");
        para.paramDic.setValue("arg2", "123");
        para.paramDic.setValue("arg3", "好天气");
        para.paramDic.setValue("@.arg4", "/0/1/2/3");
        
        para.headerVtr.push_back("User-Agent:My Test GET Agent ");
        para.headerVtr.push_back("Content-Type: application/json; charset=utf-8");
        
        SCHttpFetcher::getInstance()->fetchJSON("http://httpbin.org/get",
                                                    [](bool bSuccess, int nResponseCode, SCDictionary dic)
                                                    {
                                                        if(bSuccess)
                                                        {
                                                            SCLog("Download with GET success! result: %s",dic.exportJson().c_str());
                                                        }
                                                        else
                                                        {
                                                            SCLog("Download with GET failed!");
                                                        }
                                                        
                                                    },&para);
    };
    
    auto postCall = [](SCDictionary dic)
    {
        SCHttpFetcher::SRequestPara para;
        para.method = SCHttpFetcher::EMethod::POST;
        para.paramDic.setValue("arg1", "my-value");
        para.paramDic.setValue("arg2", "123");
        para.paramDic.setValue("arg3", "好天气");
        para.paramDic.setValue("@.arg4", "/0/1/2/3");
        
        para.headerVtr.push_back("User-Agent:My Test POS Agent ");
        para.headerVtr.push_back("Content-Type: application/json; charset=utf-8");
        
        SCHttpFetcher::getInstance()->fetchJSON("http://httpbin.org/post",
                                                    [](bool bSuccess, int nResponseCode, SCDictionary dic)
                                                    {
                                                        if(bSuccess)
                                                        {
                                                            SCLog("Download with POST success! result: %s",dic.exportJson().c_str());
                                                        }
                                                        else
                                                        {
                                                            SCLog("Download with POST failed!");
                                                        }
                                                    },&para);
    };
    
    auto ptrBvrGET = SCBehaviorCallFunc::create(getCall);
    auto ptrBvrPOST = SCBehaviorCallFunc::create(postCall);
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,40,0)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test GET", "", 20, ptrBvrGET)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test POST", "", 20, ptrBvrPOST)
        SC_END_PARENT
    SC_END_PARENT
}


