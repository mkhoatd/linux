#!/bin/bash

hoanhao(){
    s=0
    i=1
    n=$1
    while [ $i -lt $n ]
    do
        k=$(($n%$i))
        if [[ $k -eq 0 ]]
        then
            s=$(($s+$i))
        fi
        i=$(($i+1))
    done
    if [ $s -eq $n ]
    then
        ktra=1
    else
        ktra=0
    fi
    return "$ktra"
}

read -p "Nhap so: " m
hoanhao $m

if [ $? -eq 1 ]
then
    echo "$m la so hoan hao"
else
    echo "$m khong la so hoan hao"
fi
exit 0