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

#include <stdint.h>

#define BITS_PER_BYTE 8
#define AZ_UVARINT_MAX_LEN 9 /* as per spec */

/**
 * Represents an unsigned variable integer. Basically represented here as a
 * simple array with a length field.
 *
 * */
typedef struct
{
    uint8_t len;        /* number of bytes */
    uint8_t* bytes;     /* bytes themselves */
} az_uvarint_t;

az_status_t az_uvarint_encode(uint64_t num, az_uvarint_t* uvarint);
az_status_t az_uvarint_decode(az_uvarint_t uvarint, uint64_t* num);

#endif /* AZ_UVARINT_H_ */

