#!/bin/bash
printf "******************************************\n"
printf "LOGIN\n"
printf "******************************************\n"
printf "Username: " 
read username
python3 checkUsername.py $username
usernameValid=$?
if [[ usernameValid -eq 2 ]]; then
	printf "INVALID USERNAME, please register an acount or spell your username correctly\n"
	exit 1
elif [[ usernameValid -eq 0 ]]; then
	printf "INVALID USERNAME, empty field"
	exit 1
fi

totalTries=3

for (( i = 0; i < $totalTries; i++ )); do
	printf "Password: "
	read -s password
	printf "\n"
	python3 checkPassword.py $username $password
	passwordValid=$?
	if [[ passwordValid -ne 1 ]]; then
		triesLeft=$(expr $totalTries - 1 - $i)
		printf "Incorrect password, try again ($triesLeft tries left)\n"
	else
		printf "Welcome back $username \n"
		printf "Starting the game\n"
		make
		./main $username
		break;
	fi
done

