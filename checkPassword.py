
import os
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
    print("INPUT username, password")
    sys.exit(0)

with open("data/users/{}.json".format(username),'r') as f:
    old_hash, salt = json.load(f)["passwordHash"].split(":")
    new_hash = hashlib.sha256(salt.encode() + password.strip().encode()).hexdigest()
    if new_hash == old_hash:
        sys.exit(1)
    else:
        sys.exit(2)

