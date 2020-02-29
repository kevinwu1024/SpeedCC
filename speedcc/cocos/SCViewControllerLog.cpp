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


#include "SCViewControllerLog.h"
#include "../system/SCSystem.h"
#include "SCViewBuilder.h"
#include "SCViewMacros.h"

using namespace cocos2d;

NAMESPACE_SPEEDCC_BEGIN

///------------- SCViewControllerLog
void SCViewControllerLog::onCreate(SCDictionary parameters)
{
	SCViewController::onCreate(parameters);

	_logTextVtr = SCSystem::getLogFileData().split('\n');

	_pTableView = extension::TableView::create(this, Size(SCWinSize().width, SCWinSize().height-70));

	SC_BEGIN_PARENT_ROOT(nullptr,nullptr, nullptr)
		SC_BEGIN_PARENT_LAYER_COLOR(nullptr, "dock=center;", SCWinSize(), Color4B::WHITE)
			SC_INSERT_LABEL_BMFONT(nullptr, "x=0.5; y=0.90;", "SpeedCC Log", "blue_font.fnt")
			SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black; dock=top|right; x-by=-10; y-by=-10;", "Close", "", 30, SCBehaviorViewBack::create())
			SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black; dock=top|left; x-by=10; y-by=-10;", "Clear", "", 30, SCF(onButtonClear))
			SC_INSERT_USER_NODE(_pTableView, "")
		SC_END_PARENT
	SC_END_PARENT


	this->listenMessage(SCID::Msg::kMsgViewEnter, [this](SCMessage::Ptr ptrMsg)
	{
		_pTableView->reloadData();
		return true;
	});
}

void SCViewControllerLog::onButtonClear()
{
	SCSystem::deleteLogFile();
	_logTextVtr.clear();
	_pTableView->reloadData();
}

void SCViewControllerLog::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{

}

cocos2d::Size SCViewControllerLog::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	return Size(SCWinSize().width, 26);
}

cocos2d::extension::TableViewCell* SCViewControllerLog::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	extension::TableViewCell *cell = table->dequeueCell();
	auto strText = _logTextVtr[idx];
	if (!cell) 
	{
		cell = extension::TableViewCell::create();

		auto label = Label::createWithSystemFont(strText.c_str(), "Arial", 12.0);
		label->setPosition(Vec2::ZERO);
		label->setAnchorPoint(Vec2::ZERO);
		label->setTextColor(Color4B::BLACK);
		label->setTag(100);
		label->setString(strText.c_str());
		label->setDimensions(SCWinSize().width, 25);
		cell->addChild(label);
	}
	else
	{
		auto label = (Label*)cell->getChildByTag(100);
		label->setString(strText.c_str());
	}

	return cell;
}

ssize_t SCViewControllerLog::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
	return _logTextVtr.size();
}
    

NAMESPACE_SPEEDCC_END


