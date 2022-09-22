/*
*Author List: Om Doiphode, Kedar Dhamankar
*Filename: Conversion.cpp
*Functions: cvtGray(matrix),
            cvtBinary(matrix)
Here, matrix=vector<vector<double>>
*Global Variables: NONE
*/
#include <bits/stdc++.h>
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
 * Example Call: cvtBinary(image);
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
