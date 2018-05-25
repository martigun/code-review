@ECHO OFF

REM //Purpose: To fold Acctg_Changes into Div_Input

REM //set environment
SET clusterName='EssbaseCluster'
SET appName='DIVPLN'
SET dbName='DIVPLN'

REM //---- start POV ----

SET currentAccount={Descendants([Profit_And_Loss], [3101100].level)}
SET currentRptCat={Descendants([RptCat_PandL], [999999].level)}
SET currentDivision={Descendants([DeltaConsol], [P0790ATG].level)}

SET currentYear={[FY16]}
SET currentPeriod={[Jan]:[Dec]}

SET currentScenario={[Current_Fcst]}

SET currentCurrency={[Local],[USD]}
SET currentVersion={[Working],[Final]}

SET currentDataType=#DIMENSION_NOT_IN_POV

REM //---- end POV ----

REM //set the source for the copy
SET sourceRegion={[Acctg_Changes], [Div_Input]}

REM //make CSC file usisng this BAT filename
SET cscFile=CSC\%~n0.csc
ECHO //ESS_LOCALE English_UnitedStates.Latin1@Binary> %cscFile%
ECHO ([Div_Input]) := ([Div_Input] + [Acctg_Changes]);>> %cscFile%

REM // add single quotes for MSH file
SET cscFile='%cscFile%'

REM //create log file
CALL lib_LogMgmt\createLogFile.bat %~n0

REM // Run MSH Copy file
ESSMSH MSH\CopyAll_xDT.msh

PAUSE