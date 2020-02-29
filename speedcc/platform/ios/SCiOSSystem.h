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

#ifndef __SC__SCiOSSYSTEM_H__
#define __SC__SCiOSSYSTEM_H__

#import <UIKit/UIKit.h>

@interface SCiOSSystem : NSObject

+(SCiOSSystem*) sharedSystem;
-(id)init;
-(void)showAlertView:(NSString*)title
            message:(NSString*)message
            button1:(NSString*)button1
            button2:(NSString*)button2
            button3:(NSString*)button3
           buttonID:(int)buttonID;

@end


#endif // __SC__SCiOSSYSTEM_H__
