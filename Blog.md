# **Image Pipeline**
#### This blog is about our project in the Eklavya Mentorship Program by SRA VJTI 
#### And what you can see below is what we achieved by the end of this project

![Image Pipeline](/assets/intro.gif)
##### _You might be thinking that we just added colors to a B&W image huh? It's more than that ; )_

# About This Project

#### The image pipeline takes raw image from sensor and convert it to meaningful image. Several algorithms like debayering, auto exposure, auto-white balance, gamma correction, etc are implemented to construct a meaningful i.e. a processed image.
#### All algorithms will be implemented on a static raw image captured from a sensor.

### Domain explored through this project -
* Image Processing

## Aim
* The main aim of the project was to implement our own RAW Image Reader which applies Pre-Processing algorithms to a RAW image and display a processed image.

* Along with this, few Post-Processing algorithms are also applied to the image and thus few post processed images are displayed as well

## Technologies Used
1. OpenCV
1. C++
1. Python  (you can't really avoid this language, can you :) )

## Approach

#### First, convert the RAW image into a .tiff file which stores the CFA image with missing pixel values. Interpolate the missing pixel values by applying Debayering algorithms like the ones proposed by Malvar-He-Cutler and store the image in a 2d vector. Then furthermore algorithms like Auto White Balance, Auto Exposure, Color Correction, etc are applied to the image which is stored in the form of a vector, and finally, the processed image is displayed using OpenCV.

## Theory

### RAW Image
#### Raw data from an image sensor contains light intensity values captured from a scene, but these data are not intrinsically recognizable to the human eye.
#### Raw sensor data typically comes in the form of a Color Filter Array (CFA) where each pixel carries information about a single-color channel: red, green, or blue.
![RAW Image](/assets/raw.png)
#### The most common CFA pattern is the Bayer array. There are twice as many pixels that represent green light in a Bayer array image because the human eye is more sensitive to variation in shades of green and it is more closely correlated with the perception of light intensity of a scene.

### Color Filter Array
* It is an array of tiny color filters placed before the image sensor array of a camera.
* The resolution of this array is the same as that of the image sensor array.
* Each color filter may allow a different wavelength of light to pass
* This is predetermined during the camera design.
* The most common type of CFA is the Bayer pattern which is shown below: 
![Bayer Filter](/assets/CFA.png)

## Pre-Processing Algorithms

### Debayering

#### We applied two debayering algorithms in our image pipeline which were the one proposed by Malvar-He-Cutler and the other one being Bilinear Interpolation.
#### But we'll only be discussing only Malvar-He-Cutler algorithm here. You might be saying why? well duh, it's just better and gives better results
#### This algorithm is aka High-Quality Interpolation which is derived as a modification of Bilinear Interpolation
#### Algorithm -
* The idea behind high-quality interpolation is that for interpolating the missing pixels in each channel, it might not be accurate to use only the adjacent pixels located on the same channel.
* In other words, for interpolating a green pixel such as Gx in Fig we need to use the value of its adjacent green pixels as well as the value of the existing channel.
* For example, if at the location of Gx, we have a red value, we have to use that value as well as the adjacent available green values. They called their method gradient correction interpolation.
* Finally, they came up with 8 different 5*5 filters. We need to convolve the filters to pixels that we want to interpolate.
![Filters](/assets/Filters.png)

#### On applying the algorithm to a RAW image 
#### Voila! We get the following result
![Debayered Image](/assets/debayered.png)

### White Balance
* Sometimes subject appears to be yellow or blue because of the incorrect color temperature of the light in a scene.
* To reveal the color that we would see as humans, what we need is a reference point, something we know should be a certain color (or more accurately, a certain chromaticity). Then, we can rescale the R, G, B values of the pixel until it is that color.
* As it is usually possible to identify objects that should be white, we will find a pixel we know should be white (or gray), which we know should have RGB values all equal, and then we find the scaling factors necessary to force each channel's value to be equal.
* White Balance is the process of removing unrealistic color casts, so that objects which appear white in person are rendered white in your photo.

#### Result of White Balancing the image - 
![White Balanced Image](/assets/wb.png)

### Auto Exposure
* When too much or too less light strikes the image sensor, the image appears overexposed, washed out or underexposed, dark and lacking in details in different areas of the same image.
* Auto Exposure is applied to images so that such unevenness in differently exposed areas of an image are corrected.
* Image channel having normalized values in the range 0-1 is run through a loop where each pixel value is compared to the mean intensity value of the image and correction is applied accordingly
#### Result of Auto Exposing the image -
![Auto Exposed Image](/assets/image3.png)

### Gamma Correction
This is also the last one of the pre-processing algorithms just in case u got bored reading :P
#### So what is it anyways
* When twice the number of photons hit the sensor of a digital camera, it receives twice the signal (a linear relationship). 
* However, we perceive double the amount of light as only a fraction brighter (a non-linear relationship)
* Gamma correction or gamma is a nonlinear operation used to encode and decode luminance in an image

#### Result of Gamma Correction -
![Gamma Corrected Image](/assets/gamma.png)

#### So yeah that's it from our Image Pipeline for the Pre-Processing part, the results were good weren't they? :)

#### Here's one more beautiful (processed :P) image to make your day 
![](/assets/Processed.png)


## Post-Processing Algorithms
#### So let's move on to some Post-Processing algorithms now

## Color Conversion 
#### Let's play with the colors of the image first :)
### RGB → Grayscale -
#### Ahaa Grayscale, feelin' old yet?
![RGB to Gray](/assets/RGBtoGray.png)
#### Luminosity Method for conversion
* The best method is the luminosity method which successfully solves the problems of previous methods.
* Based on the observations, we should take a weighted average of the components. The contribution of blue to the final value should decrease, and the contribution of green should increase.
* After some experiments and more in-depth analysis, researchers have concluded in the equation below:

    `Grayscale = (0.3 * R + 0.59 * G + 0.11* B)/3`
* Here most weight is given to green-colored pixels as humans are said to perceive green light well.

### RGB → Binary -

* Binary images are images whose pixels have only two possible intensity values. They are normally displayed as black and white.
* Numerically, the two values are often 0 for black, and either 1 or 255 for white.
* Binary images are often produced by thresholding a grayscale or color image, in order to separate an object in the image from the background.

![RGB to Binary](/assets/RGBtoBinary.png)

### RGB → HSV -

* HSV – (hue, saturation, value), also known as HSB (hue, saturation, brightness), is often used by artists because it is often more natural to think about a color in terms of hue and saturation than in terms of additive or subtractive color components.
* HSV is a transformation of an RGB colorspace, and its components and colorimetry are relative to the RGB colorspace from which it was derived.

![RGB to HSV](/assets/RGBtoHSV.png)

#### Enough playing with the colors for now, let's look at some other algorithms

## Edge Detection
#### Not gonna explain this since it's pretty self-explanatory, jk here you go :P
#### An edge in an image is a significant local change in the image intensity. As the name suggests, edge detection is the process of detecting the edges in an image. We applied sobel edge detection here.
### Sobel Edge Detection -

* The Sobel operator performs a 2-D spatial gradient measurement on an image and so emphasizes regions of high spatial frequency that correspond to edges. Typically it is used to find the approximate absolute gradient magnitude at each point in an input grayscale image.
* In theory at least, the operator consists of a pair of 3×3 convolution kernels. One kernel is simply the transpose of other.
* These kernels are designed to respond maximally to edges running vertically and horizontally relative to the pixel grid, one kernel for each of the two perpendicular orientations.

![](/assets/edge4.png)