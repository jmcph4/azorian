/**
 * @file Contains definitions for the multihash type.
 *
 * */
#include <stdint.h>

#include "az_status.h"
#include "az_bytearray.h"
#include "az_multicodec.h"

/**
 * Represents a multihash
 *
 * */
typedef struct
{
    az_multicodec_t type;               /* type of hash */
    az_bytearray_t digest;              /* digest bytes */
} az_multihash_t;

/* Initialisation */
az_status_t az_multihash_free(az_multihash_t* multihash);

/* Codec */
az_status_t az_multihash_encode(az_multihash_t multihash,
        az_bytearray_t** bytearray);
az_status_t az_multihash_decode(az_bytearray_t bytearray,
        az_multihash_t** multihash);

/* Equality */
az_status_t az_multihash_equal(az_multihash_t a, az_multihash_t b, bool* equal);

