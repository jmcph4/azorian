#ifndef AZ_STATUS_H_
#define AZ_STATUS_H_

typedef enum
{
    AZ_STATUS_OK = 0,
    AZ_ERR_ILLEGAL_PARAM = -1,
    AZ_ERR_ALLOC_FAILURE = -2
} az_status_t;

#endif /* AZ_STATUS_H_ */

