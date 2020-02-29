LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := SpeedCC_static
LOCAL_MODULE_FILENAME := libSpeedCC

#$(call import-add-path,$(LOCAL_PATH)/../../../../cocos2d-x/v3)
#$(call import-add-path,$(LOCAL_PATH)/../../../../cocos2d-x/v3/external)
#$(call import-add-path,$(LOCAL_PATH)/../../../../cocos2d-x/v3/cocos)
#$(call import-add-path,$(LOCAL_PATH)/../../../../cocos2d-x/v3/cocos/audio/include)
#$(call import-add-path,$(LOCAL_PATH)/../../../..)


LOCAL_SRC_FILES := ../../../base/SCMemAllocator.cpp \
					../../../base/SCString.cpp \
					../../../base/SCDataBlock.cpp \
					../../../base/SCDateTime.cpp \
					../../../base/SCDictionary.cpp \
					../../../base/SCObject.cpp \
					../../../base/SCValue.cpp \
					../../../base/SCVersion.cpp \
					../../../base/SCWatchString.cpp \
					../../../base/SCBinder.cpp \
					../../../cocos/SCBinderCocos.cpp \
					../../../cocos/SCEventEmitter.cpp \
					../../../cocos/SCNodeClickable.cpp \
					../../../cocos/SCNodeStyle.cpp \
					../../../cocos/SCNodeUtils.cpp \
					../../../cocos/SCRefHolder.cpp \
					../../../cocos/SCScene.cpp \
					../../../cocos/SCSceneController.cpp \
					../../../cocos/SCSceneNavigator.cpp \
					../../../cocos/SCUIArg.cpp \
					../../../cocos/SCSceneBuilder.cpp \
					../../../cocos/SCNodeAttachment.cpp \
					../../../cocos/SCRadioGroup.cpp \
					../../../stage/SCActor.cpp \
					../../../stage/SCBehaviorCocos.cpp \
					../../../stage/SCBehaviorCommon.cpp \
					../../../stage/SCBehaviorStage.cpp \
					../../../stage/SCMessage.cpp \
					../../../stage/SCMessageDefaultProc.cpp \
					../../../stage/SCMessageDispatch.cpp \
					../../../stage/SCPerformObject.cpp \
					../../../stage/SCRole.cpp \
					../../../stage/SCRoleBuilder.cpp \
					../../../stage/SCStage.cpp \
					../../../stage/SCStrategy.cpp \
					../../../system/SCAudioManager.cpp \
					../../../system/SCSetting.cpp \
					../../../system/SCStore.cpp \
					../../../system/SCSystem.cpp \
					../../../network/SCHttpFetcher.cpp \
					../../../platform/SCOSSystem.cpp \
					src/main/cpp/SCAndroidAppEnv.cpp \
					src/main/cpp/SCAndroidSystem.cpp \





LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../base \
					$(LOCAL_PATH)/../../../cocos \
                    $(LOCAL_PATH)/../../../stage \
                    $(LOCAL_PATH)/../../../platform \
                    $(LOCAL_PATH)/../../../system \
                    $(LOCAL_PATH)/../../.. \
                    $(LOCAL_PATH)/../../../../cocos2d-x/v3/cocos \
                    $(LOCAL_PATH)/../../../../cocos2d-x/v3/external \
                    $(LOCAL_PATH)/../../../../cocos2d-x/v3/cocos/audio/include \
                    $(LOCAL_PATH)/../../../../cocos2d-x/v3 \

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_STATIC_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
