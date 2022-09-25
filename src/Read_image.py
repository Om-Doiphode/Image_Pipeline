
#  Author: Om Doiphode
#  Filename: Read_image.py
#  Functions: NONE
#  Global Variable: NONE


from PIL import Image
import numpy as np
import sys

file = sys.argv[1]
raw_data = Image.open(file)
# Getting the pixel values of the image by converting the image into a numpy array
raw = np.array(raw_data)
# Saving the pixel values in a file
with open("PixelData.txt", "w") as f:
    np.savetxt(f, raw, "%i")
