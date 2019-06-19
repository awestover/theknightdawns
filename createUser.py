
import sys
import json
import uuid
import hashlib

username = ""
password = ""
try:
    username = sys.argv[1]
    password = sys.argv[2]
except:
    sys.exit(0)

salt = uuid.uuid4().hex
hashedPassword = hashlib.sha256(salt.encode() + password.strip().encode()).hexdigest() + ':' + salt

data = {
    "passwordHash": hashedPassword,
    "currentQuest":"null",
    "questProgress":[],
    "baseStats":{
        "health": 5
    },
    "inventory": []
}

# check that the username is valid (not duplicate) in the bash script before calling this!!!
with open("data/users/{}.json".format(username), 'w') as f:
    json.dump(data, f, indent=4)


