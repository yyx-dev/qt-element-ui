.\build\release\qt-element-ui.exe

@echo off
set EXE_PATH=.\build\release\qt-element-ui.exe
set BUILD_SCRIPT=build.bat

if exist "%EXE_PATH%" (
    "%EXE_PATH%"
) else (
    call "%BUILD_SCRIPT%"
    if exist "%EXE_PATH%" (
        "%EXE_PATH%"
    ) else (
        pause
        exit /b 1
    )
)
pause