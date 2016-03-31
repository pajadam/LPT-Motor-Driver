@ECHO OFF
ECHO ###########################
ECHO  Make release version of
ECHO  LPT_Motor_Driver with 
ECHO  one click. Needs UPX and
ECHO  CBP2MAKE but it will
ECHO  work anyway, without
ECHO  these features.
ECHO  by pajadam
ECHO ###########################
ECHO - Generating updated
ECHO   makefile from CBP project
cbp2make -in LPT_Motor_Driver.cbp -out makefile -targets "Windows" -windows >nul
ECHO - Packing LPT_Motor_Driver.exe
upx -q -9 bin\Windows\LPT_Motor_Driver.exe >nul
ECHO - Creating release directory
rd /s /q release >nul
mkdir "release" >nul
ECHO - Moving needed objects to
ECHO   release folder
copy "lib\Windows\release\inpout32.dll" "release\" >nul
copy "bin\Windows\LPT_Motor_Driver.exe" "release\" >nul
ECHO Check out release folder
ECHO DONE :D
ECHO ###########################
GOTO :EOF

