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

#ifndef __SPEEDCC__SPEEDCC_H__
#define __SPEEDCC__SPEEDCC_H__

///////////////////////////////////////////////////////////////////////////////

#include "SpeedCC.h"

#include "base/SCBaseMacros.h"
#include "base/SCObject.h"
#include "base/SCString.h"
#include "base/SCBufferRefT.h"
#include "base/SCDataBlock.h"
#include "base/SCDateTime.h"
#include "base/SCValue.h"
#include "base/SCObjPtrT.h"
#include "base/SCDictionary.h"
#include "base/SCVersion.h"
#include "base/SCWatchNumberT.h"
#include "base/SCWatchString.h"
#include "base/SCBinder.h"
#include "base/SCBufferQueueT.h"

#include "system/SCSystem.h"
#include "system/SCSetting.h"
#include "system/SCAudioManager.h"
#include "system/SCStore.h"
#include "system/SCLanguage.h"

#include "cocos/SCRefHolder.h"
#include "cocos/SCViewNavigator.h"
#include "cocos/SCViewController.h"
#include "cocos/SCNodeStyle.h"
#include "cocos/SCBinderCocos.h"
#include "cocos/SCNodeUtils.h"
#include "cocos/SCViewMacros.h"
#include "cocos/SCEventEmitter.h"
#include "cocos/SCNodeClickable.h"
#include "cocos/SCNodeAttachment.h"

#include "stage/SCFSMMacros.h"
#include "stage/SCStageMacros.h"
#include "stage/SCFSMRunner.h"
#include "stage/SCFSMBuilder.h"
#include "stage/SCMessageDispatch.h"
#include "stage/SCBehaviorStage.h"
#include "stage/SCBehaviorCocos.h"
#include "stage/SCBehaviorCommon.h"
#include "stage/SCBehaviorSystem.h"
#include "stage/SCStage.h"
#include "stage/SCStrategy.h"
#include "stage/SCEntity.h"
#include "stage/SCTriggerT.h"

#include "network/SCHttpFetcher.h"

#ifdef WIN32
#include "platform/win32/SCWinTime.h"
#endif


#endif // __SPEEDCC__SPEEDCC_H__
