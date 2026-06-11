TOOLCHAIN_ROOT ?= /opt/corev
RISCV_PREFIX ?= riscv32-corev-elf-
CROSS := $(TOOLCHAIN_ROOT)/bin/$(RISCV_PREFIX)
CC := $(CROSS)gcc
AR := $(CROSS)ar

RISCV_ARCH ?= rv32imc_zicsr_zifencei
RISCV_ABI ?= ilp32
APP_ARCH ?= $(RISCV_ARCH)
APP_ABI ?= $(RISCV_ABI)
APP_CFLAGS ?=
APP_LIBS ?= -lc -lgcc -lm
APP_LDFLAGS ?=
CFLAGS := -Os -g -Wall -pedantic -mabi=$(APP_ABI) -march=$(APP_ARCH) $(APP_CFLAGS)

BUILD_DIR ?= ../build
FW_BUILD_DIR := $(BUILD_DIR)/fw

APP ?= hello-world
FW_ELF := $(FW_BUILD_DIR)/$(APP).elf

BSP_SRCS := ../bsp/crt0.S ../bsp/handlers.S ../bsp/vectors.S ../bsp/syscalls.c
BSP_OBJS := $(addprefix $(FW_BUILD_DIR)/,$(notdir $(BSP_SRCS:.S=.o)))
BSP_OBJS := $(BSP_OBJS:.c=.o)
BSP_LIB := $(FW_BUILD_DIR)/libcv-verif.a

APP_OBJ := $(FW_BUILD_DIR)/$(APP).o

.PHONY: firmware clean

firmware: $(FW_ELF)

$(FW_ELF): $(APP_OBJ) $(BSP_LIB) ../bsp/link.ld | $(FW_BUILD_DIR)
	$(CC) $(CFLAGS) -nostartfiles -o $@ \
		$(APP_OBJ) -T ../bsp/link.ld -L$(FW_BUILD_DIR) -lcv-verif \
		$(APP_LIBS) $(APP_LDFLAGS)

$(BSP_LIB): $(BSP_OBJS)
	$(AR) rcs $@ $^

$(FW_BUILD_DIR)/%.o: ../bsp/%.S | $(FW_BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(FW_BUILD_DIR)/%.o: ../bsp/%.c | $(FW_BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(APP_OBJ): $(APP).c | $(FW_BUILD_DIR)
	$(CC) $(CFLAGS) -I ../bsp -I . -c $< -o $@

$(FW_BUILD_DIR):
	mkdir -p $(FW_BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
