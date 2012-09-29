#-------------------------------------------------------------------
# This file has been automatically generated by ProjectGenerator    
# which is part of a build system designed for GUCEF                
#     (Galaxy Unlimited Framework)                                  
# For the latest info, see http://www.VanvelzenSoftware.com/        
#                                                                   
# The contents of this file are placed in the public domain. Feel   
# free to make use of it in any way you like.                       
#-------------------------------------------------------------------


ifndef MY_MODULE_PATH
  MY_MODULE_PATH := $(call my-dir)
endif
LOCAL_PATH := $(MY_MODULE_PATH)

include $(CLEAR_VARS)

@echo Module path: $(MY_MODULE_PATH)
LOCAL_MODULE := MyGUI.OpenGLESPlatform
LOCAL_MODULE_FILENAME := libMyGUI.OpenGLESPlatform
@echo Module name: $(LOCAL_MODULE)

LOCAL_SRC_FILES := \
  src/MyGUI_OpenGLRenderManager.cpp \
  src/MyGUI_OpenGLRTTexture.cpp \
  src/MyGUI_OpenGLTexture.cpp \
  src/MyGUI_OpenGLVertexBuffer.cpp

LOCAL_C_INCLUDES := \
  $(MY_MODULE_PATH)/../../../../dependencies/MyGui/Common/FileSystemInfo \
  $(MY_MODULE_PATH)/include \
  $(MY_MODULE_PATH)/../../../../dependencies/MyGui/MyGUIEngine/include \
  $(MY_MODULE_PATH)/../../../../dependencies/freetype/include \
  $(MY_MODULE_PATH)/../../../../dependencies/freetype/include/freetype \
  $(MY_MODULE_PATH)/../../../../dependencies/freetype/include/freetype/config \
  $(MY_MODULE_PATH)/../../../../dependencies/freetype/include/freetype/internal \
  $(MY_MODULE_PATH)/../../../../dependencies/freetype/include/freetype/internal/services \
  $(MY_MODULE_PATH)/../../../../dependencies/freetype/src/winfonts


LOCAL_SHARED_LIBRARIES := \
  MyGUI.Engine


LOCAL_LDLIBS := \
  -lGLESv1_CM

include $(BUILD_STATIC_LIBRARY)
