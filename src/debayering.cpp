#include <bits/stdc++.h>
#include "ColorSpace.h"
using namespace std;
using matrix = vector<vector<double>>;
int minEle(matrix image)
{
    int result = std::numeric_limits<int>::max();
    for (const auto &row : image)
    {
        int minElemInRow = *std::min_element(row.begin(), row.end());
        result = std::min(result, minElemInRow);
    }
    return result;
}
double maxEle(matrix image)
{
    double result = std::numeric_limits<int>::min();
    for (const auto &row : image)
    {
        double minElemInRow = *std::max_element(row.begin(), row.end());
        result = std::max(result, minElemInRow);
    }
    return result;
}
matrix conv2D(matrix &img, matrix &kernal)
{
    int out_h = img.size() - kernal.size() + 1;
    int out_w = img[0].size() - kernal[0].size() + 1;
    matrix ret(out_h, vector<double>(out_w, 0));
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
                    ret[i][j] += (img[i + muli][j + mulj] * kernal[muli][mulj]) / 8;
                }
            }
        }
    }
    return ret;
}
matrix G_at_BR(matrix &image)
{
    matrix kernel = {{0.0, 0.0, -1.0, 0.0, 0.0}, {0.0, 0.0, 2.0, 0.0, 0.0}, {-1.0, 2.0, 4.0, 2.0, -1.0}, {0.0, 0.0, 2.0, 0.0, 0.0}, {0.0, 0.0, -1.0, 0.0, 0.0}};
    return conv2D(image, kernel);
}
matrix RB_at_G_in_RBrow_BRcol(matrix &image)
{
    matrix kernel = {{0, 0, 0.5, 0, 0}, {0, -1, 0, -1, 0}, {-1, 4, 5, 4, -1}, {0, -1, 0, -1, 0}, {0, 0, 0.5, 0, 0}};
    return conv2D(image, kernel);
}
matrix RB_at_G_in_BRrow_RBcol(matrix &image)
{
    matrix kernel = {{0, 0, -1, 0, 0}, {0, -1, 4, -1, 0}, {0.5, 0, 5, 0, 0.5}, {0, -1, 4, -1, 0}, {0, 0, -1, 0, 0}};
    return conv2D(image, kernel);
}
matrix RB_at_BR(matrix &image)
{
    matrix kernel = {{0, 0, -1.5, 0, 0}, {0, 2, 0, 2, 0}, {-1.5, 0, 6, 0, -1.5}, {0, 2, 0, 2, 0}, {0, 0, -1.5, 0, 0}};
    return conv2D(image, kernel);
}
vector<vector<vector<double>>> autoAdjust(matrix R, matrix G, matrix B, int height, int width)
{
    vector<vector<vector<double>>> new_image;

    matrix O_R(height, vector<double>(width, 0));
    matrix O_G(height, vector<double>(width, 0));
    matrix O_B(height, vector<double>(width, 0));

    // # calculate stats
    double alow = minEle(R);
    double ahigh = maxEle(R);
    double amax = 255;
    double amin = 0;

    // #access each pixel, and auto adjust
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
vector<vector<vector<double>>> debayering(matrix image, int height, int width)
{
    matrix R(height, vector<double>(width, 0));
    matrix G(height, vector<double>(width, 0));
    matrix B(height, vector<double>(width, 0));

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
    matrix tmp = G_at_BR(image);
    cout << tmp.size() << " " << tmp[0].size() << endl;
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
    vector<vector<vector<double>>> combine = autoAdjust(R, G, B, height, width);
    R = combine[0];
    G = combine[1];
    B = combine[2];

    vector<vector<vector<double>>> colorCorrectedImage = ColorConv(R, G, B);

    debayered_image.push_back(colorCorrectedImage[0]);
    debayered_image.push_back(colorCorrectedImage[1]);
    debayered_image.push_back(colorCorrectedImage[2]);
    return debayered_image;
}