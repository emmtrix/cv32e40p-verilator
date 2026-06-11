# CV32E40P Single-Core Standalone Verilator Testbench

This directory is a standalone Verilator flow for one CV32E40P core.

- It uses RTL directly from the `cv32e40p` git submodule.
- It does not invoke `core-v-verif` Makefiles.
- It instantiates one core (`hart_id = 0`) with `COREV_PULP=1` and `FPU=0`.
- It supports runtime firmware loading through simulator plusargs.

## Prerequisites

- Verilator in `PATH`
- CORE-V toolchain in `/opt/corev`

## Run

```sh
cd cv32e40p-verilator
git submodule update --init --recursive
make run
```

By default, `make run` builds `sw/hello-world.c` into `build/fw/hello-world.elf`, then loads it at runtime.

To run an externally provided ELF executable at runtime:

```sh
make run ELF=/absolute/path/to/program.elf
```

The Makefile converts the selected ELF to `build/fw/runtime.hex` and launches:

```sh
build/verilator/obj_dir/Vtb_top_verilator +firmware=build/fw/runtime.hex +maxcycles=...
```

## Pytest

Example app expected output includes `[TB] SINGLE CORE EXIT SUCCESS`.

## Examples

- `sw/hello-world.c`: prints a hello world pass banner.
- `sw/float-add.c`: adds two floats.
- `sw/math-lib.c`: uses `sinf`, `sqrtf`, and `expf` from `math.h`.
- `sw/corev-simd.c`: uses the CORE-V SIMD instruction `cv.add.h` via inline assembly.

## Useful targets

- `make firmware` : build default firmware (`build/fw/hello-world.elf`)
- `make APP=float-add run` : float addition example
- `make APP=math-lib APP_LIBS="-lm -lc -lgcc" run` : `math.h` example (links libm)
- `make APP=corev-simd APP_ARCH=rv32imc_zicsr_zifencei_xcvsimd run` : SIMD example
- `make verilate` : compile RTL/testbench with Verilator
- `make run MAXCYCLES=5000000` : run with a custom cycle limit
- `make clean` : remove build artifacts

## Optional waveform dump

Enable VCD tracing by passing `VERI_TRACE=--trace` and enabling `VCD_TRACE` in C++ compile flags, for example:

```sh
make clean
make run VERI_TRACE=--trace VERI_CFLAGS="-O2 -DVCD_TRACE"
```

The waveform file is written to `build/verilator/waves.vcd`.

## License

Licensed under the Apache 2.0 license.
