MODEL_NAME=$1
MODEL_PATH=$2
MODEL_URL=$3
mkdir -p $MODEL_PATH
curl -s -o "model.tar.gz" "$MODEL_URL"
tar -xf "model.tar.gz" -C $MODEL_PATH
rm "model.tar.gz"
cd $MODEL_PATH
mv * pretModel
mkdir -p thisModel/config
cp pretModel/pipeline.config thisModel/config/pipeline.config

