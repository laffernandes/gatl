@echo off
rem Copyright (C) 2007 Leandro Augusto Frata Fernandes
rem 
rem author   : Fernandes, Leandro A. F.
rem e-mail   : laffernandes@gmail.com
rem home page: http://www.inf.ufrgs.br/~laffernandes
rem 
rem version  : Alpha 3.141592

rem ***********************************************************************
rem General parameters
rem ***********************************************************************
set MATLAB=%MATLAB%
set PATH=%GA_GCC_PATH%\bin;%PATH%

rem ***********************************************************************
rem Compiler parameters
rem ***********************************************************************
set COMPILER=g++
set COMPFLAGS=-c -Wall -Wno-unknown-pragmas -Wno-uninitialized -DMATLAB_MEX_FILE -L"%GA_GCC_PATH%\lib" -I"%MATLAB%\extern\include" -I"%GA_GCC_PATH%\include"
set OPTIMFLAGS=-O3 -malign-double -DNDEBUG
set DEBUGFLAGS=-g
set NAME_OBJECT=-o

rem ***********************************************************************
rem Linker parameters
rem ***********************************************************************
set LINKER=g++
set LINKFLAGS=-shared
set LINKFLAGSPOST="%OUTDIR%ga_libmx.lib" "%OUTDIR%ga_libmex.lib"
set LINKOPTIMFLAGS=-s
set LINKDEBUGFLAGS=-g -Wl,--image-base,0x28000000\n
set NAME_OUTPUT=-o "%OUTDIR%%MEX_NAME%%MEX_EXT%"