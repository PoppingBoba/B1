LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULE_DEPS := \
	lib/libc

MODULE_SRCS += \
	$(LOCAL_DIR)/objc_runtime.c \
	$(LOCAL_DIR)/Object.m

include make/module.mk