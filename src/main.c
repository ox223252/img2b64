// file auto generated

#include <stdlib.h>
#include <stdint.h>
#include "./lib/config/config_arg.h"
#include "./lib/config/config_file.h"
#include "lib/log/log.h"
#include <errno.h>
#include <string.h>

#include "lib/base64/base64.h"


#ifdef _WIN32
#define pause() getchar()
#else
#define pause()
#endif
 

int main ( int argc, char ** argv )
{
	// INIT_VAR
	char inFile[ 64 ] = { 0 };
	char outFile[ 64 ] = { 0 };
	char *out = outFile;
	int result;
 
	struct
	{
		#ifdef __LOG_H__
		uint8_t help:1,
			quiet:1,
			color:1,
			debug:1;
		#else
		uint8_t help:1,
			unused:3; // to have same allignement with and without debug/color/quiet flags
		#endif
	}flags = { 0 };
 
	param_el param[] =
	{
		{ "--help", "-h", 0x01, cT ( bool ), &flags, "help" },
		#ifdef __LOG_H__
		{ "--quiet", "-q", 0x02, cT ( bool ), &flags, "quiet" },
		{ "--color", "-c", 0x0c, cT ( bool ), &flags, "color" },
		{ "--debug", "-d", 0x08, cT ( bool ), &flags, "debug" },
		#endif
		{ "--inFile", "-i", 1, cT ( str ), &inFile, "in file name" },
		{ "--outFile", "-o", 1, cT ( str ), &outFile, "out file name" },
		{ NULL }
	};
 
	// INIT_CORE		
	// INIT_CONFIG
	if ( readParamArgs ( argc, argv, param ) )
	{ // failure case
		logVerbose ( "failure occured\n" );
		logDebug ( "read param failed line %d\n", result );
		pause ( );
		return ( __LINE__ );
	}
	else if ( flags.help )
	{// configFile read successfully
		helpParamArgs ( param );
		pause ( );
		return ( 0 );
	}
	else
	{
		logSetQuiet ( flags.quiet );
		logSetColor ( flags.color );
		logSetDebug ( flags.debug );
	}
	// END_CONFIG

	if ( !inFile[ 0 ] || 
		!outFile[ 0 ] )
	{
		if ( !inFile[ 0 ] )
		{
			printf ( "set input file name : " );
			scanf ( "%63s", inFile );
			while ( getchar ( ) != '\n' );
		}

		if ( !outFile[ 0 ] )
		{
			printf ( "set output file name : " );
			scanf ( "%63s", outFile );
			while ( getchar ( ) != '\n' );
		}
	}

	if ( result = encodeBase64 ( B64_F2F, ( uint8_t * )inFile, ( uint8_t ** )&out, NULL ) )
	{
		logVerbose ( "failure occured\n" );
		logDebug ( "encodage failed line %d\n", result );
		logDebug ( "%s\n", strerror ( errno ) );
		pause ( );
		return ( __LINE__ );
	}

	// END_CORE
	logVerbose ( "Encodage done\n" );
	pause ( );
	return ( 0 );
}

