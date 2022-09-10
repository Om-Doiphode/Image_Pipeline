import cv2 as cv
import numpy as np

image_r = []
image_g = []
image_b = []
image_r1 = []
image_g1 = []
image_b1 = []
height = 480
width = 640


with open(r"Red.txt", "r") as f:
    for line in f:
        for word in line.split():
            image_r.append(float(word))
image_array_r = np.array(image_r).reshape(height, width)


with open(r"Green.txt", "r") as f:
    for line in f:
        for word in line.split():
            image_g.append(float(word))
image_array_g = np.array(image_g).reshape(height, width)


with open(r"Blue.txt", "r") as f:
    for line in f:
        for word in line.split():
            image_b.append(float(word))
image_array_b = np.array(image_b).reshape(height, width)


with open(r"Red1.txt", "r") as f:
    for line in f:
        for word in line.split():
            image_r1.append(float(word))
image_array_r1 = np.array(image_r1).reshape(height, width)


with open(r"Green1.txt", "r") as f:
    for line in f:
        for word in line.split():
            image_g1.append(float(word))
image_array_g1 = np.array(image_g1).reshape(height, width)


with open(r"Blue1.txt", "r") as f:
    for line in f:
        for word in line.split():
            image_b1.append(float(word))
image_array_b1 = np.array(image_b1).reshape(height, width)


final_image = np.array(                                                    #Original Image
    np.dstack([image_array_r, image_array_g, image_array_b]))
final_image1 = np.array(                                                   #BLC Image
    np.dstack([image_array_r1, image_array_g1, image_array_b1]))

cv.imshow("Debayered+Gamma+WhiteB", final_image)
cv.imshow("BLC", final_image1)
cv.waitKey(0)