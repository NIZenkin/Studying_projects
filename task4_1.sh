#!/bin/bash

for((i=1;i<=10;i++))
do
	sleep 10
	echo $i
done

echo $((i-1)) > res.txt
sleep 3600
