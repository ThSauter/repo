#
# 
# $Id: GenerateXMLForDebugger.awk 27420 2013-03-13 12:46:45Z ms $
# $URL: https://svn.willert.de/V6/trunk/Component/Modelling/Rpy/Tools/GenerateXMLForDebugger.awk $
#
#
# @WST_START_PRODUCT_INFOS@
# ...
# ...
# This space left between the WST_xxx_PRODUCT_INFOS macros is reserved
# for information about the released product components.
# ...
# ...
# The WST-Generator replace the macros and fill this space with the
# appropriate contents.
# ...
# ...
# ...
# @WST_STOP_PRODUCT_INFOS@
# 
# Create a XML input file for the PC side of a monitor, based on a map file by the Keil RealView ARM toolchain.
# Actually a script which is specific for the modelling tool like Rhapsody is appended to this toolchain specific script:
# this script must handle the map file only (in its main line) and map file (toolchain-) specific details. 
#
#
#
# Usage:	gawk -f MapKeilRV2XML.awk XMLFile="<XML file>" SourceFileList="<source file list>" WSTMonitor.h
# 
# 
# 
# 

BEGIN {

	flagDebug 	  		= 0;					# Flag: 1=debug, 0=off, 2=extra info
	flagErrorExit		= 0;					# 0=no,  1=yes, we exit with an error
	flagShowHighwater	= 1;					# show in XML file: 0=no,  1=yes

	# Some variables. Although AWK does not need any declarations of these,
	# it is a placeholder for default values and comment:
	# 

	noCFiles	   = 0;							# Number of C files. AWK is 1 based !! so 0 means no files.
	noHFiles 	   = 0;							# Number of include files with .h extension
	CFiles[ 1 ]	   = "";						# Array of C files
	HFiles[ 1 ]    = "";						# Array of H files

	sizeOfWST_FSM		= "";					# The size of a WST_FSM structure
	XMLFile		   		= "";					# XML output file
	SourceFileList 		= "";					# List of source files to parse. When no path is given, the files are expected in current working dir.
												# The order of .c and .h is not important.
	RXFDimensionsFile	= "";					# The file which contains highwater maximum values
	smallBuffersMaxConstant	 = "0";				# The value of RIC_INITIAL_SMALL_BUFFERS
	mediumBuffersMaxConstant = "0";				# The value of RIC_INITIAL_MEDIUM_BUFFERS
	largeBuffersMaxConstant  = "0";				# The value of RIC_INITIAL_LARGE_BUFFERS
	eventMaxConstant		 = "0";				# The value of RIC_MAX_EVENTS
	timeoutMaxConstant		 = "0";				# The value of RIC_MAX_TIMEOUTS

	application	   = "";						# The name of the application used for animation
	
	# A list of attributes we do not want to show in animation (no spaces allowed in it):
		
	NotVisibleAttributes	= "fsm,rootState_subState,rootState_active,ric_reactive";	


	# The script uses a number of arrays to store class data. AWK supports associative indexing and multiple dimensions,
	# which makes it easy to store various class related data:
	# - the name of a class is used as index in various arrays
	# - details we must store like events, states and attributes are stored as <value>:<item> so as a single combination.
	# - since you can not 'poke' into an array at a location where there is nothing, we use some global counters
	#
	# These are our data structures:
	#
	# - addressTable[]									to store a symbol in and use its address as index, so addressTable[ 0x10000 ] -> "foo"
	# 
	# - ClassNames[]									to store a class name. The global counter noClassNames keeps track of its dimension
	# 
	# - classAttributes[ <name>, <attribute index> ]	to store attributes. The first index <name> is the class name. <attribute index> 1 is the first attribute combination
	# - noClassAttributes[ <name> ]						to store how the number of attribute combinations for a class, indexed by the name of a class.
	# - classStates[ <name>, <state index> ]			to store states. The first index <name> is the class name. <state index> 1 is the first state combination
	# - noClassStates[ <name> ]							to store how the number of state combinations for a class, indexed by the name of a class.
	# - classEvents[ <name>, <event index> ]			to store events. The first index <name> is the class name. <event index> 1 is the first event combination
	# - noClassEvents[ <name> ]							to store how the number of event combinations for a class, indexed by the name of a class.
	# - classIsDynamic[ <boolean> ]						to store a boolean if a class is dynamic, indexed by the name of a class.
	# - CouldBeClassNames[]								to store a name which could be a class. The global counter noCouldBeClassNames keeps track of its dimension
	

	ClassNames[ 1 ] 		= "";				# array of class names found 
	noClassNames			= 0;				# its dimension
	CouldBeClassNames[ 1 ]	= "";				# array of symbols which could be a class
	noCouldBeClassNames		= 0;
	EventNames[ 1 ] 		= "";				# array of event names found 
	numberEventNames			= 0;				# its dimension

	
	eventCreation[1] = "";
																				


	# Some details on this script we can use in error messages:
	# 

	thisScript	   = "GenerateXMLForDebugger.awk"
	Revision1	   = "$Id: GenerateXMLForDebugger.awk 27420 2013-03-13 12:46:45Z ms $";
	URL1		   = "$URL: https://svn.willert.de/V6/trunk/Component/Modelling/Rpy/Tools/GenerateXMLForDebugger.awk $";
}

# Print the Target section in the XML file 
# Arguments:		none 
# Returns:			nothing
# 

function printXMLTargetDetails()
{
	printf( "\t<Target>\n\n" ) 												> XMLFile;
		
	printf( "\t\t<Endianness>Little</Endianness>\n\n" ) 					> XMLFile;
		
	printf( "\t\t<Alignment unit=\"Byte\">4</Alignment>\n\n" )	> XMLFile;
		
	printf( "\t\t<!-- Type defines, size attribute is in bytes -->\n\n" ) 			> XMLFile;

	printf( "\t\t<TypeList>\n" )													> XMLFile;
	printf( "\t\t\t<Type size=\"1\">signed char</Type>\n" )		> XMLFile;
	printf( "\t\t\t<Type size=\"1\">unsigned char</Type>\n" )	> XMLFile;
	printf( "\t\t\t<Type size=\"1\">char</Type>\n" )				> XMLFile;
	printf( "\t\t\t<Type size=\"2\">signed short</Type>\n" )	> XMLFile;
	printf( "\t\t\t<Type size=\"2\">unsigned short</Type>\n" )	> XMLFile;
	printf( "\t\t\t<Type size=\"4\">signed int</Type>\n" )		> XMLFile;
	printf( "\t\t\t<Type size=\"4\">unsigned int</Type>\n" )		> XMLFile;
	printf( "\t\t\t<Type size=\"4\">int</Type>\n" )				> XMLFile;
	printf( "\t\t\t<Type size=\"4\">float</Type>\n" )			> XMLFile;
	printf( "\t\t\t<Type size=\"8\">double</Type>\n" )			> XMLFile;
	printf( "\t\t\t<Type size=\"\">WST_FSM</Type>\n" )		> XMLFile;			
	printf( "\t\t\t<Type size=\"\">WST_TSK</Type>\n" )		> XMLFile;			
	printf( "\t\t\t<Type size=\"4\">*</Type>\n" )					> XMLFile;
	printf( "\t\t</TypeList>\n\n" )											> XMLFile;
					
	printf( "\t</Target>\n\n" )												> XMLFile;
}


# Add the specified symbol to the array CouldBeClassNames[]
# Argument:			symbolName (in data section)
# Returns:			nothing
#

function addThisSymbolToCouldBeAClass( symbolName )
{
	CouldBeClassNames[ ++noCouldBeClassNames ] = symbolName;
}




# Scan the array CouldBeClassNames[] to see if a symbol is matches ClassName
# Argument:			symbolName
# Returns:			0 if not, index in CouldBeClassNames[] when found
# Local variables:	i

function isInCouldBeClassNames( ClassName, i )
{
	if ( flagDebug )
	{
		printf( "ISINCOULDBECLASSNAMES(): scanning for '%s'", ClassName );
	}

	for ( i = 1; i <= noCouldBeClassNames; i++ )
	{
		if ( CouldBeClassNames[ i ] == ClassName )
		{
			if ( flagDebug )
			{
				printf( "  -> foud it\n" );
			}
			return 1;
		}
	}
	printf( "\n" );

	return 0;
}



# Add a symbol to the address table.
# Arguments:	the address of a symbol, the name of a symbol
# Returns:	nothing
# 

function addSymbolToAddressTable( symbolAddress, symbolName )
{
	addressTable[ symbolName ] = symbolAddress;
}



# Get the address of a symbol from the address table.
# Argument:	the name of a symbol
# Returns:		the address of a symbol
# 

function getAddressOfSymbolInAddressTable( symbolName )
{
	return addressTable[ symbolName ];
}



# Return the name of the class. Its input is something like "Builder_Create"
# Argument:	symbol of create function
# Returns:	class name
# 

function itsClassNameFromFunction( symbol )
{
	return substr( symbol, 1, index( symbol, "_" ) - 1 );
}




# Read the specified list of files and initialize HFiles[] and CFiles[]
# Argument:			file name of list with names of .c and .h files, any order
# Returns:			nothing
# Local variables:	status and i
#

function readList( list, status, i )
{
    if ( flagDebug > 1 )
    {
        printf( "READLIST(): reading from '%s'\n", list );
    }
   
    i = 0;
   
    status = getline < list;
    while ( status > 0 )
    {
        ++i;        
        if ( status > 0 ){
   
            if ( index( $0, ".h" ) )
            {
                HFiles[ ++noHFiles ] = $1;
               
                addThisSymbolToCouldBeAClass( substr( $1, 1, index( $1, "." ) - 1 ) );
            }
            else if ( index( $0, ".c" ) )
            {
                CFiles[ ++noCFiles ] = $1;
            }
            else if ( NF )
            {
                printf( "%s (%d): SourceFileList '%s', line %d ('%s') is not understood\n", thisScript, FNR, list, $0, i ) > "/dev/stderr";
                flagErrorExit++;
                exit( 1 );
            }
           
        }
		status = getline < list;
    }       
       
    if ( i <= 1 )
    {
        printf( "%s (%d): Can not read file list '%s'\n", thisScript, FNR, list ) > "/dev/stderr";
        flagErrorExit++;
        exit( 1 );
    }
}



# Handle the header files: collect all class data needed for the XML file.
# Arguments:		none
# Returns:			nothing
# Local variables:	i
#

function handleHeaderFiles( i )
{
	for ( i = 1; i <= noHFiles; i++ )
	{
		if ( flagDebug > 1 )
		{
			printf( "HANDLEHEADERFILES() HFiles[ %d ] = '%s'\n", i, HFiles[ i ] );
		}
		scanHeaderForData( HFiles[ i ] );
	}
}

# Handle the source files: collect all class data needed for the XML file.
# Arguments:		none
# Returns:			nothing
# Local variables:	i
#

function handleSourceFiles( i )
{
	for ( i = 1; i <= noCFiles; i++ )
	{
		
		if ( flagDebug > 1 )
		{
			printf( "HANDLESOURCEFILES() HFiles[ %d ] = '%s'\n", i, CFiles[ i ] );
		}
		scanSourceForData( CFiles[ i ] );
	}
}



# Scan header file (.h) for data needed for the XML file 
# Arguments:		headerFile - the name of the .h file to scan
# Returns:			nothing
# Local variables:	status, i, ClassName and headerFileIncludingPrefix
#
numberOfEventParas				= 0;
classEventParas[ ClassEventName, 1 ]		= "";
function scanHeaderForData( headerFile, status, i, ClassName, headerFileIncludingPrefix )
{
	i							= 0;
	ClassName					= substr( headerFile, 1, index( headerFile, "." ) - 1 );
	
	if ( pathPrefix == "" )
	{
		headerFileIncludingPrefix	= headerFile;
	}
	else
	{
		headerFileIncludingPrefix	= pathPrefix "/" headerFile;
	}

	ClassNames[ ++noClassNames ] = ClassName;

	if ( flagDebug > 1 )
	{
		printf( "SCANHEADERFORDATA() -> class = '%s', headerFileIncludingPrefix = '%s'\n", ClassName, headerFileIncludingPrefix );
	}
	
	numberOfAttributes				= 0;
	classAttributes[ ClassName, 1 ]	= "";

	numberOfStates					= 0;
	classStates[ ClassName, 1 ]		= "";
			
	numberOfEvents					= 0;
	classEvents[ ClassName, 1 ]		= "";


	do
	{
		++i;
		status = getline <  headerFileIncludingPrefix;

		eventStruct = $1 " " $2;

		if ( NF == 3 && $1 == "struct" && ( $2 == ClassName || index( $2, "_t" ) ) )
		{
			# This is a class. Fetch all its attributes
		
			numberOfAttributes = fetchAttributes( headerFile, i, ClassName );   
		}
		else if ( $1 == "enum" && index( $2, "_Enum" ) )
		{
			# Fetch the states
			
			numberOfStates = fetchStates( headerFile, i, ClassName );   
		}
		else if ( $1 == "#define" && index( $2, "_id" ) && ! index( $0, "_state" ) && !index($0, "_Timeout_") )
		{
			# Fetch the event
		
			classEvents[ ClassName, ++numberOfEvents ] = fetchEvent( $0 );	

			if ( flagDebug > 1 )
			{
				printf( "classEvents[ %s, %d ] = '%s'\n", ClassName, numberOfEvents, classEvents[ ClassName, numberOfEvents ] );
			}
		}
		else if ( eventStruct ~ /struct ev/) {
		# Added 2010/09/07: prints additionally the parameters of the events in the xml file to make it possible to trigger events with parameters	
			ClassEventName = $2 "_" ClassName;
			do {
				getline <  headerFileIncludingPrefix;
				if($1 !~ /};/ && $1 !~ /DECLARE_MEMORY_ALLOCATOR_MEMBER/ && $1 !~ /RiCEvent/ && $1 !~ /WST_EVT/) {
					classEventParas[ClassEventName, ++numberOfEventParas ] = $1 ":" $2;
					if(ClassEventName != EventNames[numberEventNames -1]) {
					EventNames[numberEventNames] = ClassEventName;
					numberEventNames++;
					}
				}								
			} while($1 !~ /};/);
			numberEventParas [ ClassEventName ] = numberOfEventParas;
			numberOfEventParas=0;
			
		################################	
		}
	}
		while ( status > 0 )
		
	if ( i <= 1 )
	{
		printf( "%s (%d): Can not read file headerFile '%s'\n", thisScript, FNR, headerFileIncludingPrefix ) > "/dev/stderr";
		flagErrorExit++;
		exit( 1 );
	}

	noClassAttributes[ ClassName ] = numberOfAttributes;
	noClassStates[ ClassName ]	   = numberOfStates;
	noClassEvents[ ClassName ] 	   = numberOfEvents;

	if ( flagDebug > 1 )
	{
		printf( "noClassAttributes[ %s ] = %d\n", ClassName, numberOfAttributes );
		printf( "noClassStates[ %s ] = %d\n", ClassName, numberOfStates );
		printf( "noClassEvents[ %s ] = %d\n", ClassName, numberOfEvents );
	}
}


# Scan source file (.c) for data needed for the XML file 
# Arguments:		sourceFile - the name of the .c file to scan
# Returns:			nothing
# Local variables:	status, i, ClassName and sourceFileIncludingPrefix
#
function scanSourceForData( sourceFile, status, i, ClassName, sourceFileIncludingPrefix )
{
	ClassName					= substr( sourceFile, 1, index( sourceFile, "." ) - 1 );
	if ( pathPrefix == "" )
	{
		sourceFileIncludingPrefix	= sourceFile;
	}
	else
	{
		sourceFileIncludingPrefix	= pathPrefix "/" sourceFile;
	}
	
	status = getline < sourceFileIncludingPrefix;
	while(status > 0)
	{
		if( index( $0, "WSTMonitor_sendInit") )
		{
			if ( flagDebug > 1 )
			{
				printf( "ClassID from class[ %s ] = %d\n", ClassName, numberOfAttributes );
			}
			addSymbolToAddressTable( $4,  "ID." tolower( ClassName ) );
		}
		status = getline < sourceFileIncludingPrefix;
	}
	
}



# Fetch the attributes of a class.
#
# Arguments:		headerFile - the name of the .h file to scan, currentLineNo - the current line number, ClassName - the name of the class
# Returns:			the number of states written to classAttributes[]
# Local variables:	status, i, j and headerFileIncludingPrefix
#

function fetchAttributes( headerFile, currentLineNo, ClassName, status, i, j, headerFileIncludingPrefix )
{
	i = currentLineNo;
	j = 0;

	if ( pathPrefix == "" )
	{
		headerFileIncludingPrefix	= headerFile;
	}
	else
	{
		headerFileIncludingPrefix	= pathPrefix "/" headerFile;
	}
	
	do
	{
		++i;
		status = getline < headerFileIncludingPrefix;

		if ( $1 == "};" )
		{
			break;
		}
		else if ( index( $0, ";" ) )
		{
			# Fetch this attribute
			
			classAttributes[ ClassName, ++j ] = fetchAttribute( $0 );   

			if ( flagDebug > 1 )
			{
				printf( "classAttributes[ %s, %d ] = '%s'\n", ClassName, numberOfAttributes, classAttributes[ ClassName, j ] );
			}
		}
	}
		while ( status > 0 )
		
	if ( i <= currentLineNo + 1 )
	{
		printf( "%s (%d): Unxpected EOF in headerFile '%s' at line %d\n", thisScript, FNR, headerFileIncludingPrefix, i ) > "/dev/stderr";
		flagErrorExit++;
		exit( 1 );
	}
	return j;
}




# Return the Attribute of a class using the sourceLine, like for example:
#
#	int c;		/*## attribute c */
#
# We return it in format <type>:<name>
# 
# Arguments:		sourceLine - the line which contains an attribute specification
# Returns:			nothing
# Local variables:	 variable, itsType, i, n and dummyArray
#

function fetchAttribute( sourceLine, variable, itsType, i, n, dummyArray )
{
	itsType = "";
	
	n = split( substr( sourceLine, 1, index( sourceLine, ";" ) ), dummyArray );
	
	for ( i = 1; i < n; i++ )
	{
		itsType = itsType " " dummyArray[ i ];
	}
	variable = substr( dummyArray[ n ], 1, length( dummyArray[ n ] ) - 1 );
	itsType	 = removeLeadingAndTrailingWhiteSpace( itsType );

	if ( flagDebug > 1 )
	{
		printf( "FETCHATTRIBUTE(): itsType = '%s', variable = '%s'\n", itsType, variable );
	}
	return itsType ":" variable; 
}




# Fetch the states of a class. These are generated for example as:
#
# 	enum Singleton_Enum {
#		Singleton_RiCNonState = 0,
#		Singleton_state_2 = 1,
#		Singleton_state_1 = 2,
#		Singleton_state_0 = 3
#	};
#
# Arguments:		headerFile - the name of the .h file to scan, currentLineNo - the current line number, ClassName - the name of the class
# Returns:			the number of states written to classStates[]
# Local variables:	status, i, j and headerFileIncludingPrefix
#

function fetchStates( headerFile, currentLineNo, ClassName, status, i, j, headerFileIncludingPrefix )
{
	i = currentLineNo;
	j = 0;

	if ( pathPrefix == "" )
	{
		headerFileIncludingPrefix	= headerFile;
	}
	else
	{
		headerFileIncludingPrefix	= pathPrefix "/" headerFile;
	}
	
	do
	{
		++i;
		status = getline < headerFileIncludingPrefix;

		if ( $1 == "};" )
		{
			break;
		}
		else if ( $2 == "=" )
		{
			# Fetch this state
			
			classStates[ ClassName, ++j ] = fetchState( $0 );   

			if ( flagDebug > 1 )
			{
				printf( "classStates[ %s, %d ] = '%s'\n", ClassName, j, classStates[ ClassName, j ] );
			}
		}
	}
		while ( status > 0 )
		
	if ( i <= currentLineNo + 1 )
	{
		printf( "%s: Unxpected EOF in headerFile '%s' at line %d\n", thisScript, headerFileIncludingPrefix, i ) > "/dev/stderr";
		flagErrorExit++;
		exit( 1 );
	}
	return j;
}




# Return the State of a class using the sourceLine, like for example:
#
#		Singleton_RiCNonState = 0,				or:
#		Singleton_state_0 = 3
#
# Arguments:		sourceLine - the line which contains a state specification
# Returns:			the state in format <state>:<value>
# Local variables:	status, itsValue, at
#

function fetchState( sourceLine, state, itsValue, at )
{
	state		= $1;
	itsValue	= $3;
	
	if ( at = index( itsValue, "," ) )
	{
		itsValue = substr( itsValue, 1, at - 1 );
	}

	if ( flagDebug > 1 )
	{
		printf( "FETCHSTATE(): itsValue = '%s', state = '%s'\n", itsValue, state );
	}
	return state ":" itsValue; 
}




# Return the Event of a class using the sourceLine, like for example:
#
#	#define evA_Default_id 18601
#
# Arguments:		sourceLine - the line which contains an attribute specification
# Returns:			the event in format <event>:<ID>
# Local variables:	event, itsID, i, n, dummyArray
# 

function fetchEvent( sourceLine, event, itsID, i, n, dummyArray )
{
	event = $2;
	itsID = $3;

	if ( flagDebug > 1 )
	{
		printf( "FETCHEVENT(): event = '%s', ID = '%s'\n", event, itsID );
	}
	return event ":" itsID; 
}



# Remove leading and trailing whitespace of some text 
# Arguments:		someItem - a string we want to strip 
# Returns:			the input string without a leading and trailing whitespace character(s)
# Local variables:	i, n, dummyArray, dummyString
# 

function removeLeadingAndTrailingWhiteSpace( someItem, i, n, dummyArray, dummyString )
{
	n = split( someItem, dummyArray );
	
	dummyString = "";
	
	for ( i = 1; i <= n; i++ )
	{
		dummyString = dummyString dummyArray[ i ];
	}
	return dummyString;
}



# Print the header of the XML file 
# Arguments:		none 
# Returns:			nothing
# Local vars:		Revision2, URL2
# 

function printXMLHeader( Revision2, URL2 )
{
	Revision2 = "$Id: GenerateXMLForDebugger.awk 27420 2013-03-13 12:46:45Z ms $";
	URL2	  = "$URL: https://svn.willert.de/V6/trunk/Component/Modelling/Rpy/Tools/GenerateXMLForDebugger.awk $";
		
	printf( "<?xml version =\"1.0\" standalone=\"yes\"?>\n\n" )							> XMLFile;
	printf( "<!-- This file is generated by %s which consists of: -->\n", thisScript )	> XMLFile;
	printf( "<!-- %s %s -->\n", Revision1, URL1 				)						> XMLFile;
	printf( "<!-- %s %s -->\n\n", Revision2, URL2 )										> XMLFile;
	printf( "<DataModel application=\"%s\">\n\n", application )   						> XMLFile;
}


# Print the footer of the XML file 
# Arguments:		none 
# Returns:			nothing
# 

function printXMLFooter()
{
	printf( "</DataModel>\n" ) > XMLFile;
}




function getHighWaterMaximumValues( i )
{
	i = 0;
	do
	{
		++i;
		
		status = getline < RXFDimensionsFile;

		if ( $2 == "WST_INITIAL_SMALL_BUFFERS" )
		{
			smallBuffersMaxConstant = $3;
		}
		else if ( $2 == "WST_INITIAL_MEDIUM_BUFFERS" )
		{
			mediumBuffersMaxConstant = $3;
		}
		else if ( $2 == "WST_INITIAL_LARGE_BUFFERS" )
		{
			largeBuffersMaxConstant = $3;
		}
		else if ( $2 == "WST_MAX_TIMEOUTS" )
		{
			timeoutMaxConstant = $3;
		}
	}
		while ( status > 0 )
		
	if ( i <= 1 )
	{
		printf( "%s (%d): Unxpected EOF in file '%s' at line %d\n", thisScript, FNR, RXFDimensionsFile, i ) > "/dev/stderr";
		flagErrorExit++;
		exit( 1 );
	}		
}


function printHighWater()
{
	printf( "\t<Highwater>\n\n" ) 																> XMLFile;
	
	printf( "\t\t<Address>%s</Address>\n\n", getAddressOfSymbolInAddressTable( "highwater" ) )	> XMLFile;

	printf( "\t\t<HighWaterList>\n" )															> XMLFile;

	printf( "\t\t\t<CurrentAndMax>\n" )															> XMLFile;
	printf( "\t\t\t\t<Name>%s</Name>\n", "smallBuffersMax"  )								 	> XMLFile;
	printf( "\t\t\t\t<Type>%s</Type>\n", "unsigned short" 	)									> XMLFile;
	printf( "\t\t\t\t<Max>%s</Max>\n", smallBuffersMaxConstant )								> XMLFile;
	printf( "\t\t\t\t<Visible>True</Visible>\n" ) 												> XMLFile;
	printf( "\t\t\t</CurrentAndMax>\n" )														> XMLFile;

	printf( "\t\t\t<CurrentAndMax>\n" )															> XMLFile;
	printf( "\t\t\t\t<Name>%s</Name>\n", "mediumBuffersMax"  ) 									> XMLFile;
	printf( "\t\t\t\t<Type>%s</Type>\n", "unsigned short" 	)									> XMLFile;
	printf( "\t\t\t\t<Max>%s</Max>\n", mediumBuffersMaxConstant )								> XMLFile;
	printf( "\t\t\t\t<Visible>True</Visible>\n" ) 												> XMLFile;
	printf( "\t\t\t</CurrentAndMax>\n" )														> XMLFile;

	printf( "\t\t\t<CurrentAndMax>\n" )															> XMLFile;
	printf( "\t\t\t\t<Name>%s</Name>\n", "largeBuffersMax"  ) 									> XMLFile;
	printf( "\t\t\t\t<Type>%s</Type>\n", "unsigned short" 	)									> XMLFile;
	printf( "\t\t\t\t<Max>%s</Max>\n", largeBuffersMaxConstant )								> XMLFile;
	printf( "\t\t\t\t<Visible>True</Visible>\n" ) 												> XMLFile;
	printf( "\t\t\t</CurrentAndMax>\n" )														> XMLFile;

	printf( "\t\t\t<CurrentAndMax>\n" )															> XMLFile;
	printf( "\t\t\t\t<Name>%s</Name>\n", "eventsMax"  ) 										> XMLFile;
	printf( "\t\t\t\t<Type>%s</Type>\n", "unsigned short" 	)									> XMLFile;
	printf( "\t\t\t\t<Max>%s</Max>\n", eventMaxConstant	)										> XMLFile;
	printf( "\t\t\t\t<Visible>True</Visible>\n" ) 												> XMLFile;
	printf( "\t\t\t</CurrentAndMax>\n" )														> XMLFile;

	printf( "\t\t\t<CurrentAndMax>\n" )															> XMLFile;
	printf( "\t\t\t\t<Name>%s</Name>\n", "timeoutsMax"  ) 										> XMLFile;
	printf( "\t\t\t\t<Type>%s</Type>\n", "unsigned short" 	)									> XMLFile;
	printf( "\t\t\t\t<Max>%s</Max>\n", timeoutMaxConstant )										> XMLFile;
	printf( "\t\t\t\t<Visible>True</Visible>\n" )								 				> XMLFile;
	printf( "\t\t\t</CurrentAndMax>\n" )														> XMLFile;	

	printf( "\t\t\t<Attribute>\n" )																> XMLFile;
	printf( "\t\t\t\t<Name>%s</Name>\n", "bufferOverflow"  ) 									> XMLFile;
	printf( "\t\t\t\t<Type>%s</Type>\n", "unsigned char" 	)									> XMLFile;
	printf( "\t\t\t\t<Visible>True</Visible>\n" ) 												> XMLFile;
	printf( "\t\t\t</Attribute>\n" )															> XMLFile;

	printf( "\t\t</HighWaterList>\n" )															> XMLFile;

	printf( "\t</Highwater>\n\n" ) 																> XMLFile;
}


# Print the EventList section in the XML file 
# Arguments:		none 
# Returns:			nothing
# 

function printEventList( i, j )
{
	printf( "\t<EventList>\n" )	> XMLFile;
	
	# Added 2010/03/22: prints additionally the addresses of the RiC_Create_* functions in the tag <Event> to make it possible to trigger events
#	eventCreation[1] = "";
#	
#	for (i in addressTable) {
#		if(i ~ /RiC_Create/) {
#			eventCreation[i] = addressTable[i];
#			#printf( "\t\t<EventCreation address=\"%s\">%s</EventCreation>\n", addressTable[i], i  )	> XMLFile;
#			
#		}
#	}
	##################
	
	


	for ( i = 1; i <= noClassNames; i++ )
	{
		for ( j = 1; j <= noClassEvents[ ClassNames[ i ] ]; j++ )
		{
			package = substr( classEvents[ ClassNames[ i ], j ], 1, index( classEvents[ ClassNames[ i ], j ], ":" ) - 1 );
			gotParameters = 0;
			if(tolower(package) ~ tolower(evName[2])) {
				printf( "\t\t<Event id=\"%s\" name=\"%s\">", substr( classEvents[ ClassNames[ i ], j ], index( classEvents[ ClassNames[ i ], j ], ":" ) + 1 ), substr( classEvents[ ClassNames[ i ], j ], 1, index( classEvents[ ClassNames[ i ], j ], ":" ) - 1 ) )	> XMLFile;
				# Added 2010/09/07: prints additionally the parameters of the events in the xml file to make it possible to trigger events with parameters
				for ( k = 0; k <= numberEventNames; k++)
				{
					for ( l = 1; l <= numberEventParas[ EventNames[ k ] ]; l++ )
					{
						split(substr( classEvents[ ClassNames[ i ], j ], 1, index( classEvents[ ClassNames[ i ], j ], ":" ) - 1 ),Event_Package,"_id");
						if(Event_Package[1] ~ EventNames[ k ] ) #&& classEventParas[ EventNames[ k ], l] != "RiCEvent:ric_event;") 
						{
							split (classEventParas[ EventNames[ k ], l], Parameter_Wert, ":");
							split (Parameter_Wert[2], Wert, ";");
							printf( "\n\t\t\t<Parameter type=\"%s\">%s</Parameter>" , Parameter_Wert[1],Wert[1] ) > XMLFile;
							gotParameters = 1;
						}
					}
				}
				if(gotParameters == 1)
				{
					printf( "\n\t\t</Event>\n")  > XMLFile;					
				}
				else{
					printf( "</Event>\n")  > XMLFile;
				}
			}		
		}
	}
	printf( "\t\t<Event id=\"-2\" name=\"Time out event\"></Event>\n") > XMLFile;
	printf( "\t</EventList>\n\n" ) > XMLFile;
}



# Print the Class section(s) in the XML file 
# Arguments:		none 
# Returns:			nothing
# Local variables:	i, j
# 

function printClassList( i, j )
{
	for ( i = 1; i <= noClassNames; i++ )
	{
		printf( "\t<Class>\n\n" )	> XMLFile;

		printf( "\t\t<Name>%s</Name>\n\n",  ClassNames[ i ] ) 	> XMLFile;
		printf( "\t\t<ID>%s</ID>\n\n",  getAddressOfSymbolInAddressTable( "ID." tolower( ClassNames[ i ] ) ) ) 	> XMLFile;
		
		printStatesOfClass( i );
		printAttributesOfClass( i );
		
		if ( flagDebug > 1 )
		{
			printf( "SEARCHING '%s': ", "rootState_entDef." tolower( ClassNames[ i ] ) );
		}
		
		if ( getAddressOfSymbolInAddressTable( "rootState_entDef." tolower( ClassNames[ i ] ) ) != "" )
		{
			if ( flagDebug > 1 )
			{
				printf( "FOUND\n" );
			}

			printf( "\t\t\t<Function>\n" )																									> XMLFile;
			printf( "\t\t\t\t<Name>rootState_entDef</Name>\n")																				> XMLFile;
			printf( "\t\t\t\t<Address>%s</Address>\n", getAddressOfSymbolInAddressTable( "rootState_entDef." tolower( ClassNames[ i ] ) ) )	> XMLFile;
			printf( "\t\t\t</Function>\n\n" )																								> XMLFile;	
		}
		else
		{
			if ( flagDebug > 1 )
			{
				printf( "NOT FOUND\n" );
			}
		}

		printf( "\t</Class>\n\n" ) > XMLFile;
	}
}



# Find a Class in ClassNames[] 
# Arguments:		ClassName - the name of the class we want in ClassNames[]
# Returns:			index of specified ClassName in ClassNames[]
# Local variables:	i
# 

function indexOfClassInClassNames( ClassName, i )
{
	for ( i = 1; i <= noClassNames; i++ )
	{
		if ( ClassNames[ i ] == ClassName )
		{
			return i;
		}
	}
	printf( "%s (%d): Class '%s' used to instantiate from is not found\n", thisScript, FNR, ClassName ) > "/dev/stderr";
	flagErrorExit++;
	exit( 1 );	
}


# Print the State(s) of a Class in the XML file 
# Arguments:		none 
# Returns:			nothing
# Local variables:	i, j
# 

function printStatesOfClass( ClassNameIndex, j, at )
{
	for ( j = 1; j <= noClassStates[ ClassNames[ ClassNameIndex ] ]; j++ )
	{
		at = index( classStates[ ClassNames[ ClassNameIndex ], j ], ":" );
		
		printf( "\t\t\t<State Id=\"%s\">%s</State>\n", substr( classStates[ ClassNames[ ClassNameIndex ], j ], at + 1 ), substr( classStates[ ClassNames[ ClassNameIndex ], j ], 1, at - 1 ) ) > XMLFile;
	}
	printf( "\n" ) > XMLFile;
}



# Print the Attribute(s) of a Class in the XML file 
# Arguments:		ClassNameIndex - the index in the list of class names ClassNames[] 
# Returns:			nothing
# Local variables:	j, at
# 

function printAttributesOfClass( ClassNameIndex, j, at )
{
	if ( noClassAttributes[ ClassNames[ ClassNameIndex ] ] )
	{
		printf( "\t\t\t<AttributeList>\n" )		> XMLFile;
		
		for ( j = 1; j <= noClassAttributes[ ClassNames[ ClassNameIndex ] ]; j++ )
		{
			at = index( classAttributes[ ClassNames[ ClassNameIndex ], j ], ":" );
			
			printf( "\t\t\t\t<Attribute>\n" )																					> XMLFile;
			printf( "\t\t\t\t\t<Name>%s</Name>\n", substr( classAttributes[ ClassNames[ ClassNameIndex ], j ], at + 1 ) ) 		> XMLFile;
			printf( "\t\t\t\t\t<Type>%s</Type>\n", substr( classAttributes[ ClassNames[ ClassNameIndex ], j ], 1, at - 1 ) )	> XMLFile;

			if ( isAttributeVisible( substr( classAttributes[ ClassNames[ ClassNameIndex ], j ], at + 1 ) ) )
			{
				printf( "\t\t\t\t\t<Visible>True</Visible>\n" ) > XMLFile;
			}
			else
			{
				printf( "\t\t\t\t\t<Visible>False</Visible>\n" ) > XMLFile;
			}
			printf( "\t\t\t\t</Attribute>\n" )																					> XMLFile;
		}
		
		printf( "\t\t\t</AttributeList>\n\n" )	> XMLFile;
	}
}



# Check if attribute is visible
# Arguments:		attribute 
# Returns:			1 if in list, 0 if not
# Local variables:	i, n, dummy
#
function isAttributeVisible( attributeName, i, n, dummy )
{
	n = split( NotVisibleAttributes, dummy, "," );

	for ( i = 1; i <= n; i++ )
	{
		if ( flagDebug )
		{
			printf( "isattributeVisible(): attributeName = '%s', dummy[ %d ] = '%s'\n", attributeName, i, dummy[ i ] );
		}

		if ( attributeName == dummy[ i ] )
		{
			return 0;
		}
	}
	return 1;
}



# Print the XML file 
# Arguments:		none 
# Returns:			nothing
# Local variables:	i, j
#
 
function printXMLFile( i, j )
{
	printXMLHeader();
	printXMLTargetDetails();
	printEventList();
	
	if ( flagShowHighwater )
	{
		getHighWaterMaximumValues();
		printHighWater();
	}

	printClassList();

	if ( flagDebug )
	{
		printf( "'%s' -> '%s'\n", "main", getAddressOfSymbolInAddressTable( "main" ) );

		for ( i = 1; i <= noClassNames; i++ )
		{
			printf( "Class '%s'", ClassNames[ i ] );
			
			for ( j = 1; j <= noClassAttributes[ ClassNames[ i ] ]; j++ )
			{
				printf( " attribute %d = '%s'", j, classAttributes[ ClassNames[ i ], j ] );
			}
			for ( j = 1; j <= noClassStates[ ClassNames[ i ] ]; j++ )
			{
				printf( " state %d = '%s'", j, classStates[ ClassNames[ i ], j ] );
			}
			for ( j = 1; j <= noClassEvents[ ClassNames[ i ] ]; j++ )
			{
				printf( " event %d = '%s'", j, classEvents[ ClassNames[ i ], j ] );
			}
			printf( "\n" );
		}
	}
	
	printXMLFooter();
}


	
END {	
	readList( SourceFileList );
	handleHeaderFiles();
	handleSourceFiles();
	printXMLFile();	
}

