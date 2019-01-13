#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "az_status.h"
#include "az_bytearray.h"

/**
 * Initialises a <code>az_bytearray_t</code> type of size <code>len</code> and
 * containing <code>data</code>.
 *
 * @param len
 *          the number of bytes in <code>data</code>
 * @param data
 *          the data to be stored in the bytearray
 * @param bytearray
 *          pointer to a <code>az_bytearray_t</code> type to be initialised
 *
 *
 * */
az_status_t az_bytearray_init(size_t len, uint8_t* data,
        az_bytearray_t* bytearray)
{
    if(data == NULL || bytearray == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    bytearray->len = len;
    bytearray->data = calloc(len, sizeof(uint8_t));

    if(bytearray->data == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    memcpy(bytearray->data, data, len);

    return AZ_STATUS_OK;
}

/**
 * Frees all resources consumed by <code>bytearray</code> and invalidates all
 * references to it.
 *
 * @param bytearray
 *          the <code>az_bytearray_t</code> type to be deallocated
 * 
 * 
 * */
az_status_t az_bytearray_free(az_bytearray_t* bytearray)
{
    if(bytearray == NULL)
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    free(bytearray->data);
    bytearray->len = 0;
    bytearray->data = NULL;

    return AZ_STATUS_OK;
}

