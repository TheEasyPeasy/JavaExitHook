#include "utils.h"

PS_NOINLINE char *util_trim_pattern_str( const char *str )
{
    if( str )
    {
        size_t len = strlen( str );
        if( len )
        {
            char *start = (char *)str;
            char *end   = ( start + len ) - 1;

            // move start ptr up
            for( size_t i = 0; i < len; ++i )
            {
                if( isspace( *start ) || *start == '?' )
                    ++start;
            }

            // move end ptr down
            for( size_t i = len; len--; )
            {
                if( isspace( *end ) || *end == '?' )
                    --end;
            }

            // add null terminator
            *( end + 1 ) = '\0';

            // shift string bytes, this must be done in case the string is dynamically allocated and the original ptr isn't changed
            size_t new_len = strlen( start );
            if( new_len )
            {
                return memmove( (char *)str, start, ( new_len * sizeof( char ) ) + 1 );
            }
        }
    }

    return 0;
}