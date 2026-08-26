@echo off
setlocal EnableExtensions

REM ============================================================================
REM NOVA3D BUILD SETUP - MSYS2 / UCRT64
REM ============================================================================
REM IMPORTANT: THIS SCRIPT DOWNLOADS AND INSTALLS MSYS2 IF IT IS NOT PRESENT.
REM IT ALSO DOWNLOADS C++ BUILD TOOLS AND CMAKE FROM THE OFFICIAL MSYS2
REM PACKAGE REPOSITORIES. REVIEW THIS SCRIPT BEFORE RUNNING IT.
REM NO MICROSOFT VISUAL STUDIO INSTALLATION IS REQUIRED.
REM ============================================================================

set "MSYS2_ROOT=C:\msys64"
set "MSYS2_BASH=%MSYS2_ROOT%\usr\bin\bash.exe"
set "MSYS2_SFX=%TEMP%\nova3d-msys2.sfx.exe"
set "MSYS2_URL=https://github.com/msys2/msys2-installer/releases/download/nightly-x86_64/msys2-base-x86_64-latest.sfx.exe"

where powershell.exe >nul 2>&1
if errorlevel 1 (
    echo ERROR: PowerShell is required by this setup script.
    exit /b 1
)

echo.
echo ================================================================
echo NOVA3D - MSYS2 UCRT64 BUILD SETUP
echo ================================================================
echo.
echo CONSENT / TRANSPARENCY NOTICE:
echo This script may download and install MSYS2 to:
echo   %MSYS2_ROOT%
echo.
echo It will then use MSYS2 pacman to download the UCRT64 GCC C++
echo compiler, CMake, Ninja, and required build dependencies.
echo These packages are downloaded from the MSYS2 package ecosystem.
echo No Microsoft Visual Studio or MSVC installation is required.
echo.
echo The MSYS2 base archive is downloaded from the official MSYS2
necho project release infrastructure.
echo.
pause

if not exist "%MSYS2_BASH%" (
    echo.
    echo MSYS2 was not found. Downloading the MSYS2 base environment...
    echo Source: %MSYS2_URL%
    echo.
    powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "Invoke-WebRequest -UseBasicParsing -Uri '%MSYS2_URL%' -OutFile '%MSYS2_SFX%'"
    if errorlevel 1 (
        echo ERROR: Failed to download MSYS2.
        exit /b 1
    )

    echo Installing MSYS2 to %MSYS2_ROOT%...
    "%MSYS2_SFX%" -y -oC:\
    if errorlevel 1 (
        echo ERROR: MSYS2 installation failed.
        exit /b 1
    )
    del /q "%MSYS2_SFX%" >nul 2>&1
)

if not exist "%MSYS2_BASH%" (
    echo ERROR: MSYS2 bash.exe was not found after installation.
    exit /b 1
)

echo.
echo Updating MSYS2 package metadata and base packages...
"%MSYS2_BASH%" -lc "pacman --noconfirm -Syuu"
"%MSYS2_BASH%" -lc "pacman --noconfirm -Syuu"
if errorlevel 1 (
    echo ERROR: MSYS2 update failed.
    exit /b 1
)

echo.
echo Installing Nova3D's UCRT64 C++ toolchain and build tools...
echo Packages: GCC C++, CMake, Ninja, pkg-config
"%MSYS2_BASH%" -lc "pacman --noconfirm -S --needed mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-pkgconf"
if errorlevel 1 (
    echo ERROR: Required MSYS2 packages could not be installed.
    exit /b 1
)

echo.
echo Configuring Nova3D with the MSYS2 UCRT64 toolchain...
set "CHERE_INVOKING=yes"
set "MSYSTEM=UCRT64"

"%MSYS2_BASH%" -lc "cd \"$(cygpath -u '%CD%')\" && export PATH=/ucrt64/bin:/usr/bin:$PATH && cmake -S . -B build-msys2 -G Ninja -DCMAKE_BUILD_TYPE=Release"
if errorlevel 1 (
    echo ERROR: CMake configuration failed.
    exit /b 1
)

echo.
echo Building Nova3D...
"%MSYS2_BASH%" -lc "cd \"$(cygpath -u '%CD%')\" && export PATH=/ucrt64/bin:/usr/bin:$PATH && cmake --build build-msys2 --parallel"
if errorlevel 1 (
    echo ERROR: Nova3D compilation failed.
    exit /b 1
)

echo.
echo ================================================================
echo NOVA3D BUILD COMPLETED SUCCESSFULLY
 echo ================================================================
echo.
echo Build directory: build-msys2
if exist "build-msys2\nova3d_renderer_demo.exe" echo Executable: build-msys2\nova3d_renderer_demo.exe
if exist "build-msys2\Nova3D.exe" echo Executable: build-msys2\Nova3D.exe
 echo.
echo MSYS2 is installed at %MSYS2_ROOT% and can be reused for future builds.
echo ================================================================
exit /b 0
