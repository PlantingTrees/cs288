#!/bin/bash

# filename=$1

# city_pattern=" ([a-z]+ [a-z]+( ,)?)( )?([a-z]+)?"

# year_extraction="(19[0-9]{1,2})|(20[0-9]{1,2})"
# current_year=2023
# declare -A name_age_table #store name along its age
# result=$(grep -E  "$city_pattern" "$filename")
# echo $result
# # #after the name_age table has been populated pipe the result into sort in desending order 
# # #print each name & age in the name_age table to the screen 
# # #take the a screen shot of the result and submit 
# # for key in "${!name_age_table[*]}";do
# #     age_value="${name_age_table[$key]}"
# #     echo "$key is $age_value"
# # done | sort -rn -k3





# #  echo "$line"
# #             if [[ $line =~ $year_extraction ]]; then
# #                     #capture the first and last name at  the start of the line. store in name
# #                     name="(^[a-z]+ [a-z]+)"
# #                     calculated_age=$current_year - $year_extraction
# #                     #append to the table
# #                     name_age_table[$name]=$calculated_age
                    
# #                 else    
# #                     echo "No date found on line"
# #             fi
# #         else    
# #             echo "No match"