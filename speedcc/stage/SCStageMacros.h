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

#ifndef __SPEEDCC__SCSTAGEMACROS_H__
#define __SPEEDCC__SCSTAGEMACROS_H__

///----------------------
#define SC_BVR_GROUP(_bvr_,...) \
    SpeedCC::SCBehaviorMultiple::create((_bvr_),##__VA_ARGS__)

#define SC_MSG_GROUP(_msg_,...) \
    SpeedCC::SCMessageGroup::create((_msg_),##__VA_ARGS__)

#define SC_MATCHER_GROUP(_mat_,...) \
    SpeedCC::SCMessageMatcherGroup::create((_mat_),##__VA_ARGS__)

#define SCMsgDisp() \
    (SpeedCC::SCMessageDispatch::getInstance())

#endif // __SPEEDCC__SCSTAGEMACROS_H__
