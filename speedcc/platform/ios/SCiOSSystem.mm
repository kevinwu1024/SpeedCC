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


#import "SCiOSSystem.h"

#import <Foundation/Foundation.h>
#import <AdSupport/AdSupport.h>

#include <sys/sysctl.h>
#include <string.h> 

#import "support/Reachability.h"


UIViewController* s_rootViewController = nil;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
    
    // callback functions
    void scbInternetReachableChanged(const bool bNewState);
//    void scbAppEnterBackground();
//    void scbAppEnterForeground();
    void scbAppLaunched();
    
    void scbAlertBoxSelected(const int nAlertBoxID,const int nButton);
    void scbReflectShowAlertBox(const char* pszTitle,
                                const char* pszMessge,
                                const char* pszButton1,
                                const char* pszButton2,
                                const char* pszButton3,
                                const int nAlertBoxID);
    
    // inernal functions
    bool scinGetVersion(NSString* versionString,int* pMajor,int* pMinor,int* pFix);
    
    ///---------------- datetime related
    
    // datetime
    int scGetMonthName(char* pszBuf,const int nBufSize,const int nMonth,const bool bShort)
    {
        int nRet = 0;
        
        if(nMonth<=12 && nMonth>0)
        {
            NSDateFormatter* df = [[NSDateFormatter alloc] init];
            NSString* monthName = [ (bShort ? [df shortMonthSymbols] : [df monthSymbols]) objectAtIndex:(nMonth-1)];
            
            if(pszBuf && monthName.length<nBufSize)
            {
                strcpy(pszBuf,[monthName UTF8String]);
                nRet = (int)monthName.length;
            }
            else if(!pszBuf)
            {
                nRet = (int)monthName.length + 2;
            }
        }
        
        return nRet;
    }
    
    int scGetWeekName(char* pszBuf,const int nBufSize,const int nWeek,const bool bShort)
    {
        int nRet = 0;
        
        if(nWeek<=7 && nWeek>0)
        {
            NSDateFormatter* df = [[NSDateFormatter alloc] init];
            NSString* weekName = [ (bShort ? [df shortWeekdaySymbols] : [df weekdaySymbols]) objectAtIndex:(nWeek-1)];
            
            if(pszBuf && weekName.length<nBufSize)
            {
                strcpy(pszBuf,[weekName UTF8String]);
                nRet = (int)weekName.length;
            }
            else if(!pszBuf)
            {
                nRet = (int)weekName.length + 2;
            }
        }
        
        return nRet;
    }
    
    ////---------------- system related
    void scInitSpeedCC(void* pController)
    {
        s_rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
        [SCiOSSystem sharedSystem];
    }
    
    void scSetMultipleTouch(const bool bEnable)
    {
        assert(s_rootViewController!=nil);
        [s_rootViewController.view setMultipleTouchEnabled:bEnable?YES:NO];
    }
    
    bool scGetMultipleTouch()
    {
        assert(s_rootViewController!=nil);
        return s_rootViewController.view.multipleTouchEnabled ? true : false;
    }
    
    bool scGetOSVersion(int* pMajor,int* pMinor,int* pFix)
    {
        return scinGetVersion([UIDevice currentDevice].systemVersion,pMajor,pMinor,pFix);
    }
    
    // OS type. 0: unknown; 1: iOS; 2: Android
    // OS distribution. 0: unkown; 1: apple;
    // device type. 0: unkown; 1: phone; 2: tablet; 3: tv; 4:vehicle;
    // store type. 0:unkown; 1: apple app store; 2: google play; 3: amazon;
    bool scGetDeviceInfo(int* pOSMainType,
                         int* pOSDistributionType,
                         int* pDeviceType,
                         int* pIsSimulator,
                         int* pStoreType,
                         char* pszHwBuffer,
                         const int nHwBufferSize)
    {
        if(pOSMainType)
        {
            *pOSMainType = 1; // iOS
        }
        
        if(pOSDistributionType)
        {
            *pOSDistributionType = 1; // apple
        }
        
        if(pStoreType)
        {
            *pStoreType = 1; // app store
        }
        
        if(pDeviceType)
        {
            *pDeviceType = 0;
            UIUserInterfaceIdiom device = [UIDevice currentDevice].userInterfaceIdiom;
            if(device==UIUserInterfaceIdiomUnspecified)
            {
                *pDeviceType = 0;
            }
            else if(device==UIUserInterfaceIdiomPhone)
            {
                *pDeviceType = 1;
            }
            else if(device==UIUserInterfaceIdiomPad)
            {
                *pDeviceType = 2;
            }
            else
            {
                *pDeviceType = 0;
            }
        }
        
        if(pszHwBuffer)
        {
            size_t size;
            sysctlbyname("hw.machine", NULL, &size, NULL, 0);
            char* machine = (char*)malloc(size);
            sysctlbyname("hw.machine", machine, &size, NULL, 0);
            NSString *platform = [NSString stringWithUTF8String:machine];
            free(machine);
            
            if(pszHwBuffer && platform.length<nHwBufferSize)
            {
                strcpy(pszHwBuffer,[platform UTF8String]);
            }
        }
        
        if(pIsSimulator)
        {
#if TARGET_OS_SIMULATOR
            *pIsSimulator = 1;
#else
            *pIsSimulator = 0;
#endif
        }
        
        return true;
    }
    
    bool scGetFreeStorage(unsigned long* pInternal,unsigned long* pExternal)
    {
        bool bRet = false;
        
        if(pExternal)
        {
            *pExternal = 0;
        }
        
        if(pInternal)
        {
            uint64_t totalSpace = 0;
            uint64_t totalFreeSpace = 0;
            NSError* error = nil;
            NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
            NSDictionary *dictionary = [[NSFileManager defaultManager] attributesOfFileSystemForPath:[paths lastObject]
                                                                                               error: &error];
            
            if (dictionary)
            {
                NSNumber *fileSystemSizeInBytes = [dictionary objectForKey: NSFileSystemSize];
                NSNumber *freeFileSystemSizeInBytes = [dictionary objectForKey:NSFileSystemFreeSize];
                totalSpace = [fileSystemSizeInBytes unsignedLongLongValue];
                totalFreeSpace = [freeFileSystemSizeInBytes unsignedLongLongValue];
                NSLog(@"Memory Capacity of %llu MiB with %llu MiB Free memory available.", ((totalSpace/1024ll)/1024ll), ((totalFreeSpace/1024ll)/1024ll));
                
                *pInternal = totalFreeSpace;
                
                bRet = true;
            }
        }
        
        return bRet;
    }
    
    // 0: unknown; 1: portrait; 2: portrait upside down;
    // 3: landscape right; 4: landscape left
    int scGetDeviceOrientation()
    {
        switch([UIApplication sharedApplication].statusBarOrientation)
        {
            case UIInterfaceOrientationUnknown: return 0;
            case UIInterfaceOrientationPortrait: return 1;
            case UIInterfaceOrientationPortraitUpsideDown: return 2;
            case UIInterfaceOrientationLandscapeLeft: return 4;
            case UIInterfaceOrientationLandscapeRight: return 3;
        }
    }
    
    
    void scShowSystemAlertBox(const char* pszTitle,
                              const char* pszMessge,
                              const char* pszButton1,
                              const char* pszButton2,
                              const char* pszButton3,
                              const int nAlertBoxID)
    {
        NSString* title = @"";
        if(pszTitle!=NULL)
        {
            title = [NSString stringWithUTF8String:pszTitle];
        }
        
        NSString* message = @"";
        if(pszMessge!=NULL)
        {
            message = [NSString stringWithUTF8String:pszMessge];
        }
        
        NSString* button1 = nil;
        if(pszButton1!=NULL)
        {
            button1 = [NSString stringWithUTF8String:pszButton1];
        }
        
        NSString* button2 = nil;
        if(pszButton2!=NULL)
        {
            button2 = [NSString stringWithUTF8String:pszButton2];
        }
        
        NSString* button3 = nil;
        if(pszButton3!=NULL)
        {
            button3 = [NSString stringWithUTF8String:pszButton3];
        }
        
        [[SCiOSSystem sharedSystem] showAlertView:title
                                          message:message
                                          button1:button1
                                          button2:button2
                                          button3:button3
                                         buttonID:nAlertBoxID];
    }
    
    ///-------- app related
    
    bool scGetAppVersion(int* pMajor,int* pMinor,int* pFix)
    {
        NSString* versionString = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
        return scinGetVersion(versionString,pMajor,pMinor,pFix);
    }
    
    int scGetProductName(char* pszBuffer, int nBufferSize)
    {
        NSString *prodName = [[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString *)kCFBundleNameKey];
        
        if(pszBuffer==NULL)
        {
            return (int)prodName.length;
        }
        else
        {
            if(prodName.length<nBufferSize)
            {
                strcpy(pszBuffer,[prodName cStringUsingEncoding:NSUTF8StringEncoding]);
                return (int)prodName.length;
            }
        }
        
        return 0;
    }
    
    int scGetBundleID(char* pszBuffer, const int nBufferSize)
    {
        int nLength = (int)[[NSBundle mainBundle] bundleIdentifier].length;
        
        if(pszBuffer==NULL)
        {
            return nLength;
        }
        else
        {
            if(nBufferSize>nLength)
            {
                strcpy(pszBuffer,[[[NSBundle mainBundle] bundleIdentifier] UTF8String]);
                return nLength;
            }
        }
        
        return 0;
    }
    
    ///---------------- internal functions
    bool scinGetVersion(NSString* versionString,int* pMajor,int* pMinor,int* pFix)
    {
        NSArray *version = [versionString componentsSeparatedByString:@"."];
        
        if(version==nil || version.count<2)
        {
            return false;
        }
        
        if(pMajor)
        {
            *pMajor = [[version objectAtIndex:0] intValue];
        }
        
        if(pMinor)
        {
            *pMinor = [[version objectAtIndex:1] intValue];
        }
        
        if(pFix)
        {
            *pFix = (version.count>2) ? [[version objectAtIndex:2] intValue] : 0;
        }
        
        return true;
    }
    
    
    bool scGetResourcePath(char* pszBuffer,const int nBufferSize)
    {
        NSString* str = [[NSBundle mainBundle] resourcePath];
        
        if(pszBuffer && nBufferSize > str.length)
        {
            ::strcpy(pszBuffer,[str UTF8String]);
            return true;
        }
        
        return false;
    }
    
    
    bool scAndroidGetSDCardWritablePath(char* pszPathBuf, const int nBufSize)
    {
        NSLog(@"iOS doesn't support scAndroidGetSDCardWritablePath()");
        return false;
    }
    
    bool scAndroidInstallAPK(const char* pszAPKFile)
    {
        NSLog(@"iOS doesn't support scAndroidInstallAPK()");
        return false;
    }

#ifdef __cplusplus
}
#endif  // __cplusplus


////---------------- SCiOSSystem

@implementation SCiOSSystem
SCiOSSystem* s_shareSystem = nil;

+(SCiOSSystem*) sharedSystem
{
    if(s_shareSystem==nil)
    {
        s_shareSystem = [[SCiOSSystem alloc]init];
    }
    
    return s_shareSystem;
}

-(id)init
{
    self = [super init];
    
    if(self)
    {
//        [[NSNotificationCenter defaultCenter] addObserver: self
//                                                 selector: @selector(applicationDidFinishLaunching:)
//                                                     name: UIApplicationDidFinishLaunchingNotification
//                                                   object: nil];
        
//        [[NSNotificationCenter defaultCenter] addObserver: self
//                                                 selector: @selector(applicationDidBecomeActive:)
//                                                     name: UIApplicationDidBecomeActiveNotification
//                                                   object: nil];
        /*
        [[NSNotificationCenter defaultCenter] addObserver: self
                                                 selector: @selector(applicationWillEnterForeground:)
                                                     name: UIApplicationWillEnterForegroundNotification
                                                   object: nil];
        
        [[NSNotificationCenter defaultCenter] addObserver: self
                                                 selector: @selector(applicationDidEnterBackground:)
                                                     name: UIApplicationDidEnterBackgroundNotification
                                                   object: nil];
        */
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(reachabilityChanged:)
                                                     name:kReachabilityChangedNotification
                                                   object:nil];
    }
    
    return self;
}

-(void)showAlertView:(NSString*)title
            message:(NSString*)message
            button1:(NSString*)button1
            button2:(NSString*)button2
            button3:(NSString*)button3
           buttonID:(int)buttonID
{
    UIAlertView* alert = [[UIAlertView alloc] initWithTitle:title
                                                    message:message
                                                   delegate:self
                                          cancelButtonTitle:button1
                                          otherButtonTitles:[button2 length]>0?button2:nil,
                          ([button2 length]>0 && [button3 length]>0)?button3:nil,
                          nil];
    alert.tag = buttonID;
    [alert show];
}

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex
{
    scbAlertBoxSelected((int)alertView.tag,(int)buttonIndex);
}

-(void)reachabilityChanged:(NSNotification*)note
{
    Reachability* reach = [note object];
    NetworkStatus status = [reach currentReachabilityStatus];
    
    scbInternetReachableChanged(status==NotReachable);
}

//-(void) applicationDidFinishLaunching:(UIApplication*)application
//{
//    ::scbAppLaunched();
//}

//-(void) applicationDidEnterBackground:(UIApplication*)application
//{   
//    ::scbAppEnterBackground();
//}
//
////- (void)applicationDidBecomeActive:(UIApplication *)application
////{
////
////}
//
//-(void) applicationWillEnterForeground:(UIApplication*)application
//{
//    ::scbAppEnterForeground();
//}

@end
