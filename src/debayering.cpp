/*
*Author List: Om Doiphode, Kedar Dhamankar
*Filename: debayering.cpp
*Functions: minELe(matrix),
            maxEle(matrix),
            conv2D(matrix),
            G_at_B_R(matrix),matrix RB_at_G_in_RBrow_BRcol(matrix),
            matrix RB_at_G_in_BRrow_RBcol(matrix),
            matrix RB_at_BR(matrix),
            vector<vector<vector<double>>> autoAdjust(matrix, matrix, matrix, int, int),
            vector<vector<vector<double>>> debayering(matrix, int, int)
Here, matrix=vector<vector<double>>
*Global Variables: NONE
*/
#include <bits/stdc++.h>
#include "color_space_conversion.h"
#include "auto_white_balance.h"
#include "conversion.h"
using namespace std;
using matrix = vector<vector<double>>;
/*
 * Function Name: minEle
 * Input: image -> 2D vector (single channel)
 * Output: returns the min pixel values in an image
 * Logic: Computes the minimum element in a particular row and then stored in a variable minEleInRow. \
 *        Result contains the maximum possible element.
 *        The result is then compared with minEleInRow and whichever is minimum, that value is returned.
 * Example Call: minEle(image)
 */
double minEle(matrix image)
{
    double result = std::numeric_limits<int>::max();
    for (const auto &row : image)
    {
        double minElemInRow = *std::min_element(row.begin(), row.end());
        result = std::min(result, minElemInRow);
    }
    return result;
}
/*
 * Function Name: maxEle
 * Input: image -> 2D vector (single channel)
 * Output: returns the max pixel values in an image
 * Logic: Computes the maximum element in a particular row and then stored in a variable maxEleInRow.
 *        Result contains the minimum possible element.
 *        The result is then compared with maxEleInRow and whichever is maximum, that value is returned.
 * Example Call: maxEle(image)
 */
double maxEle(matrix image)
{
    double result = std::numeric_limits<int>::min();
    for (const auto &row : image)
    {
        double maxElemInRow = *std::max_element(row.begin(), row.end());
        result = std::max(result, maxElemInRow);
    }
    return result;
}

/*
 * Function Name: conv2D
 * Input: image -> 2D vector (single channel), kernal -> mask (2D vector)
 * Output: returns the image which is convoluted with the mask (kernel)
 * Example Call: conv2D(image,kernel)
 */
matrix conv2D(matrix img, matrix kernal, int n = 8)
{
    int out_h = img.size() - kernal.size() + 1;       // Height of the output image
    int out_w = img[0].size() - kernal[0].size() + 1; // Width of the output image
    matrix ret(out_h, vector<double>(out_w, 0));      // Output image of size (width x height) filled with zeros
    for (int i = 0; i < out_h; i++)
    {
        for (int j = 0; j < out_w; j++)
        {
            // compute ret[i][j]
            for (int muli = 0; muli < kernal.size(); muli++)
            {
                for (int mulj = 0; mulj < kernal[0].size(); mulj++)
                {
                    /* By skipping 0 multiplcation, time increased from 376ms to 252ms */
                    if (img[i + muli][j + mulj] == 0 || kernal[muli][mulj] == 0)
                        continue;
                    ret[i][j] += (img[i + muli][j + mulj] * kernal[muli][mulj]) / n;
                }
            }
        }
        cout << "\r [" << ceil(i * 100 / out_h) << '%' << "] ";
    }
    cout << endl;
    return ret;
}

/*
 * Function Name: G_at_B_R
 * Input: image -> 2D vector (single channel)
 * Output: Computes the contribution of green component at Blue and Red Pixels
 * Example Call: G_at_BR(image)
 */
matrix G_at_BR(matrix &image)
{
    matrix kernel = {
        {0.0, 0.0, -1.0, 0.0, 0.0},
        {0.0, 0.0, 2.0, 0.0, 0.0},
        {-1.0, 2.0, 4.0, 2.0, -1.0},
        {0.0, 0.0, 2.0, 0.0, 0.0},
        {0.0, 0.0, -1.0, 0.0, 0.0}};
    return conv2D(image, kernel);
}

/*
 * Function Name: RB_at_G_in_RBrow_BRcol
 * Input: image -> 2D vector (single channel)
 * Output: Computes the contribution of red pixel at green in R row and B column
 *         and also that of blue pixel at green pixel in B row and R column.
 * Example Call: RB_at_G_in_RBrow_BRcol(image)
 */
matrix RB_at_G_in_RBrow_BRcol(matrix &image)
{
    matrix kernel = {{0, 0, 0.5, 0, 0},
                     {0, -1, 0, -1, 0},
                     {-1, 4, 5, 4, -1},
                     {0, -1, 0, -1, 0},
                     {0, 0, 0.5, 0, 0}};
    return conv2D(image, kernel);
}

/*
 * Function Name: RB_at_G_in_BRrow_RBcol
 * Input: image -> 2D vector (single channel)
 * Output: Computes the contribution of blue pixel at green in B row and R column
 *         and also that of blue pixel at green pixel in R row and B column.
 * Example Call: RB_at_G_in_BRrow_RBcol(image)
 */
matrix RB_at_G_in_BRrow_RBcol(matrix &image)
{
    matrix kernel = {{0, 0, -1, 0, 0},
                     {0, -1, 4, -1, 0},
                     {0.5, 0, 5, 0, 0.5},
                     {0, -1, 4, -1, 0},
                     {0, 0, -1, 0, 0}};
    return conv2D(image, kernel);
}

/*
 * Function Name: RB_at_BR
 * Input: image -> 2D vector (single channel)
 * Output: Computes the contribution of red pixel at blue in B row and B column
 *         and also that of blue pixel at red pixel in R row and R column.
 * Example Call: RB_at_BR(image)
 */
matrix RB_at_BR(matrix &image)
{
    matrix kernel = {{0, 0, -1.5, 0, 0},
                     {0, 2, 0, 2, 0},
                     {-1.5, 0, 6, 0, -1.5},
                     {0, 2, 0, 2, 0},
                     {0, 0, -1.5, 0, 0}};
    return conv2D(image, kernel);
}

vector<vector<vector<double>>> autoAdjust(matrix R, matrix G, matrix B, int height, int width)
{
    vector<vector<vector<double>>> new_image;

    matrix O_R(height, vector<double>(width, 0));
    matrix O_G(height, vector<double>(width, 0));
    matrix O_B(height, vector<double>(width, 0));

    // calculate stats
    double alow = minEle(R);
    double ahigh = maxEle(R);
    double amax = 255;
    double amin = 0;

    // access each pixel, and auto adjust
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double a = R[i][j];
            O_R[i][j] = amin + (a - alow) * ((amax - amin) / (ahigh - alow));
        }
    }
    alow = minEle(G);
    ahigh = maxEle(G);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double a = G[i][j];
            O_G[i][j] = amin + (a - alow) * ((amax - amin) / (ahigh - alow));
        }
    }
    alow = minEle(B);
    ahigh = maxEle(B);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double a = B[i][j];
            O_B[i][j] = amin + (a - alow) * ((amax - amin) / (ahigh - alow));
        }
    }
    new_image.push_back(O_R);
    new_image.push_back(O_G);
    new_image.push_back(O_B);
    return new_image;
}

/*
 * Function Name: debayering
 * Input: image -> 2D vector (single channel)
 *        height -> height of the input image
 *        width -> width of the input image
 * Output: Returns the debayered image
 * Logic: Malvar He Cutler Algorithm
 * Example Call: debayering(image,640,480)
 */
vector<vector<vector<double>>> debayering(matrix image, int height, int width)
{
    cout << "Scaling process initiated..." << endl;
    image = scale(image);
    cout << "Scaling done" << endl;
    matrix R(height, vector<double>(width, 0));
    matrix G(height, vector<double>(width, 0));
    matrix B(height, vector<double>(width, 0));
    cout << "Debayering process initiated..." << endl;
    // Copying data that doesn't need interpolation
    int i1 = 0;
    for (int i = 2; i < height + 2; i++)
    {
        int j1 = 0;
        for (int j = 2; j < width + 2; j++)
        {
            if (i % 2 == 0 && j % 2 == 0)
            {
                R[i1][j1] = image[i][j];
            }
            j1++;
        }
        i1++;
    }
    i1 = 0;
    for (int i = 2; i < height + 2; i++)
    {
        int j1 = 0;
        for (int j = 2; j < width + 2; j++)
        {
            if ((i + j) % 2 == 1)
            {
                G[i1][j1] = image[i][j];
            }
            j1++;
        }
        i1++;
    }
    i1 = 0;
    for (int i = 2; i < height + 2; i++)
    {
        int j1 = 0;
        for (int j = 2; j < width + 2; j++)
        {
            if (i % 2 == 1 && j % 2 == 1)
            {
                B[i1][j1] = image[i][j];
            }
            j1++;
        }
        i1++;
    }

    // Fill in the G data at the B/R locations
    cout << "First convolution layer: " << endl;
    matrix tmp = G_at_BR(image);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i % 2 == 0 && j % 2 == 0)
            {
                G[i][j] = tmp[i][j];
            }
            else if (i % 2 == 1 && j % 2 == 1)
            {
                G[i][j] = tmp[i][j];
            }
        }
    }

    // Fill in B/R data
    cout << "Second convolution layer: " << endl;
    matrix tmp2 = RB_at_G_in_BRrow_RBcol(image);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i % 2 == 0 && j % 2 == 1)
            {
                B[i][j] = tmp2[i][j];
            }
            else if (i % 2 == 1 && j % 2 == 0)
            {
                R[i][j] = tmp2[i][j];
            }
        }
    }
    cout << "Third convolution layer: " << endl;
    matrix tmp3 = RB_at_G_in_RBrow_BRcol(image);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i % 2 == 1 && j % 2 == 0)
            {
                B[i][j] = tmp3[i][j];
            }
            else if (i % 2 == 0 && j % 2 == 1)
            {
                R[i][j] = tmp3[i][j];
            }
        }
    }
    cout << "Fourth convolution layer: " << endl;
    matrix tmp4 = RB_at_BR(image);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i % 2 == 0 && j % 2 == 0)
            {
                B[i][j] = tmp4[i][j];
            }
            if (i % 2 == 1 && j % 2 == 1)
            {
                R[i][j] = tmp4[i][j];
            }
        }
    }
    vector<vector<vector<double>>> debayered_image;

    // RGB to sRGB
    vector<vector<vector<double>>> colorCorrectedImage = ColorConv(R, G, B);

    // Making a 3D image
    debayered_image.push_back(colorCorrectedImage[0]);
    debayered_image.push_back(colorCorrectedImage[1]);
    debayered_image.push_back(colorCorrectedImage[2]);
    cout << "Debayering done" << endl;
    return debayered_image;
}

/*
* Function Name: maxPixelvalue
* Input: Passes 2d image vector of whose maximum pixel value is to be found
* Output: Returns the maximum pixel value of the image matrix
* Logic: Loops through the matrix and checks if each value is greater than maxVal at each iteration
         If yes, then that value is made the maxVal
* Example Call: maxPixelValue(image);
*/
double maxPixelvalue(matrix image)
{
    double maxVal = image[0][0];
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            if (image[i][j] > maxVal)
                maxVal = image[i][j];
        }
    }
    return maxVal;
}