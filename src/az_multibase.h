#ifndef AZ_MULTIBASE_H_
#define MULTIBASE_H_

#include <stdbool.h>

#include "az_status.h"
#include "az_bytearray.h"

/**
 * Represents a multibase type.
 *
 * */
typedef struct
{
    char prefix;        /* base encoding type */
    char* text;         /* string data */
} az_multibase_t;

#define AZ_MULTIBASE_IDENTITY '\0'
#define AZ_MULTIBASE_BASE1 '1'
#define AZ_MULTIBASE_BASE2 '0'
#define AZ_MULTIBASE_BASE8 '7'
#define AZ_MULTIBASE_BASE10 '9'
#define AZ_MULTIBASE_BASE16 'f'
#define AZ_MULTIBASE_BASE16_UPPER 'F'
#define AZ_MULTIBASE_BASE32_HEX 'v'
#define AZ_MULTIBASE_BASE32_HEX_UPPER 'V'
#define AZ_MULTIBASE_BASE32_HEX_PAD 't'
#define AZ_MULTIBASE_BASE32_HEX_PAD_UPPER 'T'
#define AZ_MULTIBASE_BASE32 'b'
#define AZ_MULTIBASE_BASE32_UPPER 'B'
#define AZ_MULTIBASE_BASE32_PAD 'c'
#define AZ_MULTIBASE_BASE32_PAD_UPPER 'C'
#define AZ_MULTIBASE_BASE32_Z 'h'
#define AZ_MULTIBASE_BASE58_FLICKR 'Z'
#define AZ_MULTIBASE_BASE58_BTC 'z'
#define AZ_MULTIBASE_BASE64 'm'
#define AZ_MULTIBASE_BASE64_URL 'M'
#define AZ_MULTIBASE_BASE64_PAD 'u'
#define AZ_MULTIBASE_BASE64_URL_PAD 'U'

/* Initialisation */
az_status_t az_multibase_init_from_string(char base, char* string,
        az_multibase_t* multibase);
az_status_t az_multibase_free(az_multibase_t* multibase);

/* Codec */
az_status_t az_multibase_encode(az_multibase_t multibase,
        az_bytearray_t** bytearray);
az_status_t az_multibase_decode(az_bytearray_t bytearray,
        az_multibase_t** multibase);
az_status_t az_mutlibase_decode_to_string(az_multibase_t multibase, char* base,
        char** string);

/* Equality */
az_status_t az_multibase_equal(az_multibase_t a, az_multibase_t b, bool* equal);

#endif /* AZ_MULTIBASE_H_ */

