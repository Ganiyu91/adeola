#!/bin/bash
echo "start compile"
gcc main1.c buffered_queue.c -o main1 -lpthread -I.
gcc main2.c buffered_queue.c -o main2 -lpthread -I.
gcc main3.c buffered_queue.c -o main3 -lpthread -I.
gcc main4.c buffered_queue.c -o main4 -lpthread -I.
echo "compile complete"
echo "test start"
echo "*********main1***********" > result
./main1 >> result
echo "*********main2***********" >> result
./main2 >> result
echo "********main3************" >> result
./main3 >> result
echo "********main4************" >> result
./main4 >> result
echo "end test"
cat result

