#!/opt/homebrew/bin/bash

#get the filenbame 
filename=$1
#capture the dates matching the regex
dates_captured="([0-9]+)[/.-]([0-9]+)[/.-](20[0-9]+)"
#holds the dirty date in an array
declare -a date_array
#holds the cleaned up date in this array
declare -A date_array_compressed
#hold the final sorted ddate on this array so it can be used as index to display the results of the sorted date 
# to the terminal. 
declare -a sorted_date_compressed
#chcek if file is valid and reads the lines of the files (date)
if [[ -f $filename ]];then
    while IFS= read -r line; do 
        date_array+=($(grep  -oE $dates_captured <<< "$line"))
    done < $filename
    else 
        echo "Not a real file"
fi
#capture every delimiter
delimiter_capture="([/.-])"
for date in ${date_array[@]};do
    if [[ $date =~ $delimiter_capture ]];then
        captured_delimiter=${BASH_REMATCH[1]}
        new_delimiter="/"
        #re[places the captured with the new delimiter
        stripped_date="${date//$captured_delimiter/$new_delimiter}"
        #store the cleaned yp dates as a key to the associtaive table as well as its dates
        date_array_compressed["$stripped_date"]=$date
    fi

done
#sort the cleaned up key usong sort 
sorted_date_compressed=($(echo "${!date_array_compressed[@]}" | tr ' ' '\n' | tr -d '\r' | sort -t '/' -k 3,3n -k 1,1n -k 2,2n))

#use the date from the sorted date to access original dates
for date in "${sorted_date_compressed[@]}";do
#print out the dates
    echo "${date_array_compressed[$date]}"
done
