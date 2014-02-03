# Copyright (C) 2009 The Android Open Source Project
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
#
LOCAL_PATH := $(call my-dir)

#libRtORB
include $(CLEAR_VARS)
LOCAL_MODULE    := prebuild-libRtORB
LOCAL_SRC_FILES := libRtORB.so
include $(PREBUILT_SHARED_LIBRARY)

# local src

include $(CLEAR_VARS)

LOCAL_MODULE    := SS2012FPGA-jni
LOCAL_SRC_FILES := SS2012FPGA-common.c SS2012FPGA-stubs.c SS2012FPGA-jni.c
LOCAL_SHARED_LIBRARIES := prebuild-libRtORB
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
