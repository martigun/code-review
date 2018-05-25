@ECHO OFF
REM // Purpose:
REM // To create a "batch_logs" directory and set the variable
REM //  of the variable `batchLogFile` to the current timestamp
REM //
REM // This file takes one argurment, the name of the file that is
REM //  producing this log file

REM // create "batch_logs" directory if it does not exist
IF NOT EXIST batch_logs MKDIR batch_logs

REM //get YYYYMMDD from %date% (format is like "Sun 07/31/2017")
SET YYYYMMDD=%date:~10,4%%date:~4,2%%date:~7,2%

REM //get HHMMSS from %time% (format is like " 8:15:59")
SET HHMMSS=%time:~0,2%%time:~3,2%%time:~6,2%

REM //check first char and replace with a zero
SET firstChar=%HHMMSS:~0,1%
if "%firstChar%" == " " SET HHMMSS=0%HHMMSS:~1,5%

REM // Set batch file name in current directory
SET batchLogFile=%cd%\batch_logs\%YYYYMMDD%%HHMMSS%_%1.txt