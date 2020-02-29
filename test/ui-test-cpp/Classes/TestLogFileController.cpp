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

#include "TestLogFileController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestLogFileController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test Log File");
    TestCaseController::onCreate(parameters);

	// delete log file first
	SCSystem::deleteLogFile();

	SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
		SC_BEGIN_PARENT_ALIGNMENT(nullptr, "dock=center;", false, 40, 0)
			SC_BEGIN_PARENT_ALIGNMENT(nullptr, "dock=center;", true, 20, 0)
				SC_INSERT_LABEL(nullptr,"text-color=black;","Log Text:","",20)
				SC_INSERT_EDITBOX(&_pEditBox,"",Size(150,26),"progressbar_bk.png",nullptr)
			SC_END_PARENT
			SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Write Log", "", 20, SCF(writeLog))

			SC_INSERT_BUTTON_LABEL(&_pEnableSaveLogLabelItem, "text-color=black;", "Enable Save Log", "", 20, SCF(enableSaveLog))
			SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Clear Log", "", 20, SCF(clearLog))
			SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Show Log", "", 20, SCF(showLog))
		SC_END_PARENT
	SC_END_PARENT
}

void TestLogFileController::enableSaveLog()
{
	if (SCSystem::isSaveLog())
	{
		_pEnableSaveLogLabelItem->setString("Disable Save Log");
	}
	else
	{
		_pEnableSaveLogLabelItem->setString("Enable Save Log");
	}
}

void TestLogFileController::writeLog()
{
	SCLog(_pEditBox->getText());
}

void TestLogFileController::clearLog()
{
	SCSystem::deleteLogFile();
}

void TestLogFileController::showLog()
{
	SCBehaviorShowLog::create()->execute();
	//auto str = SCSystem::getLogFileData();
	//SCLog(str);
}


