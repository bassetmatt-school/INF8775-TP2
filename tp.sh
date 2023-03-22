#!/bin/bash

######
# Script to run for the second TP of INF8775
#
# Designed to run with C++20, and bash as script language

help_function() {
    echo ""
    echo "Usage:"
    echo "  /bin/bash tp.sh <commands> [options]"
    echo ""
    echo "Commands (All mandatory):"
    echo "  -a <algorithm>    Specifies the algorithm used, can only take 3 values:"
    echo "                    'glouton', 'progdyn' or 'approx'."
    echo "  -e1 <path/to/e1>  Path to the file containing the points, can be"
    echo "                    absolute or relative."
    echo ""
    echo "Options:"
    echo "  -p                Shows the output of the algorithm by displaying the"
    echo "                    path in the terminal"
    echo "  -t                Shows the time taken by the algorithm to perform the"
    echo "                    operation. Displayed in ms without specifying the unit"
}

# Compilation
unset COMP SRC_FILES INC_FILES CPP_FLAGS CPP_STD OUT_FILE
COMP=g++
SRC_FILES="src/main.cpp src/algorithms.cpp src/structures.cpp src/utils.cpp"
INC_FILES="src/structures.hpp src/algorithms.hpp src/utils.hpp"
CPP_FLAGS="-O3 -Wall -Wextra -pedantic"
CPP_STD="c++20"
OUT_FILE="./bin/tp2"


compile() {
    $COMP $SRC_FILES -I"$INC_FILES" $CPP_FLAGS -std=$CPP_STD -o $OUT_FILE
}


## Parsing Command Line arguments
unset file p_flag t_flag algo
p_flag=0
t_flag=0
while getopts 'a:e:!h?pt' a
do
    case $a in
        a) algo=$OPTARG;;
        e) file=$OPTARG;;
        p) p_flag=1;;
        t) t_flag=1;;
        h) help_function;
        exit 0;;
    esac
done


# Checking if the file is provided
if [ -z $file ]; then
    echo "No file provided"
    help_function
    exit 1
fi
[[ ! -e $file ]] && echo "File '$file' doesn't exist" && exit 1

# Checks the algorithm used
if [ -z $algo ]; then
    echo "No algorithm provided"
    help_function
    exit 1
else
    if [ $algo != "glouton" ] &&
       [ $algo != "progdyn" ] &&
       [ $algo != "approx" ]; then
        echo "Wrong algorithm, '$algo' isn't a valid algorithm"
        help_function
        exit 1
    fi
fi

# Converts algo string into int recongnized by the c++ code
unset algo_code
[[ $algo = "glouton" ]] && algo_code=0
[[ $algo = "progdyn" ]] && algo_code=1
[[ $algo = "approx" ]]  && algo_code=2

# If the code isn't compiled, compiles it
mkdir -p bin;
if [ ! -e ./bin/tp2 ]; then
    compile
fi

# Execution
./bin/tp2 $file $algo_code $p_flag $t_flag
