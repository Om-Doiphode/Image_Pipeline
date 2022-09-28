/*
*Author List: Om Doiphode
*Filename: Edges.cpp
*Functions: edgeDetect(matrix)
Here, matrix=vector<vector<double>>
*Global Variables: NONE
*/
#include <bits/stdc++.h>
#include "debayering.h"
#include "Conversion.h"
using namespace std;
using matrix = vector<vector<double>>;
/*
 * Function Name: edgeDetect
 * Input: R -> Red color channel (2D vector),
 *        G -> Green color channel (2D vector),
 *        B -> Blue Color channel (2D vector).
 * Output: returns the image which has its edges higlighted
 * Logic:
 *              |-1 0 1|            |-1 -2 -1|
 *              |-2 0 2|            | 0  0  0|
 *              |-1 0 1|            | 1  2  1|
 *              Vertical            Horizontal
 * When vertical filter is applied, vertical edges become more prominent while horizontal edges get more prominent on applying horizontal filter
 * Final image is obtained by the formula I =sqrt(Ix^2 + Iy^2), where Ix is the horizontal gradient while Iy is the vertical gradient.
 * Example Call: edgeDetect(R,G,B)
 */
matrix edgeDetect(matrix R, matrix G, matrix B)
{
    matrix kernel_X = {{-1, 0, 1},
                       {-2, 0, 2},
                       {-1, 0, 1}};
    matrix kernel_Y = {{-1, -2, -1},
                       {0, 0, 0},
                       {1, 2, 1}};

    matrix gray_image = cvtGray(R, G, B);
    matrix res = conv2D(gray_image, kernel_X, 8);
    matrix res2 = conv2D(gray_image, kernel_Y, 8);
    matrix final_image(gray_image.size(), vector<double>(gray_image[0].size(), 0));
    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[0].size(); j++)
        {
            final_image[i][j] = sqrt(pow(res[i][j], 2) + pow(res2[i][j], 2));
            if (final_image[i][j] > 0.05)
                final_image[i][j] = 1;
            else
                final_image[i][j] = 0;
        }
    }
    return final_image;
}