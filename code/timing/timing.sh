#!/usr/bin/env bash

totaltime=0
rm -f tmp.asc
for times in `seq 100 1000 5000`
do
    for len in `seq 1000 10000 20000`
    do
        ELAPSED=`./timing $times $len | grep Used | awk -F ' ' '{print $2}'`
        let FLOP=times*len*2
        echo "$FLOP $ELAPSED" >> tmp.asc
    done
done

sort -n tmp.asc > results.asc
rm -f tmp.asc
