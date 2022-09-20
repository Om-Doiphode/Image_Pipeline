#include <bits/stdc++.h>
using namespace std;
using matrix = vector<vector<double>>;
double sum(matrix A)
{
    int add = 0;
    for (const auto &row : A)
    {
        for (const auto &ele : row)
        {
            add += ele;
        }
    }
    return add;
}
matrix multiply(matrix A, matrix B)
{
    matrix C;
    int n = B.size();
    for (int i = 0; i < n; i++)
    {
        vector<double> temp;
        for (int j = 0; j < n; j++)
        {
            temp.push_back(A[i][j] * B[i][j]);
        }
        C.push_back(temp);
    }
    return C;
}
matrix vectorSlice(matrix &orig, int row_lower, int row_limit, int col_lower, int col_limit)
{
    matrix res;
    for (int i = row_lower; i < row_limit; i++)
    {
        vector<double> temp;
        for (int j = col_lower; j < col_limit; j++)
        {
            temp.push_back(orig[i][j]);
        }
        res.push_back(temp);
    }
    return res;
}
// Erosion
matrix Erosion(matrix img)
{
    matrix kernal = {{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}};
    matrix new_image(img.size(), vector<double>(img[0].size(), 0));
    int addition = sum(kernal);
    int m = kernal.size(), n = kernal[0].size();
    int y = img.size(), x = img[0].size();
    int y1 = y - m + 1;
    int x1 = x - n + 1;
    for (int i = 0; i < y1; i++)
    {
        for (int j = 0; j < x1; j++)
        {
            int value = sum(multiply(vectorSlice(img, i, i + m, j, j + n), kernal));
            if (value == addition)
                new_image[i][j] = 1;
            else
                new_image[i][j] = 0;
        }
    }
    return new_image;
}

matrix Dilation(matrix img)
{
    matrix kernal = {{0, 1, 0}, {1, 1, 1}, {0, 1, 0}};
    matrix new_image(img.size(), vector<double>(img[0].size(), 0));
    int addition = sum(kernal);
    int m = kernal.size(), n = kernal[0].size();
    int y = img.size(), x = img[0].size();
    int y1 = y - m + 1;
    int x1 = x - n + 1;
    for (int i = 1; i < img.size() - 1; i++)
    {
        for (int j = 1; j < img[0].size() - 1; j++)
        {
            matrix temp = vectorSlice(img, i - 1, i + 2, j - 1, j + 2);
            double product = sum(multiply(temp, kernal));
            if (product > 0)
            {
                new_image[i][j] = 1;
            }
            else
            {
                new_image[i][j] = 0;
            }
        }
    }
    return new_image;
}
matrix Closing(matrix image)
{
    matrix final_image = Erosion(image);
    matrix final_image2 = Dilation(final_image);
    return final_image2;
}
matrix Opening(matrix image)
{
    matrix final_image = Dilation(image);
    matrix final_image2 = Erosion(final_image);
    return final_image2;
}
matrix Gradient(matrix image)
{
    matrix dilated = Dilation(image);
    matrix eroded = Erosion(image);
    matrix final_image(image.size(), vector<double>(image[0].size(), 0));
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            final_image[i][j] = dilated[i][j] - eroded[i][j];
        }
    }
    return final_image;
}
