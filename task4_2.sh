#!/bin/bash


for((i=1;i<=3;i++))
do
	j=$(pidof 'sleep')
	kill -9 "$j"
       	echo "$j Процесс убит"
done
