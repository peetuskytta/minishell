#!/bin/bash

NBR=1000

while [ $NBR -ne 0 ]
do
	echo -ne '\n' | w
	NBR=$(( $NBR - 1))
	printf $NBR
done