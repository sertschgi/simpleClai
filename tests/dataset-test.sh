#!/bin/bash

<<<<<<< HEAD
sclai create dataset -n test-dataset -l dataset-test/labelmap.pbtxt -a dataset-test -m dataset-test/train
sclai delete test-dataset
=======

echo "--------------------| starting test 1 |--------------------"

sclai create dataset -n test_dataset -l dataset-test/labelmap.pbtxt -a dataset-test -m dataset-test/train

echo "--------------------| test 1 completed |--------------------"

echo "--------------------| starting test 2 |--------------------"

sclai delete test_dataset

echo "--------------------| test 2 completed |--------------------"
>>>>>>> 109b005 (edited src/, main.cpp, dataset-test.sh)
