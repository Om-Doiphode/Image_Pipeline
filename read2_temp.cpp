#include <bits/stdc++.h>
using namespace std;
int height = 480, width = 640;
using matrix = vector<vector<double>>;
int HexToDec(string num)
{
    int length = num.length() - 1;
    int dec = 0;
    for (int i = 0; i < num.length(); i++)
    {
        if (num[i] == 'A' || num[i] == 'a')
            dec = dec + 10 * pow(16, length);
        else if (num[i] == 'B' || num[i] == 'b')
            dec = dec + 11 * pow(16, length);
        else if (num[i] == 'c' || num[i] == 'C')
            dec = dec + 12 * pow(16, length);
        else if (num[i] == 'D' || num[i] == 'd')
            dec = dec + 13 * pow(16, length);
        else if (num[i] == 'E' || num[i] == 'e')
            dec = dec + 14 * pow(16, length);
        else if (num[i] == 'F' || num[i] == 'f')
            dec = dec + 15 * pow(16, length);
        else
        {
            string number = "";
            number += num[i];
            dec = dec + pow(16, length) * stoi(number);
        }
        length--;
    }
    return dec;
}
void display(matrix);
matrix vectorSlice(matrix &orig, int a, int b, int row_lower, int row_limit)
{
    matrix res;
    for (int i = row_lower; i < row_limit; i++)
    {
        vector<double> temp;
        for (int j = a; j < b; j++)
        {
            temp.push_back(orig[i][j]);
        }
        res.push_back(temp);
    }
    return res;
}
void display(matrix A)
{
    for (const auto &row : A)
    {
        for (const auto &ele : row)
        {
            cout << ele << " ";
        }
        cout << endl;
    }
    cout << endl;
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
int sum(matrix A)
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
matrix convolve(matrix &image, matrix &kernel)
{
    matrix convolved_image(height, vector<double>(width, 0));
    int height_image = image.size();
    int width_image = image[0].size();
    int m = kernel.size();
    int n = kernel.size();
    int y = height_image - m + 1;
    int x = width_image - n + 1;
    vector<double> temp;
    int count = 0;
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            convolved_image[i].at(j) = convolved_image[i].at(j) + (((sum(multiply(vectorSlice(image, j, j + n, i, i + m), kernel))))) / 8;
        }
    }
    return convolved_image;
}
matrix G_at_BR(matrix image)
{
    matrix kernel = {{0, 0, -1, 0, 0}, {0, 0, 2, 0, 0}, {-1, 2, 4, 2, -1}, {0, 0, 2, 0, 0}, {0, 0, -1, 0, 0}};
    return convolve(image, kernel);
}
matrix RB_at_G_in_RBrow_BRcol(matrix image)
{
    matrix kernel = {{0, 0, 0.5, 0, 0}, {0, -1, 0, -1, 0}, {-1, 4, 5, 4, -1}, {0, -1, 0, -1, 0}, {0, 0, 0.5, 0, 0}};
    return convolve(image, kernel);
}
matrix RB_at_G_in_BRrow_RBcol(matrix image)
{
    matrix kernel = {{0, 0, -1, 0, 0}, {0, -1, 4, -1, 0}, {0.5, 0, 5, 0, 0.5}, {0, -1, 4, -1, 0}, {0, 0, -1, 0, 0}};
    return convolve(image, kernel);
}
matrix RB_at_BR(matrix image)
{
    matrix kernel = {{0, 0, -1.5, 0, 0}, {0, 2, 0, 2, 0}, {-1.5, 0, 6, 0, -1.5}, {0, 2, 0, 2, 0}, {0, 0, -1.5, 0, 0}};
    return convolve(image, kernel);
}
int main()
{
    fstream inputFile("Data.txt", ios::in);
    fstream outputFile("FinalFile1.txt", ios::out);
    string buffer;
    int i = 0;
    vector<double> temp;
    matrix image(height + 4, vector<double>(width + 4, 0));
    while (inputFile)
    {
        inputFile >> buffer;
        outputFile << HexToDec(buffer) << endl;
        i++;
        temp.push_back((HexToDec(buffer)));
    }
    int k = 0;
    for (int i = 2; i < height + 2; i++)
    {
        for (int j = 2; j < width + 2; j++)
        {
            image[i][j] = temp[k];
            k++;
        }
    }

    matrix R(height, vector<double>(width, 0));
    matrix G(height, vector<double>(width, 0));
    matrix B(height, vector<double>(width, 0));

    // Copying data that doesn't need interpolation
    cout << R.size() << " " << R[0].size() << endl;
    cout << image.size() << " " << image[0].size() << endl;
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
            else if (i % 2 == 1 && j % 2 == 1)
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
                R[i][j] = tmp3[i][j];
            }
            else if (i % 2 == 0 && j % 2 == 1)
            {
                B[i][j] = tmp3[i][j];
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
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (R[i][j] < 0)
                R[i][j] = 0;
            else if (R[i][j] > 65535)
                R[i][j] = 65535;
            else if (B[i][j] < 0)
                B[i][j] = 0;
            else if (B[i][j] > 65535)
                B[i][j] = 65535;
            else if (G[i][j] < 0)
                G[i][j] = 0;
            else if (G[i][j] > 65535)
                G[i][j] = 65535;
        }
    }
    fstream redFile("Red.txt", ios::out);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            redFile << R[i][j] << " ";
        }
        redFile << endl;
    }
    fstream greenFile("Green.txt", ios::out);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            greenFile << G[i][j] << " ";
        }
        greenFile << endl;
    }
    fstream blueFile("Blue.txt", ios::out);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blueFile << B[i][j] << " ";
        }
        blueFile << endl;
    }
}