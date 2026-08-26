# Nova3D Engine

Nova3D is a free C++20 3D engine project with an OpenGL 3.3 renderer, scene runtime, assets, physics, audio parsing, scripting hooks, editor state, and CMake build system.

This repository contains the public engine source and build configuration. GitHub Actions is configured to build the project on supported runners.

## Windows build: MSYS2 UCRT64

**IMPORTANT: Nova3D uses MSYS2 UCRT64 as its Windows C++ toolchain.**

**IMPORTANT: `setup-msys2-build.bat` is an installer-and-builder script. Read it before running it. It can download and install software on your computer.**

**The script does not silently install Microsoft Visual Studio. It downloads the official MSYS2 base environment and uses MSYS2 `pacman` to install the UCRT64 GCC C/C++ compiler, CMake, Ninja, and required dependencies.**

To configure and build automatically on Windows:

```bat
setup-msys2-build.bat
```

The first run installs the toolchain. Later runs reuse it. See [`docs/MSYS2_BUILD.md`](docs/MSYS2_BUILD.md) for exactly what is downloaded and why.

**Consent notice:** this repository intentionally makes the installer behavior prominent. Review the script and the MSYS2 documentation before execution. Never run an installer or build script you have not inspected.

## Build manually

Requirements: CMake 3.20+, a C++20 compiler, OpenGL development libraries, and a window-system development environment.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

See `README_FINAL.md` and `docs_architecture.md` for the current architecture and limitations.

## License

MIT. See LICENSE.
