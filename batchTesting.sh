#! /bin/bash

test1="DLIST"
test2="SLIST"

taille=8
increment=2
tailleMax=10000

while [ $taille -le $tailleMax ]
do
    ./bin/prog $test1 $test2 -F $taille -v
    taille=$((taille * increment))
done


