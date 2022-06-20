#!/bin/bash

cd bin && make clean && make && cd .. #compilation
start=1
end=15
if [ "$1" == "accepted" ]; then
    start=1;
    end=10;
fi

if [ "$1" == "notaccepted" ]; then
    start=11;
    end=15;
fi
    
for (( i=$start; i<= $end; i++ ))
do
        cat programs/program${i} | bin/Compiler;
        echo "----------------------";
        echo "Termine el programa ${i}";
        echo "----------------------";
done
