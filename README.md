# Nova3D Engine

Nova3D is a free C++20 3D engine project with an OpenGL 3.3 renderer, scene runtime, assets, physics, audio parsing, scripting hooks, editor state, and CMake build system.

This repository contains the public engine source and build configuration. GitHub Actions is configured to build the project on supported runners.

## Build

Requirements: CMake 3.20+, a C++20 compiler, OpenGL development libraries, and a window-system development environment.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

See `README_FINAL.md` and `docs_architecture.md` for the current architecture and limitations.

## License

MIT. See LICENSE.
