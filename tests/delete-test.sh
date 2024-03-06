#!/bin/bash

dtTestVersion=0
dtName="test-dataset"

for dir in $HOME/.sclai/datasets/*/;
do
    if [[ "$dtName$dtTestVersion" == "$(basename $dir)" ]];
    then
        ((++dtTestVersion))
    fi
done


echo "--------------------| starting test 1 |--------------------"

if sclai delete dataset -n $fullDtName
then
    echo -e "Deleted dataset succesfully! -> \033[32mtest 1 successful\033[0m"
    test1="\033[32msucceded\033[0m"

else
    echo -e "Failed to delete the dataset! -> \033[31mtest 1 failed\033[0m"
    test1="\033[31mfailed\033[0m"
fi

echo "--------------------| test 1 completed |--------------------"



echo "--------------------| starting test 2 |--------------------"

fullPfName="test-profile$dtTestVersion"

if sclai delete profile -n $fullPfName
then
    echo -e "Deleted profile succesfully! -> \033[32mtest 2 successful\033[0m"
    test2="\033[32msucceded\033[0m"

else
    echo -e "Failed to delete the profile! -> \033[31mtest 2 failed\033[0m"
    test2="\033[31mfailed\033[0m"
fi

echo "--------------------| test 2 completed |--------------------"

echo "--------------------| starting test 3 |--------------------"

fullPjName="test-project$dtTestVersion"

if sclai delete project -n $fullPjName
then
    echo -e "Deleted project succesfully! -> \033[32mtest 3 successful\033[0m"
    test3="\033[32msucceded\033[0m"

else
    echo -e "Failed to delete the project! -> \033[31mtest 3 failed\033[0m"
    test3="\033[31mfailed\033[0m"
fi

echo "--------------------| test 3 completed |--------------------"


echo "--------------------| starting test 4 |--------------------"

fullModelName="test-model$dtTestVersion"

if sclai delete model -n $fullModelName -p $fullPjName
then
    echo -e "Deleted model succesfully! -> \033[32mtest 4 successful\033[0m"
    test4="\033[32msucceded\033[0m"

else
    echo -e "Failed to delete the model! -> \033[31mtest 4 failed\033[0m"
    test4="\033[31mfailed\033[0m"
fi

echo "--------------------| test 4 completed |--------------------"




echo "summary:"
echo -e "test1: |$test1|"
echo -e "test2: |$test2|"
echo -e "test1: |$test3|"
echo -e "test2: |$test4|"
