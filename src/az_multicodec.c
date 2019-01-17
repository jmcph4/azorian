#include <stdint.h>

#include "az_status.h"
#include "az_uvarint.h"
#include "az_multicodec.h"

/* private helper function to convert a given native integer into the correct
 * multicodec type (good candidate for macro conversion */
az_multicodec_t make_mc(uintmax_t x)
{
    az_multicodec_t mc;

    az_status_t res = az_uvarint_init_from_int(x, &mc);

    if(res != AZ_STATUS_OK)
    {
        return (az_multicodec_t){0, 0};
    }
    
    return mc;
}

