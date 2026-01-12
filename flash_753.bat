:: flash_h753_elf.bat  – place next to MyFirmware.elf or pass it as %1
@echo off
setlocal

:: --- CONFIG ----------------------------------------------------------------
set "TOOL=C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32_Programmer_CLI.exe"
set "IMAGE=%~1"  to pass filename on CLI

:: --- CONNECT ---------------------------------------------------------------
%TOOL% -c port=SWD mode=UR freq=24000    || goto :error

:: --- ERASE -----------------------------------------------------------------
%TOOL% -c port=SWD -e all                || goto :error

:: --- PROGRAM + VERIFY ------------------------------------------------------
%TOOL% -c port=SWD -d "%IMAGE%" -v       || goto :error

:: --- RESET -----------------------------------------------------------------
%TOOL% -c port=SWD -rst                  || goto :error

echo(
echo  ✔  Flash finished
goto :eof

:error
echo  ✘  Flash failed  (errorlevel=%errorlevel%)
exit /b 1
