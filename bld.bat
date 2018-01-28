
@echo off
if not defined DevEnvDir (
 echo "%VS140COMNTOOLS%VsDevCmd.bat" 
 call "%VS140COMNTOOLS%VsDevCmd.bat" 
 echo "%VCINSTALLDIR%vcvarsall.bat" amd64
 call "%VCINSTALLDIR%vcvarsall.bat" amd64
 if errorlevel 1 goto :eof
)

cmake -H. -Bbuild -G "Visual Studio 14 2015 Win64" 
msbuild build\read_csv.sln /target:build /property:configuration=debug
build\Debug\read_dc311.exe -f dc_311-2016_100.csv
build\Debug\read_test.exe -f test.csv