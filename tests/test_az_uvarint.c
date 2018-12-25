#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <unity/unity.h>

#include <az_status.h>
#include <az_uvarint.h>

void test_az_uvarint_encode_specsample1(void)
{
    uint64_t num = 1;
    az_uvarint_t uvarint;

    az_status_t res = az_uvarint_encode(num, &uvarint);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(1, uvarint.len);
    TEST_ASSERT_EQUAL_UINT64(1, uvarint.bytes[0]);
}

void test_az_uvarint_encode_specsample2(void)
{
    uint64_t num = 127;
    az_uvarint_t uvarint;

    az_status_t res = az_uvarint_encode(num, &uvarint);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(1, uvarint.len);
    TEST_ASSERT_EQUAL_UINT64(127, uvarint.bytes[0]);
}

void test_az_uvarint_encode_specsample3(void)
{
    uint64_t num = 128;
    az_uvarint_t uvarint;

    az_status_t res = az_uvarint_encode(num, &uvarint);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(2, uvarint.len);
    TEST_ASSERT_EQUAL_UINT64(128, uvarint.bytes[0]);
    TEST_ASSERT_EQUAL_UINT64(1, uvarint.bytes[1]);
}

void test_az_uvarint_encode_specsample4(void)
{
    uint64_t num = 255;
    az_uvarint_t uvarint;

    az_status_t res = az_uvarint_encode(num, &uvarint);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(2, uvarint.len);
    TEST_ASSERT_EQUAL_UINT64(255, uvarint.bytes[0]);
    TEST_ASSERT_EQUAL_UINT64(1, uvarint.bytes[1]);
}

void test_az_uvarint_encode_specsample5(void)
{
    uint64_t num = 300;
    az_uvarint_t uvarint;

    az_status_t res = az_uvarint_encode(num, &uvarint);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(2, uvarint.len);
    TEST_ASSERT_EQUAL_UINT64(172, uvarint.bytes[0]);
    TEST_ASSERT_EQUAL_UINT64(2, uvarint.bytes[1]);
}

void test_az_uvarint_encode_specsample6(void)
{
    uint64_t num = 16384;
    az_uvarint_t uvarint;

    az_status_t res = az_uvarint_encode(num, &uvarint);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(3, uvarint.len);
    TEST_ASSERT_EQUAL_UINT64(128, uvarint.bytes[0]);
    TEST_ASSERT_EQUAL_UINT64(128, uvarint.bytes[1]);
    TEST_ASSERT_EQUAL_UINT64(1, uvarint.bytes[2]);
}

void test_az_uvarint_decode_specsample1(void)
{
    az_uvarint_t uvarint;
    uvarint.len = 1;
    uvarint.bytes = calloc(uvarint.len, sizeof(uint64_t));
    uvarint.bytes[0] = 1;

    uint64_t num = 0;
    az_status_t res = az_uvarint_decode(uvarint, &num);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(1, num);
}

void test_az_uvarint_decode_specsample2(void)
{
    az_uvarint_t uvarint;
    uvarint.len = 1;
    uvarint.bytes = calloc(uvarint.len, sizeof(uint64_t));
    uvarint.bytes[0] = 127;

    uint64_t num = 0;
    az_status_t res = az_uvarint_decode(uvarint, &num);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(127, num);
}

void test_az_uvarint_decode_specsample3(void)
{
    az_uvarint_t uvarint;
    uvarint.len = 2;
    uvarint.bytes = calloc(uvarint.len, sizeof(uint64_t));
    uvarint.bytes[0] = 128;
    uvarint.bytes[1] = 1;

    uint64_t num = 0;
    az_status_t res = az_uvarint_decode(uvarint, &num);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(128, num);
}

void test_az_uvarint_decode_specsample4(void)
{
    az_uvarint_t uvarint;
    uvarint.len = 2;
    uvarint.bytes = calloc(uvarint.len, sizeof(uint64_t));
    uvarint.bytes[0] = 255;
    uvarint.bytes[1] = 1;

    uint64_t num = 0;
    az_status_t res = az_uvarint_decode(uvarint, &num);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(255, num);
}

void test_az_uvarint_decode_specsample5(void)
{
    az_uvarint_t uvarint;
    uvarint.len = 2;
    uvarint.bytes = calloc(uvarint.len, sizeof(uint64_t));
    uvarint.bytes[0] = 172;
    uvarint.bytes[1] = 2;

    uint64_t num = 0;
    az_status_t res = az_uvarint_decode(uvarint, &num);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(300, num);
}

void test_az_uvarint_decode_specsample6(void)
{
    az_uvarint_t uvarint;
    uvarint.len = 3;
    uvarint.bytes = calloc(uvarint.len, sizeof(uint64_t));
    uvarint.bytes[0] = 128;
    uvarint.bytes[1] = 128;
    uvarint.bytes[2] = 1;

    uint64_t num = 0;
    az_status_t res = az_uvarint_decode(uvarint, &num);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(16384, num);
}

int main(void)
{
    UNITY_BEGIN();
   
    /* az_uvarint_encode */
    RUN_TEST(test_az_uvarint_encode_specsample1);
    RUN_TEST(test_az_uvarint_encode_specsample2);
    RUN_TEST(test_az_uvarint_encode_specsample3);
    RUN_TEST(test_az_uvarint_encode_specsample4);
    RUN_TEST(test_az_uvarint_encode_specsample5);
    RUN_TEST(test_az_uvarint_encode_specsample6);

    /* az_uvarint_decode */
    RUN_TEST(test_az_uvarint_decode_specsample1);
    RUN_TEST(test_az_uvarint_decode_specsample2);
    RUN_TEST(test_az_uvarint_decode_specsample3);
    RUN_TEST(test_az_uvarint_decode_specsample4);
    RUN_TEST(test_az_uvarint_decode_specsample5);
    RUN_TEST(test_az_uvarint_decode_specsample6);
   
    return UNITY_END();
}

