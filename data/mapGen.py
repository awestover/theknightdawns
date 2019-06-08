
fout = open("map1.txt", "w")

x = []
for i in range(0, 25): 
    tempstr = ""
    for j in range(0, 25): 
        tempstr+='0'
    fout.write(tempstr+"\n")
    x.append(tempstr)

print(x)
fout.close()

