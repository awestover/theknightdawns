
from PIL import Image
import sys

name = ""
num_frames = 6
if len(sys.argv) == 2:
    name = sys.argv[1]
else:
    print("error, provide more args")
    sys.exit()

img = Image.open(name)
width, height = img.size
print(width, height)
individual_width = width//num_frames
img_parts = []
for i in range(num_frames):
    img_parts.append(img.crop((i*individual_width, 0, (i+1)*individual_width, height)))

new_im = Image.new('RGBA', (width, height*2))

new_im.paste(img, (0,0))
for i in range(num_frames):
    tmpImg = img_parts[i].transpose(Image.FLIP_LEFT_RIGHT)
    new_im.paste(tmpImg, (i*individual_width, height))

new_im.save(name.replace(".", "_sheet."))

new_im.show()

