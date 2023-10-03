#!/opt/homebrew/bin/bash

#get the file
filename=$1
#pattern to match on 
city_pattern="[[:space:]][a-zA-Z]+[[:space:]][a-zA-Z]+[[:space:]]?[a-zA-Z]+"
age_pattern="([0-9]+)-([0-9]+)-([0-9]+)"
name_pattern="(^[a-zA-z]+\s[a-zA-Z]+)"
#set the current year
current_year=2023
declare -A name_age_table
declare -a result_array
#the file passed is a valid file 
if [ -f $filename ];then
    while IFS= read -r line;do 
        if [[ $line =~ $city_pattern ]];then
            result_array+=("$line") 
        fi
    done < $filename
    else
        echo "not a valid file"
fi

for line in "${result_array[@]}";do
    #echo "$line"
    #apply the age_pattern to the line 
    if [[ $line =~ $age_pattern ]];then
        #extract the year from the user
        year="${BASH_REMATCH[1]}"
        #get the age of the user 
        age=$(( $current_year - $year ))
        name=$(echo "$line" | grep -E -o $name_pattern)
        #store the name and age in the associate array 
        name_age_table[$name]=$age
    fi

done

#now that we have the name and age populated in the name_age_table we can print using the key 
#I will be using a shortcut sort function to sort the item, effectively sort breaks the lines into column and since the age is on the 4th column 
#i will use k4,4 (to specify the column) -r is to sort in a descending order and n or -n is to ensure it sorts in numeric fashion.
for row in "${!name_age_table[@]}";do
    echo "$row is ${name_age_table["$row"]}"
done | sort -rn -k4,4