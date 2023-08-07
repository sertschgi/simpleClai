#!/bin/bash

# Make sure to qmake and make it first.

buildDir=$1
sourceDir=$2
appName=$3
packagePath="$4"

if [[ -z $1 ]]; then
    echo "No arguments given: 1:buildDir not given, 2:sourceDir not given, 3:appName not given. 4:packagePath not required. exiting..."
    exit -1
elif [[ -z $2 ]]; then
    echo "To few arguments: 1: $buildDir, 2:sourceDir not given, 3:appName not given 4:packagePath not required. exiting..."
    exit -1
elif [[ -z $3 ]]; then
    echo "To few arguments: 1: $buildDir, 2:$sourceDir, 3:appName not given 4:packagePath not required. exiting..."
    exit -1
elif [[ -z $4 ]]; then
    echo "packagePath not set. Using ./package"
    packagePath="package"
fi



echo "buildDir:$buildDir, sourceDir:$sourceDir, appName:$appName"

cd $buildDir

destAppPath="$packagePath/$appName/usr/bin"
destScriptPath="$packagePath/$appName/etc/$appName/scripts"
destConfigPath="$packagePath/$appName/etc/$appName/config"
buidConfigPath="$packagePath/$appName/DEBIAN"

if [[ ! -d $destAppPath ]]; then
    mkdir -p $destAppPath
fi

if [[ ! -d $destScriptPath ]]; then
    mkdir -p $destScriptPath
fi

if [[ ! -d $destConfigPath ]]; then
    mkdir -p $destConfigPath
fi

if [[ ! -d $buidConfigPath ]]; then
    mkdir -p $buidConfigPath
fi

rm *o Makefile
mv $appName $destAppPath
cp -f $sourceDir/scripts/* $destScriptPath
cp -f $sourceDir/config/* $destConfigPath
cp -r -f $sourceDir/build_config/deb/DEBIAN/* $buidConfigPath

dpkg-deb --build "$packagePath/$appName"
