#!/bin/bash
# just exercise
# 2020/3/16
PATH=/home/zero/work
export PATH
#echo "Hello World! \a\n"

#read -p " 1 number: " firstnum
#read -p " 2 number: " secnum
#total=$((${firstnum}*${secnum}))
#echo "\ntotal ${firstnum}X${secnum} is ==> ${total}"
read -p ${1}
if [ "${1}" == "hello" ]; then #||[ "${yn}" == "y" ];then
	echo "hello"
elif [ "${1}" == "" ]; then
	echo "input a parameters, ex> {${0} someword}"
else 
	echo "the only parameter is 'hello', ex> {${0} hello}"
fi

#---find file--#
test -e /FILENAME && echo "exist" || echo "Not exist"
