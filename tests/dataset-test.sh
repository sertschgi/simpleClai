#!/bin/bash

sclai create dataset -n test-dataset -l dataset-test/labelmap.pbtxt -a dataset-test -i dataset-test/train
sclai delete test-dataset
