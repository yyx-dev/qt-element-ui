@echo off
setlocal enabledelayedexpansion

:: ����·������
set BINARY_EXE=D:\build-qt-element-ui-Desktop_Qt_5_14_2_MinGW_64_bit-Release\release\qt-element-ui.exe
set TARGET_DIR=D:\qt-element-ui_v0.1.0_windows_qt5.14.2
set TARGET_EXE=%TARGET_DIR%\qt-element-ui.exe
set ZIP_FILE=D:\qt-element-ui_v0.1.0_windows_qt5.14.2.zip

:: ���Դ�ļ��Ƿ����
if not exist "%BINARY_EXE%" (
    echo ����Դ�ļ������� %BINARY_EXE%
    pause
    exit /b 1
)

:: ����Ŀ��Ŀ¼����������ڣ�
if not exist "%TARGET_DIR%" (
    echo ���ڴ���Ŀ��Ŀ¼ %TARGET_DIR%
    mkdir "%TARGET_DIR%"
)

:: ���ƿ�ִ���ļ�
echo ���ڸ��� %BINARY_EXE% �� %TARGET_EXE%
copy /y "%BINARY_EXE%" "%TARGET_EXE%"

:: ����Ƿ��Ƴɹ�
if not exist "%TARGET_EXE%" (
    echo ���󣺸����ļ�ʧ��
    pause
    exit /b 1
)

:: ����Ŀ��Ŀ¼������ windeployqt
echo ���ڲ��� Qt ������...
cd /d "%TARGET_DIR%"
windeployqt qt-element-ui.exe

:: ѹ��Ŀ¼Ϊ ZIP��ʹ�� PowerShell��
echo ����ѹ�� %TARGET_DIR% Ϊ ZIP �ļ�...
powershell -command "Compress-Archive -Path '%TARGET_DIR%' -DestinationPath '%ZIP_FILE%' -Force"

if exist "%ZIP_FILE%" (
    echo ѹ���ɹ���ZIP �ļ��ѱ��浽 %ZIP_FILE%
) else (
    echo ����ѹ��ʧ��
)

echo ���в�����ɣ�
pause