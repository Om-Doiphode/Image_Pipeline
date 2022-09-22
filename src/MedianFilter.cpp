/*
 *Author List: Om Doiphode
 *Filename: MedianFilter.cpp
 *Functions: filter(matrix)
 Here, matrix=vector<vector<double>>
 *Global Variables: NONE
 */
#include <bits/stdc++.h>
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