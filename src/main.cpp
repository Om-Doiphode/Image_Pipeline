#include <bits/stdc++.h>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "debayering.h"
#include "WB.h"
#include "Gamma.h"
#include "ColorSpace.h"
#include "Conversion.h"
#include "Morphology.h"
using namespace cv;
using namespace std;
string filename;
using matrix = vector<vector<double>>;
int main(int argc, char **argv)
{
    string filename = argv[2];
    string readCommand = "dcraw -4 -D -T " + filename;
    int ret = system("python3.8 /home/om/Documents/ImagePipeline/src/Read_image.py");
    Mat im = imread(argv[2]);
    int height = im.rows, width = im.cols;
    // PixelData.txt ==> Contains the pixel values of CFA
    fstream inputFile("PixelData.txt", ios::in);
    double buffer;
    int i = 0;
    vector<double> temp;
    matrix image(height + 4, vector<double>(width + 4, 0));
    while (inputFile)
    {
        inputFile >> buffer;
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
    vector<vector<vector<double>>> debayered_image = debayering(image, height, width);
    matrix R = debayered_image[0], G = debayered_image[1], B = debayered_image[2];
    double avgRed = averageOfPixels(R);
    double avgGreen = averageOfPixels(G);
    double avgBlue = averageOfPixels(B);

    R = whiteBalance(R, avgRed, avgGreen, avgBlue);
    G = whiteBalance(G, avgRed, avgGreen, avgBlue);
    B = whiteBalance(B, avgRed, avgGreen, avgBlue);

    R = gammaCorrection(R, atof(argv[1]));
    G = gammaCorrection(G, atof(argv[1]));
    B = gammaCorrection(B, atof(argv[1]));

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
    rgb_image.push_back(b_img);
    rgb_image.push_back(g_img);
    rgb_image.push_back(r_img);

    Mat final_image;
    Mat filtered_image;
    cv::merge(rgb_image, final_image);
    cv::resize(final_image, final_image, Size(500, 500));

    imshow("Output", final_image);
    waitKey(0);
}