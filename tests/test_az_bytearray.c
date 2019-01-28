#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <unity/unity.h>

#include <az_status.h>
#include <az_bytearray.h>

void test_az_bytearray_init_normal(void)
{
    size_t len = 4;
    uint8_t data[4] = {0x01, 0x02, 0x03, 0x04};
    az_bytearray_t bytearray;

    az_status_t res = az_bytearray_init(len, (uint8_t*)data, &bytearray);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(len, bytearray.len);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(data, bytearray.data, len);
}

void test_az_bytearray_free_normal(void)
{
    size_t len = 4;
    uint8_t data[4] = {0x01, 0x02, 0x03, 0x04};
    az_bytearray_t bytearray;

    az_bytearray_init(len, (uint8_t*)data, &bytearray);
    
    az_status_t res = az_bytearray_free(&bytearray);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT64(0, bytearray.len);
    TEST_ASSERT_NULL(bytearray.data);
}

void test_az_bytearray_equal_normal_equal(void)
{
    az_bytearray_t bytearray_a;
    bytearray_a.len = 4;
    bytearray_a.data = calloc(4, sizeof(uint8_t));
    bytearray_a.data[0] = 0x01;
    bytearray_a.data[1] = 0x02;
    bytearray_a.data[2] = 0x03;
    bytearray_a.data[3] = 0x04;

    az_bytearray_t bytearray_b;
    bytearray_b.len = 4;
    bytearray_b.data = calloc(4, sizeof(uint8_t));
    bytearray_b.data[0] = 0x01;
    bytearray_b.data[1] = 0x02;
    bytearray_b.data[2] = 0x03;
    bytearray_b.data[3] = 0x04;

    bool equal = false;
    az_status_t res = az_bytearray_equal(bytearray_a, bytearray_b, &equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(equal);
}

void test_az_bytearray_equal_normal_unequal(void)
{
    az_bytearray_t bytearray_a;
    bytearray_a.len = 4;
    bytearray_a.data = calloc(4, sizeof(uint8_t));
    bytearray_a.data[0] = 0x01;
    bytearray_a.data[1] = 0x02;
    bytearray_a.data[2] = 0x03;
    bytearray_a.data[3] = 0x04;

    az_bytearray_t bytearray_b;
    bytearray_b.len = 4;
    bytearray_b.data = calloc(4, sizeof(uint8_t));
    bytearray_b.data[0] = 0x05;
    bytearray_b.data[1] = 0x06;
    bytearray_b.data[2] = 0x07;
    bytearray_b.data[3] = 0x08;

    bool equal = false;
    az_status_t res = az_bytearray_equal(bytearray_a, bytearray_b, &equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_FALSE(equal);
}

void test_az_bytearray_slice_normal(void)
{
    uint8_t bytes[4] = {0x01, 0x02, 0x03, 0x04};

    az_bytearray_t bytearray;
    az_bytearray_init(4, bytes, &bytearray);

    uintmax_t start = 0;
    uintmax_t end = 2;

    az_bytearray_t expected_slice;
    az_bytearray_init(end - start, bytes, &expected_slice);

    az_bytearray_t* actual_slice = NULL;

    az_status_t res = az_bytearray_slice(bytearray, start, end, &actual_slice);

    bool slices_equal = false;
    az_bytearray_equal(*actual_slice, expected_slice, &slices_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(slices_equal);
}

void test_az_bytearray_append_normal(void)
{
    uint8_t bytes[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    az_bytearray_t a;
    az_bytearray_init(4, bytes, &a);

    az_bytearray_t b;
    az_bytearray_init(4, &bytes[4], &b);

    az_bytearray_t expected_bytearray;
    az_bytearray_init(8, bytes, &expected_bytearray);

    az_bytearray_t actual_bytearray;
    az_bytearray_init(4, bytes, &actual_bytearray);

    az_status_t res = az_bytearray_append(b, &actual_bytearray);

    bool equal = false;
    az_bytearray_equal(expected_bytearray, actual_bytearray, &equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(equal);
}

int main(void)
{
    UNITY_BEGIN();
   
    /* az_bytearray_init */
    RUN_TEST(test_az_bytearray_init_normal);

    /* az_bytearray_free */
    RUN_TEST(test_az_bytearray_free_normal);

    /* az_bytearray_equal */
    RUN_TEST(test_az_bytearray_equal_normal_equal);
    RUN_TEST(test_az_bytearray_equal_normal_unequal);

    /* az_bytearray_slice */
    RUN_TEST(test_az_bytearray_slice_normal);

    /* az_bytearray_append */
    RUN_TEST(test_az_bytearray_append_normal);

    return UNITY_END();
}

