#!/bin/bash

# Read the filename from the command-line argument
filename="$1"

# Date pattern
date_pattern="([0-9]{2})[\.\/\-][0-9]{2}[\.\/\-][0-9]{4}"

# Declare an array to store the dates
declare -a result_array

# Read each line from the file
while IFS= read -r line; do
    # Use grep -E -o to find dates in the line and add them to the result_array
    items_on_each_line=$(echo "$line" | grep -E -o "$date_pattern")
    for item in $items_on_each_line; do
        result_array+=("$item")
    done
done < "$filename"

#append to the array
result_array=("${result_array[@]}")


# Get the size of the array
size_result_array="${#result_array[*]}"

# Check if the array is empty
if [ "$size_result_array" -eq 0 ]; then
    echo "Empty array size: 0"
else
    
    # Sort the dates in the result_array since thgere are multiple delimiters we translate to one delimter and traslate back
    sorted_array=($(printf '%s\n' "${result_array[@]}" | tr '/.-'  |sort -t| tr '/.-'  ))

    # Restore the original format and print the sorted dates
    for item in "${sorted_array[@]}"; do
        
        item="${item//-//}"
        item="${item////-}"
        item="${item//|/-}"
        
        echo "$item"
    done
fi