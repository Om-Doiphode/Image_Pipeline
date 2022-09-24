/*
 *Author List: Om Doiphode
 *Filename: MedianFilter.cpp
 *Functions: filter(matrix)
 Here, matrix=vector<vector<double>>
 *Global Variables: NONE
 */
#include <bits/stdc++.h>
#include "debayering.h"
using namespace std;
using matrix = vector<vector<double>>;
/*
 * Function Name: filter
 * Input: image -> 2D vector of image
 * Output: returns filtered image
 * Logic: average=(sum of pixel values)/total number of pixel values
 * Example Call: filter(image);
 */
matrix filter(matrix image)
{
    // Traverse the image. For every 3X3 area,
    // find the median of the pixels and
    // replace the center pixel by the median
    int m = image.size(), n = image[0].size();
    matrix new_image(image.size(), vector<double>(image[0].size(), 0));
    for (int i = 1; i < m - 1; i++)
    {
        for (int j = 1; j < n - 1; j++)
        {
            vector<double> temp{image[i - 1][j - 1], image[i - 1][j], image[i - 1][j + 1], image[i][j - 1], image[i][j], image[i][j + 1], image[i + 1][j - 1], image[i + 1][j], image[i + 1][j + 1]};
            sort(temp.begin(), temp.end());
            new_image[i][j] = temp[4];
        }
    }
    return new_image;
}
matrix meanFilter(matrix image, int kernel_size = 3)
{
    matrix kernel(kernel_size, vector<double>(kernel_size, 0));
    for (int i = 0; i < kernel_size; i++)
    {
        for (int j = 0; j < kernel_size; j++)
        {
            kernel[i][j] = 1 / pow(kernel_size, 2);
        }
    }
    return conv2D(image, kernel);
}
// Function to create Gaussian filter
matrix gaussianFilterCreation(int kernel_size = 3)
{
    matrix kernel(kernel_size, vector<double>(kernel_size, 0));
    // initialising standard deviation to 1.0
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;

    // sum is for normalization
    double sum = 0.0;

    // generating (kernel_size x kernel_size) kernel
    for (int x = -(kernel_size) / 2; x <= (kernel_size) / 2; x++)
    {
        for (int y = -kernel_size / 2; y <= kernel_size / 2; y++)
        {
            r = sqrt(x * x + y * y);
            kernel[x + (kernel_size) / 2][y + (kernel_size) / 2] = (exp(-(r * r) / s)) / (M_PI * s);
            sum += kernel[x + (kernel_size) / 2][y + (kernel_size) / 2];
        }
    }

    // normalising the Kernel
    for (int i = 0; i < kernel_size; ++i)
        for (int j = 0; j < kernel_size; ++j)
            kernel[i][j] /= sum;
    return kernel;
}
matrix gaussianFilter(matrix image, int kernel_size = 3)
{
    matrix kernel = gaussianFilterCreation(kernel_size);
    return conv2D(image, kernel);
}