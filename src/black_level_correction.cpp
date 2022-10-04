/*
 * Author List: Kedar Dhamankar
 * Filename: black_level_correction.cpp
 * Functions: maxPixelvalue, blackLevelCorrection
 * Global Variables: matrix (2d vector)
 */

#include <bits/stdc++.h>
#include <debayering.h>

using namespace std;

using matrix = vector<vector<double>>;

/*
* Function Name: BlackLevelCorection
* Input: Passes image matrix
* Output: Returns the black level corrected image
* Logic: Image channel is run through a loop where each
         pixel is compared to the global threshold value
         and correction is applied accordingly
* Example Call: AutoExposure(image, Green_mean);
*/

matrix blackLevelCorrection(matrix image)
{
    double maxVal = maxPixelvalue(image);                         // Contains maximum pixel value of image matrix
    matrix res(image.size(), vector<double>(image[0].size(), 0)); // Corrected image matrix declared
    double glob_thresh_val = maxVal / 2;                          // stores global threshold value of image matrix
    for (int i = 0; i < image.size(); i++)                        // looping through image channel
    {
        for (int j = 0; j < image[0].size(); j++)
        { // Comparing each pixel value to global threshold value and applying BLC
            if (image[i][j] <= glob_thresh_val)
            {
                res[i][j] = image[i][j] - 0.001 * image[i][j];
            }
            else if (image[i][j] <= 0.55 * maxVal) // 0.5 < intensity <= 0.55
            {
                res[i][j] = image[i][j] - 0.25 * image[i][j];
            }
            else if (image[i][j] <= 0.59 * maxVal) // 0.55 < intensity <= 0.59
            {
                res[i][j] = image[i][j] - 0.20 * image[i][j];
            }
            else if (image[i][j] <= 0.63 * maxVal) // 0.59 < intensity <= 0.63
            {
                res[i][j] = image[i][j] - 0.15 * image[i][j];
            }
            else if (image[i][j] <= 0.65 * maxVal) // 0.63 < intensity <= 0.65
            {
                res[i][j] = image[i][j] - 0.10 * image[i][j];
            }
            else if (image[i][j] <= 0.66 * maxVal) // 0.65 < intensity <= 0.66
            {
                res[i][j] = image[i][j] - 0.06 * image[i][j];
            }
            else if (image[i][j] <= 0.67 * maxVal) // 0.66 < intensity <= 0.67
            {
                res[i][j] = image[i][j] - 0.03 * image[i][j];
            }
            else if (image[i][j] <= 0.68 * maxVal) // 0.67 < intensity <= 0.68
            {
                res[i][j] = image[i][j] - 0.01 * image[i][j];
            }
            else if (image[i][j] <= 0.69 * maxVal) // 0.68 < intensity <= 0.69
            {
                res[i][j] = image[i][j] - 0.005 * image[i][j];
            }
            else if (image[i][j] <= 0.70 * maxVal) // 0.69 < intensity <= 0.70
            {
                res[i][j] = image[i][j] - 0.001 * image[i][j];
            }
            else
            {
                res[i][j] = image[i][j];
            }
        }
    }
    return res; // Returns corrected image to the function
}