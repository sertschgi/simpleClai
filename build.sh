#!/bin/bash

qtFolder=$1
qtVersion=$2

realpath $qtFolder 2> /dev/null
if [ $? -eq 127 ]; then
    echo "Please specify the folder of your Qt-installation"
    exit -1
fi

realpath $qtVersion 2> /dev/null
if [ $? -eq 127 ]; then
    echo "Please specify the version of your Qt-installation"
    exit -1
fi


sudo chmod +x build_config/deb/*.sh

cmake -B build/release -D CMAKE_PREFIX_PATH=$qtFolder/$qtVersion/gcc_64/lib/cmake/Qt6
cmake --build 'build/release' --target all


bash build_config/deb/mkpkg-dfp.sh
