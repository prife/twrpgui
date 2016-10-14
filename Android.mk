# Copyright (C) 2007 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

RECOVERY_PATH := bootable/recovery/
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

TARGET_RECOVERY_GUI := true

LOCAL_SRC_FILES := \
    appdemo/main.cpp \
    common/find_file.cpp \
    common/infomanager.cpp \
    common/set_metadata.c \
    common/data.cpp \
    common/twrp-functions.cpp \
	common/tw_atomic.cpp \

LOCAL_MODULE := testui

RECOVERY_API_VERSION := 3
RECOVERY_FSTAB_VERSION := 2
LOCAL_CFLAGS += -DRECOVERY_API_VERSION=$(RECOVERY_API_VERSION)
LOCAL_CFLAGS += -Wno-unused-parameter

LOCAL_C_INCLUDES += \
    system/vold \
    system/extras/ext4_utils \
    system/core/adb \
    system/core/libsparse \
    $(RECOVERY_PATH) \
    $(RECOVERY_PATH)/ui/include

LOCAL_FORCE_STATIC_EXECUTABLE := true

LOCAL_STATIC_LIBRARIES := \
    libguitwrp \
	libminuitwrp \
    libminzip \
    libft2 \
    libpng \
    libz \
    libselinux \
    libpixelflinger_twrp \
    libutils \
    liblog \
    libcutils \
    libc++_static \
    libm \
    libc

include $(BUILD_EXECUTABLE)

include $(call all-makefiles-under,$(LOCAL_PATH))
