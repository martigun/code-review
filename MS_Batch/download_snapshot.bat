@echo off
REM *******************************************************************************
REM Script History
REM *******************************************************************************
REM Nightly backup script. Downloads the previous night’s automatic backup
REM and keeps a running 7 days on the local server
REM Created by: GWM
REM Created on: 20SEP2017
REM
REM This batch file was written to be run from `C:\oracle\EPM Automate\bin`
REM
REM code source: https://womaninepm.com/2017/04/07/epm-cloud-psa-back-up-your-snapshots/
REM all double-quotes had to be switch out, since they copied in not as CHR(22)
REM
REM
REM epmautomate login 874700 Delta123 https://arcs-test-a424120.epm.us2.oraclecloud.com a424120
REM
REM *******************************************************************************
SET returnvalue=0
SET user=874700
SET domain=a424120

REM PROD vs TEST url
SET url=https://arcs-a424120.epm.us2.oraclecloud.com
REM SET url=https://arcs-test-a424120.epm.us2.oraclecloud.com

REM this is where items get downloaded by default
SET defaultLocalDir="C:\oracle\EPM Automate\bin"

REM get YYYYMMDD from %date%
REM default %date% format is like "Sun 07/31/2017"
SET YYYYMMDD=%date%
SET YYYYMMDD=%YYYYMMDD:~10,4%%YYYYMMDD:~4,2%%YYYYMMDD:~7,2%

REM get HHMMSS from %time%
SET HHMMSS=%time%
SET HHMMSS=%HHMMSS:~0,2%%HHMMSS:~3,2%%HHMMSS:~6,2%

REM check first char and replace with a zero
SET firstChar=%HHMMSS:~0,1%
if "%firstChar%" == " " SET HHMMSS=0%HHMMSS:~1,5%

REM create logfile with timestamp
SET logfile=%defaultLocalDir%\batch_logs\batch_log_%YYYYMMDD%%HHMMSS%.log
ECHO -- Batch Log %YYYYMMDD%%HHMMSS% -- > %logfile%
@echo off

REM password can be EPW file or plaintext
REM SET pwd=%defaultLocalDir%\password.epw
SET pwd=Delta123

REM location for backups to reside
REM note that O:\ must be \\Natlrcchqrfs02\daldata02
SET targetLoc="O:\FIN_Controller\Financial Systems\ARCS\Backups\"

REM delete existing `.prefs` file in current and target
IF EXIST %defaultLocalDir%\.prefs DEL %defaultLocalDir%\.prefs >> %logfile%
IF EXIST %targetLoc%\.prefs DEL %targetLoc%\.prefs >> %logfile%
@echo off

REM change directory to backup location
CD /D %targetLoc% >> %logfile%
IF %ERRORLEVEL% NEQ 0 (
echo Change directory with error %ERRORLEVEL%.
)

REM log into environment
REM note that logging in creates the `.prefs` file, which all
REM other epmautomate calls rely on
ECHO Logging into environment %url% >> %logfile%
call epmautomate login %user% %pwd% %url% %domain% >> %logfile%
@echo off
IF %ERRORLEVEL% NEQ 0 (
echo Login failed with error %ERRORLEVEL%.
goto :END
)

REM delete any existing `Artifact Snapshot.zip` file
IF EXIST "Artifact Snapshot.zip" DEL "Artifact Snapshot.zip" >> %logfile%
@echo off

REM download latest snapshot
ECHO Downloading latest backup snapshot >> %logfile%
call epmautomate downloadfile "Artifact Snapshot" >> %logfile%
@echo off
ECHO Artifacts downloaded successfully >> %logfile%
IF %ERRORLEVEL% NEQ 0 (
echo Login failed with error %ERRORLEVEL%.
goto :END
)

REM set new file name for backup
REM note that backups happen at 5am
SET sourceFileNewName=%YYYYMMDD%0500_prod.zip

REM rename the snapshot file to todays date @ 5 am
ECHO Renaming the file >> %logfile%
REN "Artifact Snapshot.zip" %sourceFileNewName% >> %logfile%
@echo off

REM REM location for backups to reside
REM SET targetLoc="\\Natlrcchqrfs02\daldata02\FIN_Controller\Financial Systems"
REM SET targetLoc=%targetLoc%"\ARCS\Backups\"

REM REM copy the source to target
REM ECHO Renaming the local file >> %logfile%
REM SET sourcePath=%defaultLocalDir%\%sourceFileNewName%
REM COPY %sourcePath% %targetLoc% >> %logfile%
REM @echo off



REM log out
ECHO Logging Out >> %logfile%
call epmautomate logout >> %logfile%
@echo off
IF %ERRORLEVEL% NEQ 0 (
echo Logout failed with error %ERRORLEVEL%.
goto :END
)

REM End
:END
ECHO Return code: %ERRORLEVEL%
SET returnValue=%ERRORLEVEL%
EXIT /B %returnValue%