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

#ifndef __SPEEDCC__SCID_H__
#define __SPEEDCC__SCID_H__

NAMESPACE_SPEEDCC_BEGIN

    // for SCMessage parameters in it's Dictionary
#define SC_KEY_CONTROLLER       "sc-controller"     // SCController*
#define SC_KEY_NUMBER           "sc-number"         // int
#define SC_KEY_NAME             "sc-name"           // SCString
#define SC_KEY_COMMAND          "sc-command"        // SCString
#define SC_KEY_STATE            "sc-state"          // ESCState
#define SC_KEY_CCREF            "sc-cc-ref"        // SCRef2Ptr::Ptr
#define SC_KEY_DELTA            "sc-delta"         // float
#define SC_KEY_RESULT           "sc-result"        // relying on specific message definition, for sendMessage() as well
#define SC_KEY_ID               "sc-id"             // int
#define SC_KEY_FINISHFUNC       "sc-finish-func"    // SCViewController::FinishFunc_t
#define SC_KEY_WATCH            "sc-watch"          // SWatchXXX::Ptr
#define SC_KEY_LENGTH           "sc-length"           // unsigned int
    
    // for SCBehavior parameters in it's Dictionary
#define SC_KEY_ENTITY           "sc-entity" // SCEntity::Ptr
#define SC_KEY_ENTITYID			"sc-entity-id" // int
#define SC_KEY_STRATEGY         "sc-strategy" // SCStrategy::Ptr
#define SC_KEY_STAGE            "sc-stage" // SCStrategy::Ptr
#define SC_KEY_MESSAGE          "sc-message"   // SCMessage::Ptr
#define SC_KEY_FSMRUNNER        "sc-fsm-runner" // SCFSMRunner::Ptr
#define SC_KEY_FSMSTATECOMP		"sc-fsm-state-comp" // SFSMStateComponent::Ptr
    
    // alertbox
#define SC_KEY_TITLE            "sc-title" // SCString
#define SC_KEY_TEXT             "sc-text"   // SCString
#define SC_KEY_STRING0          "sc-button0"    // SCString
#define SC_KEY_STRING1          "sc-button1"    // SCString
#define SC_KEY_STRING2          "sc-button2"    // SCString
    
    // IAP
#define SC_KEY_FEATUREID        "sc-feature-id"    // int
#define SC_KEY_PRICE            "sc-price" // SCString
#define SC_KEY_CURRENCY         "sc-currency" // SCString
    
    // touch
#define SC_KEY_TOUCH            "sc-touch"           // cocos2d::Touch*
#define SC_KEY_TOUCHES          "sc-touches"        // std::vector<cocos2d::Touch*>
#define SC_KEY_CCEVENT          "sc-cc-event"       // cocos2d::Event*
    
    // acceleration
#define SC_KEY_X                "sc-x" // double or float
#define SC_KEY_Y                "sc-y" // double or float
#define SC_KEY_Z                "sc-z" // double or float
#define SC_KEY_TIMESTAMP        "sc-timestamp" // double
    
// keyboard
#define SC_KEY_KEYBOARDCODE     "sc-keyboard-code"  // cocos2d::EventKeyboard::KeyCode

// language
#define SC_KEY_LANGUAGE_PRE     "sc-language-pre" // SCLanguage::ELanguageType
#define SC_KEY_LANGUAGE_CUR     "sc-language-cur" // SCLanguage::ELanguageType
    
struct SCID
{
    enum Msg
    {
        // there is no parameter
        kMsgNULL  =  0,
            
        // there is no parameter
        kMsgQuit,

		// SC_KEY_COMMAND => SCString
		kMsgCommand,
            
        // “code”: EErrorCode
        // "message": SCString
//            kMsgError,
            
        // app launch
        // there is no parameter
        kMsgAppLaunch,
            
        // game enter foreground
        // there is no parameter
        kMsgAppEnterForeground,
            
        // game enter background
        // there is no parameter
        kMsgAppEnterBackground,
            
        // internet reachable changed
        // key: SC_KEY_STATE
        kMsgInternetReachableChanged,
            
        // key: SC_KEY_CONTROLLER
        // controller accepts itself message only
        kMsgViewEnter,
            
        // key: SC_KEY_CONTROLLER
        // controller accepts itself message only
        kMsgViewEnterTransitionDidFinish,
            
        // key: SC_KEY_CONTROLLER
        // controller accepts itself message only
        kMsgViewExit,
            
        // key: SC_KEY_CONTROLLER
        // controller accepts itself message only
        kMsgViewExitTransitionDidStart,
            
        // key: SC_KEY_TOUCH       (for single touch)
        // key: SC_RESULT  (result from receiver, by defualt is true)
        // key: SC_KEY_TOUCHES     (for multiple touch)
        // key: SC_KEY_CCEVENT
        // lisenter: owner scene controller
        kMsgTouchBegan,
            
        // key: SC_KEY_TOUCH       (for single touch)
        // key: SC_KEY_TOUCHES     (for multiple touch)
        // key: SC_KEY_CCEVENT
        // lisenter: owner scene controller
        kMsgTouchMoved,
            
        // key: SC_KEY_TOUCH       (for single touch)
        // key: SC_KEY_TOUCHES     (for multiple touch)
        // key: SC_KEY_CCEVENT
        // lisenter: owner scene controller
        kMsgTouchEnded,
            
        // key: SC_KEY_TOUCH       (for single touch)
        // key: SC_KEY_TOUCHES     (for multiple touches)
        // key: SC_KEY_CCEVENT
        // lisenter: owner scene controller
        kMsgTouchCancelled,
            
        // key: SC_KEY_X
        // key: SC_KEY_Y
        // key: SC_KEY_Z
        // key: SC_KEY_TIMESTAMP
        // key: SC_KEY_CCEVENT
        kMsgAcceleration,
            
        // key: SC_KEY_KEYBOARDCODE
        // key: SC_KEY_CCEVENT
        kMsgKeyboardKeyDown,
            
        // key: SC_KEY_KEYBOARDCODE
        // key: SC_KEY_CCEVENT
        kMsgKeyboardKeyUp,
            
        // key: SC_KEY_CCREF
        kMsgNodeClicked,
            
        kMsgSettingMusicChanged,
        kMsgSettingSoundChanged,
        // show alert box,
        // must block it if want to show customize alert box
        // otherwise will show with system alert box
        // SC_KEY_TITLE => SCString
        // SC_KEY_TEXT => SCString
        // SC_KEY_ID => int
        // SC_KEY_STRING0 => SCString
        // SC_KEY_STRING1 => SCString (optional)
        // SC_KEY_STRING2 => SCString (optional)
//            kMsgShowAlertBox,

		// SC_KEY_ID:<int>, entity id
		// SC_KEY_RESULT:<bool>, new active state
		kMsgEntityActiveChanged, 

		// SC_KEY_ID:<int>, strategy id
		// SC_KEY_RESULT:<bool>, new active state
		kMsgStrategyActiveChanged,
            
        // SC_KEY_ID => int
        // SC_KEY_RESULT => int
        kMsgAlertBoxSelected,
        //        // "number" => int; number of scenes to back
        //        kMsgViewBack,
            
        // store prcoess cancelled by user
        // no parameter
        kMsgStoreUserCancelled,
            
        // IAP purchased is success
        // SC_KEY_FEATUREID => int
        kMsgStorePurchaseSuccess,
            
        // IAP purchased is failed
        // SC_KEY_FEATUREID => int
        kMsgStorePurchaseFailed,
            
        // IAP restored is success
        // delivery: post
        kMsgStoreRestoreSuccess,
            
        // IAP restored is failed
        // delivery: post
        kMsgStoreRestoreFailed,
            
        // retrieve IAP success
        // SC_KEY_FEATUREID => int
        // SC_KEY_CURRENCY => SCString
        // SC_KEY_PRICE => float
        kMsgStoreIAPInfoSuccess,
            
        // retrieve IAP failed
        kMsgStoreIAPInfoFailed,
            
        // "layer" => cocos2d::Ref*; touch belong to layer
        //        kMsgTouch,
            
        // send this message every frame
        // delivery: send
        // key: SC_KEY_DELTA
        kMsgFrame,
            
        // MSG_ARG_KEY_CONTROLLER/SC_KEY_CONTROLLER => SCViewController*
        kMsgModalSceneGotFocus,
            
        // MSG_ARG_KEY_CONTROLLER/SC_KEY_CONTROLLER => SCViewController*
        kMsgModalSceneLostFocus,
            
        //        // MSG_ARG_KEY_CONTROLLER/SC_KEY_CONTROLLER => SCViewController*
        //        kMsgPushModalScene,
            
        // SC_KEY_ID
        // for download text, SC_KEY_RESULT is SCString
        // for download json, SC_KEY_RESULT is SCDictionary
        // for download data, SC_KEY_RESULT is SCDataBlock
        // for download file, SC_KEY_RESULT is SCString of path
        kMsgHttpDownloadCompleted,
            
        // SC_KEY_ID
        kMsgHttpDownloadFailed,
        
        // SC_KEY_ID
        // for previous language SC_KEY_LANGUAGE_PRE
        // for current language SC_KEY_LANGUAGE_CUR
        kMsgLanguageChanged,

		// SC_KEY_FSMSTATECOMP
		kMsgFSMStateChanged,
        
//            // SC_KEY_ID
//            // SC_KEY_SIZE, total file size
//            kMsgHttpDownloadFileLength,
//            
//            // SC_KEY_ID
//            // SC_KEY_SIZE, delta size of data is written
//            kMsgHttpDownloadFileDataWriten,
            
    };
    
    // strategy ID
    enum Stgy
    {
		kStgyAuto = -1,
        kStgyNull  = 0,
            
        kStgyEmpty,
    };
    
    // entity ID
    enum Ent
    {
        kEntAuto = -1,
        kEntNull = 0,
    };
    
    enum State
    {
        kStateInvalid = 0xffffffff,
    };
        
    enum {kUserID = 65535};
        
};
NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCID_H__
