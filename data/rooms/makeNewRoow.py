
import sys
import os

num_tiles = 32
newRoom = ""
try:
    newRoom = sys.argv[1]
except:
    print("input room as argument")
    sys.exit()

new_txt = ""
with open("rooms.txt", "r") as f:
    num_rooms = int(f.readline())
    new_txt += str(num_rooms+1)+"\n"
    for i in range(num_rooms):
        new_txt += f.readline().strip()+"\n"
new_txt+=newRoom

with open("rooms.txt", "w") as f:
    f.write(new_txt)

os.mkdir(newRoom)

exampleObjectsjson = [
{
	"pos": [18,15],
	"type": "dialogue",
	"body": {"title": "quest, part 1", "description":"This is the first quest"}
},
{
	"pos": [15,10],
	"type": "dialogue",
	"body": {"title": "quest, part 2", "description":"This is a follow up quest"}
},
{
	"pos": [10,5],
	"type": "teleporter",
	"body": {"newRoom": "startRoom", "newPos": [20,20]}
}
]
os.system("echo {} >> {}/objects.json".format(str(exampleObjectsjson), newRoom))

exampleObstacles = "1"*num_tiles + "\n" + ("1"+"0"*(num_tiles-2)+"1\n")*(num_tiles-2) + "1"*num_tiles 
os.system("echo \"{}\" >> {}/obstacles.txt".format(str(exampleObstacles), newRoom))

exampleDimensions = "{} {}".format(num_tiles, num_tiles); # tiles
os.system("echo {} >> {}/dimensions.txt".format(exampleDimensions, newRoom))


