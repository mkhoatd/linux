#!/bin/bash
tinh() {
    thuong=`echo "scale=5; $1/$2" | bc`
    echo $thuong
}

read -p "Nhap so a=" a
read -p "Nhap so b=" b

y=$(tinh $a $b)
echo $y
awk -vA="$y" 'BEGIN {printf "KET QUA = %.2f\n", A}'
exit 0