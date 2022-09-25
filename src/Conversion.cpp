/*
*Author List: Om Doiphode, Kedar Dhamankar
*Filename: Conversion.cpp
*Functions: matrix cvtGray(matrix),
            matirx cvtBinary(matrix),
            matrix rgb2hsv(matrix,matrix)
Here, matrix=vector<vector<double>>
*Global Variables: NONE
*/
#include <bits/stdc++.h>
#include "debayering.h"
#include "WB.h"
using namespace std;
using matrix = vector<vector<double>>;
/*
 * Function Name: cvtGray
 * Input: R -> Red color channel (2D vector),
 *        G -> Green color channel (2D vector),
 *        B -> Blue Color channel (2D vector).
 * Output: returns the grayscale image.
 * Logic: Converts the image to grayscale by the following formula (R+G+B)/3
 * Example Call: cvtGray(R,G,B)
 */
matrix cvtGray(matrix R, matrix G, matrix B)
{
    matrix res(R.size(), vector<double>(R[0].size(), 0));
    for (int i = 0; i < R.size(); i++)
    {
        for (int j = 0; j < R[0].size(); j++)
        {
            res[i][j] = float(R[i][j] + G[i][j] + B[i][j]) / 3;
        }
    }
    return res;
}
/*
 * Function Name: cvtBinary
 * Input: image -> grayscale Image (2D vector)
 * Output: returns the binary image
 * Logic: We set a threshold of 0.8, any pixel value less than the threshold will be set to 0 otherwise it will be set to 1.
 * Example Call: cvtBinary(image)
 */
matrix cvtBinary(matrix image)
{
    double threshold = 0.8;
    matrix res(image.size(), vector<double>(image[0].size(), 0));
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            if (image[i][j] < threshold)
            {
                res[i][j] = 0;
            }
            else
            {
                res[i][j] = 1;
            }
        }
    }
    return res;
}
/*
 * Function Name: rgb2hsv
 * Input: R -> red color channel (2D vector), G -> green color channel (2D vector), B -> blue color channel
 * Output: returns the image in HSV format (3D vector)
 * Logic:
    Hue calculation :
    if cmax and cmin equal 0, then h = 0
    if cmax equal r then compute h = (60 * ((g – b) / diff) + 360) % 360
    if cmax equal g then compute h = (60 * ((b – r) / diff) + 120) % 360
    if cmax equal b then compute h = (60 * ((r – g) / diff) + 240) % 360

   Saturation computation :
    if cmax = 0, then s = 0
    if cmax does not equal 0 then compute s = (diff/cmax)*100

   Value computation :
    v = cmax*100
 * Example Call: rgb2hsv(R,G,B)
 */
vector<vector<vector<double>>> rgb2hsv(matrix R, matrix G, matrix B)
{
    matrix H(R.size(), vector<double>(R[0].size(), 0));
    matrix S(R.size(), vector<double>(R[0].size(), 0));
    matrix V(R.size(), vector<double>(R[0].size(), 0));
    vector<vector<vector<double>>> hsv_image;
    for (int i = 0; i < R.size(); i++)
    {
        for (int j = 0; j < R[0].size(); j++)
        {
            double cmax = max(R[i][j], max(G[i][j], B[i][j]));
            double cmin = min(R[i][j], min(G[i][j], B[i][j]));
            double difference = cmax - cmin;
            // if cmax and cmax are equal then h = 0
            if (cmax == cmin)
            {
                H[i][j] = 0;
            }

            // if cmax equal r then compute h
            else if (cmax == R[i][j])
            {
                H[i][j] = fmod(60 * ((G[i][j] - B[i][j]) / difference) + 360, 360);
            }

            // if cmax equal g then compute h
            else if (cmax == G[i][j])
            {
                H[i][j] = fmod(60 * ((B[i][j] - R[i][j]) / difference) + 120, 360);
            }

            // if cmax equal b then compute h
            else if (cmax == B[i][j])
            {
                H[i][j] = fmod(60 * ((R[i][j] - G[i][j]) / difference) + 240, 360);
            }

            // if cmax equal zero
            if (cmax == 0)
            {
                S[i][j] = 0;
            }
            else
            {
                S[i][j] = (difference / cmax) * 100;
            }

            // compute v
            V[i][j] = cmax * 100;
        }
    }
    H = scale(H);
    S = scale(S);
    V = scale(V);
    hsv_image.push_back(H);
    hsv_image.push_back(S);
    hsv_image.push_back(V);
    return hsv_image;
}