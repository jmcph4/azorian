/**
 * @file az_bytearray.c
 *
 * Contains implementation of the bytearray API via function definitions.
 *
 * */
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
 * @return <code>az_status_t</code> type indicating result of operation
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>data == NULL || bytearray == NULL</code>
 * @throw AZ_ERR_ALLOC_FAILURE
 *          if memory allocation fails
 * @see <code>az_bytearray_free</code>
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
 * @return <code>az_status_t</code> type indicating result of operation
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>bytearray == NULL</code>
 * @see <code>az_bytearray_init</code> 
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

/* Equality */

/**
 * Determines whether two bytearrays, <code>a</code> and <code>b</code>, are
 * equal.
 *
 * @param a
 *          the first bytearray to compare
 * @param b
 *          the second bytearray to compare
 * @param equal
 *          pointer to a <code>bool</code>, indicating equality
 * @return <code>az_status_t</code> indicating success of operation
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>equal == NULL</code>
 *
 * */
az_status_t az_bytearray_equal(az_bytearray_t a, az_bytearray_t b, bool* equal)
{
    if(equal == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    *equal = true;

    /* compare lengths */
    if(a.len != b.len)
    {
        *equal = false;
    }

    /* compare bytes */
    for(size_t i=0;i<a.len;i++)
    {
        if(a.data[i] != b.data[i])
        {
            *equal = false;
            break;
        }
    }

    return AZ_STATUS_OK;
}

