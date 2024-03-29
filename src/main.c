// file auto generated

#include <stdlib.h>
#include <stdint.h>
#include "./lib/config/config_arg.h"
#include "./lib/config/config_file.h"
#include "lib/log/log.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "lib/base64/base64.h"


#ifdef _WIN32
#define pause() getchar()
#else
#define pause()
#define O_BINARY 0
#endif
 
static int verifyFileExistAndRemove ( char * name )
{
	int rd;
	if ( !access( name, F_OK ) )
	{
		printf ( "file exist, delete (y/n)?\n\n" );
		do
		{
			#ifndef _WIN32
			printf ( "\e[A\e[2K" );
			#endif
			rd = getchar ( );
			while ( getchar ( ) != '\n' );

			if ( rd == 'n' || rd == 'N' )
			{
				return ( __LINE__ );
			}
		}
		while ( ( rd != 'y' ) && ( rd != 'Y' ) );

		remove ( name );
	}
	return ( 0 );
}

int main ( int argc, char ** argv )
{
	// INIT_VAR
	char *inFile[ 512 ] = { NULL };
	char *outFile = NULL;
	char ext[ 16 ] = { 0 };
	char inName[ 64 ] = { 0 };
	char outName[ 64 ] = { 0 };
	FILE *file = NULL;
	int result = 0;
	int nbElements = 0;
 
	struct
	{
		uint8_t help:1,
		#ifdef __LOG_H__
			quiet:1,
			color:1,
			debug:1;
		#else
			unused:3; // to have same allignement with and without debug/color/quiet flags
		#endif
		uint8_t outHtml:1,
			format:1;
	}flags = { 0 };
 
	param_el param[] =
	{
		{ "--help", "-h", 0x01, cT ( bool ), &flags, "help" },
		#ifdef __LOG_H__
		{ "--quiet", "-q", 0x02, cT ( bool ), &flags, "quiet" },
		{ "--color", "-c", 0x0c, cT ( bool ), &flags, "color" },
		{ "--debug", "-d", 0x08, cT ( bool ), &flags, "debug" },
		#endif
		{ "--format", "-f", 0x20, cT ( bool ), &flags, "add data:image/ext;base64 at the begining of file" },
		{ "--inFile", "-i", 512, cT ( ptrStr ), &inFile, "in file name" },
		{ "--outFile", "-o", 1, cT ( ptrStr ), &outFile, "out file name" },
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
		printf ( "Licence GPLv2\n" );
		printf ( "made by ox223252\n" );
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

	for ( int i = 0; i < 512; i++ )
	{
		if ( !inFile[ i ] )
		{
			break;
		}
	}

	if ( !inFile[ 0 ] || 
		!outFile[ 0 ] )
	{
		if ( !inFile[ 0 ] )
		{
			printf ( "set input file name : " );
			scanf ( "%63s", inName );
			inFile[ 0 ] = inName;
			while ( getchar ( ) != '\n' );
		}

		if ( !outFile )
		{
			printf ( "set output file name : " );
			scanf ( "%63s", outName );
			outFile = outName;
			while ( getchar ( ) != '\n' );
		}
	}

	for ( nbElements = 0; nbElements < 512; nbElements++ )
	{
		if ( !inFile[ nbElements ] )
		{
			break;
		}
	}
	nbElements;

	if ( nbElements == 1 )
	{
		// verify if fille already exist
		if ( verifyFileExistAndRemove ( outFile ) )
		{
			logVerbose ( "Encodage abort\n" );
			pause ( );
			return ( 0 );
		}
	}

	// get output format
	for ( int i = strlen ( outFile ) - 1; i >= 0; i-- )
	{
		if ( outFile[ i ] == '.' )
		{
			if ( ( !strcmp ( "htm", &outFile[ i + 1 ] ) ) ||
				( !strcmp ( "html", &outFile[ i + 1 ] ) ) )
			{
				flags.outHtml = 1;
				flags.format = 1;
			}
			break;
		}
	}

	for ( int j = 0; j < nbElements; j++ )
	{
		logVerbose ( "file : %s\n", inFile[ j ] );

		// if output format is HTML
		// if output format is requested

		if ( ( flags.outHtml )
			|| ( flags.format ) )
		{
			// get input format
			for ( int i = strlen ( inFile[ j ] ) - 1; i >= 0; i-- )
			{
				if ( inFile[ j ][ i ] == '.' )
				{
					strcpy ( ext, &inFile[ j ][ i + 1 ] );
					break;
				}
			}

			// if it's an image
			if ( !strcmp ( ext, "bmp" ) ||
				!strcmp ( ext, "png" ) ||
				!strcmp ( ext, "jpg" ) ||
				!strcmp ( ext, "jpeg" ) )
			{
				file = fopen ( outFile, "a+" );
				if ( file > 0 )
				{
					fseek ( file, 0, SEEK_SET );
					if ( flags.outHtml )
					{
						fprintf ( file, "<img src=\"" );
					}
					if ( flags.format )
					{
						fprintf ( file, "data:image/%s;base64,", ext );
					}

					fclose ( file );
					file = NULL;
				}
			}
		}

		// encode file
		if ( result = encodeBase64 ( B64_F2F, inFile[ j ], outFile, NULL ) )
		{
			logVerbose ( "KO\n" );

			logVerbose ( "failure occured\n" );
			logDebug ( "encodage failed line %d\n", result );
			logDebug ( "%s\n", strerror ( errno ) );
			pause ( );
			return ( __LINE__ );
		}

		// if we write an image in a html file
		file = fopen ( outFile, "r+" );
		if ( file > 0 )
		{
			fseek ( file, 0, SEEK_END );
			if ( ( flags.outHtml ) &&
				( !strcmp ( ext, "bmp" ) ||
				!strcmp ( ext, "png" ) ||
				!strcmp ( ext, "jpg" ) ||
				!strcmp ( ext, "jpeg" ) ) )
			{
				fprintf ( file, "\"/>" );
			}
			fprintf( file, "\n" );
			fclose ( file );
			file = NULL;
		}

		logVerbose ( "OK\n" );
	}

	// END_CORE
	pause ( );
	return ( 0 );
}

