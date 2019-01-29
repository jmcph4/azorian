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
    uint8_t bytes[22] = {0x11, 0x14, 0x88, 0xc2, 0xf1, 0x1f, 0xb2, 0xce, 0x39, 0x2a, 0xcb,
                          0x5b, 0x29, 0x86, 0xe6, 0x40, 0x21, 0x1c, 0x46, 0x90,
                          0x07, 0x3e};

    /* expected hash digest */
    az_bytearray_t expected_digest;
    az_bytearray_init(digest_size, digest, &expected_digest);

    /* set up multihash type manually */
    az_multihash_t multihash;
    multihash.type = hash_type;
    multihash.digest = expected_digest;

    az_bytearray_t expected_bytes;
    az_bytearray_init(22, bytes, &expected_bytes);

    /* encode */
    az_bytearray_t* actual_bytes = NULL;
    az_status_t res = az_multihash_encode(multihash, &actual_bytes);

    /* compare equality of expected and actual bytearrays */
    bool equal_bytes = false;
    az_bytearray_equal(*actual_bytes, expected_bytes, &equal_bytes);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(equal_bytes);
}

void test_az_multihash_decode_specsample1(void)
{
    /* expected values of each multihash field */    
    az_multicodec_t hash_type = AZ_MULTICODEC_SHA1;
    uintmax_t digest_size = 20;
    uint8_t digest_bytes[20] = {0x88, 0xc2, 0xf1, 0x1f, 0xb2, 0xce, 0x39, 0x2a, 0xcb,
                          0x5b, 0x29, 0x86, 0xe6, 0x40, 0x21, 0x1c, 0x46, 0x90,
                          0x07, 0x3e};
    uint8_t bytes[22] = {0x11, 0x14, 0x88, 0xc2, 0xf1, 0x1f, 0xb2, 0xce, 0x39,
                                   0x2a, 0xcb, 0x5b, 0x29, 0x86, 0xe6, 0x40,
                                   0x21, 0x1c, 0x46, 0x90, 0x07, 0x3e};

    /* expected hash digest */
    az_bytearray_t bytearray;
    az_bytearray_init(digest_size + 2, bytes, &bytearray);

    az_bytearray_t digest;
    az_bytearray_init(digest_size, digest_bytes, &digest);

    /* expected multihash type */
    az_multihash_t expected_multihash;
    expected_multihash.type = hash_type;
    expected_multihash.digest = digest;

    /* decode */
    az_multihash_t* actual_multihash = NULL;
    az_status_t res = az_multihash_decode(bytearray, &actual_multihash);

    /* compare equality of expected and actual multihashes */
    bool multihashes_equal = false;
    az_multihash_equal(expected_multihash, *actual_multihash,
            &multihashes_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(multihashes_equal);
}

void test_az_multihash_equal_normal_equal(void)
{
    uint8_t digest_bytes[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    az_bytearray_t digest_a;
    az_bytearray_init(4, digest_bytes, &digest_a);

    az_bytearray_t digest_b;
    az_bytearray_init(4, digest_bytes, &digest_b);

    az_multihash_t* multihash_a = NULL;
    az_multihash_decode(digest_a, &multihash_a);

    az_multihash_t* multihash_b = NULL;
    az_multihash_decode(digest_b, &multihash_b);

    bool equal = false;
    az_status_t res = az_multihash_equal(*multihash_a, *multihash_b, &equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(equal);
}

void test_az_multihash_equal_normal_unequal(void)
{
    uint8_t digest_bytes[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    az_bytearray_t digest_a;
    az_bytearray_init(4, digest_bytes, &digest_a);

    az_bytearray_t digest_b;
    az_bytearray_init(4 ,&digest_bytes[4], &digest_b);

    az_multihash_t* multihash_a = NULL;
    az_multihash_decode(digest_a, &multihash_a);

    az_multihash_t* multihash_b = NULL;
    az_multihash_decode(digest_b, &multihash_b);

    bool equal = true;
    az_status_t res = az_multihash_equal(*multihash_a, *multihash_b, &equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_FALSE(equal);
}

int main(void)
{
    UNITY_BEGIN();
   
    /* az_multihash_encode */
    RUN_TEST(test_az_multihash_encode_specsample1);

    /* az_multihash_decode */
    RUN_TEST(test_az_multihash_decode_specsample1);

    /* az_multihash_equal */
    RUN_TEST(test_az_multihash_equal_normal_equal);
    RUN_TEST(test_az_multihash_equal_normal_unequal);

    return UNITY_END();
}

