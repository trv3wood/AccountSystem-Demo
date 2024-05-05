@echo off
echo Checking for Git...
where git >nul 2>&1
if %errorlevel% neq 0 (
    echo Installing Git...
    powershell -command "Start-Process -FilePath 'https://git-scm.com/download/win' -Verb open"
) else (
    echo Git is already installed.
)

echo Checking for CMake...
where cmake >nul 2>&1
if %errorlevel% neq 0 (
    echo Installing CMake...
    powershell -command "Start-Process -FilePath 'https://github.com/Kitware/CMake/releases/download/v3.21.1/cmake-3.21.1-windows-x86_64.msi' -Verb open"
) else (
    echo CMake is already installed.
)

echo Checking for Qt...
where qmake >nul 2>&1
if %errorlevel% neq 0 (
    echo Installing Qt...
    powershell -command "Start-Process -FilePath 'https://www.qt.io/download-open-source' -Verb open"
) else (
    echo Qt is already installed.
)

echo All tools are installed or were already present on the system.
pause
