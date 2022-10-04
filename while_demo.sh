#!/bin/bash
secretcode=agent007
echo “Guess the code!”
echo “Enter your guess: \c” 
read yourguess
while [[ $secretcode != $yourguess ]] 
do
    echo “Good guess but wrong. Try again!” 
    echo “Enter your guess: \c”
    read yourguess
done
echo “Wow! You are a genius!!”
exit 0