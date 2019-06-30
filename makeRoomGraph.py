
import os
import json
from pprint import pprint

roomNames = []
roomObjectData = {}
with open("data/rooms/rooms.txt", 'r') as f:
    nrooms = int(f.readline())
    for i in range(nrooms): 
        roomNames.append(f.readline().strip())

teleporterCt = 0
for room in roomNames:
    roomObjectFile = os.path.join("data/rooms",room,"objects.json")
    with open(roomObjectFile, 'r') as f:
        roomObjectData[room] = []
        dataTmp = json.load(f)
        for val in dataTmp:
            if val["type"] in ["teleporter", "battlePortal", "antiBattlePortal"]:
                roomObjectData[room].append((teleporterCt, val))
                teleporterCt += 1

graph = [[0 for j in range(teleporterCt)] for i in range(teleporterCt)]

def taxicabDist(posA, posB):
    return abs(posA[0]-posB[0]) + abs(posA[1]-posB[1])

idxConversion = [{} for i in range(teleporterCt)]

## 0 means that a teleporter is not reachable from a teleporter (note: no self loops)
for roomName in roomObjectData:
    for curTeleporter in roomObjectData[roomName]:
        # if the teleporters are in the same room the distance between them is the length of the path between them within their common room
        for otherTeleporter in roomObjectData[roomName]:
            graph[curTeleporter[0]][otherTeleporter[0]] = taxicabDist(curTeleporter[1]["pos"], otherTeleporter[1]["pos"])
        # if the teleporters are not in the same room, then the distance from 
        for otherTeleporter in roomObjectData[curTeleporter[1]["body"]["newRoom"]]:
            graph[curTeleporter[0]][otherTeleporter[0]] = taxicabDist(curTeleporter[1]["body"]["newPos"], otherTeleporter[1]["pos"])
        idxConversion[curTeleporter[0]] = {"room": roomName, "id": curTeleporter[1]["id"], "pos":curTeleporter[1]["pos"]}

with open("data/rooms/graph.json", "w") as f:
    json.dump({"teleporterCt": teleporterCt, "graph": graph, "idxConversion": idxConversion}, f, indent=4)

