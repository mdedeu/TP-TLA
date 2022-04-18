#!/bin/bash

cd bin && make clean && make && cd .. #compilation

for i in {1..15}
do
 cat programs/program${i} | bin/Compiler
 echo "----------------------"
 echo "Termine el programa ${i}"
 echo "----------------------"
done