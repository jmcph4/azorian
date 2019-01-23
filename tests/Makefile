PROJ_NAME = azorian
SRC_DIR = ../src
BUILD_DIR = ../build
INC_DIR = ../include
UNITY_DIR = $(INC_DIR)/unity

CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -g3 -I$(SRC_DIR) -L$(BUILD_DIR) -l$(PROJ_NAME) -I$(INC_DIR)

.PHONY: all
all: test_az_bytearray test_az_uvarint test_az_multihash test_az_multibase

test_az_bytearray: test_az_bytearray.c $(UNITY_DIR)/unity.c
	$(CC) $^ $(CFLAGS) -o $(BUILD_DIR)/$@

test_az_uvarint: test_az_uvarint.c $(UNITY_DIR)/unity.c
	$(CC) $^ $(CFLAGS) -o $(BUILD_DIR)/$@

test_az_multihash: test_az_multihash.c $(UNITY_DIR)/unity.c
	$(CC) $^ $(CFLAGS) -o $(BUILD_DIR)/$@

test_az_multibase: test_az_multibase.c $(UNITY_DIR)/unity.c
	$(CC) $^ $(CFLAGS) -o $(BUILD_DIR)/$@

