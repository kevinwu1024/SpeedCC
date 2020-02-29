#import <UIKit/UIKit.h>
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
//    @autoreleasepool {
//        return UIApplicationMain(argc, argv, nil, @"AppController");
//    }
    @autoreleasepool {
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}
