#! /bin/bash

test1="DLIST"
test2="SLIST"

taille=2
increment=2
tailleMax=1000

nbTest=10

echo "n;$test1;$test2;"

while [ $taille -le $tailleMax ]
do
    ./bin/prog $test1 $test2 -F $taille -v -C $nbTest
    taille=$((taille + increment))
done


