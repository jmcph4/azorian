#include <stdlib.h>
#include <stdint.h>

#include "az_status.h"
#include "az_uvarint.h"

uint64_t _u64_log2(uint64_t n)
{
    uint64_t a = 0;
    uint64_t b = 0;

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
 * @param uvarint
 * @return result type indicating success or failure
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if `uvarint == NULL`
 * @throw AZ_ERR_vARINT_TOO_BIG
 *          if the <code>num</code> is too large to fit in
 *          <code>AZ_UVARINT_MAX_LEN</code>
 * @see az_uvarint_decode 
 *
 * */
az_status_t az_uvarint_encode(uint64_t num, az_uvarint_t* uvarint)
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

    uint64_t n = num;

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
 * @param num
 * @return result type indicating success or failure
 * @see az_uvarint_encode
 *
 * */
az_status_t az_uvarint_decode(az_uvarint_t uvarint, uint64_t* num)
{
    if(num == NULL)
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    uint64_t k = 0;
    uint64_t n = 0;

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

