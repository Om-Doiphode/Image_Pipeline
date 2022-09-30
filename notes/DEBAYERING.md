
### Debayering

#### Color Filter Arrays

* It is an array of tiny color filters placed before
the image sensor array of a camera.
* The resolution of this array is the same as that
of the image sensor array.
* Each color filter may allow a different
wavelength of light to pass – this is pre-
determined during the camera design.
* The most common type of CFA is the Bayer
pattern which is shown below:
![Bayer pattern](https://upload.wikimedia.org/wikipedia/commons/thumb/3/37/Bayer_pattern_on_sensor.svg/220px-Bayer_pattern_on_sensor.svg.png)
![Profile/Cross section of sensor](https://upload.wikimedia.org/wikipedia/commons/thumb/1/1c/Bayer_pattern_on_sensor_profile.svg/350px-Bayer_pattern_on_sensor_profile.svg.png)

<i>Profile/Cross-section of sensor</i>
* The Bayer pattern collects information at red,
green, blue wavelengths only as shown above.
* The Bayer pattern uses twice the number of green
elements as compared to red or blue elements.
* This is because both the M and L cone cells of the retina are
sensitive to green light.
* The raw (uncompressed) output of the Bayer pattern is
called as the <b>Bayer pattern image</b> or the <b>mosaiced (*)
image.</b>
* The mosaiced image needs to be converted to a normal
RGB image by a process called color image <b>demosaicing.</b>



![](https://upload.wikimedia.org/wikipedia/commons/thumb/6/6d/Colorful_spring_garden_Bayer_%2B_RGB.png/240px-Colorful_spring_garden_Bayer_%2B_RGB.png)
1. Original scene
2. Output of a 120×80-pixel sensor with a Bayer filter
3. Output color-coded with Bayer filter colors
4. Reconstructed image after interpolating missing color information
5. Full RGB version at 120×80-pixels for comparison (e.g. as a film scan, Foveon or pixel shift image might appear)

### Demosaicing algorithm
* Demosaicing involves interpolation of missing
color values from nearby pixels.
* There exist a plethora of demosaicing algorithms.
* We will be seeing two algorithms here, <b>Bilinear interpolation</b> and its modified version, <b>Malvar-He-Cutler Linear Image demosaicing</b>

#### Bilinear Interpolation
* Bilinear interpolating is the easiest method we can use to demosaic a Bayer image. 
* The idea behind this method is that since there is a high probability that the value of a missed pixels has a similarity to the value of its existing adjacent pixels, we can interpolate the missed values in each channel by taking the average of its adjacent pixels. 
* In other words, we start from the red channel, and for any missed values, we take a look over its adjacent pixels and if they contain a value, we take their average and assign the calculated average to the missed pixel.


![](https://miro.medium.com/max/984/1*4SxAttPO_FssX09PEVhLrA.png)


As shown above, we can use the following equations to interpolate the values of Gx, Bx, and Rx:


![](https://miro.medium.com/max/486/1*TNCnRWqYMQ_YuTWkx_qT4w.gif)

![](https://miro.medium.com/max/486/1*Kg9RgQu5j5eFBPGS0JywpQ.gif)

![](https://miro.medium.com/max/492/1*Jz5gjvh1E-uE3KMFMzsJ5w.gif)


#### Malvar-He-Cutler Algorithm

* The idea behind high-quality interpolation is that for interpolating the missed pixels in each channel, it might not be accurate to use only the adjacent pixels located on the same channel. 
* In other words, for interpolating a green pixel such as Gx in Fig.2, we need to use the value of its adjacent green pixels as well as the value of the existing channel. 
* For example, if at the location of Gx, we have a red value, we have to use that value as well as the adjacent available green values. They called their method gradient correction interpolation.

* Finally, they came up with 8 different 5*5 filters. We need to convolve the filters to pixels that we want to interpolate.


* The method is derived as a modification of bilinear interpolation. Let R, G, B denote the red, green,
and blue channels. At a red or blue pixel location, the bilinear interpolation of the green component
is the average of its four axial neighbors,

^G<sup>bl</sup> (i, j) = <sup>1</sup>/<sub>4</sub>
(G(i − 1, j) + G(i + 1, j) + G(i, j − 1) + G(i, j + 1)).

* Bilinear interpolation of the red and blue components is similar, but using instead the four
diagonal neighbors.
* The visual quality of bilinear demosaicking is generally quite poor. Since the channels are in-
terpolated independently, the misalignments near edges produce strong color distortions and zipper
artifacts.
* To improve upon the quality of the bilinear method, Malvar, He, and Cutler follow the work of
Pei and Tam by adding Laplacian cross-channel corrections.
* Consider the case of finding G at an R or a B pixel.
* If the actual R value differs considerably from the linearly
interpolated R value, it means that there is a sharp luminance
change at that pixel.
* The green component at a red pixel
location is estimated as

G(i, j) = ˆG<sup>bl</sup> (i, j) + α∆<sub>R</sub>(i, j),

where ∆<sub>R</sub> is the discrete 5-point Laplacian of the red channel,

∆<sub>R</sub>(i, j) := R(i, j) − <sup>1</sup>/<sub>4</sub>
(R(i − 2, j) + R(i + 2, j) + R(i, j − 2) + R(i, j + 2)).

* To estimate a red component at a green pixel location,

ˆR(i, j) = ˆR<sup>bl</sup> (i, j) + β∆<sub>G</sub>(i, j)

where ∆<sub>G</sub> is a discrete 9-point Laplacian of the green channel.

* To estimate a red component at a blue pixel location,

ˆR(i, j) = ˆR<sup>bl</sup> (i, j) + γ∆<sub>B</sub> (i, j),

where ∆<sub>B</sub> is the discrete 5-point Laplacian of the blue channel. 
* By symmetry, blue components are
estimated in a manner similar to the estimation of the red components. These formulas are shown
in more detail in the next section.

* The parameters α, β and γ control the weight of the Laplacian correction terms. To set these
parameters optimally, the values producing the minimum mean squared error over the Kodak image
suite were computed. These values were then rounded to dyadic rationals to obtain

α = <sup>1</sup>/<sub>2</sub> , β = <sup>5</sup>/<sub>8</sub> , γ = <sup>3</sup>/<sub>4</sub>.

* The advantage of this rounding is that the filters may be efficiently implemented with integer
arithmetic and bitshifting. The filters approximate the optimal Wiener filters within 5% in terms of
mean squared error for a 5 × 5 support.
* The demosaicking is implemented by convolution with a set of linear filters. There are eight
different filters for interpolating the different color components at different locations. 
* For example, at a green pixel location in a red row, the red component is interpolated by

R(i, j) = <sup>1</sup>/<sub>8</sub>
( &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<sup>1</sup>/<sub>2</sub> G(i, j − 2)
  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;−G(i − 1, j − 1) &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;−G(i + 1, j − 1)

&nbsp;&nbsp;−G(i − 2, j) &nbsp;&nbsp;&nbsp;&nbsp;+&nbsp;&nbsp; 4R(i − 1, j) &nbsp;&nbsp;&nbsp;+&nbsp;&nbsp;&nbsp;&nbsp; 5G(i, j) &nbsp;&nbsp;&nbsp;+ &nbsp;&nbsp;&nbsp;&nbsp;4R(i + 1, j) &nbsp;&nbsp;+&nbsp;&nbsp; −G(i + 2, j)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;−G(i − 1, j + 1) &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;−G(i + 1, j + 1)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;+<sup>1</sup>/<sub>2</sub> G(i, j + 2)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ).

* The filters can be implemented using integer arithmetic. Suppose that the input CFA data is
given as a 2D integer array F (i, j), then the interpolation above can be implemented as

R(i, j) = ( F (i, j − 2) + F (i, j + 2)+
−2(F (i − 1, j − 1) + F (i + 1, j − 1) + F (i − 2, j) + F (i + 2, j) + F (i − 1, j + 1) + F (i + 1, j + 1))+
+8(F (i − 1, j) + F (i + 1, j))+
+10F (i, j) )/16,

and the division by 16 can be efficiently implemented by bitshifting. The other filters are implemented
similarly.

![5 x 5 Filters](https://miro.medium.com/max/982/1*lJg8EZlsLhK5FJLTgfVJeQ.png)

<i>5 x 5 linear filters</i>


![](g_at_b_r.png)

![](r_at_b.png)

![](r_at_g.png)

![](b_at_r.png)

![](r_at_g.png)