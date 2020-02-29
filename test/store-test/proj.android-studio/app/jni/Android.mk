LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#$(call import-add-path,$(LOCAL_PATH)/../../../../cocos2dx/v3)
#$(call import-add-path,$(LOCAL_PATH)/../../../../cocos2dx/v3/external)
#$(call import-add-path,$(LOCAL_PATH)/../../../../cocos2dx/v3/cocos)
#$(call import-add-path,$(LOCAL_PATH)/../../../../cocos2dx/v3/cocos/audio/include)
#$(call import-add-path,$(LOCAL_PATH)/../../../../speedcc/platform/android/speedcc)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/TestHomeController.cpp \
                   ../../../Classes/TestStageController.cpp \
                   ../../../Classes/TestLabelBindingController.cpp \
                   ../../../Classes/TestAlertBoxController.cpp \
                   ../../../Classes/TestCaseController.cpp \
                   ../../../Classes/TestDockController.cpp \
                   ../../../Classes/TestLoadingController.cpp \
                   ../../../Classes/TestPageViewController.cpp \
                   ../../../Classes/TestProgressController.cpp \
                   ../../../Classes/TestUIMiscController.cpp \



LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
                    $(LOCAL_PATH)/../../../../../speedcc \

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := SpeedCC_static
#LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,../../../../speedcc/platform/android/speedcc)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
