/**
 * @file Contains definitions for the multihash type.
 *
 * */
#include <stdint.h>

#include "az_status.h"
#include "az_uvarint.h"
#include "az_multicodec.h"

/**
 * Represents a multihash
 *
 * */
typedef struct
{
    az_multicodec_t hash_type;          /* type of hash */
    az_uvarint_t digest_size;           /* length of digest, in bytes */
    uint8_t* digest;                    /* digest bytes */
} az_multihash_t;

az_status_t az_multihash_encode(az_multicodec_t hash_type,
        uintmax_t digest_size, uint8_t* digest, az_multihash_t* multihash);
az_status_t az_multihash_decode(az_multihash_t multihash,
        az_multicodec_t* hash_type, uintmax_t* digest_size, uint8_t** digest);

