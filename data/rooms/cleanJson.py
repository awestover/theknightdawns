
import json
import sys

path = ""
try:
    path = sys.argv[1]
except:
    print("Please input a path")
    sys.exit()

with open(path, 'r') as f:
    data = json.load(f)

with open(path, 'w') as f:
    json.dump(data, f, indent=4)

