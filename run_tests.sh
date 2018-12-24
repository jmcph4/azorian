#!/bin/bash

# iterate over each test executable
for filename in build/test_*; do
    $filename
done

