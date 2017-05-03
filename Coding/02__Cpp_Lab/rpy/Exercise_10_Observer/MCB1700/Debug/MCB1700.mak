
####################################################################
######### Auto generated makefile to prepare the RXF and ###########
######### Rhapsody generated files for building in an    ###########
######### external IDE.                                  ###########
####################################################################
##
## Based on properties version:
## $Id: WST_RXF_V6.prp 33415 2016-01-13 13:44:18Z eroemer $
## $URL: https://svn.willert.de/V6/trunk/Component/Modelling/Rpy/Config/UserSettings/WST_RXF_V6.prp $
##

BuildSet=Debug
OMConfigurationCPPCompileSwitches=  -DWST_RXF_V6  $(CPPCompileDebug)
OMFileCPPCompileSwitches=$(OMFileCPPCompileSwitches)
LinkCommandSet=$(LinkDebug)
INCLUDE_PATH= \
  $(INCLUDE_QUALIFIER)C:\Keil_v5\ARM\PACK\Keil\MDK-Middleware\7.4.0\Board
OMROOT="C:\Users\Hochschule Ulm\IBM\Rational\Rhapsody\8.1.4\Share"


# Rhapsody version
# Use buildnumbers like 686414 for 6.2, 749034 for 7.0, 820118 for 7.1 and so on

InstalledRpyVer		= "@RHAPSODYVER_9641846"
RICVERSION 			= $(InstalledRpyVer:@RHAPSODYVER_=)


WST_RELEASE_PATH	= "C:\Users\Hochschule Ulm\Willert\RXF-Eval_Rpy-Cpp-ARM_V6.01"
WST_RELEASE_TOOLS	= $(WST_RELEASE_PATH)\Tools
WST_RELEASE_SRC		= $(WST_RELEASE_PATH)\Source
WST_RELEASE_CFG		= $(WST_RELEASE_PATH)\Config


################# Programs and flags ############################
####################################################################

## Programs
CP		= copy
RM		= del
RXF		= RXF-Eval_Rpy-Cpp-ARM_V6_01


##################### Identifier and Buildsets #####################
####################################################################

## Framework Environment
TARGET_TYPE		= Executable


## Compiler and Linker macros
CPPCompileDebug							= -D_DEBUG -DWST_CFG_HIGHWATERMARKS 
CPPCompileRelease						= -DNDEBUG -DWST_CFG_HIGHWATERMARKS 
LinkDebug								= 
LinkRelease								= 
ConfigurationCPPCompileSwitches			=   -DWST_RXF_V6  $(CPPCompileDebug)
ConfigurationCPPCompileSwitchesDefines  = $(ConfigurationCPPCompileSwitches)


##################################################################
##################### Context generated macros ###################

FLAGSFILE=
RULESFILE=
OMROOT="C:\Users\Hochschule Ulm\IBM\Rational\Rhapsody\8.1.4\Share"
RHPROOT="C:\Program Files (x86)\IBM\Rational\Rhapsody\8.1.4"

CPP_EXT=.cpp
H_EXT=.h
OBJ_EXT=
EXE_EXT=.dat
LIB_EXT=.lib

INSTRUMENTATION=None

TIME_MODEL=RealTime

TARGET_TYPE=Executable

TARGET_NAME=MCB1700

TARGET_MAIN=MainMCB1700

LIBS=

INCLUDE_PATH= \
  $(INCLUDE_QUALIFIER)C:\Keil_v5\ARM\PACK\Keil\MDK-Middleware\7.4.0\Board

ADDITIONAL_OBJS=

OBJS= \
  LedBar.obj \
  Poti.obj \
  PotiSubject.obj \
  PotiObserver.obj \
  Display.obj \
  Default.obj





##################### Clean Target ##############################
#################################################################


clean:
	@$(WST_RELEASE_TOOLS)\MyEcho -------
	@$(WST_RELEASE_TOOLS)\MyEcho Cleaning
	@$(WST_RELEASE_TOOLS)\MyEcho -------
	@if exist RxfDimensions.h  	 		$(RM) RxfDimensions.h
	@if exist RxfConstants.h  	 		$(RM) RxfConstants.h
	@if exist RhapsodyRun.bat  	 		$(RM) RhapsodyRun.bat


############################### Flags ##############################
####################################################################


INCLUDE_QUALIFIER		= -I
WST_SHORT_SECTION_NAMES	= 0


############################# all target############################
####################################################################


!IF "$(TARGET_TYPE)" == "Executable"

all:	RhapsodyRun.bat RxfDimensions.h RxfConstants.h WSTMemoryTypes.h
	@$(WST_RELEASE_TOOLS)\MyEcho > $(TARGET_NAME).dat
	@$(WST_RELEASE_TOOLS)\MyEcho 
	@$(WST_RELEASE_TOOLS)\MyEcho Please use Code | Run to deploy generated files to your IDE project and build your application

!ELSE

all:	RhapsodyRun.bat RxfDimensions.h RxfConstants.h WSTMemoryTypes.h
	@$(WST_RELEASE_TOOLS)\MyEcho > $(TARGET_NAME).lib
	@$(WST_RELEASE_TOOLS)\MyEcho 
	@$(WST_RELEASE_TOOLS)\MyEcho Please use Code | Run to deploy generated files to your IDE project and build your application

!ENDIF



####################### OO RTX Dimensions #############################
#######################################################################

# Generate RxfDimensions.h with all actual dimensions, set via properties in Rhapsody
# 
RxfDimensions.h:	MCB1700.mak
	@$(WST_RELEASE_TOOLS)\MyEcho Generating $@
	@$(WST_RELEASE_TOOLS)\MyEcho -------
	@$(WST_RELEASE_TOOLS)\MyEcho /* This $@ is generated by MCB1700.mak; do not edit! */				>  $@
	@$(WST_RELEASE_TOOLS)\MyEcho 																			>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho \#define WST_MAX_TIMEOUTS				32U				>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho /* No WST_TMM_MAX_IRQ_TIMEOUTS define required in the OO-RTX. */>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho \#define WST_TINY_BUFFER_SIZE			0U		>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho \#define WST_SMALL_BUFFER_SIZE			16U		>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho \#define WST_MEDIUM_BUFFER_SIZE			32U		>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho \#define WST_LARGE_BUFFER_SIZE			96U		>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho \#define WST_HUGE_BUFFER_SIZE			0U		>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho \#define WST_INITIAL_TINY_BUFFERS		0U	>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho \#define WST_INITIAL_SMALL_BUFFERS		12U	>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho \#define WST_INITIAL_MEDIUM_BUFFERS		6U	>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho \#define WST_INITIAL_LARGE_BUFFERS		2U	>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho \#define WST_INITIAL_HUGE_BUFFERS		0U	>> $@ 
	@$(WST_RELEASE_TOOLS)\MyEcho \#define WST_MS_PER_TICK					10U		>> $@


#rule to generate RXF  configuration. 
#The file RxfConstants.h is included by WSTEnvironment.h which is included by the OO RTX sources 
RxfConstants.h:		MCB1700.mak
	@$(WST_RELEASE_TOOLS)\MyEcho ---------
	@$(WST_RELEASE_TOOLS)\MyEcho Generating $@
	@$(WST_RELEASE_TOOLS)\MyEcho ---------
	@$(WST_RELEASE_TOOLS)\MyEcho /* This $@ is generated by MCB1700.mak via Rhapsody; do not edit! */	>  $@
	@$(WST_RELEASE_TOOLS)\MyEcho #include "RxfCompilerConstants.h"										>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho #include "RxfRTOSConstants.h"											>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho #include "RxfTargetConstants.h"											>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho -@D@ $(ConfigurationCPPCompileSwitchesDefines)							>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho -@D@ $(WSTAdditionalDefinesMEM)											>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho -@D@ -DWST_ANIMATION -DWST_LIVE_ANIMATION -DWST_TARGET_DEBUGGING_ENABLED											>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho -@D@ $(WSTAdditionalDefinesTC)											>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho -@D@ -DWST_RPY_VTBL_KIND_OXF								>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho -@D@ -DWST_MEM_NO_DEBUG												>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho -@D@ -DWST_MEM_REQUEST_ONE_POOL											>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho -@D@ -DWST_MEM_DISABLE_INTERRUPTS											>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho -@D@ -DWST_MEM_NO_STATISTICS											>> $@	
	@$(WST_RELEASE_TOOLS)\MyEcho -@D@ -DWST_MEM_NO_TAIL													>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho ^#define WST_MEM_TINY_POOL_DEFINITION 		uint32 tinyBuffers[ WST_INITIAL_TINY_BUFFERS ]  [ ( WST_TINY_BUFFER_SIZE + sizeof( WST_MEM_Block) + 3 ) / 4 ];				>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho ^#define WST_MEM_SMALL_POOL_DEFINITION 	uint32 smallBuffers[ WST_INITIAL_SMALL_BUFFERS ]  [ ( WST_SMALL_BUFFER_SIZE + sizeof( WST_MEM_Block) + 3 ) / 4 ];			>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho ^#define WST_MEM_MEDIUM_POOL_DEFINITION	uint32 mediumBuffers[ WST_INITIAL_MEDIUM_BUFFERS ][ ( WST_MEDIUM_BUFFER_SIZE + sizeof( WST_MEM_Block) + 3 ) / 4 ];			>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho ^#define WST_MEM_LARGE_POOL_DEFINITION		uint32 largeBuffers[ WST_INITIAL_LARGE_BUFFERS ]  [ ( WST_LARGE_BUFFER_SIZE + sizeof( WST_MEM_Block) + 3 ) / 4 ];			>> $@
	@$(WST_RELEASE_TOOLS)\MyEcho ^#define WST_MEM_HUGE_POOL_DEFINITION		uint32 hugeBuffers[ WST_INITIAL_HUGE_BUFFERS ]  [ ( WST_HUGE_BUFFER_SIZE + sizeof( WST_MEM_Block) + 3 ) / 4 ];				>> $@




######################### Named Sections ##############################
#######################################################################

# Generate WSTMemoryTypes.h with the compiler pragmas needed to define named sections
# 
WSTMemoryTypes.h:	WSTMemoryTypePragmas.txt WSTMemoryTypeMacro.template $(WST_RELEASE_TOOLS)\macroAndPragma2Header.awk
	@$(WST_RELEASE_TOOLS)\MyEcho Creating $@
	@$(WST_RELEASE_TOOLS)\MyEcho -------
	@$(WST_RELEASE_TOOLS)\gawk.exe -f $(WST_RELEASE_TOOLS)\macroAndPragma2Header.awk pragmaFile=WSTMemoryTypePragmas.txt useShortSectionNames=$(WST_SHORT_SECTION_NAMES) WSTMemoryTypeMacro.template > $@


WSTMemoryTypePragmas.txt:	$(WST_RELEASE_CFG)\MemorySections\WSTMemoryTypePragmas.txt 
	@$(WST_RELEASE_TOOLS)\MyEcho Copying $<
	@$(WST_RELEASE_TOOLS)\MyEcho -------
	@$(CP) $(WST_RELEASE_CFG)\MemorySections\WSTMemoryTypePragmas.txt > NUL
	
WSTMemoryTypeMacro.template:	$(WST_RELEASE_CFG)\MemorySections\WSTMemoryTypeMacro.template
	@$(WST_RELEASE_TOOLS)\MyEcho Copying $<
	@$(WST_RELEASE_TOOLS)\MyEcho -------
	@$(CP) $(WST_RELEASE_CFG)\MemorySections\WSTMemoryTypeMacro.template  > NUL


RhapsodyRun.bat:	$(WST_RELEASE_TOOLS)\RhapsodyRun.bat MCB1700.mak
	@$(WST_RELEASE_TOOLS)\MyEcho Preparing $<
	@$(WST_RELEASE_TOOLS)\MyEcho -------
	@$(WST_RELEASE_TOOLS)\MyEcho @rem The InvokeExecutable property does not support to extract macros,					>  RhapsodyRun.bat
	@$(WST_RELEASE_TOOLS)\MyEcho @rem so we generate this batch file as a workaround.										>> RhapsodyRun.bat
	@$(WST_RELEASE_TOOLS)\MyEcho @if not exist CurrentFileList.txt copy NUL CurrentFileList.txt							>> RhapsodyRun.bat
	@$(WST_RELEASE_TOOLS)\MyEcho @copy CurrentFileList.txt PreviousFileList.txt											>> RhapsodyRun.bat
	@$(WST_RELEASE_TOOLS)\MyEcho "@dir /s /on /b *.cpp *.c *.h > CurrentFileList.txt"	>> RhapsodyRun.bat
	@$(WST_RELEASE_TOOLS)\MyEcho @call \"$(WST_RELEASE_TOOLS)\RhapsodyRun.bat\"										>> RhapsodyRun.bat


########################### End of Makefile ###########################
#######################################################################

