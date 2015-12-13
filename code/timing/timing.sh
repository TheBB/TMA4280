#!/usr/bin/env bash

totaltime=0
rm -f tmp.asc
for ntimes in `seq 100 1000 5000`
do
    for len in `seq 1000 10000 20000`
    do
        ELAPSED=`./timing $ntimes $len | grep Used | awk -F ' ' '{print $2}'`
        let FLOP=ntimes*len*2
        echo "$FLOP $ELAPSED" >> tmp.asc
    done
done

sort -n tmp.asc > results.asc
rm -f tmp.asc
