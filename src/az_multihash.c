/**
 * @file az_multihash.c
 *
 * Contains implementations of API functions in the form of function
 * definitions.
 *
 * */
#include <stdint.h>
#include <stdlib.h>

#include "az_status.h"
#include "az_uvarint.h"
#include "az_multicodec.h"
#include "az_multihash.h"

/**
 * Initialises and populates a <code>az_multihash_t</code> type from the
 * provided fields.
 *
 * @param hash_type
 *          a <code>a_multicodec_t</code> type representing the type of hash
 *          digest being represented
 * @param digest_size
 *          a native integer type representing the number of bytes of digest
 *          data to be expected
 * @param digest
 *          a pointer to an array of bytes representing the digest data to be
 *          encoded
 * @param multihash
 *          a pointer to a <code>az_multihash_t</code> type to store the
 *          encoded multihash values in
 * @return <code>az_status_t</code> result type indicating success or failure
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>digest == NULL || multihash == NULL</code>
 * @see <code>az_multihash_decode</code>
 *
 * */
az_status_t az_multihash_encode(az_multicodec_t hash_type,
        uintmax_t digest_size, uint8_t* digest, az_multihash_t* multihash)
{
    if(digest == NULL || multihash == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    multihash->hash_type = hash_type;

    /* encode native integer type to unsigned varint */
    az_status_t res = az_uvarint_encode(digest_size, &multihash->digest_size);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    multihash->digest = calloc(digest_size, sizeof(uint8_t));

    if(multihash->digest == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    /* copy digest bytes into multihash structure */
    for(uintmax_t i=0;i<digest_size;i++)
    {
        multihash->digest[i] = digest[i];
    }

    return AZ_STATUS_OK;
}

/**
 * Extracts the fields from a <code>az_multihash_t</code> type.
 *
 * @param multihash
 *          the <code>az_multihash_t</code> type containing the multihash
 * @param hash_type
 *          a pointer to a <code>a_multicodec_t</code> type representing the
 *          type of digest being represented
 * @param digest_size
 *          a pointer to a native integer type representing the number of bytes
 *          of digest data to be expected
 * @param digest
 *          a double-indirection pointer to an array of bytes that will contain
 *          the digest data
 * @return <code>az_status_t</code> result type indicating success or failure
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>digest == NULL || multihash == NULL</code>
 * @throw AZ_ERR_ALLOC_FAILURE
 *          if allocation of target digest buffer fails
 * @see <code>az_multihash_encode</code>
 *
 * */
az_status_t az_multihash_decode(az_multihash_t multihash,
        az_multicodec_t* hash_type, uintmax_t* digest_size, uint8_t** digest)
{
    /* null guard */
    if(hash_type == NULL || digest_size == NULL || digest == NULL)
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    *hash_type = multihash.hash_type;
   
    /* decode digest size from unsigned varint into native integer */ 
    az_status_t res = az_uvarint_decode(multihash.digest_size, digest_size);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    *digest = calloc(*digest_size, sizeof(uint8_t));

    if(*digest == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    /* copy digest bytes back out into caller's buffer */
    for(uintmax_t i=0;i<*digest_size;i++)
    {
        (*digest)[i] = multihash.digest[i];
    }

    return AZ_STATUS_OK;
}

