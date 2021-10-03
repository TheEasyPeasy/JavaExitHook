#pragma once

#include <stdint.h>
#include <stdbool.h>

/* shorthands */

#ifdef _MSC_VER
    #define PS_NOINLINE __declspec( noinline )
#elif __GNUC__
    #define PS_NOINLINE __attribute__( ( noinline ) )
#else
    #error "Unknown compiler."
#endif

/* types */

typedef struct PS_PatternByte
{
    uint8_t m_value;
    bool    m_is_wildcard;
} PS_PatternByte;

typedef struct PS_Pattern
{
    size_t         m_amount;  // amount of bytes in array
    PS_PatternByte **m_bytes; // array of bytes
} PS_Pattern;

typedef struct PS_PatternBatch
{
    PS_Pattern *m_pattern; // input pattern
    uintptr_t  *m_addr;    // output address
} PS_PatternBatch;

typedef struct PS_PatternBatches
{
    size_t          m_amount;     // amount of patterns in array
    PS_PatternBatch **m_patterns; // array of batched patterns
} PS_PatternBatches;

/* funcs */

#ifdef __cplusplus
extern "C"
{
#endif

    /* single pattern */

    // construct "PS_PatternByte", must be freed
    // returns NULL on failure
    PS_NOINLINE PS_PatternByte *ps_make_pattern_byte( uint8_t value, bool is_wildcard );

    // attempt to add a byte to a "PS_Pattern", byte must be created with "ps_make_pattern_byte"
    // returns false on failure
    PS_NOINLINE bool ps_add_pattern_byte( PS_Pattern *pattern, PS_PatternByte *byte );

    // free a "PS_Pattern" with bytes in it
    PS_NOINLINE void ps_free_pattern( PS_Pattern *pattern );

    // convert an IDA-style pattern string to a "PS_Pattern" type
    // returns false on failure
    PS_NOINLINE bool ps_build_idastyle( PS_Pattern *out_pattern, const char *pattern );

    // convert a code-style pattern string to a "PS_Pattern" type
    // returns false on failure
    PS_NOINLINE bool ps_build_codestyle( PS_Pattern *out_pattern, const char *pattern, const char *mask );

    // find pattern by "PS_Pattern"
    // must construct a "PS_Pattern" from "ps_make_pattern" and "ps_add_pattern_byte", free with "ps_free_pattern"
    // returns NULL on failure
    PS_NOINLINE uintptr_t ps_find( PS_Pattern *pattern, uintptr_t start, size_t size );

    // find pattern by IDA-style pattern
    // example: "AA B CC ? DD" (double question marks and single bytes are supported)
    // returns NULL on failure
    PS_NOINLINE uintptr_t ps_find_idastyle( const char *pattern, uintptr_t start, size_t size );

    // find pattern by code-style pattern
    // example: "\xAA\xBB\xCC\x00\xDD", "xxx?x"
    // returns NULL on failure
    PS_NOINLINE uintptr_t ps_find_codestyle( const char *pattern, const char *mask, uintptr_t start, size_t size );

    /* multiple patterns */

    // free a "PS_PatternBatches" with patterns in it
    PS_NOINLINE void ps_free_pattern_batch( PS_PatternBatches *batch );

    // adds an IDA-style pattern to a "PS_PatternBatch"
    PS_NOINLINE void ps_add_codestyle_batch( PS_PatternBatches *batch, uintptr_t *found, const char *pattern, const char *mask );

    // adds a code-style pattern to a "PS_PatternBatch"
    PS_NOINLINE void ps_add_idastyle_batch( PS_PatternBatches *batch, uintptr_t *found, const char *pattern );

    // find all patterns in a batch
    PS_NOINLINE void ps_find_batch( PS_PatternBatches *batch, uintptr_t start, size_t size );

#ifdef __cplusplus
}
#endif