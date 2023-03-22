#!/bin/bash
# Pour glouton et approx
for n in {"1000","5000","10000","50000","100000"}; do
    ./inst_gen.py -s $n -n 50
done

# Pour tous les algorithmes
for n in {"5","10","15","20","25"}; do
    ./inst_gen.py -s $n -n 50 -x DP
done
