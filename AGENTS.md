# AGENTS

## Project Goal

This repository provides a standalone Verilator-based simulation environment for a single-core CV32E40P processor, including software build and simulation flows for functional demos and validation.

## Layout

```
bsp/          board-support package (crt0, linker script, syscalls)
sw/           software examples and sw/Makefile
tb/           Verilator testbench RTL/C++ and tb/Makefile
cv32e40p/     RTL git submodule
Makefile      top-level orchestrator (delegates to sw/ and tb/)
```

## Scope

- Simulate and validate single-core CV32E40P behavior.
- Maintain reproducible firmware build and simulation flows.
- Keep testbench, software examples, and automation aligned with single-core use cases.

## Language Policy

The project language is **English**.

Use English for all repository communication and contribution artifacts, including:

- Pull request titles, descriptions, and review comments
- Commit messages
- Issue titles and comments
- Code comments and documentation
- Branch names

## Contribution Expectations

- Keep changes focused and reviewable.
- Include clear context in pull requests (what changed and why).
- Update related documentation when behavior or workflows change.
