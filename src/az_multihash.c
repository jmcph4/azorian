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
 *
 *
 * */
az_status_t az_multihash_encode(az_multihash_t multihash,
        az_bytearray_t** bytearray)
{
    if(bytearray == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    az_bytearray_t* type_bytes = NULL;
    az_status_t res = az_uvarint_encode(multihash.type, &type_bytes);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    /* encode digest length as a uvarint type */
    az_uvarint_t size_uvarint;
    res = az_uvarint_init_from_int(multihash.digest.len, &size_uvarint);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    /* encode uvarint */
    az_bytearray_t* size_bytes = NULL;
    res = az_uvarint_encode(size_uvarint, &size_bytes);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    az_bytearray_t* digest_bytes = &multihash.digest;

    /* allocate space in caller's memory for bytearray */
    *bytearray = calloc(1, sizeof(az_bytearray_t));

    if(*bytearray == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    /* concatenate all three bytearrays */
    res = az_bytearray_append(*type_bytes, *bytearray);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    res = az_bytearray_append(*size_bytes, *bytearray);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    res = az_bytearray_append(*digest_bytes, *bytearray);

    if(res != AZ_STATUS_OK)
    {
        return res;
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
az_status_t az_multihash_decode(az_bytearray_t bytearray,
        az_multihash_t** multihash)
{
    if(multihash == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    if(bytearray.len < 3) /* bounds check */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    size_t type_end = 0;

    /* determine where first uvarint ends */
    for(size_t i=0;i<bytearray.len;i++)
    {
        if(i > AZ_UVARINT_MAX_LEN && bytearray.data[i] >= 255)
        {
            return AZ_ERR_ILLEGAL_PARAM;
        }

        /* we've reached the end of our first uvarint */
        if(bytearray.data[i] < 255)
        {
            type_end = i;
            break;
        }
    }

    type_end++;

    /* take slice of main bytearray to represent uvarint */
    az_bytearray_t* type_slice = NULL;
    az_status_t res = az_bytearray_slice(bytearray, 0, type_end, &type_slice);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    /* interpret the type bytes as a multicodec */
    az_multicodec_t* hash_type = NULL;
    res = az_uvarint_decode(*type_slice, &hash_type);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    size_t size_end = 0;

    /* find where second uvarint (digest size) ends */
    for(size_t i=type_end;i<bytearray.len;i++)
    {
        if(i > AZ_UVARINT_MAX_LEN && bytearray.data[i] >= 255)
        {
            return AZ_ERR_ILLEGAL_PARAM;
        }

        if(bytearray.data[i] < 255)
        {
            size_end = i;
            break;
        }
    }

    size_end++;

    /* extract bytes for the hash size */
    az_bytearray_t* size_slice = NULL;
    res = az_bytearray_slice(bytearray, type_end, size_end, &size_slice);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    /* decode size slice as a uvarint */
    az_uvarint_t* hash_size = NULL;
    res = az_uvarint_decode(*size_slice, &hash_size);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    /* get number of bytes in digest as native integer type */
    uintmax_t digest_size = 0;
    res = az_uvarint_decode_to_int(*hash_size, &digest_size);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    /* extract digest bytes */
    az_bytearray_t* digest_slice = NULL;
    res = az_bytearray_slice(bytearray, size_end, bytearray.len,
            &digest_slice);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    /* allocate space in caller's memory for multihash type */
    *multihash = calloc(1, sizeof(az_multihash_t));

    if(*multihash == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    (*multihash)->type = *hash_type;
    (*multihash)->digest = *digest_slice;

    return AZ_STATUS_OK;
}

/* Equality */

/***/
az_status_t az_multihash_equal(az_multihash_t a, az_multihash_t b, bool* equal)
{
    if(equal == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    bool types_equal = false;
    az_status_t res = az_uvarint_equal(a.type, b.type, &types_equal);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    bool digests_equal = false;
    res = az_bytearray_equal(a.digest, b.digest, &digests_equal);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    *equal = types_equal && digests_equal;

    return AZ_STATUS_OK;
}

