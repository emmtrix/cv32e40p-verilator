APP ?= hello-world
ELF := $(abspath build/fw/$(APP).elf)

.PHONY: all firmware verilate run clean

all: run

firmware:
	$(MAKE) -C sw APP=$(APP) firmware

verilate:
	$(MAKE) -C tb verilate

run: firmware
	$(MAKE) -C tb ELF=$(ELF) run

clean:
	$(MAKE) -C sw clean
	$(MAKE) -C tb clean
