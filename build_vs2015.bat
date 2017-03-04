@echo off

set bfolder=b_vs2015
set genfor="Visual Studio 14 2015"

if not exist %bfolder% mkdir %bfolder%
cd %bfolder%

cmake -G %genfor% ..

pause