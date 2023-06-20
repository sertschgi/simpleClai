# run with higher permissions! else it will not work

REQUIRED_TF_VERSION=2.12.*
REQUIRED_CUDA_VERSION="11.8.0"
REQUIRED_CUDNN_VERSION="8.6.0.163"

API_PATH="$PROFILE_PATH/api"
RESEARCH_PATH="$API_PATH/models/research"
OBJECT_DETECTION_PATH="$RESEARCH_PATH/object_detection"

NAME=$1

PROFILE_PATH="$SA_PROFILE_PATH/$name"
mkdir $PROFILE_PATH

if ! command -v curl >/dev/null 2>&1; then
    sudo apt install curl
fi

if ! command -v conda >/dev/null 2>&1; then
    echo "Anaconda not installed. Installing..."

    NEWEST="Anaconda3-$(curl -s https://repo.anaconda.com/archive/ | grep -Eo "Anaconda3-[0-9]+\.[0-9]+(-[0-9]+)?-Linux-x86_64\.sh" | grep -Eo "[0-9]+\.[0-9]+(-[0-9]+)?" | sort -rn | head -n 1)-Linux-x86_64.sh"
    INSTALL_DIR="/opt/anaconda" # <-- no permission to write -> elevated permissions

    curl -O "https://repo.anaconda.com/archive/$NEWEST"
    bash $NEWEST -b -p $INSTALL_DIR

    echo "export PATH=$INSTALL_DIR/bin:$PATH" >> ~/.bashrc

    rm $NEWEST
    source ~/.bashrc

    conda --version
fi

ENV_PATH="$API_PATH/sa_$NAME"

conda create -p $ENV_PATH pip python=3.9
conda activate "sa_$NAME"

cuda_version=$(nvcc --version | grep "release" | awk '{print $6}' | cut -d ',' -f1)

if [ "$cuda_version" == "$REQUIRED_CUDA_VERSION" ]; then
    conda install -c conda-forge cudatoolkit=$REQUIRED_CUDA_VERSION
    python3 -m pip install nvidia-cudnn-cu11==$REQUIRED_CUDNN_VERSION tensorflow==$REQUIRED_TF_VERSION
fi

mkdir -p $ENV_PATH/etc/conda/activate.d
echo 'CUDNN_PATH=$(dirname $(python -c "import nvidia.cudnn;print(nvidia.cudnn.__file__)"))' >> $ENV_PATH/etc/conda/activate.d/env_vars.sh
echo 'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CONDA_PREFIX/lib/:$CUDNN_PATH/lib' >> $ENV_PATH/etc/conda/activate.d/env_vars.sh
source $ENV_PATH/etc/conda/activate.d/env_vars.sh

if ! command -v git >/dev/null 2>&1; then
    sudo apt install git
fi

if ! command -v protoc --version >/dev/null 2>&1; then
    python3 -m pip install protobuf
fi

git clone https://github.com/tensorflow/models.git $API_PATH

cd $RESEARCH_PATH
protoc "$OBJECT_DETECTION_PATH/protos/*.proto" --python_out=.
cp "$OBJECT_DETECTION_PATH/packages/tf2/setup.py" .
python -m pip install .





