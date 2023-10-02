#!/bin/bash

# Current year
current_year=2023

# Define a regular expression pattern for lines with multi-word cities
city_pattern="[[:alpha:]]+[[:space:]][[:alpha:]]+"

# Read input from the command line, which can be piped or redirected from a file
while IFS= read -r line; do
    # Check if the line matches the city pattern
    if [[ $line =~ $city_pattern ]]; then
        # Extract the date of birth using a regular expression
        if [[ $line =~ ([0-9]{4}-[0-9]{2}-[0-9]{2}) ]]; then
            dob="${BASH_REMATCH[1]}"
            # Calculate the age
            year_of_birth="${dob%%-*}"
            age=$((current_year - year_of_birth))
            
            # Extract the name
            name="${line%%,*}"
            
            # Print the name and age
            echo "$name is $age"
        fi
    fi
done
