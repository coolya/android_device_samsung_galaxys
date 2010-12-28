ifeq ($(TARGET_DEVICE),galaxys)
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES +=\
    bootable/recovery/minui\
    external/libpng\
    external/zlib

LOCAL_SRC_FILES := graphics.c

ifneq ($(BOARD_LDPI_RECOVERY),)
    LOCAL_CFLAGS += -DBOARD_LDPI_RECOVERY='"$(BOARD_LDPI_RECOVERY)"'
endif

ifneq ($(BOARD_HAS_JANKY_BACKBUFFER),)
    LOCAL_CFLAGS += -DBOARD_HAS_JANKY_BACKBUFFER
endif

LOCAL_MODULE := libminui_galaxys
LOCAL_MODULE_TAGS := eng

include $(BUILD_STATIC_LIBRARY)
endif

