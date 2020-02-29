LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                ../../../../gtest/src/gtest-all.cc \
                   ../../../Classes/TestSCString.cpp \
                   ../../../Classes/TestSCDataBlock.cpp \
                   ../../../Classes/TestSCValue.cpp \
                   ../../../Classes/TestSCWatchNumber.cpp \
                   ../../../Classes/TestSCWatchString.cpp \
                   ../../../Classes/TestSCNodeProperty.cpp \
                   ../../../Classes/TestSCComponent.cpp \
                   ../../../Classes/TestSCDictionary.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
                    $(LOCAL_PATH)/../../../../../speedcc \
                    $(LOCAL_PATH)/../../../../../cocos2dx/v3/cocos \
                    $(LOCAL_PATH)/../../../../gtest/include \
                    $(LOCAL_PATH)/../../../../gtest \

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := SpeedCC_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,../../../../speedcc/platform/android/speedcc)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
