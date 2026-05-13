#!/usr/bin/env bash

for i in {1..1048576}; do
    echo "Running client iteration $i"
	./build/client
done
