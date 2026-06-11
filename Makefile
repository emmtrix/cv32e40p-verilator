APP ?= hello-world

.PHONY: all firmware verilate run clean

all: run

firmware:
	$(MAKE) -C sw APP=$(APP) firmware

verilate:
	$(MAKE) -C tb verilate

run: firmware
	$(MAKE) -C tb APP=$(APP) run

clean:
	$(MAKE) -C sw clean
	$(MAKE) -C tb clean
