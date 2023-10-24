#!/opt/homebrew/bin/bash

#get the filenbame 
filename=$1
#capture the dates matching the regex
dates_captured="([0-9]+)[/.-]([0-9]+)[/.-](20[0-9]+)"
declare -a date_array
declare -A date_array_compressed
declare -a sorted_date_compressed
if [[ -f $filename ]];then
    while IFS= read -r line; do 
        date_array+=($(grep  -oE $dates_captured <<< "$line"))
    done < $filename
    else 
        echo "Not a real file"
fi
delimiter_capture="([/.-])"
for date in ${date_array[@]};do
    if [[ $date =~ $delimiter_capture ]];then
        captured_delimiter=${BASH_REMATCH[1]}
        new_delimiter="/"
        stripped_date="${date//$captured_delimiter/$new_delimiter}"
        date_array_compressed["$stripped_date"]=$date
    fi

done

sorted_date_compressed=($(echo "${!date_array_compressed[@]}" | tr ' ' '\n' | tr -d '\r' | sort -t '/' -k 3,3n -k 1,1n -k 2,2n))


for date in "${sorted_date_compressed[@]}";do
    echo "${date_array_compressed[$date]}"
done