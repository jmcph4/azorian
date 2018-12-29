/**
 * @file az_uvarint.c
 *
 * Contains implementations of API functions in the form of function
 * definitions.
 *
 * */
#include <stdlib.h>
#include <stdint.h>

#include "az_status.h"
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
 * Converts <code>num</code> from a native unsigned 64-bit integer into an
 * unsigned multiformat variable integer.
 *
 * @param num
 *          the native unsigned 64-bit integer to be encoded
 * @param uvarint
 *          reference to the <code>az_uvarint_t</code> type to store the
 *          encoded representation
 * @return <code>az_status_t</code> result type indicating success or failure
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>uvarint == NULL</code>
 * @throw AZ_ERR_VARINT_TOO_BIG
 *          if <code>num</code> is too large to fit in
 *          <code>AZ_UVARINT_MAX_LEN</code>
 * @see <code>az_status_t</code>
 * @see <code>az_uvarint_decode</code>
 *
 * */
az_status_t az_uvarint_encode(uintmax_t num, az_uvarint_t* uvarint)
{
    if(uvarint == NULL)
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    size_t num_bytes = (_u64_log2(num) / (BITS_PER_BYTE - 1)) + 1;

    if(num_bytes > AZ_UVARINT_MAX_LEN) /* bounds check */
    {
        return AZ_ERR_VARINT_TOO_BIG;
    }

    /* set up our az_uvarint_t type */
    uvarint->len = num_bytes;
    uvarint->bytes = calloc(num_bytes, sizeof(uint8_t));

    if(uvarint->bytes == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    } 

    if(num <= 127) /* base case */
    {
        uvarint->bytes[0] = num;
        return AZ_STATUS_OK;
    }

    uintmax_t n = num;

    for(unsigned int i=0;i<num_bytes;i++)
    {
        uvarint->bytes[i] = n | 0x80;        
        n >>= 7;

        if(i + 1 == num_bytes)
        {
            uvarint->bytes[i] &= 0x7f;
            break;
        }
    }

    return AZ_STATUS_OK;
}

/**
 * Converts <code>uvarint</code> from an unsigned multiformat variable integer
 * into a native unsigned 64-bit integer.
 *
 * @param uvarint
 *          the <code>az_uvarint_t</code> type to be decoded
 * @param num
 *          reference to a native unsigned 64-bit integer to store the decoded
 *          contents
 * @return <code>az_status_t</code> result type indicating success or failure
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>num == NULL</code>
 * @see <code>az_status_t</code>
 * @see <code>az_uvarint_encode</code>
 *
 * */
az_status_t az_uvarint_decode(az_uvarint_t uvarint, uintmax_t* num)
{
    if(num == NULL)
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    uintmax_t k = 0;
    uintmax_t n = 0;

    for(unsigned int i=0;i<uvarint.len;i++)
    {
        k = uvarint.bytes[i] & 0x7f;
        n |= k << (i * 7);

        if((uvarint.bytes[i] & 0x80) == 0)
        {
            *num = n;
            break;
        }
    }

    return AZ_STATUS_OK;
}

