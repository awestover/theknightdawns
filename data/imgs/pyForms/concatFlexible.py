
from PIL import Image
import os

#  files = [
#          'mage_full.png',
#          'mageIdle.png',
#          'mageAttack.png'
#          ]
#  folder = "."
#  out_name = "mage_full.png"
#  imgs = [Image.open(os.path.join(folder, name)) for name in files]

img = Image.open("mage_sheet.png")

new_im = Image.new('RGBA', img.size)

new_im.paste(img.crop((0, 0, 80*6, 80*7)), (0,0))
new_im.paste(img.crop((0, 80*8, 80*6, 80*9)), (0,80*7))
new_im.paste(img.crop((0, 80*7, 80*6, 80*8)), (0,80*8))

#  new_im.paste(imgs[0], (0,0))
#  new_im.paste(imgs[1], (0,4*80))
#  new_im.paste(imgs[2], (0,5*80))
#  new_im.save(os.path.join(folder, out_name))
new_im.save("mage_sheet2.png")
new_im.show()



