#!/bin/bash

dtTestVersion=1
dtName="test-dataset"

for dir in $HOME/.sclai/datasets/*/;
do
    if [[ "$dtName$dtTestVersion" == "$(basename $dir)" ]];
    then
        ((++dtTestVersion))
    fi
done

fullDtName=$dtName$dtTestVersion

echo $fullDtName

echo "--------------------| starting test 1 |--------------------"

if sclai create dataset -n $fullDtName -l dataset-test/labelmap.pbtxt -a dataset-test/train -m dataset-test/train;
then
    echo -e "Created dataset succesfully! -> \033[32mtest 1 successful\033[0m"
    test1="\033[32msucceded\033[0m"

else
    echo -e "Failed to create dataset! -> \033[31mtest 1 failed\033[0m"
    test1="\033[31mfailed\033[0m"
fi

echo "--------------------| test 1 completed |--------------------"



echo "--------------------| starting test 2 |--------------------"

fullPfName="test-profile$dtTestVersion"

if sclai create profile -n $fullPfName -f tensorflow -s object_detection
then
    echo -e "Created profile succesfully! -> \033[32mtest 2 successful\033[0m"
    test2="\033[32msucceded\033[0m"

else
    echo -e "Failed create the profile! -> \033[31mtest 2 failed\033[0m"
    test2="\033[31mfailed\033[0m"
fi

echo "--------------------| test 2 completed |--------------------"

echo "--------------------| starting test 3 |--------------------"

fullPjName="test-project$dtTestVersion"

if sclai create project -n $fullPjName -d $fullDtName -p $fullPfName
then
    echo -e "Created project succesfully! -> \033[32mtest 3 successful\033[0m"
    test3="\033[32msucceded\033[0m"

else
    echo -e "Failed to create the project! -> \033[31mtest 3 failed\033[0m"
    test3="\033[31mfailed\033[0m"
fi

echo "--------------------| test 3 completed |--------------------"


echo "--------------------| starting test 4 |--------------------"

fullModelName="test-model$dtTestVersion"

if sclai create model -n $fullModelName -p $fullPjName -m "CenterNet MobileNetV2 FPN"
then
    echo -e "Created model succesfully! -> \033[32mtest 4 successful\033[0m"
    test4="\033[32msucceded\033[0m"

else
    echo -e "Failed to create the model! -> \033[31mtest 4 failed\033[0m"
    test4="\033[31mfailed\033[0m"
fi

echo "--------------------| test 4 completed |--------------------"




echo "summary:"
echo -e "test1: |$test1|"
echo -e "test2: |$test2|"
echo -e "test1: |$test3|"
echo -e "test2: |$test4|"

