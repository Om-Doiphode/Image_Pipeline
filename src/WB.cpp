/*
 *Author List: Om Doiphode
 *Filename: WB.cpp
 *Functions: averageofPixels(matrix),
            scale(matrix, double, double),
            maxNumber(double, double, double),
            whiteBalance(matrix, double, double, double)
 Here, matrix=vector<vector<double>>
 *Global Variables: NONE
 */
#include <bits/stdc++.h>
#include "../include/debayering.h"
using namespace std;
using matrix = vector<vector<double>>;
/*
 * Function Name: averageOfPixels
 * Input: image -> 2D vector of image
 * Output: returns the mean of the pixel values
 * Logic: average=(sum of pixel values)/total number of pixel values
 * Example Call: averageOfPixels(image);
 */
double averageOfPixels(matrix image)
{
    double average, sum = 0;
    int count = 0;
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            sum += image[i][j];
            count++;
        }
    }
    return (sum / count);
}

/*
 * Function Name: scale
 * Input: image --> single channel image,
 *        a, b --> range of values over which the image needs to be normalised, default is [0,1]
 * Output: returns the largest number of the three numbers
 * Logic:
The linear normalization of a digital image is performed according to
the formula
Output_channel = 255 * (Input_channel - min) / (max-min)
 * Example Call: scale(image);
 *
 */
matrix scale(matrix image, double a = 0, double b = 1)
{
    int maxELement = maxEle(image), minElement = minEle(image);
    matrix result(image.size(), vector<double>(image[0].size(), 0));
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            result[i][j] = (double)((image[i][j] - (maxELement + minElement) / 2.0) / (maxELement - minElement));
            result[i][j] = (double)(result[i][j] * (b - a) + (b + a) / 2.0);
        }
    }
    return result;
}
/*
 * Function Name: maxNumber
 * Input: a,b,c-> three numbers from which the max number needs to be found out
 * Output: returns the largest number of the three numbers
 * Logic: If the first number is greater than second and third number then return the first number else if the second number is greater than first and third number then return second number otherwise return third number
 * Example Call: maxNumber(5,2,10);
 *
 */
double maxNumber(double a, double b, double c)
{
    if (a >= b && a >= c)
        return a;
    if (b >= a && b >= c)
        return b;
    return c;
}
/*
* Function Name: whiteBalance
* Input:image -> 2D vector of images,
        avgRed-> average of red pixel values,
        avgGreen-> average of green pixel values,
        avgBlue -> average of blue pixel values.
* Output: returns the normalised image
* Logic: Uses the Gray World Algorithm
        produces an estimate of illumination by computing the mean of each channel of the image.
* Example Call: whiteBalance(image,34,32,34);
*
*/
matrix whiteBalance(matrix image, double avgRed, double avgGreen, double avgBlue)
{
    double avgi = averageOfPixels(image);
    double ri = maxNumber(avgRed, avgBlue, avgGreen) / (double)avgi;
    return scale(image, 0, ri);
}