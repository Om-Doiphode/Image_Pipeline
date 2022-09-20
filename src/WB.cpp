#include <bits/stdc++.h>
#include "../include/debayering.h"
using namespace std;
using matrix = vector<vector<double>>;

double averageOfPixels(matrix image)
{
    double average, sum = 0;
    int count = 0;
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            sum += image[i][j];
            count++;
        }
    }
    return (sum / count);
}
matrix scale(matrix image, double a = 0, double b = 1)
{
    int maxELement = maxEle(image), minElement = minEle(image);
    matrix result(image.size(), vector<double>(image[0].size(), 0));
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            result[i][j] = (double)((image[i][j] - (maxELement + minElement) / 2.0) / (maxELement - minElement));
            result[i][j] = (double)(result[i][j] * (b - a) + (b + a) / 2.0);
        }
    }
    return result;
}
double maxNumber(double a, double b, double c)
{
    if (a >= b && a >= c)
        return a;
    if (b >= a && b >= c)
        return b;
    return c;
}
matrix whiteBalance(matrix image, double avgRed, double avgGreen, double avgBlue)
{
    double avgi = averageOfPixels(image);
    double ri = maxNumber(avgRed, avgBlue, avgGreen) / (double)avgi;
    cout << avgRed << " " << avgBlue << " " << avgGreen << " " << avgi << " " << ri << endl;
    return scale(image, 0, ri);
}