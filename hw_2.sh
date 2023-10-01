#!/bin/bash
#read the files 
filename=$1
#date pattern 
date_pattern="([0-9]{2})[\.\/\-][0-9]{2}[\.\/\-][0-9]{4}"
#result result
declare -a result_array
#sorted array
declare -a sorted_array
#read each line from the file
while IFS= read -r line; do 
    items_on_each_line=$(echo "$line" | grep -E -o $date_pattern )
        for item in $items_on_each_line;do
            result_array+=($item)
        done
    
done < $filename


#get the size of array 
size_result_array="${#result_array[*]}"
sorted_array=($(for item in "${result_array[@]}"; do echo "$item"; done | sort ))

if [ $size_result_array -eq 0 ];then
    echo "empty array size: 0"
else
    for date in "${sorted_array[@]}"; do
    echo "$date"
done
fi