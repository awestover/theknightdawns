
from PIL import Image
import os

files = [
        'mage_full.png',
        'mageIdle.png',
        'mageAttack.png'
        ]
folder = "."
out_name = "mage_full.png"
imgs = [Image.open(os.path.join(folder, name)) for name in files]

new_im = Image.new('RGBA', (80*6, 80*9))

new_im.paste(imgs[0], (0,0))
new_im.paste(imgs[1], (0,4*80))
new_im.paste(imgs[2], (0,5*80))
new_im.save(os.path.join(folder, out_name))
new_im.show()



