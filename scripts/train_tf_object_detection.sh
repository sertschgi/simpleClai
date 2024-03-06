#!/bin/bash

MODEL_PATH=$1
PROJECT_PATH=$2
PROFILE_PATH=$3
VENV_PATH=$4

SAI_APP_SCRIPTS_PATH=$5

BATCH_SIZE=$6

if [ -z $BATCH_SIZE ]; then
    BATCH_SIZE="1"
fi

BFLOAT16=$7

if [ -z $BFLOAT16 ]; then
    BFLOAT16="false"
fi


FINE_TUNE_CHECKPOINT="$MODEL_PATH/pretModel/checkpoint/ckpt-0"
LABEL_MAP_PATH="$PROJECT_PATH/annotations/label_map.pbtxt"
TRAIN_INPUT_PATH="$PROJECT_PATH/annotations/train.record"
TEST_INPUT_PATH="$PROJECT_PATH/annotations/test.record"

API_PATH="$PROFILE_PATH/api"
RESEARCH_PATH="$API_PATH/models/research"
OBJECT_DETECTION_PATH="$RESEARCH_PATH/object_detection"

MODEL_TRAIN_PATH="$MODEL_PATH/thisModel"
PIPELINE_CONF="$MODEL_TRAIN_PATH/config/pipeline.config"

eval "$(conda shell.bash hook)"
conda activate $VENV_PATH
source $VENV_PATH/etc/conda/activate.d/env_vars.sh

echo $LD_LIBRARY_PATH
export XLA_FLAGS="--xla_gpu_cuda_data_dir=$VENV_PATH/lib"

python $SAI_APP_SCRIPTS_PATH/configure_conf_file.py --config_file $PIPELINE_CONF --train_input_path $TRAIN_INPUT_PATH --eval_input_path $TEST_INPUT_PATH --checkpoint_path $FINE_TUNE_CHECKPOINT --batch_size $BATCH_SIZE --label_map $LABEL_MAP_PATH --bfloat16 $BFLOAT16


cd $OBJECT_DETECTION_PATH

python model_main_tf2.py --model_dir $MODEL_TRAIN_PATH --pipeline_config_path $PIPELINE_CONF
