#include <bits/stdc++.h>
using namespace std;
using matrix = vector<vector<double>>;
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