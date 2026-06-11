CV32E40P_DIR ?= ../cv32e40p
RTL_DIR := $(abspath $(CV32E40P_DIR)/rtl)
MANIFEST := $(CV32E40P_DIR)/cv32e40p_manifest.flist

TOOLCHAIN_ROOT ?= /opt/corev
RISCV_PREFIX ?= riscv32-corev-elf-
OBJCOPY := $(TOOLCHAIN_ROOT)/bin/$(RISCV_PREFIX)objcopy

VERILATOR ?= verilator
VERI_CFLAGS ?= -O2
VERI_TRACE ?=
MAXCYCLES ?= 2000000
LOG_FILE ?=

BUILD_DIR ?= ../build
FW_BUILD_DIR := $(BUILD_DIR)/fw
VERI_BUILD_DIR := $(BUILD_DIR)/verilator
VERI_OBJ_DIR := $(VERI_BUILD_DIR)/obj_dir

SV_TB_SRCS := \
	tb_top_verilator.sv \
	tb_cv32e40p_cluster_wrapper.sv \
	tb_riscv/include/perturbation_defines.sv \
	tb_riscv/riscv_rvalid_stall.sv \
	tb_riscv/riscv_gnt_stall.sv \
	mm_ram.sv \
	dp_ram.sv \
	scratchpad_ram.sv

CPP_TB_SRC := $(abspath tb_top_verilator.cpp)
SIM_EXE := $(VERI_OBJ_DIR)/Vtb_top_verilator

HEX := $(FW_BUILD_DIR)/runtime.hex

.PHONY: run verilate clean

run: verilate
	@test -f "$(ELF)" || { echo "Missing ELF: $(ELF)"; exit 1; }
	$(OBJCOPY) -O verilog $(ELF) $(HEX)
	$(SIM_EXE) +firmware=$(HEX) +maxcycles=$(MAXCYCLES)$(if $(strip $(LOG_FILE)), +log_file=$(LOG_FILE),)

verilate: $(SIM_EXE)

$(SIM_EXE): $(SV_TB_SRCS) $(CPP_TB_SRC) $(MANIFEST) | $(VERI_BUILD_DIR)
	DESIGN_RTL_DIR=$(RTL_DIR) $(VERILATOR) --cc --sv --exe \
		--top-module tb_top_verilator \
		--Wno-lint --Wno-UNOPTFLAT --Wno-MODDUP \
		--Wno-BLKANDNBLK --Wno-MULTIDRIVEN --Wno-COMBDLY \
		$(VERI_TRACE) \
		$(SV_TB_SRCS) -f $(MANIFEST) $(CPP_TB_SRC) \
		--Mdir $(VERI_OBJ_DIR) \
		-CFLAGS "-std=gnu++14 $(VERI_CFLAGS)"
	$(MAKE) -C $(VERI_OBJ_DIR) -f Vtb_top_verilator.mk

$(VERI_BUILD_DIR):
	mkdir -p $(VERI_BUILD_DIR)

clean:
	rm -rf $(VERI_BUILD_DIR)
