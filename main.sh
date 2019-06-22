#!/bin/bash
printf """
 _        _       _________ _______          _________ ______   _______           _       
| \    /\( (    /|\__   __/(  ____ \|\     /|\__   __/(  __  \ (  ___  )|\     /|( (    /|
|  \  / /|  \  ( |   ) (   | (    \/| )   ( |   ) (   | (  \  )| (   ) || )   ( ||  \  ( |
|  (_/ / |   \ | |   | |   | |      | (___) |   | |   | |   ) || (___) || | _ | ||   \ | |
|   _ (  | (\ \) |   | |   | | ____ |  ___  |   | |   | |   | ||  ___  || |( )| || (\ \) |
|  ( \ \ | | \   |   | |   | | \_  )| (   ) |   | |   | |   ) || (   ) || || || || | \   |
|  /  \ \| )  \  |___) (___| (___) || )   ( |   | |   | (__/  )| )   ( || () () || )  \  |
|_/    \/|/    )_)\_______/(_______)|/     \|   )_(   (______/ |/     \|(_______)|/    )_)
"""

PS3="ENTER:"
 
# set shuttle list
select action in createAccount login howToPlay
do
	case $action in
		login)
			break;
			;;
		createAccount)
			break;
			;;
		howToPlay)
			echo "awsd to move. Follow the arrow to complete quests. In the process you will sometimes have to fight mages"
			;;
		*)		
			echo "Error: Invalid option (choose from {1,2,3})"
			;;		
	esac
done

case $action in
	login)
		sh login.sh;
		;;
	createAccount)
		sh createUser.sh; 
		;;
	*) 
		echo "come again soon"
		;;
esac

