/**
 * @file az_multibase.c
 *
 * Contains implementation of the multibase API in the form of function
 * definitions.
 *
 * */
#include <stdlib.h>
#include <string.h>

#include "az_status.h"
#include "az_bytearray.h"
#include "az_multibase.h"

/* Initialisation */

/**
 * Initialises <code>multibase</code> from a prefix character
 * (<code>base</code>) and a null-terminated string (<code>string</code>).
 *
 * @param base
 *          the base character of the multibase string
 * @param string
 *          the null-terminated string to be used for initialisation
 * @param multibase
 *          pointer to a <code>az_multibase_t</code> type to store the multibase
 *          data
 * @return a <code>az_status_t</code> type indicating result of operation
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>string == NULL</code> or <code>multibase == NULL</code> or
 *          if the string is of zero length
 * @throw AZ_ERR_ALLOC_FAILURE
 *          if memory allocation fails
 * @see <code>az_multibase_free</code>
 *
 * */
az_status_t az_multibase_init_from_string(char base, char* string,
        az_multibase_t* multibase)
{
    if(string == NULL || multibase == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    if(strlen(string) == 0) /* bounds check */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }
   
    multibase->prefix = base;
    multibase->text = calloc(strlen(string) + 1, sizeof(char));

    if(multibase->text == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    strncpy(multibase->text, string, strlen(string));

    return AZ_STATUS_OK;
}

/**
 * Frees all resources consumed by <code>multibase</code>.
 *
 * @param multibase
 *          a pointer to a <code>az_multibase_t</code> representing the
 *          multibase object
 * @return a <code>az_status_t</code> type indicating result of operation
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>multibase == NULL</code>
 * @see <code>az_multibase_init_from_string</code>
 *
 * */
az_status_t az_multibase_free(az_multibase_t* multibase)
{
    if(multibase == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    multibase->prefix = '\0';
    free(multibase->text);
    multibase->text = NULL;

    return AZ_STATUS_OK;
}

/* Codec */

/**
 * Converts a <code>az_multibase_t</code> type into an
 * <code>az_bytearray_t</code> type.
 *
 * Upon successful completion of this operation, <code>bytearray</code> will
 * point to a pointer which will in turn point to a valid bytearray type storing
 * the binary representation of the multibase data.
 *
 * @param multibase
 *          a <code>az_multibase_t</code> type object representing the multibase
 *          data
 * @param bytearray
 *          a double-indirection pointer to an <code>az_bytearray_t</code> type
 *          to store the binary representation of the multibase data
 * @return a <code>az_status_t</code> type indicating result of operation
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>bytearray == NULL</code>
 *
 * @see <code>az_multibase_decode</code>
 * */
az_status_t az_multibase_encode(az_multibase_t multibase,
        az_bytearray_t** bytearray)
{
    if(bytearray == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    /* allocate space in caller's memory for the az_bytearray_t type */
    *bytearray = calloc(1, sizeof(az_bytearray_t));

    if(*bytearray == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    /* allocate space for our working buffer */
    char* concatenated = calloc(1 + strlen(multibase.text) + 1, sizeof(char));

    if(concatenated == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    /* build our concatenated representation of the multibase string */
    concatenated[0] = multibase.prefix;
    strncpy(&concatenated[1], multibase.text, strlen(multibase.text));

    /* initialise caller's bytearray type with our concatenated string */
    az_status_t res = az_bytearray_init(strlen(concatenated) + 1,
            (uint8_t*)concatenated, *bytearray);

    if(res != AZ_STATUS_OK)
    {
        return res;
    }

    free(concatenated);    

    return AZ_STATUS_OK;
}

/**
 * Converts a <code>az_bytearray_t</code> type into a
 * <code>az_multibase_t</code> type.
 *
 * Upon successful completion of this operation, <code>multibase</code> will
 * point to a pointer which in turn will point to a valid multibase object.
 *
 * @param bytearray
 *          the binary representation of the multibase data
 * @param multibase
 *          a double-indirection pointer to a <code>az_multibase_t</code> type
 *          to store the multibase data
 * @result a <code>az_status_t</code> type indicating result of operation
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>multibase == NULL</code> or if the bytearray contains less
 *          than three bytes of data (as this cannot be a valid multibase
 *          string)
 * @throw AZ_ERR_ALLOC_FAILURE
 *          if memory allocation fails
 * @see <code>az_multibase_encode</code>
 *
 *
 * */
az_status_t az_multibase_decode(az_bytearray_t bytearray,
        az_multibase_t** multibase)
{
    if(multibase == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }
 
    /* a multibase string must have a prefix char and a terminatin NULL byte */
    if(bytearray.len <= 2) /* bounds check */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    /* allocate space in caller's memory for az_multibase_t type */
    *multibase = calloc(1, sizeof(az_multibase_t));

    if(*multibase == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    (*multibase)->prefix = bytearray.data[0];

    /* allocate space for text data */
    (*multibase)->text = calloc(bytearray.len - 1, sizeof(char));

    if((*multibase)->text == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    /* copy data into caller's multibase type */
    memcpy((*multibase)->text, &bytearray.data[1], bytearray.len - 2);

    return AZ_STATUS_OK;
}

/**
 * Converts a <code>az_multibase_t</code> type into a native prefix character
 * and a native C-string.
 *
 * Upon successful completion of this operation, <code>string</code> will point
 * to a heap-allocated block of memory <em>under caller's control</em>.
 *
 * @param multibase
 *          a <code>az_multibase_t</code> type representing the multibase data
 * @param base
 *          a pointer to a native character type to store the base prefix
 * @param string
 *          a pointer to a native string type to store the actual multibase
 *          contents
 * @return a <code>az_status_t</code> type indicating result of operation
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>base == NULL</code> or <code>string == NULL</code>
 * @throw AZ_ERR_ALLOC_FAILURE
 *          if memory allocation fails
 * @see <code>az_multibase_encode</code>
 * @see <code>az_multibase_decode</code>
 *
 * */
az_status_t az_multibase_decode_to_string(az_multibase_t multibase, char* base,
        char** string)
{
    if(base == NULL || string == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    *base = multibase.prefix;

    /* allocate space in caller's memory for prefix char */
    *string = calloc(strlen(multibase.text) + 1, sizeof(char));

    if(*string == NULL) /* allocation check */
    {
        return AZ_ERR_ALLOC_FAILURE;
    }

    /* copy string into caller's buffer */
    strncpy(*string, multibase.text, strlen(multibase.text));

    return AZ_STATUS_OK;
}

/* Equality */

/**
 * Determines whether two <code>az_multibase_t</code> types are equal or not.
 *
 * @param a
 *          first multibase type to compare
 * @param b
 *          second multibase type to compare
 * @param equal
 *          pointer to a boolean flag indicating equality
 * @return a <code>az_status_t</code> type indicating result of operation
 * @throw AZ_ERR_ILLEGAL_PARAM
 *          if <code>equal == NULL</code>
 *
 * */
az_status_t az_multibase_equal(az_multibase_t a, az_multibase_t b, bool* equal)
{
    if(equal == NULL) /* null guard */
    {
        return AZ_ERR_ILLEGAL_PARAM;
    }

    *equal = a.prefix == b.prefix && !strcmp(a.text, b.text);

    return AZ_STATUS_OK;
}

