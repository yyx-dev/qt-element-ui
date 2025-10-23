@echo off
setlocal enabledelayedexpansion

:: 设置路径变量
set BINARY_EXE=D:\build-qt-element-ui-Desktop_Qt_5_14_2_MinGW_64_bit-Release\release\qt-element-ui.exe
set TARGET_DIR=D:\qt-element-ui_v0.1.0_windows_qt5.14.2
set TARGET_EXE=%TARGET_DIR%\qt-element-ui.exe
set ZIP_FILE=D:\qt-element-ui_v0.1.0_windows_qt5.14.2.zip

:: 检查源文件是否存在
if not exist "%BINARY_EXE%" (
    echo 错误：源文件不存在 %BINARY_EXE%
    pause
    exit /b 1
)

:: 创建目标目录（如果不存在）
if not exist "%TARGET_DIR%" (
    echo 正在创建目标目录 %TARGET_DIR%
    mkdir "%TARGET_DIR%"
)

:: 复制可执行文件
echo 正在复制 %BINARY_EXE% 到 %TARGET_EXE%
copy /y "%BINARY_EXE%" "%TARGET_EXE%"

:: 检查是否复制成功
if not exist "%TARGET_EXE%" (
    echo 错误：复制文件失败
    pause
    exit /b 1
)

:: 进入目标目录并运行 windeployqt
echo 正在部署 Qt 依赖项...
cd /d "%TARGET_DIR%"
windeployqt qt-element-ui.exe

:: 压缩目录为 ZIP（使用 PowerShell）
echo 正在压缩 %TARGET_DIR% 为 ZIP 文件...
powershell -command "Compress-Archive -Path '%TARGET_DIR%' -DestinationPath '%ZIP_FILE%' -Force"

if exist "%ZIP_FILE%" (
    echo 压缩成功！ZIP 文件已保存到 %ZIP_FILE%
) else (
    echo 错误：压缩失败
)

echo 所有操作完成！
pause