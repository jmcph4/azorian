#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <unity/unity.h>

#include <az_status.h>
#include <az_uvarint.h>

void test_az_uvarint_init_from_int_specsample1(void)
{
    uintmax_t num = 1;
    az_uvarint_t uvarint;

    az_status_t res = az_uvarint_init_from_int(num, &uvarint);

    /* build expected bytearray */
    uint8_t bytes[1] = {0x01};
    az_bytearray_t expected_bytes;
    az_bytearray_init(1, (uint8_t*)bytes, &expected_bytes);

    bool bytearrays_equal = false;
    az_bytearray_equal(*uvarint.bytes, expected_bytes, &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(num, uvarint.num);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_uvarint_init_from_int_specsample2(void)
{
    uintmax_t num = 127;
    az_uvarint_t uvarint;

    az_status_t res = az_uvarint_init_from_int(num, &uvarint);

    /* build expected bytearray */
    uint8_t bytes[1] = {127};
    az_bytearray_t expected_bytes;
    az_bytearray_init(1, (uint8_t*)bytes, &expected_bytes);

    bool bytearrays_equal = false;
    az_bytearray_equal(*(uvarint.bytes), expected_bytes, &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(num, uvarint.num);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_uvarint_init_from_int_specsample3(void)
{
    uintmax_t num = 128;
    az_uvarint_t uvarint;

    az_status_t res = az_uvarint_init_from_int(num, &uvarint);

    /* build expected bytearray */
    uint8_t bytes[2] = {128, 1};
    az_bytearray_t expected_bytes;
    az_bytearray_init(2, (uint8_t*)bytes, &expected_bytes);

    bool bytearrays_equal = false;
    az_bytearray_equal(*(uvarint.bytes), expected_bytes, &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(num, uvarint.num);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_uvarint_init_from_int_specsample4(void)
{
    uintmax_t num = 255;
    az_uvarint_t uvarint;

    az_status_t res = az_uvarint_init_from_int(num, &uvarint);

    /* build expected bytearray */
    uint8_t bytes[2] = {255, 1};
    az_bytearray_t expected_bytes;
    az_bytearray_init(2, (uint8_t*)bytes, &expected_bytes);

    bool bytearrays_equal = false;
    az_bytearray_equal(*(uvarint.bytes), expected_bytes, &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(num, uvarint.num);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_uvarint_init_from_int_specsample5(void)
{
    uintmax_t num = 300;
    az_uvarint_t uvarint;

    az_status_t res = az_uvarint_init_from_int(num, &uvarint);

    /* build expected bytearray */
    uint8_t bytes[2] = {172, 2};
    az_bytearray_t expected_bytes;
    az_bytearray_init(2, (uint8_t*)bytes, &expected_bytes);

    bool bytearrays_equal = false;
    az_bytearray_equal(*(uvarint.bytes), expected_bytes, &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(num, uvarint.num);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_uvarint_init_from_int_specsample6(void)
{
    uintmax_t num = 16384;
    az_uvarint_t uvarint;

    az_status_t res = az_uvarint_init_from_int(num, &uvarint);

    /* build expected bytearray */
    uint8_t bytes[3] = {128, 128, 1};
    az_bytearray_t expected_bytes;
    az_bytearray_init(3, (uint8_t*)bytes, &expected_bytes);

    bool bytearrays_equal = false;
    az_bytearray_equal(*(uvarint.bytes), expected_bytes, &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(num, uvarint.num);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_uvarint_free_normal(void)
{
    uintmax_t num = 33;
    az_uvarint_t uvarint;

    az_uvarint_init_from_int(num, &uvarint);

    az_status_t res = az_uvarint_free(uvarint);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_NULL(uvarint.bytes);
    TEST_ASSERT_EQUAL_UINT64(0, uvarint.num);

}

void test_az_uvarint_encode_specsample1(void)
{
    uintmax_t num = 1;
    az_uvarint_t uvarint;
    uint8_t expected_bytes[1] = {1};

    az_uvarint_init_from_int(num, &uvarint);

    /* construct expected bytearrays */
    az_bytearray_t expected_bytearray;
    az_bytearray_init(1, (uint8_t*)expected_bytes, &expected_bytearray);

    az_bytearray_t* actual_bytearray = NULL;
    az_status_t res = az_uvarint_encode(uvarint, &actual_bytearray);

    bool bytearrays_equal = false;
    az_bytearray_equal(*actual_bytearray, expected_bytearray, &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_uvarint_encode_specsample2(void)
{
    uintmax_t num = 127;
    az_uvarint_t uvarint;
    uint8_t expected_bytes[1] = {127};

    az_uvarint_init_from_int(num, &uvarint);

    /* construct expected bytearrays */
    az_bytearray_t expected_bytearray;
    az_bytearray_init(1, (uint8_t*)expected_bytes, &expected_bytearray);

    az_bytearray_t* actual_bytearray = NULL;
    az_status_t res = az_uvarint_encode(uvarint, &actual_bytearray);

    bool bytearrays_equal = false;
    az_bytearray_equal(*actual_bytearray, expected_bytearray, &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_uvarint_encode_specsample3(void)
{
    uintmax_t num = 128;
    az_uvarint_t uvarint;
    uint8_t expected_bytes[2] = {128, 1};

    az_uvarint_init_from_int(num, &uvarint);

    /* construct expected bytearrays */
    az_bytearray_t expected_bytearray;
    az_bytearray_init(2, (uint8_t*)expected_bytes, &expected_bytearray);

    az_bytearray_t* actual_bytearray = NULL;
    az_status_t res = az_uvarint_encode(uvarint, &actual_bytearray);

    bool bytearrays_equal = false;
    az_bytearray_equal(*actual_bytearray, expected_bytearray, &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_uvarint_encode_specsample4(void)
{
    uintmax_t num = 255;
    az_uvarint_t uvarint;
    uint8_t expected_bytes[2] = {255, 1};

    az_uvarint_init_from_int(num, &uvarint);

    /* construct expected bytearrays */
    az_bytearray_t expected_bytearray;
    az_bytearray_init(2, (uint8_t*)expected_bytes, &expected_bytearray);

    az_bytearray_t* actual_bytearray = NULL;
    az_status_t res = az_uvarint_encode(uvarint, &actual_bytearray);

    bool bytearrays_equal = false;
    az_bytearray_equal(*actual_bytearray, expected_bytearray, &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_uvarint_encode_specsample5(void)
{
    uintmax_t num = 300;
    az_uvarint_t uvarint;
    uint8_t expected_bytes[2] = {172, 2};

    az_uvarint_init_from_int(num, &uvarint);

    /* construct expected bytearrays */
    az_bytearray_t expected_bytearray;
    az_bytearray_init(2, (uint8_t*)expected_bytes, &expected_bytearray);

    az_bytearray_t* actual_bytearray = NULL;
    az_status_t res = az_uvarint_encode(uvarint, &actual_bytearray);

    bool bytearrays_equal = false;
    az_bytearray_equal(*actual_bytearray, expected_bytearray, &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_uvarint_encode_specsample6(void)
{
    uintmax_t num = 16384;
    az_uvarint_t uvarint;
    uint8_t expected_bytes[3] = {128, 128, 1};

    az_uvarint_init_from_int(num, &uvarint);

    /* construct expected bytearrays */
    az_bytearray_t expected_bytearray;
    az_bytearray_init(3, (uint8_t*)expected_bytes, &expected_bytearray);

    az_bytearray_t* actual_bytearray = NULL;
    az_status_t res = az_uvarint_encode(uvarint, &actual_bytearray);

    bool bytearrays_equal = false;
    az_bytearray_equal(*actual_bytearray, expected_bytearray,
            &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_uvarint_decode_specsample1(void)
{
    uintmax_t num = 1;
    az_bytearray_t bytearray;
    uint8_t expected_bytes[1] = {1};

    az_bytearray_init(1, (uint8_t*)expected_bytes, &bytearray);

    /* construct expected uvarint */
    az_uvarint_t expected_uvarint;
    expected_uvarint.num = num;
    expected_uvarint.bytes = &bytearray;

    az_uvarint_t* actual_uvarint = NULL;
    az_status_t res = az_uvarint_decode(bytearray, &actual_uvarint);

    bool uvarints_equal = false;
    az_uvarint_equal(*actual_uvarint, expected_uvarint, &uvarints_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(uvarints_equal);
}

void test_az_uvarint_decode_specsample2(void)
{
    uintmax_t num = 127;
    az_bytearray_t bytearray;
    uint8_t expected_bytes[1] = {127};

    az_bytearray_init(1, (uint8_t*)expected_bytes, &bytearray);

    /* construct expected uvarint */
    az_uvarint_t expected_uvarint;
    expected_uvarint.num = num;
    expected_uvarint.bytes = &bytearray;

    az_uvarint_t* actual_uvarint = NULL;
    az_status_t res = az_uvarint_decode(bytearray, &actual_uvarint);

    bool uvarints_equal = false;
    az_uvarint_equal(*actual_uvarint, expected_uvarint, &uvarints_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(uvarints_equal);
}

void test_az_uvarint_decode_specsample3(void)
{
    uintmax_t num = 128;
    az_bytearray_t bytearray;
    uint8_t expected_bytes[2] = {128, 1};

    az_bytearray_init(2, (uint8_t*)expected_bytes, &bytearray);

    /* construct expected uvarint */
    az_uvarint_t expected_uvarint;
    expected_uvarint.num = num;
    expected_uvarint.bytes = &bytearray;

    az_uvarint_t* actual_uvarint = NULL;
    az_status_t res = az_uvarint_decode(bytearray, &actual_uvarint);

    bool uvarints_equal = false;
    az_uvarint_equal(*actual_uvarint, expected_uvarint, &uvarints_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(uvarints_equal);
}

void test_az_uvarint_decode_specsample4(void)
{
    uintmax_t num = 255;
    az_bytearray_t bytearray;
    uint8_t expected_bytes[2] = {255, 1};

    az_bytearray_init(2, (uint8_t*)expected_bytes, &bytearray);

    /* construct expected uvarint */
    az_uvarint_t expected_uvarint;
    expected_uvarint.num = num;
    expected_uvarint.bytes = &bytearray;

    az_uvarint_t* actual_uvarint = NULL;
    az_status_t res = az_uvarint_decode(bytearray, &actual_uvarint);

    bool uvarints_equal = false;
    az_uvarint_equal(*actual_uvarint, expected_uvarint, &uvarints_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(uvarints_equal);
}

void test_az_uvarint_decode_specsample5(void)
{
    uintmax_t num = 300;
    az_bytearray_t bytearray;
    uint8_t expected_bytes[2] = {172, 2};

    az_bytearray_init(2, (uint8_t*)expected_bytes, &bytearray);

    /* construct expected uvarint */
    az_uvarint_t expected_uvarint;
    expected_uvarint.num = num;
    expected_uvarint.bytes = &bytearray;

    az_uvarint_t* actual_uvarint = NULL;
    az_status_t res = az_uvarint_decode(bytearray, &actual_uvarint);

    bool uvarints_equal = false;
    az_uvarint_equal(*actual_uvarint, expected_uvarint, &uvarints_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(uvarints_equal);
}

void test_az_uvarint_decode_specsample6(void)
{
    uintmax_t num = 16384;
    az_bytearray_t bytearray;
    uint8_t expected_bytes[3] = {128, 128, 1};

    az_bytearray_init(3, (uint8_t*)expected_bytes, &bytearray);

    /* construct expected uvarint */
    az_uvarint_t expected_uvarint;
    expected_uvarint.num = num;
    expected_uvarint.bytes = &bytearray;

    az_uvarint_t* actual_uvarint = NULL;
    az_status_t res = az_uvarint_decode(bytearray, &actual_uvarint);

    bool uvarints_equal = false;
    az_uvarint_equal(*actual_uvarint, expected_uvarint, &uvarints_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(uvarints_equal);
}

void test_az_uvarint_decode_to_int_specsample1(void)
{
    uintmax_t expected_num = 1;
    az_uvarint_t uvarint;
    az_uvarint_init_from_int(expected_num, &uvarint);
    
    uintmax_t actual_num = 0;
    az_status_t res = az_uvarint_decode_to_int(uvarint, &actual_num);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(expected_num, actual_num);
}


void test_az_uvarint_decode_to_int_specsample2(void)
{
    uintmax_t expected_num = 127;
    az_uvarint_t uvarint;
    az_uvarint_init_from_int(expected_num, &uvarint);
    
    uintmax_t actual_num = 0;
    az_status_t res = az_uvarint_decode_to_int(uvarint, &actual_num);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(expected_num, actual_num);
}

void test_az_uvarint_decode_to_int_specsample3(void)
{
    uintmax_t expected_num = 128;
    az_uvarint_t uvarint;
    az_uvarint_init_from_int(expected_num, &uvarint);
    
    uintmax_t actual_num = 0;
    az_status_t res = az_uvarint_decode_to_int(uvarint, &actual_num);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(expected_num, actual_num);
}

void test_az_uvarint_decode_to_int_specsample4(void)
{
    uintmax_t expected_num = 255;
    az_uvarint_t uvarint;
    az_uvarint_init_from_int(expected_num, &uvarint);
    
    uintmax_t actual_num = 0;
    az_status_t res = az_uvarint_decode_to_int(uvarint, &actual_num);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(expected_num, actual_num);
}

void test_az_uvarint_decode_to_int_specsample5(void)
{
    uintmax_t expected_num = 300;
    az_uvarint_t uvarint;
    az_uvarint_init_from_int(expected_num, &uvarint);
    
    uintmax_t actual_num = 0;
    az_status_t res = az_uvarint_decode_to_int(uvarint, &actual_num);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(expected_num, actual_num);
}

void test_az_uvarint_decode_to_int_specsample6(void)
{
    uintmax_t expected_num = 16384;
    az_uvarint_t uvarint;
    az_uvarint_init_from_int(expected_num, &uvarint);
    
    uintmax_t actual_num = 0;
    az_status_t res = az_uvarint_decode_to_int(uvarint, &actual_num);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(expected_num, actual_num);
}

void test_az_uvarint_equal_normal_equal(void)
{
    uint64_t num_a = 33;
    uint64_t num_b = 33;
    az_uvarint_t uvarint_a;
    az_uvarint_t uvarint_b;
    
    az_status_t res_encode_a = az_uvarint_init_from_int(num_a, &uvarint_a);
    az_status_t res_encode_b = az_uvarint_init_from_int(num_b, &uvarint_b);
   
    bool equal = false;
    az_status_t res_equality = az_uvarint_equal(uvarint_a, uvarint_b, &equal);

    TEST_ASSERT_EQUAL_UINT64(num_a, num_b);
    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res_encode_a);
    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res_encode_b);
    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res_equality);
    TEST_ASSERT_TRUE(equal);
}

void test_az_uvarint_equal_normal_unequal(void)
{
    uint64_t num_a = 33;
    uint64_t num_b = 12;
    az_uvarint_t uvarint_a;
    az_uvarint_t uvarint_b;
    
    az_status_t res_encode_a = az_uvarint_init_from_int(num_a, &uvarint_a);
    az_status_t res_encode_b = az_uvarint_init_from_int(num_b, &uvarint_b);
   
    bool equal = true;
    az_status_t res_equality = az_uvarint_equal(uvarint_a, uvarint_b, &equal);

    TEST_ASSERT_FALSE(num_a == num_b);
    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res_encode_a);
    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res_encode_b);
    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res_equality);
    TEST_ASSERT_FALSE(equal);
}

int main(void)
{
    UNITY_BEGIN();
   
    /* az_uvarint_init_from_int */
    RUN_TEST(test_az_uvarint_init_from_int_specsample1);
    RUN_TEST(test_az_uvarint_init_from_int_specsample2);
    RUN_TEST(test_az_uvarint_init_from_int_specsample3);
    RUN_TEST(test_az_uvarint_init_from_int_specsample4);
    RUN_TEST(test_az_uvarint_init_from_int_specsample5);
    RUN_TEST(test_az_uvarint_init_from_int_specsample6);

    /* az_uvarint_encode */
    RUN_TEST(test_az_uvarint_encode_specsample1);
    RUN_TEST(test_az_uvarint_encode_specsample2);
    RUN_TEST(test_az_uvarint_encode_specsample3);
    RUN_TEST(test_az_uvarint_encode_specsample4);
    RUN_TEST(test_az_uvarint_encode_specsample5);
    RUN_TEST(test_az_uvarint_encode_specsample6);

    /* az_uvarint_encode */
    RUN_TEST(test_az_uvarint_decode_specsample1);
    RUN_TEST(test_az_uvarint_decode_specsample2);
    RUN_TEST(test_az_uvarint_decode_specsample3);
    RUN_TEST(test_az_uvarint_decode_specsample4);
    RUN_TEST(test_az_uvarint_decode_specsample5);
    RUN_TEST(test_az_uvarint_decode_specsample6);
    
    /* az_uvarint_decode_to_int */
    RUN_TEST(test_az_uvarint_decode_to_int_specsample1);
    RUN_TEST(test_az_uvarint_decode_to_int_specsample2);
    RUN_TEST(test_az_uvarint_decode_to_int_specsample3);
    RUN_TEST(test_az_uvarint_decode_to_int_specsample4);
    RUN_TEST(test_az_uvarint_decode_to_int_specsample5);
    RUN_TEST(test_az_uvarint_decode_to_int_specsample6);
   
    /* az_uvarint_equal */
    RUN_TEST(test_az_uvarint_equal_normal_equal);
    RUN_TEST(test_az_uvarint_equal_normal_unequal);

    return UNITY_END();
}

