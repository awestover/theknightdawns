#!/bin/bash
printf "******************************************\n"
printf "CREATE AN ACCOUNT\n"
printf "******************************************\n"
printf "Username: " 
read username
python3 checkUsername.py $username
usernameValid=$?
if [[ usernameValid -eq 1 ]]; then
	printf "INVALID USERNAME, username already exists\n"
	exit 1
elif [[ usernameValid -eq 0 ]]; then
	printf "INVALID USERNAME, empty field"
	exit 1
fi

printf "Password: "
read -s password
printf "\n"
printf "Input password again to verify spelling: "
read -s passwordAgain
printf "\n"
if [[ "$passwordAgain" == "$password" ]]
then
	printf "Welcome $username. I will create an account for you.\n"
	python3 createUser.py $username $password
	printf "Now you can login to your account\n"
	sh login.sh
else
	printf "Passwords don't match\n"
fi

