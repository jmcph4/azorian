#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <unity/unity.h>

#include <az_status.h>
#include <az_uvarint.h>
#include <az_multibase.h>

void test_az_multibase_init_from_string_specsample1(void)
{
    char base = AZ_MULTIBASE_BASE16;
    char* string = "4D756C74696261736520697320617765736F6D6521205C6F2F";
    az_multibase_t multibase;

    az_status_t res = az_multibase_init_from_string(base, string, &multibase);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT8(base, multibase.prefix);
    TEST_ASSERT_EQUAL_STRING(string, multibase.text);
}

void test_az_multibase_init_from_string_specsample2(void)
{
    char base = AZ_MULTIBASE_BASE32;
    char* string = "JV2WY5DJMJQXGZJANFZSAYLXMVZW63LFEEQFY3ZP";
    az_multibase_t multibase;

    az_status_t res = az_multibase_init_from_string(base, string, &multibase);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT8(base, multibase.prefix);
    TEST_ASSERT_EQUAL_STRING(string, multibase.text);
}

void test_az_multibase_init_from_string_specsample3(void)
{
    char base = AZ_MULTIBASE_BASE58_BTC;
    char* string = "YAjKoNbau5KiqmHPmSxYCvn66dA1vLmwbt";
    az_multibase_t multibase;

    az_status_t res = az_multibase_init_from_string(base, string, &multibase);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT8(base, multibase.prefix);
    TEST_ASSERT_EQUAL_STRING(string, multibase.text);
}

void test_az_multibase_init_from_string_specsample4(void)
{
    char base = AZ_MULTIBASE_BASE64;
    char* string = "TXVsdGliYXNlIGlzIGF3ZXNvbWUhIFxvLw==";
    az_multibase_t multibase;

    az_status_t res = az_multibase_init_from_string(base, string, &multibase);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT8(base, multibase.prefix);
    TEST_ASSERT_EQUAL_STRING(string, multibase.text);
}

void test_az_multibase_free_normal(void)
{
    /* set up multibase type */
    char base = AZ_MULTIBASE_BASE16;
    char* string = "4D756C74696261736520697320617765736F6D6521205C6F2F";
    az_multibase_t multibase;
    az_multibase_init_from_string(base, string, &multibase);
    
    az_status_t res = az_multibase_free(&multibase);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_EQUAL_UINT8('\0', multibase.prefix);
    TEST_ASSERT_NULL(multibase.text);
}

void test_az_multibase_encode_specsample1(void)
{
    char base = AZ_MULTIBASE_BASE16;
    char* string = "4D756C74696261736520697320617765736F6D6521205C6F2F";

    /* build multibase type to encode */
    az_multibase_t multibase;
    az_multibase_init_from_string(base, string, &multibase);

    /* build concatenated string for bytearray conversion */
    char* concatenated = calloc(strlen(string) + 2, sizeof(char));
    concatenated[0] = base;
    strncpy(&concatenated[1], string, strlen(string));

    /* initialise expected bytearray */
    az_bytearray_t expected_bytearray;
    az_bytearray_init(strlen(concatenated) + 1, (uint8_t*)concatenated,
            &expected_bytearray);

    az_bytearray_t* actual_bytearray = NULL;

    az_status_t res = az_multibase_encode(multibase, &actual_bytearray);

    /* test for bytearray equality */
    bool bytearrays_equal = false;
    az_bytearray_equal(*actual_bytearray, expected_bytearray,
            &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_multibase_encode_specsample2(void)
{
    char base = AZ_MULTIBASE_BASE32;
    char* string = "JV2WY5DJMJQXGZJANFZSAYLXMVZW63LFEEQFY3ZP";

    /* build multibase type to encode */
    az_multibase_t multibase;
    az_multibase_init_from_string(base, string, &multibase);

    /* build concatenated string for bytearray conversion */
    char* concatenated = calloc(strlen(string) + 2, sizeof(char));
    concatenated[0] = base;
    strncpy(&concatenated[1], string, strlen(string));

    /* initialise expected bytearray */
    az_bytearray_t expected_bytearray;
    az_bytearray_init(strlen(concatenated) + 1, (uint8_t*)concatenated,
            &expected_bytearray);

    az_bytearray_t* actual_bytearray = NULL;

    az_status_t res = az_multibase_encode(multibase, &actual_bytearray);

    /* test for bytearray equality */
    bool bytearrays_equal = false;
    az_bytearray_equal(*actual_bytearray, expected_bytearray,
            &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_multibase_encode_specsample3(void)
{
    char base = AZ_MULTIBASE_BASE58_BTC;
    char* string = "YAjKoNbau5KiqmHPmSxYCvn66dA1vLmwbt";

    /* build multibase type to encode */
    az_multibase_t multibase;
    az_multibase_init_from_string(base, string, &multibase);

    /* build concatenated string for bytearray conversion */
    char* concatenated = calloc(strlen(string) + 2, sizeof(char));
    concatenated[0] = base;
    strncpy(&concatenated[1], string, strlen(string));

    /* initialise expected bytearray */
    az_bytearray_t expected_bytearray;
    az_bytearray_init(strlen(concatenated) + 1, (uint8_t*)concatenated,
            &expected_bytearray);

    az_bytearray_t* actual_bytearray = NULL;

    az_status_t res = az_multibase_encode(multibase, &actual_bytearray);

    /* test for bytearray equality */
    bool bytearrays_equal = false;
    az_bytearray_equal(*actual_bytearray, expected_bytearray,
            &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_multibase_encode_specsample4(void)
{
    char base = AZ_MULTIBASE_BASE64;
    char* string = "TXVsdGliYXNlIGlzIGF3ZXNvbWUhIFxvLw==";

    /* build multibase type to encode */
    az_multibase_t multibase;
    az_multibase_init_from_string(base, string, &multibase);

    /* build concatenated string for bytearray conversion */
    char* concatenated = calloc(strlen(string) + 2, sizeof(char));
    concatenated[0] = base;
    strncpy(&concatenated[1], string, strlen(string));

    /* initialise expected bytearray */
    az_bytearray_t expected_bytearray;
    az_bytearray_init(strlen(concatenated) + 1, (uint8_t*)concatenated,
            &expected_bytearray);

    az_bytearray_t* actual_bytearray = NULL;

    az_status_t res = az_multibase_encode(multibase, &actual_bytearray);

    /* test for bytearray equality */
    bool bytearrays_equal = false;
    az_bytearray_equal(*actual_bytearray, expected_bytearray,
            &bytearrays_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(bytearrays_equal);
}

void test_az_multibase_decode_specsample1(void)
{
    char base = AZ_MULTIBASE_BASE16;
    char* string = "4D756C74696261736520697320617765736F6D6521205C6F2F";

    /* build concatenated string for bytearray conversion */
    char* concatenated = calloc(strlen(string) + 2, sizeof(char));
    concatenated[0] = base;
    strncpy(&concatenated[1], string, strlen(string));

    /* initialise bytearray */
    az_bytearray_t bytearray;
    az_bytearray_init(strlen(concatenated) + 1, (uint8_t*)concatenated,
            &bytearray);

    /* build expected multibase type */
    az_multibase_t expected_multibase;
    expected_multibase.prefix = base;
    expected_multibase.text = string;

    az_multibase_t* actual_multibase = NULL;
    az_status_t res = az_multibase_decode(bytearray, &actual_multibase);

    /* test for multibase equality */
    bool multibases_equal = false;
    az_multibase_equal(*actual_multibase, expected_multibase,
            &multibases_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(multibases_equal);
}

void test_az_multibase_decode_specsample2(void)
{
    char base = AZ_MULTIBASE_BASE32;
    char* string = "JV2WY5DJMJQXGZJANFZSAYLXMVZW63LFEEQFY3ZP";

    /* build concatenated string for bytearray conversion */
    char* concatenated = calloc(strlen(string) + 2, sizeof(char));
    concatenated[0] = base;
    strncpy(&concatenated[1], string, strlen(string));

    /* initialise bytearray */
    az_bytearray_t bytearray;
    az_bytearray_init(strlen(concatenated) + 1, (uint8_t*)concatenated,
            &bytearray);

    /* build expected multibase type */
    az_multibase_t expected_multibase;
    expected_multibase.prefix = base;
    expected_multibase.text = string;

    az_multibase_t* actual_multibase = NULL;
    az_status_t res = az_multibase_decode(bytearray, &actual_multibase);

    /* test for multibase equality */
    bool multibases_equal = false;
    az_multibase_equal(*actual_multibase, expected_multibase,
            &multibases_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(multibases_equal);
}

void test_az_multibase_decode_specsample3(void)
{
    char base = AZ_MULTIBASE_BASE58_BTC;
    char* string = "YAjKoNbau5KiqmHPmSxYCvn66dA1vLmwbt";

    /* build concatenated string for bytearray conversion */
    char* concatenated = calloc(strlen(string) + 2, sizeof(char));
    concatenated[0] = base;
    strncpy(&concatenated[1], string, strlen(string));

    /* initialise bytearray */
    az_bytearray_t bytearray;
    az_bytearray_init(strlen(concatenated) + 1, (uint8_t*)concatenated,
            &bytearray);

    /* build expected multibase type */
    az_multibase_t expected_multibase;
    expected_multibase.prefix = base;
    expected_multibase.text = string;

    az_multibase_t* actual_multibase = NULL;
    az_status_t res = az_multibase_decode(bytearray, &actual_multibase);

    /* test for multibase equality */
    bool multibases_equal = false;
    az_multibase_equal(*actual_multibase, expected_multibase,
            &multibases_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(multibases_equal);
}


void test_az_multibase_decode_specsample4(void)
{
    char base = AZ_MULTIBASE_BASE64;
    char* string = "TXVsdGliYXNlIGlzIGF3ZXNvbWUhIFxvLw==";

    /* build concatenated string for bytearray conversion */
    char* concatenated = calloc(strlen(string) + 2, sizeof(char));
    concatenated[0] = base;
    strncpy(&concatenated[1], string, strlen(string));

    /* initialise bytearray */
    az_bytearray_t bytearray;
    az_bytearray_init(strlen(concatenated) + 1, (uint8_t*)concatenated,
            &bytearray);

    /* build expected multibase type */
    az_multibase_t expected_multibase;
    expected_multibase.prefix = base;
    expected_multibase.text = string;

    az_multibase_t* actual_multibase = NULL;
    az_status_t res = az_multibase_decode(bytearray, &actual_multibase);

    /* test for multibase equality */
    bool multibases_equal = false;
    az_multibase_equal(*actual_multibase, expected_multibase,
            &multibases_equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(multibases_equal);
}

void test_az_multibase_equal_normal_equal(void)
{
    char base_a = AZ_MULTIBASE_BASE16;
    char base_b = AZ_MULTIBASE_BASE16;
    char* string_a = "foo";
    char* string_b = "foo";

    az_multibase_t multibase_a;
    az_multibase_t multibase_b;

    az_multibase_init_from_string(base_a, string_a, &multibase_a);
    az_multibase_init_from_string(base_b, string_b, &multibase_b);

    bool equal = false;
    az_status_t res = az_multibase_equal(multibase_a, multibase_b, &equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_TRUE(equal);
}

void test_az_multibase_equal_normal_unequal(void)
{
    char base_a = AZ_MULTIBASE_BASE16;
    char base_b = AZ_MULTIBASE_BASE32;
    char* string_a = "foo";
    char* string_b = "bar";

    az_multibase_t multibase_a;
    az_multibase_t multibase_b;

    az_multibase_init_from_string(base_a, string_a, &multibase_a);
    az_multibase_init_from_string(base_b, string_b, &multibase_b);

    bool equal = false;
    az_status_t res = az_multibase_equal(multibase_a, multibase_b, &equal);

    TEST_ASSERT_EQUAL_INT(AZ_STATUS_OK, res);
    TEST_ASSERT_FALSE(equal);
}

int main(void)
{
    UNITY_BEGIN();
  
    /* az_multibase_init_from_string */
    RUN_TEST(test_az_multibase_init_from_string_specsample1);
    RUN_TEST(test_az_multibase_init_from_string_specsample2);
    RUN_TEST(test_az_multibase_init_from_string_specsample3);
    RUN_TEST(test_az_multibase_init_from_string_specsample4);

    /* az_multibase_free */
    RUN_TEST(test_az_multibase_free_normal);

    /* az_multibase_encode */
    RUN_TEST(test_az_multibase_encode_specsample1);
    RUN_TEST(test_az_multibase_encode_specsample2);
    RUN_TEST(test_az_multibase_encode_specsample3);
    RUN_TEST(test_az_multibase_encode_specsample4);

    /* az_multibase_decode */
    RUN_TEST(test_az_multibase_decode_specsample1);
    RUN_TEST(test_az_multibase_decode_specsample2);
    RUN_TEST(test_az_multibase_decode_specsample3);
    RUN_TEST(test_az_multibase_decode_specsample4);

    /* az_multibase_equal */
    RUN_TEST(test_az_multibase_equal_normal_equal);
    RUN_TEST(test_az_multibase_equal_normal_unequal);

    return UNITY_END();
}

