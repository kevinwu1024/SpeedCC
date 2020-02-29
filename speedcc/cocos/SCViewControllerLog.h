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

#ifndef __SPEEDCC__SCVIEWCONTROLLERLOG_H__
#define __SPEEDCC__SCVIEWCONTROLLERLOG_H__

#include "cocos2d.h"
#include "SCCocosDef.h"
#include "SCViewController.h"
#include "extensions/cocos-ext.h"

NAMESPACE_SPEEDCC_BEGIN

class SCViewControllerLog
:public SpeedCC::SCViewController
,public cocos2d::extension::TableViewDataSource
,public cocos2d::extension::TableViewDelegate
{
public:
	virtual void onCreate(SpeedCC::SCDictionary parameters) override;

	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view)override {}
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view)override {}
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)override;
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table)override;

	void onButtonClear();

private:
	std::vector<SCString>			_logTextVtr;
	cocos2d::extension::TableView*	_pTableView;
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCVIEWCONTROLLERLOG_H__
