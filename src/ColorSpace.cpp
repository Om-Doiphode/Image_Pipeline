/*
 *Author List: Om Doiphode, Kedar Dhamankar
 *Filename: ColorSpace.cpp
 *Functions: double sumOfRows(vector<double>),
             matrix inverse(matrix),
             vector<vector<vector<double>>> ColorConv(matrix, matrix, matrix)
 *Global Variable: NONE
 */
#include <bits/stdc++.h>
using namespace std;
using matrix = vector<vector<double>>;

double sumOfRows(vector<double> row)
{
    double s = 0;
    for (int i = 0; i < row.size(); i++)
        s += row[i];
    return s;
}
/*
 * Function Name: inverse
 * Input: mat -> 2D vector
 * Output: returns the inverse of matrix
 * Logic:  AA^-1 = I
 *        where A is the input matrix, I is the identity matrix and A^-1 is the inverse of matrix A.
 * Example Call: inverse(matrix)
 */
matrix inverse(matrix mat)
{
    matrix inv(mat.size(), vector<double>(mat[0].size(), 0));
    // finding determinant
    double determinant = 0;
    for (int i = 0; i < mat.size(); i++)
        determinant = determinant + (mat[0][i] * (mat[1][(i + 1) % 3] * mat[2][(i + 2) % 3] - mat[1][(i + 2) % 3] * mat[2][(i + 1) % 3]));
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[0].size(); j++)
            inv[i][j] = ((mat[(j + 1) % 3][(i + 1) % 3] * mat[(j + 2) % 3][(i + 2) % 3]) - (mat[(j + 1) % 3][(i + 2) % 3] * mat[(j + 2) % 3][(i + 1) % 3])) / determinant;
    }
    return inv;
}
vector<vector<vector<double>>> ColorConv(matrix R, matrix G, matrix B)
{
    matrix rgb2xyz = {{0.4124564, 0.3575761, 0.1804375},
                      {0.2126729, 0.7151522, 0.0721750},
                      {0.0193339, 0.1191920, 0.9503041}};
    matrix xyz2cam = {{0.6653, -0.1486, -0.0611},
                      {-0.4221, 1.3303, 0.0929},
                      {-0.0881, 0.2416, 0.7226}};
    matrix rgb2cam(rgb2xyz.size(), vector<double>(rgb2xyz[0].size(), 0));
    for (int i = 0; i < rgb2xyz.size(); i++)
    {
        for (int j = 0; j < rgb2xyz[0].size(); j++)
        {
            rgb2cam[i][j] = xyz2cam[i][j] * rgb2xyz[i][j];
        }
    }
    matrix denom(rgb2cam.size(), vector<double>(rgb2cam[0].size(), 0));
    for (int i = 0; i < rgb2cam.size(); i++)
    {
        for (int j = 0; j < rgb2cam[0].size(); j++)
        {
            denom[i][j] = sumOfRows(rgb2cam[i]);
        }
    }
    for (int i = 0; i < rgb2cam.size(); i++)
    {
        for (int j = 0; j < rgb2cam[0].size(); j++)
        {
            rgb2cam[i][j] = double(rgb2cam[i][j]) / double(denom[i][j]);
        }
    }
    matrix cam2rgb = inverse(rgb2cam);
    for (int i = 0; i < R.size(); i++)
    {
        for (int j = 0; j < R[0].size(); j++)
        {
            R[i][j] = cam2rgb[0][0] * R[i][j] + cam2rgb[0][1] * G[i][j] + cam2rgb[0][2] * B[i][j];
        }
    }
    for (int i = 0; i < G.size(); i++)
    {
        for (int j = 0; j < G[0].size(); j++)
        {
            G[i][j] = cam2rgb[1][0] * R[i][j] + cam2rgb[1][1] * G[i][j] + cam2rgb[1][2] * B[i][j];
        }
    }
    for (int i = 0; i < B.size(); i++)
    {
        for (int j = 0; j < B[0].size(); j++)
        {
            B[i][j] = cam2rgb[2][0] * R[i][j] + cam2rgb[2][1] * G[i][j] + cam2rgb[2][2] * B[i][j];
        }
    }
    for (int i = 0; i < R.size(); i++)
    {
        for (int j = 0; j < R[0].size(); j++)
        {
            if (R[i][j] > 1)
                R[i][j] = 1;
            else if (R[i][j] < 0)
                R[i][j] = 0;
        }
    }
    for (int i = 0; i < G.size(); i++)
    {
        for (int j = 0; j < G[0].size(); j++)
        {
            if (G[i][j] > 1)
                G[i][j] = 1;
            else if (G[i][j] < 0)
                G[i][j] = 0;
        }
    }
    for (int i = 0; i < B.size(); i++)
    {
        for (int j = 0; j < B[0].size(); j++)
        {
            if (B[i][j] > 1)
                B[i][j] = 1;
            else if (B[i][j] < 0)
                B[i][j] = 0;
        }
    }
    vector<vector<vector<double>>> final_image;
    final_image.push_back(R);
    final_image.push_back(G);
    final_image.push_back(B);

    return final_image;
}