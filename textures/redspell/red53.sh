#!/bin/bash

index=0

for file in *.*; do
    extension="${file##*.}"
    new_name="red${index}.${extension}"
    mv "$file" "$new_name"
    ((index++))
done
