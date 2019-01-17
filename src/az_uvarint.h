/**
 * @file az_uvarint.h
 *
 * Contains definition of <code>az_uvarint_t</code> type and defines the
 * unsigned variable integer API, in the form of funtion prototype
 * declarations.
 *
 * */
#ifndef AZ_UVARINT_H_
#define AZ_UVARINT_H_

#include <stdbool.h>
#include <stdint.h>

#include "az_status.h"
#include "az_bytearray.h"

#define BITS_PER_BYTE 8
#define AZ_UVARINT_MAX_LEN 9 /* as per spec */

/**
 * Represents an unsigned variable integer. Basically represented here as a
 * simple array with a length field.
 *
 * */
typedef struct
{
    uintmax_t num;              /* number represented, in native format */
    az_bytearray_t* bytes;      /* bytes containing binary representation */
} az_uvarint_t;

/* Initialisation */
az_status_t az_uvarint_init_from_int(uintmax_t num, az_uvarint_t* uvarint);
az_status_t az_uvarint_free(az_uvarint_t uvarint);

/* Codec */
az_status_t az_uvarint_encode(az_uvarint_t uvarint, az_bytearray_t** bytearray);
az_status_t az_uvarint_decode(az_bytearray_t bytearray, az_uvarint_t** uvarint);
az_status_t az_uvarint_decode_to_int(az_uvarint_t uvarint, uintmax_t* num);

/* Equality */
az_status_t az_uvarint_equal(az_uvarint_t a, az_uvarint_t b, bool* equal);

#endif /* AZ_UVARINT_H_ */

