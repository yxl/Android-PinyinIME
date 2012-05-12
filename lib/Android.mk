LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
         $(call all-subdir-java-files) \
         name/yxl/inputmethod/pinyin/IPinyinDecoderService.aidl

LOCAL_MODULE := name.yxl.inputmethod.pinyin.lib

include $(BUILD_STATIC_JAVA_LIBRARY)
