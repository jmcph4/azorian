#ifndef AZ_BYTEARRAY_H_
#define AZ_BYTEARRAY_H_

#include <stdint.h>
#include <stdbool.h>

/**
 *
 *
 * */
typedef struct
{
    size_t len;
    uint8_t* data;
} az_bytearray_t;

/* Initialisation */
az_status_t az_bytearray_init(size_t len, uint8_t* data,
        az_bytearray_t* bytearray);
az_status_t az_bytearray_free(az_bytearray_t* bytearray);

/* Equality */
az_status_t az_bytearray_equal(az_bytearray_t a, az_bytearray_t b, bool* equal);

#endif /* AZ_BYTEARRAY_H_ */

