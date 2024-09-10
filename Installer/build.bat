@echo off

:: Cleaning build files ::
:clean
echo Cleaning previous builds...
rmdir /S /Q build
rmdir /S /Q target
if "%~1"=="c" goto cleanexit

:: Building Rust Binaries ::
echo beginning rust build
mkdir build
cargo build
if %ERRORLEVEL% neq 0 (
    echo rust failed to compile the installer, returning error code: %ERRORLEVEL%
    pause
    exit /b %ERRORLEVEL%
)
echo rust compiler success

:: Copy binaries files to the build directory ::
echo Copying binaries to the build directory

copy target\debug\*.exe build\
if %ERRORLEVEL% neq 0 (
    echo failed to copy binaries to build folder.
    echo however the rust build completed, you can find the build in target/debug/
    echo sorry about that!

    echo build completed successfully
    pause
    exit /b %ERRORLEVEL%
)

:: Done ! ::
echo build and copy completed successfully
echo results found in the /build/ directory
pause
cls
cargo run
exit /b 0

:: if the user only wanted to run the clean command ::
:cleanexit
echo clean complete. the script will now finish!
pause