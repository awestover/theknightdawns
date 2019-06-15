
import os
import sys

username = ""
try:
    username = sys.argv[1]
except:
    sys.exit(0) # error

names = os.listdir("data/users")
names = [name.replace(".json","") for name in names]
if username in names: 
    sys.exit(1) # repeat name
else:
    sys.exit(2) # unique name
