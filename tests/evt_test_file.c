/*
 * Library file type testing program
 *
 * Copyright (C) 2011-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "evt_test_libcerror.h"
#include "evt_test_libclocale.h"
#include "evt_test_libcsystem.h"
#include "evt_test_libevt.h"
#include "evt_test_libuna.h"
#include "evt_test_macros.h"
#include "evt_test_memory.h"

#if SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make evt_test_file generate verbose output
#define EVT_TEST_FILE_VERBOSE
 */

/* Retrieves source as a narrow string
 * Returns 1 if successful or -1 on error
 */
int evt_test_file_get_narrow_source(
     const system_character_t *source,
     char *narrow_string,
     size_t narrow_string_size,
     libcerror_error_t **error )
{
	static char *function     = "evt_test_file_get_narrow_source";
	size_t narrow_source_size = 0;
	size_t source_length      = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result                = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( narrow_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid narrow string.",
		 function );

		return( -1 );
	}
	if( narrow_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid narrow string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow string size.",
		 function );

		return( -1 );
	}
#else
	narrow_source_size = source_length + 1;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( narrow_string_size < narrow_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: narrow string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
#else
	if( system_string_copy(
	     narrow_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
	narrow_string[ source_length ] = 0;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves source as a wide string
 * Returns 1 if successful or -1 on error
 */
int evt_test_file_get_wide_source(
     const system_character_t *source,
     wchar_t *wide_string,
     size_t wide_string_size,
     libcerror_error_t **error )
{
	static char *function   = "evt_test_file_get_wide_source";
	size_t wide_source_size = 0;
	size_t source_length    = 0;

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result              = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( wide_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid wide string.",
		 function );

		return( -1 );
	}
	if( wide_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid wide string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	wide_source_size = source_length + 1;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine wide string size.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( wide_string_size < wide_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: wide string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     wide_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}
	wide_string[ source_length ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int evt_test_file_open_source(
     libevt_file_t **file,
     const system_character_t *source,
     libcerror_error_t **error )
{
	static char *function = "evt_test_file_open_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( libevt_file_initialize(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libevt_file_open_wide(
	          *file,
	          source,
	          LIBEVT_OPEN_READ,
	          error );
#else
	result = libevt_file_open(
	          *file,
	          source,
	          LIBEVT_OPEN_READ,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file != NULL )
	{
		libevt_file_close(
		 *file,
		 NULL );
		libevt_file_free(
		 file,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source file
 * Returns 1 if successful or -1 on error
 */
int evt_test_file_close_source(
     libevt_file_t **file,
     libcerror_error_t **error )
{
	static char *function = "evt_test_file_close_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( libevt_file_close(
	     *file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file.",
		 function );

		result = -1;
	}
	if( libevt_file_free(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libevt_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int evt_test_file_initialize(
     void )
{
	libcerror_error_t *error = NULL;
	libevt_file_t *file      = NULL;
	int result               = 0;

	/* Test libevt_file_initialize
	 */
	result = libevt_file_initialize(
	          &file,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "file",
         file );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libevt_file_free(
	          &file,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NULL(
         "file",
         file );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libevt_file_initialize(
	          NULL,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	file = (libevt_file_t *) 0x12345678UL;

	result = libevt_file_initialize(
	          &file,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	file = NULL;

#if defined( HAVE_EVT_TEST_MEMORY )

	/* Test libevt_file_initialize with malloc failing
	 */
	evt_test_malloc_attempts_before_fail = 0;

	result = libevt_file_initialize(
	          &file,
	          &error );

	if( evt_test_malloc_attempts_before_fail != -1 )
	{
		evt_test_malloc_attempts_before_fail = -1;
	}
	else
	{
		EVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		EVT_TEST_ASSERT_IS_NULL(
		 "file",
		 file );

		EVT_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libevt_file_initialize with memset failing
	 */
	evt_test_memset_attempts_before_fail = 0;

	result = libevt_file_initialize(
	          &file,
	          &error );

	if( evt_test_memset_attempts_before_fail != -1 )
	{
		evt_test_memset_attempts_before_fail = -1;
	}
	else
	{
		EVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		EVT_TEST_ASSERT_IS_NULL(
		 "file",
		 file );

		EVT_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_EVT_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libevt_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libevt_file_free function
 * Returns 1 if successful or 0 if not
 */
int evt_test_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libevt_file_free(
	          NULL,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libevt_file_open functions
 * Returns 1 if successful or 0 if not
 */
int evt_test_file_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libevt_file_t *file      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = evt_test_file_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libevt_file_initialize(
	          &file,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "file",
         file );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test open
	 */
	result = libevt_file_open(
	          file,
	          narrow_source,
	          LIBEVT_OPEN_READ,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Clean up
	 */
	result = libevt_file_close(
	          file,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libevt_file_free(
	          &file,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NULL(
         "file",
         file );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libevt_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libevt_file_open_wide functions
 * Returns 1 if successful or 0 if not
 */
int evt_test_file_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libevt_file_t *file      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = evt_test_file_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libevt_file_initialize(
	          &file,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "file",
         file );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test open
	 */
	result = libevt_file_open_wide(
	          file,
	          wide_source,
	          LIBEVT_OPEN_READ,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Clean up
	 */
	result = libevt_file_close(
	          file,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libevt_file_free(
	          &file,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NULL(
         "file",
         file );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libevt_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libevt_file_get_ascii_codepage functions
 * Returns 1 if successful or 0 if not
 */
int evt_test_file_get_ascii_codepage(
     libevt_file_t *file )
{
	libcerror_error_t *error = NULL;
	int codepage             = 0;
	int result               = 0;

	result = libevt_file_get_ascii_codepage(
	          file,
	          &codepage,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libevt_file_get_ascii_codepage(
	          NULL,
	          &codepage,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libevt_file_get_ascii_codepage(
	          file,
	          NULL,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libevt_file_set_ascii_codepage functions
 * Returns 1 if successful or 0 if not
 */
int evt_test_file_set_ascii_codepage(
     void )
{
	int supported_codepages[ 15 ] = {
		LIBEVT_CODEPAGE_ASCII,
		LIBEVT_CODEPAGE_WINDOWS_874,
		LIBEVT_CODEPAGE_WINDOWS_932,
		LIBEVT_CODEPAGE_WINDOWS_936,
		LIBEVT_CODEPAGE_WINDOWS_949,
		LIBEVT_CODEPAGE_WINDOWS_950,
		LIBEVT_CODEPAGE_WINDOWS_1250,
		LIBEVT_CODEPAGE_WINDOWS_1251,
		LIBEVT_CODEPAGE_WINDOWS_1252,
		LIBEVT_CODEPAGE_WINDOWS_1253,
		LIBEVT_CODEPAGE_WINDOWS_1254,
		LIBEVT_CODEPAGE_WINDOWS_1255,
		LIBEVT_CODEPAGE_WINDOWS_1256,
		LIBEVT_CODEPAGE_WINDOWS_1257,
		LIBEVT_CODEPAGE_WINDOWS_1258 };

	int unsupported_codepages[ 17 ] = {
		LIBEVT_CODEPAGE_ISO_8859_1,
		LIBEVT_CODEPAGE_ISO_8859_2,
		LIBEVT_CODEPAGE_ISO_8859_3,
		LIBEVT_CODEPAGE_ISO_8859_4,
		LIBEVT_CODEPAGE_ISO_8859_5,
		LIBEVT_CODEPAGE_ISO_8859_6,
		LIBEVT_CODEPAGE_ISO_8859_7,
		LIBEVT_CODEPAGE_ISO_8859_8,
		LIBEVT_CODEPAGE_ISO_8859_9,
		LIBEVT_CODEPAGE_ISO_8859_10,
		LIBEVT_CODEPAGE_ISO_8859_11,
		LIBEVT_CODEPAGE_ISO_8859_13,
		LIBEVT_CODEPAGE_ISO_8859_14,
		LIBEVT_CODEPAGE_ISO_8859_15,
		LIBEVT_CODEPAGE_ISO_8859_16,
		LIBEVT_CODEPAGE_KOI8_R,
		LIBEVT_CODEPAGE_KOI8_U };

	libcerror_error_t *error = NULL;
	libevt_file_t *file      = NULL;
	int codepage             = 0;
	int index                = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libevt_file_initialize(
	          &file,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "file",
         file );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test set ASCII codepage
	 */
	for( index = 0;
	     index < 15;
	     index++ )
	{
		codepage = supported_codepages[ index ];

		result = libevt_file_set_ascii_codepage(
		          file,
		          codepage,
		          &error );

		EVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        EVT_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
	/* Test error cases
	 */
	result = libevt_file_set_ascii_codepage(
	          NULL,
	          LIBEVT_CODEPAGE_ASCII,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	for( index = 0;
	     index < 17;
	     index++ )
	{
		codepage = unsupported_codepages[ index ];

		result = libevt_file_set_ascii_codepage(
		          file,
		          codepage,
		          &error );

		EVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

	        EVT_TEST_ASSERT_IS_NOT_NULL(
	         "error",
	         error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libevt_file_free(
	          &file,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NULL(
         "file",
         file );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libevt_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libevt_file_get_version functions
 * Returns 1 if successful or 0 if not
 */
int evt_test_file_get_version(
     libevt_file_t *file )
{
	libcerror_error_t *error = NULL;
	uint32_t major_version   = 0;
	uint32_t minor_version   = 0;
	int result               = 0;

	result = libevt_file_get_version(
	          file,
	          &major_version,
	          &minor_version,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libevt_file_get_version(
	          NULL,
	          &major_version,
	          &minor_version,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libevt_file_get_version(
	          file,
	          NULL,
	          &minor_version,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libevt_file_get_version(
	          file,
	          &major_version,
	          NULL,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libevt_file_get_number_of_records functions
 * Returns 1 if successful or 0 if not
 */
int evt_test_file_get_number_of_records(
     libevt_file_t *file )
{
	libcerror_error_t *error = NULL;
	int number_of_records    = 0;
	int result               = 0;

	result = libevt_file_get_number_of_records(
	          file,
	          &number_of_records,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libevt_file_get_number_of_records(
	          NULL,
	          &number_of_records,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libevt_file_get_number_of_records(
	          file,
	          NULL,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libevt_file_get_number_of_recovered_records functions
 * Returns 1 if successful or 0 if not
 */
int evt_test_file_get_number_of_recovered_records(
     libevt_file_t *file )
{
	libcerror_error_t *error = NULL;
	int number_of_records    = 0;
	int result               = 0;

	result = libevt_file_get_number_of_recovered_records(
	          file,
	          &number_of_records,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libevt_file_get_number_of_recovered_records(
	          NULL,
	          &number_of_records,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libevt_file_get_number_of_recovered_records(
	          file,
	          NULL,
	          &error );

	EVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EVT_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libcerror_error_t *error   = NULL;
	system_character_t *source = NULL;
	libevt_file_t *file        = NULL;
	system_integer_t option    = 0;
	int result                 = 0;

	while( ( option = libcsystem_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( EVT_TEST_FILE_VERBOSE )
	libevt_notify_set_verbose(
	 1 );
	libevt_notify_set_stream(
	 stderr,
	 NULL );
#endif

	EVT_TEST_RUN(
	 "libevt_file_initialize",
	 evt_test_file_initialize );

	EVT_TEST_RUN(
	 "libevt_file_free",
	 evt_test_file_free );

	/* TODO add test for libevt_file_signal_abort */

	EVT_TEST_RUN(
	 "libevt_file_set_ascii_codepage",
	 evt_test_file_set_ascii_codepage );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		EVT_TEST_RUN_WITH_ARGS(
		 "libevt_file_open",
		 evt_test_file_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		EVT_TEST_RUN_WITH_ARGS(
		 "libevt_file_open_wide",
		 evt_test_file_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBEVT_HAVE_BFIO )

		/* TODO add test for libevt_file_open_file_io_handle */

#endif /* defined( LIBEVT_HAVE_BFIO ) */

		/* TODO add test for libevt_file_close */

		/* Initialize test
		 */
		result = evt_test_file_open_source(
		          &file,
		          source,
		          &error );

		EVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        EVT_TEST_ASSERT_IS_NOT_NULL(
	         "file",
	         file );

	        EVT_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		/* TODO add test for libevt_file_is_corrupted */

		EVT_TEST_RUN_WITH_ARGS(
		 "libevt_file_get_ascii_codepage",
		 evt_test_file_get_ascii_codepage,
		 file );

		EVT_TEST_RUN_WITH_ARGS(
		 "libevt_file_get_version",
		 evt_test_file_get_version,
		 file );

		/* TODO add test for libevt_file_get_flags */

		EVT_TEST_RUN_WITH_ARGS(
		 "libevt_file_get_number_of_records",
		 evt_test_file_get_number_of_records,
		 file );

		/* TODO add test for libevt_file_get_record */

		EVT_TEST_RUN_WITH_ARGS(
		 "libevt_file_get_number_of_recovered_records",
		 evt_test_file_get_number_of_recovered_records,
		 file );

		/* TODO add test for libevt_file_get_recovered_record */

		/* Clean up
		 */
		result = evt_test_file_close_source(
		          &file,
		          &error );

		EVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		EVT_TEST_ASSERT_IS_NULL(
	         "file",
	         file );

	        EVT_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		evt_test_file_close_source(
		 &file,
		 NULL );
	}
	return( EXIT_FAILURE );
}

