from PIL import Image
import numpy as np


file = input("Enter the file name (.tiff): ")
raw_data = Image.open(file)
raw = np.array(raw_data)
with open("PixelData.txt", "w") as f:
    np.savetxt(f, raw, "%i")
