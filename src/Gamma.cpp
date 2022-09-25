/*
*Author List: Om Doiphode
*Filename: Gamma.cpp
*Functions: matrix gammaCorrection(matrix,double)
Here, matrix=vector<vector<double>>
*Global Variables: NONE
*/
#include <bits/stdc++.h>
using namespace std;
using matrix = vector<vector<double>>;
/*
 * Function Name: gammaCorrection
 * Input: image -> 2D vector (1 channel image),
 *        gamma -> value for gamma
 * Output: returns the gamma corrected image
 * Logic: Calculates the pixel value for gamma corrected image by the formula
 *          O=I^Y
 *        where O -> Gamma corrected image,
 *              I -> Intensity (Pixel value)
 *        If gamma<0, image will be darker
 *        If gamma>0, image will be brighter
 * Example Call: gammaCorrection(image,2);
 */
matrix gammaCorrection(matrix image, double gamma)
{
    matrix res(image.size(), vector<double>(image[0].size(), 0));
    double power = 1 / gamma;
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            res[i][j] = double(pow(image[i][j], power));
        }
    }
    return res;
}