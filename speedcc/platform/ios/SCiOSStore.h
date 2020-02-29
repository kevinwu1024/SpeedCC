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

#ifndef __SPEEDCC__SCiOSSTORE_H__
#define __SPEEDCC__SCiOSSTORE_H__

#import <UIKit/UIKit.h>
#import <StoreKit/StoreKit.h>

@interface SCiOSStore : NSObject<SKPaymentTransactionObserver,SKRequestDelegate, SKProductsRequestDelegate>
{
    NSMutableDictionary*     _productID2ProductDic;
}

typedef NS_ENUM(NSInteger, IAPPurchaseNotificationStatus)
{
    IAPPurchaseFailed, // Indicates that the purchase was unsuccessful
    IAPPurchaseSucceeded, // Indicates that the purchase was successful
    IAPRestoredFailed, // Indicates that restoring products was unsuccessful
    IAPRestoredSucceeded, // Indicates that restoring products was successful
};

+(SCiOSStore*) sharedStore;

-(id) init;
-(BOOL) purchase:(NSString*)iap;
-(BOOL) restore;
-(void) requestIAPInfo:(NSArray<NSString*>*)iapArray;
@end


#endif // __SPEEDCC__SCiOSSTORE_H__
