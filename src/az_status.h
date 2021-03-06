/**
 * @file az_status.h
 *
 * Contains definitions for the <code>az_status_t</code> type.
 *
 * */
#ifndef AZ_STATUS_H_
#define AZ_STATUS_H_

/**
 * Describes the result of an API call in Azorian.
 *
 * */
typedef enum
{
    AZ_STATUS_OK = 0,
    AZ_ERR_ILLEGAL_PARAM = -1,
    AZ_ERR_ALLOC_FAILURE = -2,
    AZ_ERR_VARINT_TOO_BIG = -3
} az_status_t;

#endif /* AZ_STATUS_H_ */

