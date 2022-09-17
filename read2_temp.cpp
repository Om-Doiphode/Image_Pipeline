#include <bits/stdc++.h>
#include <math.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat im = imread("Flash2.tiff");
int height = im.rows, width = im.cols;
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
vector<vector<vector<double>>> tonemapping(matrix R, matrix G, matrix B);
vector<vector<vector<double>>> autoContrast(matrix R, matrix G, matrix B)
{
    vector<vector<vector<double>>> final_image;
    double max_R = maxEle(R);
    double max_G = maxEle(G);
    double max_B = maxEle(B);

    double min_R = minEle(R);
    double min_G = minEle(G);
    double min_B = minEle(B);

    double input_range_R = max_R - min_R;
    double input_range_G = max_G - min_G;
    double input_range_B = max_B - min_B;

    double alpha_R = 255 / input_range_R;
    double alpha_G = 255 / input_range_G;
    double alpha_B = 255 / input_range_B;

    double beta_R = -min_R * alpha_R;
    double beta_G = -min_G * alpha_G;
    double beta_B = -min_B * alpha_B;

    matrix O_R(height, vector<double>(width, 0));
    matrix O_G(height, vector<double>(width, 0));
    matrix O_B(height, vector<double>(width, 0));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            O_R[i][j] = alpha_R * R[i][j] + beta_R;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            O_G[i][j] = alpha_G * G[i][j] + beta_G;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            O_B[i][j] = alpha_B * B[i][j] + beta_B;
        }
    }
    final_image.push_back(O_R);
    final_image.push_back(O_G);
    final_image.push_back(O_B);

    return final_image;
}

matrix Truncate(matrix image, int brightness, double factor = 1)
{
    matrix final_image(height, vector<double>(width, 0));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((image[i][j] + brightness) < 0)
                final_image[i][j] = 0;
            else if ((image[i][j] + brightness) > 255)
                final_image[i][j] = 255;
            else
                final_image[i][j] = image[i][j];
        }
    }
    return final_image;
}
matrix Contrast(matrix image, int contrast)
{
    // double factor = (259 * (contrast + 255)) / (255 * (259 - contrast));
    matrix final_image(height, vector<double>(width, 0));
    // for (int i = 0; i < height; i++)
    // {
    //     for (int j = 0; j < width; j++)
    //     {
    //         if (((image[i][j] * factor - 128) + 128) < 0)
    //             final_image[i][j] = 0;
    //         else if (((image[i][j] * factor - 128) + 128) > 255)
    //             final_image[i][j] = 255;
    //         else
    //             final_image[i][j] = image[i][j];
    //     }
    // }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            final_image[i][j] = image[i][j] * contrast;
        }
    }
    return final_image;
}
vector<vector<vector<double>>> autoAdjust(matrix R, matrix G, matrix B)
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
vector<vector<vector<double>>> RGB2YUV(matrix R, matrix G, matrix B)
{
    vector<vector<vector<double>>> final_image;
    matrix Y(height, vector<double>(width, 0));
    matrix U(height, vector<double>(width, 0));
    matrix V(height, vector<double>(width, 0));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Y[i][j] = 0.299 * R[i][j] + 0.587 * G[i][j] + 0.114 * B[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            U[i][j] = 0.492 * (B[i][j] - Y[i][j]);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            V[i][j] = 0.877 * (R[i][j] - Y[i][j]);
        }
    }
    final_image.push_back(Y);
    final_image.push_back(U);
    final_image.push_back(V);
    return final_image;
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
    vector<vector<vector<double>>> combine = autoAdjust(R, G, B);
    R = combine[0];
    G = combine[1];
    B = combine[2];

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
matrix EdgeDetect(matrix image)
{
    matrix kernel = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
    return conv2D(image, kernel);
}
matrix gaussblur(matrix image)
{
    matrix kernel = {{1 / 16, 2 / 16, 1 / 16}, {2 / 16, 4 / 16, 2 / 16}, {1 / 16, 2 / 16, 1 / 16}};
    return conv2D(image, kernel);
}
matrix Bright(matrix R, matrix G, matrix B)
{
    matrix luminance(height, vector<double>(width, 0));
    int count = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            luminance[i][j] = 0.3 * R[i][j] + 0.59 * G[i][j] + 0.11 * B[i][j];
        }
    }
    double avg, sum = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sum += luminance[i][j];
            count++;
        }
    }
    avg = double(sum) / count;
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

    // Grayscale Image
    matrix grayImage = cvtGray(R, G, B);
    Mat edges;
    // Binary Image
    matrix Binary = cvtBinary(grayImage);
    // Erosion
    matrix ErodedImage = Erosion(Binary);

    // Flipping
    matrix HorizontalFlip = FlipImage(grayImage);

    // Working Bilateral Filter
    // Mat gray_image(ErodedImage.size(), ErodedImage.at(0).size(), CV_64FC1);
    // for (int i = 0; i < gray_image.rows; ++i)
    //     for (int j = 0; j < gray_image.cols; ++j)
    //         gray_image.at<double>(i, j) = ErodedImage.at(i).at(j);

    // Mat bin_image(ErodedImage.size(), ErodedImage.at(0).size(), CV_64FC1);
    // for (int i = 0; i < gray_image.rows; ++i)
    //     for (int j = 0; j < gray_image.cols; ++j)
    //         bin_image.at<double>(i, j) = Binary.at(i).at(j);

    // Mat edges_image(height, width, CV_32F);
    // erode(gray_image, edges_image, 5);
    // gray_image.convertTo(gray_image, CV_32F);
    // bilateralFilter(gray_image, edges_image, 3, 3, 10);

    vector<Mat> rgb_image;
    Mat r_img(R.size(), R.at(0).size(), CV_64FC1);
    for (int i = 0; i < r_img.rows; ++i)
    {
        for (int j = 0; j < r_img.cols; ++j)
        {
            r_img.at<double>(i, j) = R.at(i).at(j);
        }
    }
    Mat g_img(G.size(), G.at(0).size(), CV_64FC1);
    for (int i = 0; i < g_img.rows; ++i)
    {
        for (int j = 0; j < g_img.cols; ++j)
        {
            g_img.at<double>(i, j) = G.at(i).at(j);
        }
    }
    Mat b_img(B.size(), B.at(0).size(), CV_64FC1);
    for (int i = 0; i < b_img.rows; ++i)
    {
        for (int j = 0; j < b_img.cols; ++j)
        {
            b_img.at<double>(i, j) = B.at(i).at(j);
        }
    }
    r_img.convertTo(r_img, CV_32F);
    g_img.convertTo(g_img, CV_32F);
    b_img.convertTo(b_img, CV_32F);

    rgb_image.push_back(b_img);
    rgb_image.push_back(g_img);
    rgb_image.push_back(r_img);

    // Mat edges_img(edges_image.size(), edges_image.at(0).size(), CV_64FC1);
    // for (int i = 0; i < edges_img.rows; ++i)
    //     for (int j = 0; j < edges_img.cols; ++j)
    //         edges_img.at<double>(i, j) = edges_image.at(i).at(j);

    // namedWindow("foobar");
    // imshow("foobar", gray_img);

    Mat I(height, width, CV_64FC1);
    for (int i = 0; i < I.rows; i++)
    {
        for (int j = 0; j < I.cols; j++)
        {
            I.at<double>(i, j) = double(R[i][j] * 20 + G[i][j] * 40 + B[i][j]) / 61.0;
        }
    }
    Mat C_R(height, width, CV_64FC1);
    Mat C_G(height, width, CV_64FC1);
    Mat C_B(height, width, CV_64FC1);
    for (int i = 0; i < R.size(); i++)
    {
        for (int j = 0; j < R[0].size(); j++)
        {
            C_R.at<double>(i, j) = R[i][j] / I.at<double>(i, j);
        }
    }
    for (int i = 0; i < G.size(); i++)
    {
        for (int j = 0; j < G[0].size(); j++)
        {
            C_G.at<double>(i, j) = G[i][j] / I.at<double>(i, j);
        }
    }
    for (int i = 0; i < B.size(); i++)
    {
        for (int j = 0; j < B[0].size(); j++)
        {
            C_B.at<double>(i, j) = B[i][j] / I.at<double>(i, j);
        }
    }
    Mat L(height, width, CV_64FC1);
    for (int i = 0; i < I.rows; i++)
    {
        for (int j = 0; j < I.cols; j++)
        {
            L.at<double>(i, j) = log2(I.at<double>(i, j));
        }
    }
    L.convertTo(L, CV_32F);
    Mat BiL(height, width, CV_32F);
    bilateralFilter(L, BiL, 3, 3, 10);

    Mat D(height, width, CV_32F);
    D = Mat::zeros(height, width, CV_32F);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            D.at<double>(i, j) = L.at<double>(i, j) - BiL.at<double>(i, j);
        }
    }
    // D.convertTo(D, CV_32F);
    Mat final_image;
    Mat filtered_image;
    merge(rgb_image, final_image);
    resize(final_image, final_image, Size(500, 500));

    // resize(edges_img, edges_img, Size(500, 500));
    imshow("RGB", final_image);
    imshow("Intensity", I);
    imshow("Chrome", C_B);
    imshow("Log", L);
    imshow("Bilateral", BiL);
    imshow("Detail", D);
    // imshow("Gray", gray_image);
    // imshow("Bin", bin_image);
    // imshow("Erode", edges_image);
    // imwrite("RGB.jpg", final_image);
    waitKey(0);
}
