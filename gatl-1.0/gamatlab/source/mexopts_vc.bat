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
set GA_MSVC_PATH=%GA_MSVS_PATH%\VC
set MSSDK_PATH='.registry_lookup("SOFTWARE\Microsoft\Microsoft SDKs\Windows","CurrentInstallFolder").'
set PATH=%GA_MSVC_PATH%\BIN\;%MSSDK_PATH%\bin;%GA_MSVS_PATH%\Common7\IDE;%GA_MSVS_PATH%\Common7\Tools;%GA_MSVS_PATH%\Common7\Tools\bin;%GA_MSVC_PATH%\VCPackages;%MATLAB_BIN%;%PATH%
set INCLUDE=%GA_MSVC_PATH%\ATLMFC\INCLUDE;%GA_MSVC_PATH%\INCLUDE;%MSSDK_PATH%\INCLUDE;%INCLUDE%
set LIB=%GA_MSVC_PATH%\ATLMFC\LIB;%GA_MSVC_PATH%\LIB;%MSSDK_PATH%\lib;%MATLAB%\extern\lib\win32;%LIB%

rem ***********************************************************************
rem Compiler parameters
rem ***********************************************************************
set COMPILER=cl
set COMPFLAGS=/c /Zp8 /GR /W3 /EHsc- /Zc:wchar_t- /DMATLAB_MEX_FILE /D_CRT_SECURE_NO_WARNINGS /nologo /bigobj /openmp
set OPTIMFLAGS=/MD /O2 /Oy- /DNDEBUG
set DEBUGFLAGS=/MD /Zi /Fd"%OUTDIR%%MEX_NAME%%MEX_EXT%.pdb"
set NAME_OBJECT=/Fo

rem ***********************************************************************
rem Linker parameters
rem ***********************************************************************
set LIBLOC=%MATLAB%\extern\lib\win32\microsoft
set LINKER=link
set LINKFLAGS=/dll /export:%ENTRYPOINT% /MAP /LIBPATH:"%LIBLOC%" libmx.lib libmex.lib libmat.lib /implib:%LIB_NAME%.x /MACHINE:X86 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib
set LINKOPTIMFLAGS=/OPT:REF /OPT:ICF
set LINKDEBUGFLAGS=/DEBUG /PDB:"%OUTDIR%%MEX_NAME%%MEX_EXT%.pdb"
set NAME_OUTPUT=/out:"%OUTDIR%%MEX_NAME%%MEX_EXT%"
set RSP_FILE_INDICATOR=@

rem ***********************************************************************
rem Post link commands
rem ***********************************************************************
set POSTLINK_CMDS=del "%OUTDIR%%MEX_NAME%.map"
set POSTLINK_CMDS1=del %LIB_NAME%.x
set POSTLINK_CMDS2=mt -outputresource:"%OUTDIR%%MEX_NAME%%MEX_EXT%";2 -manifest "%OUTDIR%%MEX_NAME%%MEX_EXT%.manifest"
set POSTLINK_CMDS3=del "%OUTDIR%%MEX_NAME%%MEX_EXT%.manifest"