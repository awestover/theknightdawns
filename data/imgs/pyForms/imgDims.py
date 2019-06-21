
from PIL import Image
import sys

file = ""
try:
    file = sys.argv[1]
except:
    print("error, didn't provide file arg")
    sys.exit()

im = Image.open(file)
print(im.size)

