/**
 * @file az_uvarint.c
 *
 * Contains implementations of API functions in the form of function
 * definitions.
 *
 * */
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "az_status.h"
#include "az_bytearray.h"
#include "az_uvarint.h"

/* private helper function to compute floor(log2(n)) */
uintmax_t _u64_log2(uintmax_t n)
{
    uintmax_t a = 0;
    uintmax_t b = 0;

    b = (n > 0xffff) << 4;
	n >>= b;
    a = (n > 0xff) << 3;
    n >>= a, b |= a;
    a = (n > 0xf) << 2;
    n >>= a, b |= a;
    a = (n > 0x3) << 1;
    n >>= a, b |= a;

    return b | (n >> 1);
}

/**
 * Initialises <code>uvarint</code> from native integer <code>num</code>.
 *
 * @param num
 *          native integer to use for initialisation
 * @param uvarint
 *          a pointer to a <code>az_uvarint_t</code> type to be initialised
 * @return a <code>az_status_t</code> type indicating result of operation
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>uvarint == NULL</code>
 * @throw AZ_ERR_VARINT_TOO_BIG
 *          if the number of bytes required to represent <code>num</code> as an
 *          unsigned variable integer exceeds <code>AZ_UVARINT_MAX_LEN</code>
 * @throw AZ_ERR_ALLOC_FAILURE
 *          if memory allocation fails
 * @see <code>az_uvarint_init_free</code>
 *
 * */
az_status_t az_uvarint_init_from_int(uintmax_t num, az_uvarint_t* uvarint)
{
    if(uvarint == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    size_t num_bytes = (_u64_log2(num) / (BITS_PER_BYTE - 1)) + 1;

    if(num_bytes > AZ_UVARINT_MAX_LEN) /* bounds check */
    {
        return AZ_ERR_VARINT_TOO_BIG;
    }

    /* setup uvarint type */
    uvarint->bytes = calloc(1, sizeof(az_bytearray_t));

    if(uvarint->bytes == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    } 

    uint8_t* data = calloc(num_bytes, sizeof(uint8_t));
   
    if(data == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    if(num <= 127) /* base case */
    {
        data[0] = num;
    }
    else
    {
        uintmax_t n = num;

        for(unsigned int i=0;i<num_bytes;i++)
        {
            data[i] = n | 0x80;        
            n >>= 7;

            if(i + 1 == num_bytes)
            {
                data[i] &= 0x7f;
                break;
            }
        }
    }

    /* initialise underlying bytearray type */
    az_status_t res = az_bytearray_init(num_bytes, data, uvarint->bytes);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }
    
    free(data);

    uvarint->num = num;
    
    return AZ_STATUS_OK;
}


az_status_t az_uvarint_free(az_uvarint_t uvarint)
{
    az_status_t res = AZ_STATUS_OK;

    if(uvarint.bytes == NULL)
    {
        res = az_bytearray_free(uvarint.bytes);

        if(res != AZ_STATUS_OK)
        {
            return res;
        }
    }

    uvarint.num = 0;
    uvarint.bytes = NULL;

    return AZ_STATUS_OK;
}

az_status_t az_uvarint_encode(az_uvarint_t uvarint, az_bytearray_t** bytearray)
{
    if(bytearray == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    /* allocate memory for caller's copy of bytes */
    *bytearray = calloc(1, sizeof(az_bytearray_t));

    if(*bytearray == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    az_status_t res = az_bytearray_init(uvarint.bytes->len, uvarint.bytes->data,
            *bytearray);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    return AZ_STATUS_OK;
}

/**
 * Converts arbitrary binary data (<code>bytearray</code>) to an unsigned
 * variasble integer (<code>uvarint</code>).
 *
 * @param bytearray
 *          a <code>az_bytearray_t/code> type containing the binary data
 * @param uvarint
 *          a pointer to a <code>az_uvarint_t</code> to be initiated
 * @return a <code>az_status_t</code> type indicating result of operation
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>uvarint == NULL</code>
 * @throw AZ_ERR_ALLOC_FAILURE
 *          if memory allocation fails
 * @see <code>az_uvarint_encode</code>
 * @see <code>az_uvarint_from_int</code>
 *
 * */
az_status_t az_uvarint_decode(az_bytearray_t bytearray, az_uvarint_t** uvarint)
{
    if(uvarint == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    *uvarint = calloc(1, sizeof(az_uvarint_t));

    if(*uvarint == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    (*uvarint)->bytes = calloc(1, sizeof(az_bytearray_t));

    if((*uvarint)->bytes == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    az_status_t res = az_bytearray_init(bytearray.len, bytearray.data,
            (*uvarint)->bytes);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    uint8_t* data = bytearray.data; /* alias for readability */

    uintmax_t k = 0;
    uintmax_t n = 0;

    for(unsigned int i=0;i<bytearray.len;i++)
    {
        k = data[i] & 0x7f;
        n |= k << (i * 7);

        if((data[i] & 0x80) == 0)
        {
            (*uvarint)->num = n;
            break;
        }
    }

    return AZ_STATUS_OK;
}

az_status_t az_uvarint_decode_to_int(az_uvarint_t uvarint, uintmax_t* num)
{
    if(num == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    *num = uvarint.num;

    return AZ_STATUS_OK;
}

/**
 * Determines whether two unsigned variable integers, <code>a</code> and
 * <code>b</code>, are equal.
 *
 * Note that, due to the mathematical properties of equality, the ordering of
 * <code>a</code> and <code>b</code> is unimportant (i.e. commutativity).
 *
 * @param a
 *          first unsigned variable integer to be checked
 * @param b
 *          second unsigned variable integer to be checked
 * @param equal
 *          reference to a <code>bool</code> type, containing the result of the
 *          equality test
 * @return <code>az_status_t</code> result type indicating success or failure
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>equal == NULL</code>
 *
 * */
az_status_t az_uvarint_equal(az_uvarint_t a, az_uvarint_t b, bool* equal)
{
    if(equal == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    if(a.num != b.num)
    {
        *equal = false;
        return AZ_STATUS_OK;
    }

    az_status_t res = az_bytearray_equal(*a.bytes, *b.bytes, equal);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    return AZ_STATUS_OK;
}

