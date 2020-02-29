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

#include "TestTriggerController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestTriggerController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test Trigger");
    TestCaseController::onCreate(parameters);
    
    _ptrCaseBvr->setCase(0, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseBool, this)));
    _ptrCaseBvr->setCase(1, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseInt, this)));
    _ptrCaseBvr->setCase(2, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseString, this)));
    
    _ptrCaseBvr->execute();
}

void TestTriggerController::testCaseBool()
{
    (*_ptrWatchDescription) = "(Test BOOL)";
    _pContainerLayer->removeAllChildren();
    
    auto ptrBoolTrigger = SCTriggerBool::create(true);
    ptrBoolTrigger->addCondition(SCTrigger::EComparsion::kEqual,
                                  true,
                                  SCBehaviorCallFunc::create([](SCDictionary dic)
                                                             {
                                                                 bool bResult = false;
                                                                 SCWatchBool::Ptr ptrWatch = dic.getValue(SC_KEY_WATCH).getObject<SCWatchBool::Ptr>(&bResult);
                                                                 SCASSERT(bResult);
                                                                 SCLog("Trigger True, value: '%s'",ptrWatch->getString().c_str());
                                                             }));
    
    ptrBoolTrigger->addCondition(SCTrigger::EComparsion::kEqual,
                                  false,
                                  SCBehaviorCallFunc::create([](SCDictionary dic)
                                                             {
                                                                 bool bResult = false;
                                                                 SCWatchBool::Ptr ptrWatch = dic.getValue(SC_KEY_WATCH).getObject<SCWatchBool::Ptr>(&bResult);
                                                                 SCASSERT(bResult);
                                                                 SCLog("Trigger False, value: '%s'",ptrWatch->getString().c_str());
                                                             }));
    
    auto ptrBvrTestTrue = SCBehaviorCallFunc::create([ptrBoolTrigger]()
                                                     {
                                                         (*(ptrBoolTrigger->getWatch())) = true;
                                                     });
    
    auto ptrBvrTestFalse = SCBehaviorCallFunc::create([ptrBoolTrigger]()
                                                     {
                                                         (*(ptrBoolTrigger->getWatch())) = false;
                                                     });
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,40,0)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test True", "", 20, ptrBvrTestTrue)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test False", "", 20, ptrBvrTestFalse)
        SC_END_PARENT
    SC_END_PARENT
}

void TestTriggerController::testCaseInt()
{
    (*_ptrWatchDescription) = "(Test INT)";
    _pContainerLayer->removeAllChildren();
    
    auto ptrIntTrigger = SCTriggerInt::create();
	ptrIntTrigger->addCondition(SCTrigger::EComparsion::kEqual,
									0,
									SCBehaviorCallFunc::create([](SCDictionary dic)
								{
									bool bResult = false;
									SCWatchInt::Ptr ptrWatch = dic.getValue(SC_KEY_WATCH).getObject<SCWatchInt::Ptr>(&bResult);
									SCASSERT(bResult);
									SCLog("Trigger 0, value: '%s'", ptrWatch->getString().c_str());
								}));

    ptrIntTrigger->addCondition(SCTrigger::EComparsion::kEqual,
                                  1,
                                  SCBehaviorCallFunc::create([](SCDictionary dic)
                                                             {
                                                                 bool bResult = false;
                                                                 SCWatchInt::Ptr ptrWatch = dic.getValue(SC_KEY_WATCH).getObject<SCWatchInt::Ptr>(&bResult);
                                                                 SCASSERT(bResult);
                                                                 SCLog("Trigger 1, value: '%s'",ptrWatch->getString().c_str());
                                                             }));
    
    ptrIntTrigger->addCondition(SCTrigger::EComparsion::kEqual,
                                  2,
                                  SCBehaviorCallFunc::create([](SCDictionary dic)
                                                             {
                                                                 bool bResult = false;
                                                                 SCWatchInt::Ptr ptrWatch = dic.getValue(SC_KEY_WATCH).getObject<SCWatchInt::Ptr>(&bResult);
                                                                 SCASSERT(bResult);
                                                                 SCLog("Trigger 2, value: '%s'",ptrWatch->getString().c_str());
                                                             }));
    
    auto ptrBvrTest0 = SCBehaviorCallFunc::create([ptrIntTrigger]()
                                                  {
                                                      (*(ptrIntTrigger->getWatch())) = 0;
                                                  });
    
    auto ptrBvrTest1 = SCBehaviorCallFunc::create([ptrIntTrigger]()
                                                     {
                                                         (*(ptrIntTrigger->getWatch())) = 1;
                                                     });
    
    auto ptrBvrTest2 = SCBehaviorCallFunc::create([ptrIntTrigger]()
                                                      {
                                                          (*(ptrIntTrigger->getWatch())) = 2;
                                                      });
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,40,0)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test 0", "", 20, ptrBvrTest0)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test 1", "", 20, ptrBvrTest1)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test 2", "", 20, ptrBvrTest2)
        SC_END_PARENT
    SC_END_PARENT
}

void TestTriggerController::testCaseString()
{
    (*_ptrWatchDescription) = "(Test String)";
    _pContainerLayer->removeAllChildren();
    
    auto ptrStrTrigger = SCTriggerString::create();
    ptrStrTrigger->addCondition(SCTrigger::EComparsion::kEqual,
                                "",
                                SCBehaviorCallFunc::create([](SCDictionary dic)
                                                           {
                                                               bool bResult = false;
                                                               SCWatchString::Ptr ptrWatch = dic.getValue(SC_KEY_WATCH).getObject<SCWatchString::Ptr>(&bResult);
                                                               SCASSERT(bResult);
                                                               SCLog("Trigger Empty, value: '%s'",ptrWatch->getString().c_str());
                                                           }));
    
    ptrStrTrigger->addCondition(SCTrigger::EComparsion::kEqual,
                                "abc",
                                SCBehaviorCallFunc::create([](SCDictionary dic)
                                                           {
                                                               bool bResult = false;
                                                               SCWatchString::Ptr ptrWatch = dic.getValue(SC_KEY_WATCH).getObject<SCWatchString::Ptr>(&bResult);
                                                               SCASSERT(bResult);
                                                               SCLog("Trigger abc, value: '%s'",ptrWatch->getString().c_str());
                                                           }));
    
    ptrStrTrigger->addCondition(SCTrigger::EComparsion::kEqual,
                                "123",
                                SCBehaviorCallFunc::create([](SCDictionary dic)
                                                           {
                                                               bool bResult = false;
                                                               SCWatchString::Ptr ptrWatch = dic.getValue(SC_KEY_WATCH).getObject<SCWatchString::Ptr>(&bResult);
                                                               SCASSERT(bResult);
                                                               SCLog("Trigger 123, value: '%s'",ptrWatch->getString().c_str());
                                                           }));
    
    auto ptrBvrTest0 = SCBehaviorCallFunc::create([ptrStrTrigger]()
                                                  {
                                                      (*(ptrStrTrigger->getWatch())) = "";
                                                  });
    
    auto ptrBvrTest1 = SCBehaviorCallFunc::create([ptrStrTrigger]()
                                                  {
                                                      (*(ptrStrTrigger->getWatch())) = "abc";
                                                  });
    
    auto ptrBvrTest2 = SCBehaviorCallFunc::create([ptrStrTrigger]()
                                                  {
                                                      (*(ptrStrTrigger->getWatch())) = "123";
                                                  });
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,40,0)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test Empty", "", 20, ptrBvrTest0)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test 'abc'", "", 20, ptrBvrTest1)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Test '123'", "", 20, ptrBvrTest2)
        SC_END_PARENT
    SC_END_PARENT
}
