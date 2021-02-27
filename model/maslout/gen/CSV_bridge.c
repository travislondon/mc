/*----------------------------------------------------------------------------
 * File:  CSV_bridge.c
 *
 * Description:
 * Methods for bridging to an external entity.
 *
 * External Entity:  Comma Separated Values (CSV)
 * 
 * your copyright statement can go here (from te_copyright.body)
 *--------------------------------------------------------------------------*/

#include "maslout_sys_types.h"
#include "CSV_bridge.h"
#include "LOG_bridge.h"
#include "STRING_bridge.h"
#include "T_bridge.h"
#include "TRACE_bridge.h"
#include "V_bridge.h"

/*
 * Bridge:  readline
 */
i_t
CSV_readline( c_t * p_filename, c_t * p_values[8] )
{
  static FILE * f;
  static c_t filename[ ESCHER_SYS_MAX_STRING_LEN ] = {0};
  c_t line[ ESCHER_SYS_MAX_STRING_LEN ] = {0};
  i_t valuecount = 0;

  if ( 0 != Escher_strcmp( p_filename, filename ) ) {
    strcpy( filename, p_filename );
    if ( 0 == ( f = fopen( p_filename, "r" ) ) ) {
      return valuecount; /* No marking file.  This is O.K.  */
    }
  }
  /* read a line */
  while ( 0 != fgets( line, ESCHER_SYS_MAX_STRING_LEN, f ) ) {
    /* Skip comment lines.  */
    if ( ( 0 == strchr( line, '#' ) ) && ( 0 != strchr( line, ',' ) ) ) {
      c_t * token = strtok( line, ",\n" );
      while ( NULL != token ) {
        if ( 2000 < Escher_strlen( token ) ) {
          TRACE_log( "warning", 190, "detected marking value of more than 2000 bytes" );
        }
        strncpy( p_values[ valuecount++ ], token, 2000 );
        token = strtok( NULL, ",\n" );
      }
      break;
    }
  }
  return valuecount;
}


/*
 * Bridge:  writeline
 */
i_t
CSV_writeline( c_t * p_filename, c_t * p_values[8] )
{
  static FILE * f;
  static c_t filename[ ESCHER_SYS_MAX_STRING_LEN ] = {0};
  c_t line[ ESCHER_SYS_MAX_STRING_LEN ] = {0};
  i_t valuecount = 0;

  if ( 0 != Escher_strcmp( p_filename, filename ) ) {
    strcpy( filename, p_filename );
    if ( 0 == ( f = fopen( p_filename, "w" ) ) ) {
      TRACE_log( "error", 191, "could not open marking file" );
      return valuecount;
    }
  }
  /* write a line */
  while ( 0 < Escher_strlen( p_values[ valuecount ] ) ) {
    if ( valuecount > 0 ) fputs( ",", f );
    fputs( p_values[ valuecount ], f );
    valuecount++;
  }
  /* Write the file.  */
  fputs( line, f );
  fputs( "\n", f );
  return valuecount;
}

