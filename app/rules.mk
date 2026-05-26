LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULE_DEPS := \
	lib/libobjc

MODULE_SRCS += \
	$(LOCAL_DIR)/app.c \
	$(LOCAL_DIR)/app_objc.m

MODULE_OPTIONS := extra_warnings

include make/module.mk
