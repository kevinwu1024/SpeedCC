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

#include "TestCaseController.h"

USING_NS_CC;

void TestCaseController::onCreate(SCDictionary parameters)
{
    SCViewController::onCreate(parameters);
    
    _ptrWatchDescription = SCWatchString::create();
    _ptrCaseBvr = SCBehaviorCaseInt::create();
    auto ptrNextBvr = SCBehaviorCallFunc::create([this]()
                                                 {
                                                     (*_ptrCaseBvr->getWatch())++;
                                                     if(_ptrCaseBvr->getCaseCount()-1 <= (*_ptrCaseBvr->getWatch()))
                                                     {
                                                         _pNextMenuItem->setVisible(false);
                                                     }
                                                     
                                                     _pPreMenuItem->setVisible(true);
                                                     _ptrCaseBvr->execute();
                                                 });
    
    auto ptrPreBvr = SCBehaviorCallFunc::create([this]()
                                                 {
                                                     (*_ptrCaseBvr->getWatch())--;
                                                     if((*_ptrCaseBvr->getWatch())<=0)
                                                     {
                                                         _pPreMenuItem->setVisible(false);
                                                     }
                                                     _pNextMenuItem->setVisible(true);
                                                     _ptrCaseBvr->execute();
                                                 });
    
    bool bDock = false;
    if(parameters.hasKey("name"))
    {
        auto value = parameters.getValue("name");
        bDock = (value.getString()=="dock");
    }
    
    SCString strTitle;
    if(parameters.hasKey("title"))
    {
        auto value = parameters.getValue("title");
        strTitle = value.getString();
    }
    
    SC_BEGIN_PARENT_ROOT(nullptr, nullptr,SCWinSize())
        SC_BEGIN_PARENT_LAYER_COLOR(nullptr,"dock=center;",SCWinSize(),Color4B::WHITE)
    
            if(bDock)
            {
                // title
                SC_INSERT_LABEL_BMFONT(nullptr,"dock=top|mid-x; y-by=-100;",strTitle,"blue_font.fnt")
                SC_INSERT_LABEL(nullptr, "dock=top|mid-x; y-by=-150; text-color=black;", _ptrWatchDescription, "", 18)
                
                // back button
                SC_INSERT_BUTTON_LABEL(nullptr,  "text-color=black; dock=left|top; x-by=3; y-by=-100;", "Back", "", 22, SCBehaviorViewBack::create())
                
                SC_INSERT_BUTTON(&_pNextMenuItem,  "dock=bottom|mid-x; y-by=100; x-by=60;", "btn_arrow.png", ptrNextBvr)
                
                SC_INSERT_BUTTON(&_pPreMenuItem,  "dock=bottom|mid-x; y-by=100; x-by=-60; rotation=180; visible=false;", "btn_arrow.png", ptrPreBvr)
            }
            else
            {
                // title
                SC_INSERT_LABEL_BMFONT(nullptr,"dock=top|mid-x; y-by=-50;",strTitle,"blue_font.fnt")
                SC_INSERT_LABEL(nullptr,"dock=top|mid-x; y-by=-100; text-color=black;", _ptrWatchDescription, "", 18)
                
                // back button
                SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black; dock=left|top; x-by=3; y-by=-3;", "Back", "", 22, SCBehaviorViewBack::create())
                
                SC_INSERT_BUTTON(&_pNextMenuItem,"dock=bottom|mid-x; y-by=50; x-by=60;", "btn_arrow.png", ptrNextBvr)
                
                SC_INSERT_BUTTON(&_pPreMenuItem,"dock=bottom|mid-x; y-by=50; x-by=-60; rotation=180; visible=false;", "btn_arrow.png", ptrPreBvr)
            }
    
            SC_INSERT_LAYER(&_pContainerLayer, "dock=center;", SCWinSize())

        SC_END_PARENT
    SC_END_PARENT
}


