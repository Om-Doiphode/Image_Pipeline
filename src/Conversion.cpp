#include <bits/stdc++.h>
using namespace std;
using matrix = vector<vector<double>>;
// Grayscale
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
// Binary
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
