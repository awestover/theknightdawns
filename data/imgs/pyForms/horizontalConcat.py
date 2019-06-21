
from PIL import Image
import sys
import os

prefix = ""
folder = ""
try:
    prefix = sys.argv[1]
    folder = sys.argv[2]
except:
    print("provide a prefix and a folder")
    sys.exit()

names = os.listdir(folder)
names = [ni for ni in names if prefix in ni]
names.sort()
print("horizontally concatentating {}".format(names))
imgs = [Image.open(os.path.join(folder, name)) for name in names]
width, height = imgs[0].size  # yeah they better all be the same size

new_im = Image.new('RGBA', (width*len(names), height))

for i in range(len(imgs)):
    new_im.paste(imgs[i], (i*width, 0))
new_im.save(os.path.join(folder, prefix+"_row.png"))
new_im.show()

