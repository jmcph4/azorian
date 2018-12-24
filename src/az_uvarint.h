#ifndef AZ_UVARINT_H_
#define AZ_UVARINT_H_

#include <stdint.h>

#define BITS_PER_BYTE 8
#define AZ_UVARINT_MAX_LEN 9 /* as per spec */

typedef struct
{
    uint8_t len;        /* number of bytes */
    uint8_t* bytes;     /* bytes themselves */
} az_uvarint_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

az_status_t az_uvarint_encode(uint64_t num, az_uvarint_t* uvarint);
az_status_t az_uvarint_decode(az_uvarint_t uvarint, uint64_t* num);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AZ_UVARINT_H_ */

