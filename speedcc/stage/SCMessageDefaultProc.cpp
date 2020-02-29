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

#include "SCMessageDefaultProc.h"

#include "../system/SCSetting.h"
#include "../system/SCStore.h"
#include "../system/SCSystem.h"

#include "../platform/SCOSSystem.h"

NAMESPACE_SPEEDCC_BEGIN

void SCMessageDefaultProc::addMessageBehavior(int nMsgID, SCBehavior::Ptr ptrBvr)
{
	SC_RETURN_V_IF(ptrBvr == nullptr);
	_msgID2BvrMap[nMsgID] = ptrBvr;
}

void SCMessageDefaultProc::removeMessageBehavior(int nMsgID)
{
	_msgID2BvrMap.erase(nMsgID);
}

void SCMessageDefaultProc::addCommandBehavior(const SCString& strCmd, SCBehavior::Ptr ptrBvr)
{
	SC_RETURN_V_IF(ptrBvr == nullptr || strCmd == "");
	_cmd2BvrMap[strCmd] = ptrBvr;
}

void SCMessageDefaultProc::removeCommandBehavior(const SCString& strCmd)
{
	_cmd2BvrMap.erase(strCmd);
}

void SCMessageDefaultProc::addAlertBoxCallback(const std::function<void(int)>& func,
                                                const int nAlertBoxID)
{
    SCASSERT(func!=nullptr);
    SCASSERT(nAlertBoxID>0);
    _alertBoxID2CBMap[nAlertBoxID] = func;
}

bool SCMessageDefaultProc::preProcessMessage(SCMessage::Ptr ptrMsg)
{
	bool bRet = true;

	if (ptrMsg->nMsgID == SCID::Msg::kMsgCommand)
	{// for command
		auto strCmd = ptrMsg->parameters.getValue(SC_KEY_COMMAND).getString();
		auto it = _cmd2BvrMap.find(strCmd);
		if (it != _cmd2BvrMap.end())
		{
			if ((*it).second != nullptr)
			{
				(*it).second->execute(ptrMsg->parameters);
			}
			bRet = false;
		}
	}
	else
	{// for message
		auto it = _msgID2BvrMap.find(ptrMsg->nMsgID);
		if (it != _msgID2BvrMap.end())
		{
			if ((*it).second != nullptr)
			{
				(*it).second->execute(ptrMsg->parameters);
			}
			bRet = false;
		}
	}

	return bRet;
}
    
void SCMessageDefaultProc::processMessage(SCMessage::Ptr ptrMsg)
{
    SCASSERT(ptrMsg!=nullptr);
        
	// return if there is default behavior
	SC_RETURN_V_IF(!this->preProcessMessage(ptrMsg));

    switch(ptrMsg->nMsgID)
    {
		// enter background
        case SCID::Msg::kMsgAppEnterBackground:
        {
            SCSetting::getInstance()->flush();
        }
            break;
                
		// alert box 
        case SCID::Msg::kMsgAlertBoxSelected:
        {
            auto nAlertBoxID = ptrMsg->parameters.getValue(SC_KEY_ID).getInt();
            auto it = _alertBoxID2CBMap.find(nAlertBoxID);
            if(it!=_alertBoxID2CBMap.end())
            {
                auto nSelected = ptrMsg->parameters.getValue(SC_KEY_RESULT).getInt();
                (*it).second(nSelected);
                _alertBoxID2CBMap.erase(it);
            }
        }
            break;
                
		// quit
        case SCID::Msg::kMsgQuit:
            exit(0);
            break;
    }
}
NAMESPACE_SPEEDCC_END
