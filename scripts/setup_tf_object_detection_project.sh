#!/bin/bash

PROJECT_PATH=$1
DATASET_PATH=$2
PROFILE_PATH=$3
VENV_PATH=$4

SAI_APP_SCRIPTS_PATH=$5

TT_RATIO=$6

if [ -z $TT_RATIO ]; then
    TT_RATIO="0.1"
fi

echo "Project path: $PROJECT_PATH"
mkdir -p $PROJECT_PATH

cd $PROJECT_PATH

eval "$(conda shell.bash hook)"
conda activate $VENV_PATH
source $VENV_PATH/etc/conda/activate.d/env_vars.sh

python $SAI_APP_SCRIPTS_PATH/partition_dataset.py -i $DATASET_PATH/images -lmo annotations -l $DATASET_PATH/labels -o images -r $TT_RATIO -x

python $SAI_APP_SCRIPTS_PATH/generate_tfrecord.py -x images/train -l annotations/label_map.pbtxt -o annotations/train.record
python $SAI_APP_SCRIPTS_PATH/generate_tfrecord.py -x images/test -l annotations/label_map.pbtxt -o annotations/test.record
