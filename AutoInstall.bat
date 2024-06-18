@echo off

title Install KolbriLib

	set DefaultToochainPath=C:\MinGW\msys\1.0\home\autobuild\tools\win32


if %1.==. goto Input else set arg=%1

if %1 == help goto help

if %1 == default set arg=%DefaultToochainPath%

:start
	if %arg%.==. goto WrongToolchain
	if exist %arg% goto build else goto WrongToolchain
	
	
:build
	echo "Build Lib"
	mkdir build
	cd build
	cmake .. -G "MinGW Makefiles"
	make
	cd ..
	goto EndProgramm
	
:help
	echo Instalator of KolibriLib 
	echo "Template of use: AutoInstall <Path to toolchain>"
	echo example: AutoInstall C:\MinGW\msys\1.0\home\autobuild\tools\win32
	echo use argument "default" for use default path "C:\MinGW\msys\1.0\home\autobuild\tools\win32"
	goto EndProgramm
	
	

:Input

	set /p arg="Path to kos32 Toolchain: "
	
	if %arg% == default  echo "use default (%DefaultToochainPath%)" set arg=%DefaultToochainPath%
	
	goto start
	
:WrongToolchain
	echo Folder %arg% doesn't exist, try again
	goto Input
	
:EndProgramm