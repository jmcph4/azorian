/**
 * @file az_bytearray.h
 *
 * Contains API definitions for the bytearray implementation in the form of
 * function declarations.
 *
 * */
#ifndef AZ_BYTEARRAY_H_
#define AZ_BYTEARRAY_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "az_status.h"

/**
 * Represents an array of bytes, storing arbitrary binary data.
 *
 * */
typedef struct
{
    size_t len;         /* number of bytes stored */
    uint8_t* data;      /* actual bytes */
} az_bytearray_t;

/* Initialisation */
az_status_t az_bytearray_init(size_t len, uint8_t* data,
        az_bytearray_t* bytearray);
az_status_t az_bytearray_free(az_bytearray_t* bytearray);

/* Equality */
az_status_t az_bytearray_equal(az_bytearray_t a, az_bytearray_t b, bool* equal);

/* Operations */
az_status_t az_bytearray_slice(az_bytearray_t bytearray, uintmax_t start,
        uintmax_t end, az_bytearray_t** slice);

#endif /* AZ_BYTEARRAY_H_ */

