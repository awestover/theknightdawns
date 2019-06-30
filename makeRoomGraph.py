
import os
import json
from pprint import pprint

roomNames = []
roomObjectData = {}
with open("data/rooms/rooms.txt", 'r') as f:
    n = int(f.readline())
    for i in range(n): 
        roomNames.append(f.readline().strip())
n = len(roomNames)

for room in roomNames:
    roomObjectFile = os.path.join("data/rooms",room,"objects.json")
    with open(roomObjectFile, 'r') as f:
        roomObjectData[room] = json.load(f)

graph = [[-1 if j != i else 0 for j in range(n)] for i in range(n)]

pprint(graph)

## SUPER IMPORTANT:
## aww crap
## if there are multiple teleporters into a room, then distance between rooms is not unique...
### hmm
## this is not a super straightforward Dijkstra's anymore...


