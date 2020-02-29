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

#import <Foundation/Foundation.h>
#import <sys/sysctl.h>

#import "SCiOSStore.h"


#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
    
    void scbStorePurchaseItemResult(const char* pszIAP,int nResult);
    void scbStoreRestoreItemResult(const char* pszIAP,int nResult);
    void scbStoreRetrieveItemInfoResult(const char* pszIAP, const char* pszCurrency, float fPrice,int nResult);
    void scbStoreUserCancelled();
    
    // callback: scbPurchaseItemResult()
    bool scStorePurchaseItem(const char* pszIAP,const bool bConsumable)
    {
        // bConsumable parameter for android use.
        if(pszIAP==NULL)
        {
            return false;
        }
        
        return [[SCiOSStore sharedStore] purchase:[NSString stringWithUTF8String:pszIAP]] ? true : false;
    }
    
    // callback: scbPurchaseItemInfoResult()
    bool scStoreRequestItemInfo(char** pszIAP,const int nIAPCount)
    {
        bool ret = false;
        
        if(pszIAP!=NULL && nIAPCount>0)
        {
            NSMutableArray* array = [[NSMutableArray alloc]init];
            
            for(int i=0; i<nIAPCount; ++i)
            {
                if(pszIAP[i]!=NULL)
                {
                    NSString* str = [NSString stringWithUTF8String:pszIAP[i]];
                    [array addObject:str];
                }
            }
            
            if(array.count>0)
            {
                [[SCiOSStore sharedStore] requestIAPInfo:array];
                ret = true;
            }
        }
        
        return ret;
    }
    
    // callback: scbPurchaseRestoreResult()
    bool scStoreRestorePurchased()
    {
        return [[SCiOSStore sharedStore] restore] ? true : false;
    }
    

#ifdef __cplusplus
}
#endif  // __cplusplus

@implementation SCiOSStore

static SCiOSStore* s_shareStore = nil;

+(SCiOSStore*) sharedStore
{
    if(s_shareStore==nil)
    {
        s_shareStore = [[SCiOSStore alloc]init];
    }
    
    return s_shareStore;
}

-(id) init
{
    if(self=[super init])
    {
        _productID2ProductDic = [[NSMutableDictionary alloc]init];
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    }
    
    return self;
}

-(BOOL) purchase:(NSString*)iap
{
    NSAssert(iap!=nil,@"iap should not be nil");
    BOOL ret = NO;
    if([SKPaymentQueue canMakePayments])
    {
        if(_productID2ProductDic.count==0)
        {
            NSLog(@"SpeedCC Error: There is no IAP Product cached, did requestIAPInfo() be called successfully?");
            ::scbStorePurchaseItemResult(NULL,1);
        }
        else
        {
            SKProduct* product = [_productID2ProductDic objectForKey:iap];
            if(product!=nil)
            {
                SKMutablePayment* payment = [SKMutablePayment paymentWithProduct:product];
                [[SKPaymentQueue defaultQueue] addPayment:payment];
                ret = YES;
            }
            else
            {
                NSLog(@"SpeedCC Error: There is no match IAP in cache.");
            }
            
        }
    }
    else
    {
        NSLog(@"Warning: Purchases are disabled on this device.");
    }
    
    return ret;
}

-(BOOL) restore
{
    if([SKPaymentQueue canMakePayments])
    {
        [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
    }
    else
    {
        NSLog(@"SpeedCC Warning: Purchases are disabled on this device.");
    }
    
    return NO;
}

-(void) requestIAPInfo:(NSArray<NSString*>*)iapArray
{
    if([SKPaymentQueue canMakePayments])
    {
        [_productID2ProductDic removeAllObjects];
        SKProductsRequest* request = [[SKProductsRequest alloc] initWithProductIdentifiers:
                                      [NSSet setWithArray:iapArray]];
        request.delegate = self;
        
        [request start];
    }
    else
    {
        NSLog(@"SpeedCC Warning: Purchases are disabled on this device.");
    }
}

#pragma mark Request IAP Info delegate methods
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    if (response.products.count > 0)
    {
        for (SKProduct* product in response.products)
        {
            [_productID2ProductDic setObject:product forKey:product.productIdentifier];
            
            ::scbStoreRetrieveItemInfoResult([product.productIdentifier cStringUsingEncoding:NSUTF8StringEncoding],
                                             [[product.priceLocale objectForKey:NSLocaleCurrencyCode] cStringUsingEncoding:NSUTF8StringEncoding],
                                            [[product price] floatValue],0);
        }
    }
    
    if (response.invalidProductIdentifiers.count > 0)
    {
        for (NSString* productID in response.invalidProductIdentifiers)
        {
            ::scbStoreRetrieveItemInfoResult([productID cStringUsingEncoding:NSUTF8StringEncoding],NULL,0,1);
        }
    }
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error
{
    NSLog(@"SpeedCC Error: Retrive IAP info failed. Reason: %@",error.localizedFailureReason);
    ::scbStoreRetrieveItemInfoResult(NULL,NULL,0,1);
}

#pragma mark purchase IAP Info delegate methods

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    for(SKPaymentTransaction* transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchasing:
            {
                NSLog(@"added payment to SKPaymentQueue, purchasing ... ");
            }
                break;
                
            case SKPaymentTransactionStatePurchased:
            {
                NSLog(@"SpeedCC Log: Deliver content for '%@'",transaction.payment.productIdentifier);
                
//                NSAssert(!transaction.downloads,@"IAP transaction should not be download");
//                if(!transaction.downloads)
                {
                    [self completeTransaction:transaction forStatus:IAPPurchaseSucceeded];
                }
            }
                break;
                
            case SKPaymentTransactionStateRestored:
            {
                NSLog(@"SpeedCC Log: Restore content for %@",transaction.payment.productIdentifier);
                
//                NSAssert(!transaction.downloads,@"IAP transaction should not be download");
//                if(!transaction.downloads)
                {
                    [self completeTransaction:transaction forStatus:IAPRestoredSucceeded];
                }
            }
                break;
                
            case SKPaymentTransactionStateFailed:
            {
                NSLog(@"SpeedCC Error: Purchase of '%@' failed. Reason: %@",transaction.payment.productIdentifier,transaction.error);
                [self completeTransaction:transaction forStatus:IAPPurchaseFailed];
            }
                break;
            default:
                break;
        }
    }
}


// Logs all transactions that have been removed from the payment queue
- (void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray *)transactions
{
    for(SKPaymentTransaction * transaction in transactions)
    {
        NSLog(@"SpeedCC Log: %@ was removed from the payment queue.", transaction.payment.productIdentifier);
    }
}


// Called when an error occur while restoring purchases. Notify the user about the error.
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error
{
    if(error.code == SKErrorPaymentCancelled)
    {
        ::scbStoreUserCancelled();
    }
    else
    {// restored failed
        ::scbStoreRestoreItemResult(NULL,1);
    }
}


// Called when all restorable transactions have been processed by the payment queue
- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue
{
    NSLog(@"SpeedCC Log: All restorable transactions have been processed by the payment queue.");
}


-(void)completeTransaction:(SKPaymentTransaction *)transaction forStatus:(NSInteger)status
{
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        switch(status)
        {
            case IAPPurchaseFailed:
                ::scbStorePurchaseItemResult([transaction.payment.productIdentifier cStringUsingEncoding:NSUTF8StringEncoding],1);
                break;
                
            case IAPPurchaseSucceeded:
                ::scbStorePurchaseItemResult([transaction.payment.productIdentifier cStringUsingEncoding:NSUTF8StringEncoding],0);
                break;
                
            case IAPRestoredSucceeded:
                ::scbStoreRestoreItemResult([transaction.payment.productIdentifier cStringUsingEncoding:NSUTF8StringEncoding],0);
                break;
                
            default:
                NSAssert(NO,@"SpeedCC Error: Unknown Status in IAP completeTransaction: method");
                break;
        }
    }
    else
    {
        ::scbStoreUserCancelled();
    }
    
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
}

@end
