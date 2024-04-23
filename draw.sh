#!/bin/bash

make

# initialize the string
string=""

# create a buffer full of coordinates

for ((i = 0; i < 23; i++)); do
	for ((j = 0; j < 23; j++)); do
		string+="$i $j\n"
	done
done

# bomb the input with coordinates
echo -e "$string" | ./bovo
