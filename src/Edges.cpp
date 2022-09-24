#include <bits/stdc++.h>
#include "debayering.h"
#include "Conversion.h"
using namespace std;
using matrix = vector<vector<double>>;
matrix double_thresh(matrix image, double lowthreshratio = 0.05, double highthreshratio = 0.09)
{
    double highThreshold = maxEle(image) * highthreshratio;
    double lowThreshold = highThreshold * lowthreshratio;

    matrix res(image.size(), vector<double>(image[0].size(), 0));
    int weak = 25, strong = 255;

    vector<double> strongI, strongJ, weakI, weakJ, zeroI, zeroJ;
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            if (image[i][j] >= highThreshold)
            {
                strongI.push_back(i);
                strongJ.push_back(j);
            }
            else if (image[i][j] < lowThreshold)
            {
                zeroI.push_back(i);
                zeroJ.push_back(j);
            }
            else if ((image[i][j] <= highThreshold) && (image[i][j] >= lowThreshold))
            {
                weakI.push_back(i);
                weakJ.push_back(j);
            }
        }
    }
    for (int i = 0; i < strongI.size(); i++)
    {
        res[strongI[i]][strongJ[i]] = strong;
    }
    for (int i = 0; i < weakI.size(); i++)
    {
        res[weakI[i]][weakJ[i]] = weak;
    }
    return res;
}
matrix edgeDetect(matrix R, matrix G, matrix B)
{
    // matrix res(R.size(), vector<double>(R[0].size(), 0));
    matrix kernel_X = {{-1, 0.0, 1}, {-2, 0.0, 2}, {-1, 0.0, 1}};
    matrix kernel_Y = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    matrix gray_image = cvtGray(R, G, B);
    matrix res = conv2D(gray_image, kernel_X);
    matrix res2 = conv2D(gray_image, kernel_Y);
    matrix final_image(gray_image.size(), vector<double>(gray_image[0].size(), 0));
    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[0].size(); j++)
        {
            final_image[i][j] = sqrt(pow(res[i][j], 2) + pow(res2[i][j], 2));
        }
    }
    // matrix after_threshold = double_thresh(final_image);
    return final_image;
}