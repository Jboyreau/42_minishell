{ df --total -h | grep 'total' | sed -nE 's/total *[0-9]*[A-Z] *//p' | sed -nE 's/[A-Z] +.+//p' ; 
df --total -h | grep 'total' | awk {'print "/" $2'} ; 
df --total -h | grep 'total' | awk {'printf(" (%s)"), $5'} ; } | tr -d "\n"
printf "\n"
