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

#ifndef __SPEEDCC__SCMESSAGEDEFAULTPROC_H__
#define __SPEEDCC__SCMESSAGEDEFAULTPROC_H__

#include "SCMessage.h"
#include "SCPlayObject.h"

NAMESPACE_SPEEDCC_BEGIN

class SCMessageDefaultProc final
{
    friend class SCMessageDispatch;
        
public:
    void addAlertBoxCallback(const std::function<void(int)>& func, const int nAlertBoxID);
        
	void addMessageBehavior(int nMsgID, SCBehavior::Ptr ptrBvr);
	void removeMessageBehavior(int nMsgID);

	void addCommandBehavior(const SCString& strCmd, SCBehavior::Ptr ptrBvr);
	void removeCommandBehavior(const SCString& strCmd);

protected:
    void processMessage(SCMessage::Ptr ptrMsg);
        
private:
	bool preProcessMessage(SCMessage::Ptr ptrMsg);

private:
    std::map<int,std::function<void(int)> >     _alertBoxID2CBMap;
	std::map<int, SCBehavior::Ptr>				_msgID2BvrMap;
	std::map<SCString, SCBehavior::Ptr>			_cmd2BvrMap;
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCMESSAGEDEFAULTPROC_H__
