LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULE_DEPS := 	\
	lib/libc	\
	lib/libcpp	\
	lib/b

MODULE_SRCS += $(LOCAL_DIR)/debug.c
MODULE_SRCS += $(LOCAL_DIR)/fs.c \
			   $(LOCAL_DIR)/fsplus.cc
MODULE_SRCS += $(LOCAL_DIR)/shell.c

MODULE_OPTIONS := test

include make/module.mk
