#include <bits/stdc++.h>

using namespace std;

using matrix = vector<vector<double>>;


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


matrix blackLevelCorrection(matrix image)
{
    double maxVal = maxPixelvalue(image);
    matrix res(image.size(), vector<double>(image[0].size(), 0));
    double glob_thresh_val = maxVal / 2;
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
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
    return res;
}