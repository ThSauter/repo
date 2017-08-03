# $Id: macroAndPragma2Header.awk 34164 2016-04-06 08:50:44Z eroemer $
# $URL: https://svn.willert.de/V6/trunk/Component/Modelling/Rpy/Tools/macroAndPragma2Header.awk $
#
# 
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
#
# This script generates macros and pragmas in 'WSTMemoryTypes.h' 
# 
# The macros are according to http://fogbugz.willert.de/fogbugz/default.php?W98
# 
# The memory categories, running phases, data types and memory types are described in a template,
# which is input for this script.
# 
# The pragmas are typically defined in a compiler specific file MemoryTypePragmas.txt
#
# The phases are not implemented yet.
# 
# Help: http://www.gnu.org/software/gawk/manual/
#
# Usage: awk -f macroAndPragma2Header.awk pragmaFile=MemoryTypePragmas.txt MemoryTypeMacro.template
#
# Email: support@willert.de
#


BEGIN {
	flagDebug				= 0;			# for debugging
	flagErrorExit			= 0;			# 0=no, 1=yes, we exit with an error
	pragmaFile				= "";			# e.g. MemoryTypePragmasKeilRV-ARM7.txt, MemoryTypePragmasMetrowerks-HC08.txt, etc
	useShortSectionNames    = 0;			# if set, use the first two characters of all tokens which build a section name in printDataMacroAndPragmas()
	
	nMemoryCategories 		= 0;			# dimension memoryCategories[]
	memoryCategories[ 1 ]	= "";			# RXF, RTOS, APPL
	nPhases					= 0;			# dimension phases[]
	phases[ 1 ] 			= "";			# POWERON, POWERDOWN, SLEEP, RUNNING
	nDataSizes				= 0;			# dimension dataSizes[]
	dataSizes[ 1 ]			= "";			# 8 (bits), 16 (bits), 32 (bits), UNSPECIFIED (bits)
	nDataTypes				= 0;			# dimension dataTypes[]
	dataTypes[ 1 ] 			= "";			# INIT, NOINIT, CONST
	nMemoryTypes			= 0;			# dimension memoryTypes[]
	memoryTypes[ 1 ]		= "";			# FAST, SLOW

	nPragmaCodeMemoryTypes			= 0;		# index in pragmaCodeMemoryTypes[ x ]
	pragmaCodeMemoryTypes[ 1, 1 ] 	= "";		# storage CODE related pragmas.
												# First: memory type. Second: 1 (START_SEC) or 2 (STOP_SEC)
	pragmaDataMemoryTypes[ 1, 1, 1, 1 ]	= "";	# storage DATA related pragmas
												# First: <memory type>, second: <data type>, third: <data size>. Last: 1 (START_SEC) or 2 (STOP_SEC)

	thisScript				= "macroAndPragma2Header.awk";
	ID						= "$Id: macroAndPragma2Header.awk 34164 2016-04-06 08:50:44Z eroemer $";
	
	sub( "Id:", "", ID );
	sub( "URL:", "", URL );
	printf( "/* This file is generated via %s - do not edit!\n *\n *\n */\n\n", ID );
}
{
	if ( at = index( $0, "Memory categories:" ) )
	{
		nMemoryCategories = split( substr( $0, at + 18 ), memoryCategories, "," );

		for ( z = 1; z <= nMemoryCategories; z++ )
		{
			gsub( " ", "", memoryCategories[ z ] );
			
			if ( flagDebug > 1 )
			{
				printf( "memoryCategories[ %d ] = '%s'\n", z, memoryCategories[ z ] );
			}
		} 
	}
	else if ( at = index( $0, "Phases:" ) )
	{
		nPhases = split( substr( $0, at + 7 ), phases, "," );

		for ( z = 1; z <= nPhases; z++ )
		{
			gsub( " ", "", phases[ z ] );

			if ( flagDebug > 1 )
			{
				printf( "phases[ %d ] = '%s'\n", z, phases[ z ] );
			}
		} 
	}
	else if ( at = index( $0, "Data size:" ) )
	{
		nDataSizes = split( substr( $0, at + 10 ), dataSizes, "," );
		
		for ( z = 1; z <= nDataSizes; z++ )
		{
			dataSizes[ z ] = substr( dataSizes[ z ], 1, index( dataSizes[ z ], " (" ) );
			gsub( " ", "", dataSizes[ z ] );

			if ( flagDebug > 1 )
			{
				printf( "dataSizes[ %d ] = '%s'\n", z, dataSizes[ z ] );
			}
		} 
	}
	else if ( at = index( $0, "Data type:" ) )
	{
		nDataTypes = split( substr( $0, at + 10 ), dataTypes, "," );

		for ( z = 1; z <= nDataTypes; z++ )
		{
			gsub( " ", "", dataTypes[ z ] );

			if ( flagDebug > 1 )
			{
				printf( "dataTypes[ %d ] = '%s'\n", z, dataTypes[ z ] );
			}
		} 
	}
	else if ( at = index( $0, "Memory type:" ) )
	{
		nMemoryTypes = split( substr( $0, at + 12 ), memoryTypes, "," );

		for ( z = 1; z <= nMemoryTypes; z++ )
		{
			gsub( " ", "", memoryTypes[ z ] );

			if ( flagDebug > 1 )
			{
				printf( "memoryTypes[ %d ] = '%s'\n", z, memoryTypes[ z ] );
			}
		} 
	}
	else if ( index( $0, "Id:" ) )
	{
			sub( "Id:", "" );
	}
	print;
}



function fetchAllPragmas( status, z )
{
	status = 1;

	while ( status > 0 )
	{
		status = getline < pragmaFile;
		
		if ( status <= 0 )
		{
			if ( ! nPragmaCodeMemoryTypes )
			{
				close( pragmaFile );	
				return 0;
			}
			else
			{
				# We are done.
			
				if ( flagDebug )
				{
					printf( "fetchAllPragmas(): status = %d, read '%s'\n", status, $0 );
				}
				close( pragmaFile );	
				return 1;
			}
		}
		
		if ( flagDebug )
		{
			printf( "fetchAllPragmas() (start): reading %-40.40s\n", $0 );
		}

		if ( $1 == "CODE" )
		{	
			# Fetch all pragmas, CODE first, then DATA
			
			fetchCodePragmas();		# the first pair (START_SEC/STOP_SEC) for memoryTypes[ 1 ]
			
			for ( z = 2; z <= nMemoryTypes; z++ )
			{
				# the next pair(s) (START_SEC/STOP_SEC) for memoryTypes[ z ]
				
				status = getline < pragmaFile;
		
				if ( status <= 0 )
				{
					printf( "%s: Unexpected EOF reading CODE pragmas from '%s'", thisScript, pragmaFile ) > "/dev/stderr";
					flagErrorExit++;
					exit( 1 );
				}
				if ( flagDebug )
				{
					printf( "fetchAllPragmas(), CODE section: reading %-40.40s\n", $0 );
				}
				fetchCodePragmas();
			}
			fetchDataPragmas();		# each pair for each memoryType[]
		}
	}
}


function isInMemoryTypes( type, z )
{
	for ( z = 1; z <= nMemoryTypes; z++ )
	{
		if ( flagDebug > 1 )
		{
			printf( "isInMemoryTypes(): Verifying '%s' against '%s' ", type, memoryTypes[ z ] );
		}
		
		if ( type == memoryTypes[ z ] )
		{
			if ( flagDebug > 1 )
			{
				printf( "-> memoryTypes[ %d ]\n", z );
			}
			return z;
		}

		if ( flagDebug > 1 )
		{
			printf( "\n" );
		}
	}
	if ( flagDebug > 1 )
	{
		printf( "-> not found!\n", z );
	}

	return 0;
}


function isInDataTypes( type, z )
{
	for ( z = 1; z <= nDataTypes; z++ )
	{
		if ( flagDebug > 1 )
		{
			printf( "isInDataTypes(): Verifying '%s' against '%s' ", type, dataTypes[ z ] );
		}
		
		if ( type == dataTypes[ z ] )
		{
			if ( flagDebug > 1 )
			{
				printf( "-> dataTypes[ %d ]\n", z );
			}
			return z;
		}

		if ( flagDebug > 1 )
		{
			printf( "\n" );
		}
	}
	if ( flagDebug > 1 )
	{
		printf( "-> not found!\n", z );
	}

	return 0;
}


function isInDataSizes( type, z )
{
	for ( z = 1; z <= nDataSizes; z++ )
	{
		if ( flagDebug > 1 )
		{
			printf( "isInDataSizes(): Verifying '%s' against '%s' ", type, dataSizes[ z ] );
		}
		
		if ( type == dataSizes[ z ] )
		{
			if ( flagDebug > 1 )
			{
				printf( "-> dataSizes[ %d ]\n", z );
			}
			return z;
		}

		if ( flagDebug > 1 )
		{
			printf( "\n" );
		}
	}
	if ( flagDebug > 1 )
	{
		printf( "-> not found!\n", z );
	}
	return 0;
}


# Read the code pragmas for a single memory type (e.g. fast or slow).
# We need to process a pair, which consists of a named section (macro is START_SEC) and a default section (macro is STOP_SEC).
# We use pragmaCodeMemoryTypes[ <memory type>, <start|stop> ]. All indexes are 1 based.
# 

function fetchCodePragmas()
{
	nPragmaCodeMemoryTypes++;

	if ( flagDebug )
	{
		printf( "fetchCodePragmas(): nPragmaCodeMemoryTypes=%d\n", nPragmaCodeMemoryTypes );
	}
	
	if ( ! isInMemoryTypes( $2 ) )
	{
		printf( "%s: Illegal CODE pragma specifier '%s' found in line %d '%s'", thisScript, $2, FNR, pragmaFile ) > "/dev/stderr";
		flagErrorExit++;
		exit( 1 );
	}
	pragmaCodeMemoryTypes[ nPragmaCodeMemoryTypes, 1 ] = fetchPragma();

	if ( flagDebug > 1 )
	{
		printf( "%-40.40s -> pragmaCodeMemoryTypes[ %d, 1 ] = '%s'\n", $0, nPragmaCodeMemoryTypes, pragmaCodeMemoryTypes[ nPragmaCodeMemoryTypes, 1 ] );
	}

	status = getline < pragmaFile;

	if ( status <= 0 )
	{
		printf( "%s: No closing CODE pragma for '%s' in '%s'", thisScript, $2, pragmaFile ) > "/dev/stderr";
		flagErrorExit++;
		exit( 1 );
	}
	pragmaCodeMemoryTypes[ nPragmaCodeMemoryTypes, 2 ] = fetchPragma();

	if ( flagDebug )
	{
		printf( "fetchCodePragmas() (end): reading %-40.40s\n", $0 );
	}
	if ( flagDebug > 1 )
	{
		printf( "%-40.40s -> pragmaCodeMemoryTypes[ %d, 2 ] = '%s'\n", $0, nPragmaCodeMemoryTypes, pragmaCodeMemoryTypes[ nPragmaCodeMemoryTypes, 2 ] );
	}
}


# Read the data pragmas for a single memory type (e.g. fast or slow), but all data types (e.g. init/noinit/const) and all sizes (8/16/32/unspecified)
# Each time, we need to process a pair, which consists of a named section (macro is START_SEC) and a default section (macro is STOP_SEC).
# We use pragmaDataMemoryTypes[ <memory type>, <data type>, <data size>, <start|stop> ]. All indexes are 1 based.
# 

function fetchDataPragmas( status, i, j, k, indexMemoryType, indexDataType, indexDataSize )
{
	if ( flagDebug )
	{
		printf( "fetchDataPragmas(): nMemoryTypes=%d, nDataTypes=%d, nDataSizes=%d\n", nMemoryTypes, nDataTypes, nDataSizes );
	}

	for ( i = 1; i <= nMemoryTypes; i++ )
	{
		for ( j = 1; j <= nDataTypes; j++ )
		{
			for ( k = 1; k <= nDataSizes; k++ )
			{
				status = getline < pragmaFile;
		
				if ( status <= 0 )
				{
					printf( "%s: Unexpected EOF reading DATA pragmas (%dth memory type, %dth data type, %dth data size) from '%s'", thisScript, i, j, k, pragmaFile ) > "/dev/stderr";
					flagErrorExit++;
					exit( 1 );
				}
				if ( flagDebug )
				{
					printf( "fetchDataPragmas(), DATA section: reading %-40.40s\n", $0 );
				}
	
				if ( ! ( indexMemoryType = isInMemoryTypes( $2 ) ) || ! ( indexDataType = isInDataTypes( $3 ) ) || ! ( indexDataSize = isInDataSizes( $4 ) ) )
				{
					printf( "%s: Illegal DATA pragma specifier '%s %s %s' found in line %d '%s'", thisScript, $2, $3, $4, FNR, pragmaFile ) > "/dev/stderr";
					flagErrorExit++;
					exit( 1 );
				}
				pragmaDataMemoryTypes[ indexMemoryType, indexDataType, indexDataSize, 1 ] = fetchPragma();
			
				if ( flagDebug > 1 )
				{
					printf( "%-40.40s -> pragmaDataMemoryTypes[ %d, %d, %d, 1 ] = '%s' (memoryType %d = '%s', dataType %d = '%s', dataSize %d = '%s')\n", $0, indexMemoryType, indexDataType, indexDataSize, pragmaDataMemoryTypes[ indexMemoryType, indexDataType, indexDataSize, 1 ], indexMemoryType, memoryTypes[ indexMemoryType ], indexDataType, dataTypes[ indexDataType ], indexDataSize, dataSizes[ indexDataSize ] );
				}
			
				status = getline < pragmaFile;
			
				if ( status <= 0 )
				{
					printf( "%s: No closing DATA pragma for '%s' in '%s'", thisScript, pragmaDataMemoryTypes[ indexMemoryType, indexDataType, indexDataSize, 1 ], pragmaFile ) > "/dev/stderr";
					flagErrorExit++;
					exit( 1 );
				}
				pragmaDataMemoryTypes[ indexMemoryType, indexDataType, indexDataSize, 2 ] = fetchPragma();
			
				if ( flagDebug > 1 )
				{
					printf( "%-40.40s -> pragmaDataMemoryTypes[ %d, %d, %d, 2 ] = '%s' (memoryType %d = '%s', dataType %d = '%s', dataSize %d = '%s')\n", $0, indexMemoryType, indexDataType, indexDataSize, pragmaDataMemoryTypes[ indexMemoryType, indexDataType, indexDataSize, 2 ], indexMemoryType, memoryTypes[ indexMemoryType ], indexDataType, dataTypes[ indexDataType ], indexDataSize, dataSizes[ indexDataSize ] );
				}
			}
		}
	}
}



function fetchPragma( pragma, at )
{
	if ( at = index( $0, "#pragma" ) )
	{
		pragma = substr( $0, at );										/* fetch proper line part	*/
		pragma = substr( pragma, 1, index( pragma, "/*" ) - 1 );		/* remove comment, if any	*/
	}
	else
	{
		pragma = "";
	}
	return( pragma );
}


function printMacrosAndPragmas( i, j, k, l, m, sectionName, pragma )
{
	if ( flagDebug )
	{
		printf( "nMemoryCategories = %d: ", nMemoryCategories );
		for ( i = 1; i <= nMemoryCategories; i++ )
		{
			printf( "'%s' ", memoryCategories[ i ] );
		}
		printf( "\n" );

		printf( "nPhases = %d: ", nPhases );
		for ( i = 1; i <= nPhases; i++ )
		{
			printf( "'%s' ", phases[ i ] );
		}
		printf( "\n" );

		printf( "nMemoryTypes  = %d: ", nMemoryTypes );
		for ( i = 1; i <= nMemoryTypes; i++ )
		{
			printf( "'%s' ", memoryTypes [ i ] );
		}
		printf( "\n" );

		printf( "nDataTypes = %d: ", nDataTypes );
		for ( i = 1; i <= nDataTypes; i++ )
		{
			printf( "'%s' ", dataTypes[ i ] );
		}
		printf( "\n" );

		printf( "nDataSizes = %d: ", nDataSizes );
		for ( i = 1; i <= nDataSizes; i++ )
		{
			printf( "'%s' ", dataSizes[ i ] );
		}
		printf( "\n" );
	}
	
	printf( "\n\n\n\n" );
	
	for ( l = 1; l <= nMemoryCategories; l++ )
	{
		for ( m = 1; m <= nPhases; m++ )
		{
			for ( i = 1; i <= nMemoryTypes; i++ )
			{
				printCodeMacroAndPragmas( l, m, i );
				printDataMacroAndPragmas( l, m, i );
			}
		}
	}			
}


function printCodeMacroAndPragmas( l, m, i )
{
	sectionName = "CODE_" memoryCategories[ l ] "_" phases[ m ] "_" memoryTypes[ i ];

	# For some toolchains, no pragma may be used in some cases, so pragma may end up empty.
	# Furthermore, not all pragma commands do have a '%s' in it, so when gsub fails, this is not a problem.
	# 

	pragma      = pragmaCodeMemoryTypes[ i, 1 ];
	gsub( "%s", sectionName, pragma );
	
	printf( "#if defined( WST_%s_%s_%s_%s_%s )\n" , memoryCategories[ l ], phases[ m ], "START_SEC", "CODE", memoryTypes[ i ] );
	printf( "#undef WST_%s_%s_%s_%s_%s\n" , memoryCategories[ l ], phases[ m ], "START_SEC", "CODE", memoryTypes[ i ] );
	printf( "%s\n", pragma );
	printf( "#endif\n\n" );

	pragma      = pragmaCodeMemoryTypes[ i, 2 ];
	gsub( "%s", sectionName, pragma );

	printf( "#if defined( WST_%s_%s_%s_%s_%s )\n" , memoryCategories[ l ], phases[ m ], "STOP_SEC",  "CODE", memoryTypes[ i ] );
	printf( "#undef WST_%s_%s_%s_%s_%s\n" , memoryCategories[ l ], phases[ m ], "STOP_SEC",  "CODE", memoryTypes[ i ] );
	printf( "%s\n", pragma );
	printf( "#endif\n\n" );
}


function printDataMacroAndPragmas( l, m, i, j, k  )
{
	for ( k = 1; k <= nDataSizes; k++ )
	{
		for ( j = 1; j <= nDataTypes; j++ )
		{
			if ( flagDebug > 1 )
			{
				printf( "pragmaDataMemoryTypes[ %d, %d, %d, %d ] = %s\n", i, j, k, 1, pragmaDataMemoryTypes[ i, j, k, 1 ] );
				printf( "pragmaDataMemoryTypes[ %d, %d, %d, %d ] = %s\n", i, j, k, 2, pragmaDataMemoryTypes[ i, j, k, 2 ] );
			}
		
			if ( useShortSectionNames )
			{
				sectionName = "DA" substr( memoryCategories[ l ], 1, 2 ) substr( phases[ m ], 1, 2 ) substr( dataSizes[ k ], 1, 2 ) substr( dataTypes[ j ], 1, 2 ) substr( memoryTypes[ i ] 1, 2 );
			}
			else
			{
				sectionName = "DATA_" memoryCategories[ l ] "_" phases[ m ] "_" dataSizes[ k ] "_" dataTypes[ j ] "_" memoryTypes[ i ];
			}	

			# For some toolchains, no pragma may be used in some cases, so pragma may end up empty.
			# Furthermore, not all pragma commands do have a '%s' in it, so when gsub fails, this is not a problem.
			# 
			
			pragma      = pragmaDataMemoryTypes[ i, j, k, 1 ];
			gsub( "%s", sectionName, pragma );
			
			printf( "#if defined( WST_%s_%s_%s_%s_%s_%s_%s )\n" , memoryCategories[ l ], phases[ m ], "START_SEC", "DATA", dataTypes[ j ], dataSizes[ k ], memoryTypes[ i ] );
			printf( "#undef WST_%s_%s_%s_%s_%s_%s_%s\n" , memoryCategories[ l ], phases[ m ], "START_SEC", "DATA", dataTypes[ j ], dataSizes[ k ], memoryTypes[ i ] );
			printf( "%s\n", pragma );
			printf( "#endif\n\n" );
		
			pragma      = pragmaDataMemoryTypes[ i, j, k, 2 ];
			gsub( "%s", sectionName, pragma );
		
			printf( "#if defined( WST_%s_%s_%s_%s_%s_%s_%s )\n" , memoryCategories[ l ], phases[ m ], "STOP_SEC", "DATA", dataTypes[ j ], dataSizes[ k ], memoryTypes[ i ] );
			printf( "#undef WST_%s_%s_%s_%s_%s_%s_%s\n" , memoryCategories[ l ], phases[ m ], "STOP_SEC", "DATA", dataTypes[ j ], dataSizes[ k ], memoryTypes[ i ] );
			printf( "%s\n", pragma );
			printf( "#endif\n\n" );
		}
	}
}


END {
	
	if ( ! nMemoryCategories || ! nPhases || ! nDataSizes || ! nDataTypes || ! nMemoryTypes )
	{
		printf( "%s: Illegal input", thisScript ) > "/dev/stderr";
		exit( 1 );
	}
	if ( flagErrorExit )
	{
		exit( 1 );
	}
	if ( fetchAllPragmas() )
	{
		printMacrosAndPragmas();
	}
	else
	{
		printf( "\n\n/* This file is empty - the pragma file used for input contains no pragmas\n * most probably not to slow down the compilation.\n */\n\n\n" );
	}
}
