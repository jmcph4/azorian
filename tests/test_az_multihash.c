#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <unity/unity.h>

#include <az_status.h>
#include <az_uvarint.h>
#include <az_multicodec.h>
#include <az_multihash.h>

void test_az_multihash_encode_specsample1(void)
{
    az_multicodec_t hash_type = AZ_MULTICODEC_SHA1;
    uintmax_t digest_size = 20;
    uint8_t digest[20] = {0x88, 0xc2, 0xf1, 0x1f, 0xb2, 0xce, 0x39, 0x2a, 0xcb,
                          0x5b, 0x29, 0x86, 0xe6, 0x40, 0x21, 0x1c, 0x46, 0x90,
                          0x07, 0x3e};
    az_multihash_t multihash;

    az_status_t res = az_multihash_encode(hash_type, digest_size,
            (uint8_t*)digest, &multihash);

    /* expected values for each multihash fields */
    az_multicodec_t expected_hash_type = AZ_MULTICODEC_SHA1;
    az_uvarint_t expected_digest_size = make_mc(20);

    /* compare hash types */
    bool equal_hash_types = false;
    az_uvarint_equal(multihash.hash_type, expected_hash_type,
            &equal_hash_types);

    /* compare digest sizes */
    bool equal_digest_sizes = false;
    az_uvarint_equal(multihash.digest_size, expected_digest_size,
            &equal_digest_sizes);

    /* compare digest bytes */
    bool equal_digests = true;

    for(uintmax_t i=0;i<digest_size;i++)
    {
        if(digest[i] != multihash.digest[i])
        {
            equal_digests = false;
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(equal_hash_types);
    TEST_ASSERT_TRUE(equal_digest_sizes);
    TEST_ASSERT_TRUE(equal_digests);
}

void test_az_multihash_decode_specsample1(void)
{
    /* expected values of each multihash field */    
    az_multicodec_t expected_hash_type = AZ_MULTICODEC_SHA1;
    uintmax_t expected_digest_size = 20;
    uint8_t expected_digest[20] = {0x88, 0xc2, 0xf1, 0x1f, 0xb2, 0xce, 0x39,
                                   0x2a, 0xcb, 0x5b, 0x29, 0x86, 0xe6, 0x40,
                                   0x21, 0x1c, 0x46, 0x90, 0x07, 0x3e};

    /* build multihash type */
    az_multihash_t multihash;
    multihash.hash_type = expected_hash_type;
    multihash.digest_size = make_mc(expected_digest_size);
    multihash.digest = calloc(expected_digest_size, sizeof(uint8_t));

    for(uintmax_t i=0;i<expected_digest_size;i++)
    {
        multihash.digest[i] = expected_digest[i];
    }

    az_multicodec_t hash_type;
    uintmax_t digest_size = 0;
    uint8_t* digest = NULL;

    az_status_t res = az_multihash_decode(multihash, &hash_type, &digest_size,
            &digest);

    /* compare hash types */
    bool equal_hash_types = false;
    az_uvarint_equal(hash_type, expected_hash_type, &equal_hash_types);

    /* compare digest bytes */
    bool equal_digests = true;

    for(uintmax_t i=0;i<expected_digest_size;i++)
    {
        if(digest[i] != multihash.digest[i])
        {
            equal_digests= false;
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(equal_hash_types);
    TEST_ASSERT_EQUAL_UINT64(expected_digest_size, digest_size);
    TEST_ASSERT_TRUE(equal_digests);

}

int main(void)
{
    UNITY_BEGIN();
   
    /* az_multihash_encode */
    RUN_TEST(test_az_multihash_encode_specsample1);

    /* az_multihash_decode */
    RUN_TEST(test_az_multihash_decode_specsample1);

    return UNITY_END();
}

