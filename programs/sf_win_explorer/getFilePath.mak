# Microsoft Developer Studio Generated NMAKE File, Based on getFilePath.dsp
!IF "$(CFG)" == ""
CFG=getFilePath - Win32 Debug
!MESSAGE No configuration specified. Defaulting to getFilePath - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "getFilePath - Win32 Release" && "$(CFG)" != "getFilePath - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "getFilePath.mak" CFG="getFilePath - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "getFilePath - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "getFilePath - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "getFilePath - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\sf_win_explorer.exe"


CLEAN :
	-@erase "$(INTDIR)\EditDiag.obj"
	-@erase "$(INTDIR)\getFilePath.obj"
	-@erase "$(INTDIR)\getFilePath.pch"
	-@erase "$(INTDIR)\getFilePath.res"
	-@erase "$(INTDIR)\getFilePathDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase ".\sf_win_explorer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\getFilePath.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\getFilePath.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\getFilePath.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\sf_win_explorer.pdb" /machine:I386 /out:"sf_win_explorer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\EditDiag.obj" \
	"$(INTDIR)\getFilePath.obj" \
	"$(INTDIR)\getFilePathDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\getFilePath.res"

".\sf_win_explorer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "getFilePath - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\sf_win_explorer.exe"


CLEAN :
	-@erase "$(INTDIR)\EditDiag.obj"
	-@erase "$(INTDIR)\getFilePath.obj"
	-@erase "$(INTDIR)\getFilePath.pch"
	-@erase "$(INTDIR)\getFilePath.res"
	-@erase "$(INTDIR)\getFilePathDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\sf_win_explorer.pdb"
	-@erase ".\sf_win_explorer.exe"
	-@erase ".\sf_win_explorer.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\getFilePath.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\getFilePath.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\getFilePath.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\sf_win_explorer.pdb" /debug /machine:I386 /out:"sf_win_explorer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\EditDiag.obj" \
	"$(INTDIR)\getFilePath.obj" \
	"$(INTDIR)\getFilePathDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\getFilePath.res"

".\sf_win_explorer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("getFilePath.dep")
!INCLUDE "getFilePath.dep"
!ELSE 
!MESSAGE Warning: cannot find "getFilePath.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "getFilePath - Win32 Release" || "$(CFG)" == "getFilePath - Win32 Debug"
SOURCE=.\EditDiag.cpp

"$(INTDIR)\EditDiag.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\getFilePath.pch"


SOURCE=.\getFilePath.cpp

"$(INTDIR)\getFilePath.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\getFilePath.pch"


SOURCE=.\getFilePath.rc

"$(INTDIR)\getFilePath.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\getFilePathDlg.cpp

"$(INTDIR)\getFilePathDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\getFilePath.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "getFilePath - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\getFilePath.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\getFilePath.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "getFilePath - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\getFilePath.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\getFilePath.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

