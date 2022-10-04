#!/bin/bash
echo " Use one of the following cc:"
echo " d or D: display date"
echo " l or L: To see the listing of file in your present working directory"
echo " w or W: To see who's logged in"
echo " q or Q: To quit" 
echo "Enter your option and hit <Enter>: \c"
read option
case "$option" in 
    d|D) date;;
    l|L) ls;;
    w|W) who;;
    q|Q) exit 0;;
    *) echo "Invalid option; try running the program again."; exit 1;;
esac
exit 0
