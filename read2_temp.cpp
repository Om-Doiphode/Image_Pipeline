#include <bits/stdc++.h>
#include <math.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int height = 477, width = 640;
using matrix = vector<vector<double>>;
double averageOfPixels(matrix image)
{
    double average, sum = 0;
    int count = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sum += image[i][j];
            count++;
        }
    }
    return (sum / count);
}
matrix gammaCorrection(matrix image, double gamma)
{
    matrix res(height, vector<double>(width, 0));
    double power = 1 / gamma;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            res[i][j] = double(pow(image[i][j], power));
        }
    }
    return res;
}
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
int maxEle(matrix image)
{
    int result = std::numeric_limits<int>::min();
    for (const auto &row : image)
    {
        int minElemInRow = *std::max_element(row.begin(), row.end());
        result = std::max(result, minElemInRow);
    }
    return result;
}
// Normalization
matrix scale(matrix image, double a = 0, double b = 1)
{
    int maxELement = maxEle(image), minElement = minEle(image);
    matrix result(height, vector<double>(width, 0));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
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
void display(matrix);
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
matrix padding2D(matrix &img, int ph, int pw)
{
    // padding ph lines of 0 on top and bottom, pw lines of 0 on left and right
    int new_height = img.size() + 2 * ph;
    int new_width = img[0].size() + 2 * pw;
    matrix ret(new_height, vector<double>(new_width, 0));

    for (int i = ph; i < ph + img.size(); i++)
        for (int j = pw; j < pw + img[0].size(); j++)
            ret[i][j] = img[i - ph][j - pw];
    return ret;
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
double maxPixelvalue(matrix image)
{
    double maxVal = image[0][0];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
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
    matrix res(height, vector<double>(width, 0));
    double glob_thresh_val = maxVal / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
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
vector<vector<vector<double>>> debayering(matrix image)
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
    R = blackLevelCorrection(R);
    G = blackLevelCorrection(G);
    B = blackLevelCorrection(B);

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
    debayered_image.push_back(R);
    debayered_image.push_back(G);
    debayered_image.push_back(B);
    return debayered_image;
}

// Grayscale
matrix cvtGray(matrix R, matrix G, matrix B)
{
    matrix res(height, vector<double>(width, 0));
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
    matrix res(height, vector<double>(width, 0));
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
// Erosion
matrix Erosion(matrix img)
{
    matrix kernal = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    matrix new_image(height, vector<double>(width, 0));
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
matrix FlipImage(matrix image)
{
    matrix res(height, vector<double>(width, 0));
    for (int i = 0; i < image.size() - 1; i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            res[i][j] = image[i][height - j - 1];
        }
    }
    return res;
}
int main()
{
    // CSClOutput.txt ==> Contains the pixel values of CFA
    fstream inputFile("CSCloutput.txt", ios::in);
    // fstream outputFile("FinalFile1.txt", ios::out);
    double buffer;
    int i = 0;
    vector<double> temp;
    matrix image(height + 4, vector<double>(width + 4, 0));
    while (inputFile)
    {
        inputFile >> buffer;
        // outputFile << (buffer) << endl;
        i++;
        temp.push_back((buffer));
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
    vector<vector<vector<double>>> debayered_image = debayering(image);
    matrix R = debayered_image[0], G = debayered_image[1], B = debayered_image[2];
    double avgRed = averageOfPixels(R);
    double avgGreen = averageOfPixels(G);
    double avgBlue = averageOfPixels(B);

    R = whiteBalance(R, avgRed, avgGreen, avgBlue);
    G = whiteBalance(G, avgRed, avgGreen, avgBlue);
    B = whiteBalance(B, avgRed, avgGreen, avgBlue);

    R = gammaCorrection(R, 0.7);
    G = gammaCorrection(G, 0.7);
    B = gammaCorrection(B, 0.7);
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

    // Merging the three channels and storing the values in a file
    fstream file3("RGBImage.txt", ios::out);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // mat.at<Vec3b>(i, j) = {R[i][j], G[i][j], B[i][j]}
            file3 << R[i][j] << " " << G[i][j] << " " << B[i][j] << " ";
        }
        file3 << endl;
    }

    // Grayscale Image
    matrix grayImage = cvtGray(R, G, B);
    fstream grayFile("Gray.txt", ios::out);
    for (int i = 0; i < grayImage.size(); i++)
    {
        for (int j = 0; j < grayImage[0].size(); j++)
        {
            grayFile << grayImage[i][j] << " ";
        }
        grayFile << endl;
    }

    // Binary Image
    fstream BinFile("Binary.txt", ios::out);
    matrix Binary = cvtBinary(grayImage);
    k = 0;
    for (int i = 0; i < Binary.size(); i++)
    {
        for (int j = 0; j < Binary[0].size(); j++)
        {
            BinFile << Binary[i][j] << " ";
            // Image[k++] = Binary[i][j];
        }
        BinFile << endl;
    }

    // Erosion
    matrix ErodedImage = Erosion(Binary);
    fstream Erode("Erode.txt", ios::out);
    for (int i = 0; i < ErodedImage.size(); i++)
    {
        for (int j = 0; j < ErodedImage[0].size(); j++)
        {
            Erode << ErodedImage[i][j] << " ";
        }
        Erode << endl;
    }

    // Flipping
    matrix HorizontalFlip = FlipImage(grayImage);
    fstream Flip("Flip.txt", ios::out);
    for (int i = 0; i < HorizontalFlip.size(); i++)
    {
        for (int j = 0; j < HorizontalFlip[0].size(); j++)
        {
            Flip << HorizontalFlip[i][j] << " ";
        }
        Flip << endl;
    }
    // // const Mat img(grayImage);
    // cv::Mat g_img(grayImage.size(), grayImage.at(0).size(), CV_64FC1);
    // for (int i = 0; i < g_img.rows; ++i)
    //     for (int j = 0; j < g_img.cols; ++j)
    //         g_img.at<double>(i, j) = grayImage.at(i).at(j);

    // namedWindow("foobar");
    // imshow("foobar", g_img);
    Mat img1 = imread("Flash2.tiff");
    // cout << image.type() << " " << image.depth();
    for (int i = 0; i < img1.rows; ++i)
    {
        for (int j = 0; j < img1.cols; ++j)
        {
            cout << img1.at<ushort>(i, j) << " ";
            if (img1.at<short>(i, j) == 864)
            {
                cout << "I: " << i << "J: " << j << endl;
                break;
            }
        }
    }

    namedWindow("Image");
    imshow("Image", img1);
    waitKey(0);
}