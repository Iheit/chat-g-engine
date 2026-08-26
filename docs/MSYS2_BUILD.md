# Nova3D Windows Build: MSYS2 UCRT64

## IMPORTANT: read this before running the setup script

**Nova3D intentionally uses MSYS2 UCRT64 for its Windows C++ toolchain.**

The repository's `setup-msys2-build.bat` is an **installer-and-builder script**. It may download and install software on your computer. It is deliberately transparent about what it does.

### What the script downloads

1. The official MSYS2 base environment.
2. The MSYS2 UCRT64 GCC C/C++ toolchain.
3. CMake.
4. Ninja.
5. Required package dependencies.

The MSYS2 installer is obtained from the official MSYS2 release infrastructure. Package installation is performed with MSYS2's `pacman` package manager.

**No Microsoft Visual Studio or MSVC installation is required.**

**Review the batch file yourself before running it. Do not run build/install scripts you have not inspected.**

## Why MSYS2?

Nova3D uses the UCRT64 environment because it provides a modern 64-bit Windows GCC/MinGW toolchain and a straightforward package manager. It also keeps the project independent of a full Visual Studio installation.

## Automatic build

From a Windows command prompt, in the repository root:

```bat
setup-msys2-build.bat
```

The script will:

- stop if PowerShell is unavailable;
- download the MSYS2 base archive when `C:\msys64` is missing;
- update the MSYS2 package database and base system;
- install the UCRT64 C++ toolchain, CMake, Ninja, and pkg-config;
- configure Nova3D with CMake;
- compile a Release build.

The first run is larger because the toolchain must be installed. Subsequent builds reuse the existing MSYS2 installation.

## Official MSYS2 documentation

- https://www.msys2.org/
- https://www.msys2.org/docs/installer/
- https://www.msys2.org/docs/ci/
- https://www.msys2.org/docs/package-management/

## Important security note

Nova3D does not ask for administrator credentials, GitHub credentials, passwords, API tokens, or authentication secrets. The setup script only performs the software installation and build operations described above.
