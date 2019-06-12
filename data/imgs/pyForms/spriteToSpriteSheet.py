
from PIL import Image
import sys

name = ""
num_frames = 2
if len(sys.argv) == 2:
    name = sys.argv[1]
else:
    print("error, provide more args")
    sys.exit()

img = Image.open(name)
width, height = img.size
individual_width = width//num_frames
img_parts = []
for i in range(num_frames):
    img_parts.append(img.crop((i*individual_width, 0, (i+1)*individual_width, height)))

new_im = Image.new('RGBA', (width, height*4))

new_im.paste(img, (0,0))
new_im.paste(img.rotate(180), (0,height))
for i in range(num_frames):
    new_im.paste(img_parts[i].rotate(90), (i*individual_width, 2*height))
    new_im.paste(img_parts[i].rotate(270), (i*individual_width, 3*height))

new_im.save(name.replace(".", "_sheet."))

new_im.show()

