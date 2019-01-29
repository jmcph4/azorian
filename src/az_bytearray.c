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

/* Operations */

/**
 * Extracts a closed interval of <code>bytearray</code> into
 * <code>slice</code>.
 *
 * @param bytearray
 *          the bytearray to take a slice from
 * @param start
 *          the index to start slicing at
 * @param end
 *          the index to stop slicing at
 * @param slice
 *          a double-indirection pointer to an <code>az_bytearray_t</code> type
 *          to store the sliced bytes
 * @return an <code>az_status_t</code> type indicating result of operation
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>slice == NULL</code>, <code>start</code> is out of bounds,
 *          <code>end</code> is out of bounds, the size of the interval
 *          (i.e. <code>end - start</code>) is the same size as or bigger than
 *          <code>bytearray</code> itself
 * @throw AZ_ERR_ALLOC_FAILURE
 *          if memory allocation fails
 *
 * */
az_status_t az_bytearray_slice(az_bytearray_t bytearray, uintmax_t start,
        uintmax_t end, az_bytearray_t** slice)
{
    if(slice == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    uintmax_t slice_len = end - start;

    /* bounds check */
    if(start >= end || start >= bytearray.len || end > bytearray.len ||
            slice_len >= bytearray.len)
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    /* allocate space for local buffer */
    uint8_t* slice_bytes = calloc(slice_len, sizeof(uint8_t));

    if(slice_bytes == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    /* copy required bytes into local buffer */
    memcpy(slice_bytes, &bytearray.data[start], slice_len);

    *slice = calloc(1, sizeof(az_bytearray_t));

    if(*slice == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    /* use local buffer to initialise new bytearray type */
    az_status_t res = az_bytearray_init(slice_len, slice_bytes, *slice);

    if(res != AZ_STATUS_OK)
    {
        free(slice_bytes);
        return res;
    }

    free(slice_bytes);

    return AZ_STATUS_OK;
}

/**
 * Appends <code>back</code> onto <code>front</code>.
 *
 * @param back
 *          the bytearray to be added onto the end of <code>front</code>
 * @param front
 *          the bytearray to be appended to
 * @return an <code>az_status_t</code> type indicating success of operation
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>front == NULL</code>
 *
 * */
az_status_t az_bytearray_append(az_bytearray_t back, az_bytearray_t* front)
{
    if(front == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    front->data = realloc(front->data, front->len + back.len);
    memcpy(&front->data[front->len], back.data, back.len);
    front->len += back.len;

    return AZ_STATUS_OK;
}

