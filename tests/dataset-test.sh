#!/bin/bash

echo "--------------------| starting test 1 |--------------------"

sclai create dataset -n test_dataset -l dataset-test/labelmap.pbtxt -a dataset-test -m dataset-test/train

echo "--------------------| test 1 completed |--------------------"

echo "--------------------| starting test 2 |--------------------"

sclai delete test_dataset

echo "--------------------| test 2 completed |--------------------"
