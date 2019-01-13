#ifndef AZ_BYTEARRAY_H_
#define AZ_BYTEARRAY_H_


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

#endif /* AZ_BYTEARRAY_H_ */

