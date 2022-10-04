#!/bin/bash
testArr=("Debbie" "Jamie" "John" "Kitty" "Kuhn" "Shah")
for people in ${testArr[@]}
do
    echo "Hello $people"
done
exit 0