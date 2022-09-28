/*
 *Author List: Om Doiphode, Kedar Dhamankar
 *Filename: main.cpp
 *Functions: main(int,char**)
 *Global Variable: NONE
 */

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
#include "Filters.h"
#include "Edges.h"
#include "CreateImage.h"
using namespace cv;
using namespace std;
using matrix = vector<vector<double>>;
/*
* Function Name: main
* Input: char **argv
         argv[1] -> value for gamma
         argv[2] -> path to the image file
* Output: int to inform the caller that the program exited correctly or incorrectly (C code standard)
* Logic:  Ask the user for the path to the image file, read the image file and store its pixel values in a .txt file.
          Make a 2D vector of image from the stored pixel values and apply debayering, White Balance, gamma Correction algorithms.
*Example Call: Called automatically by the Operating System
*/
int main(int argc, char **argv)
{
    string filename = argv[2]; // Getting the filename from the command line
    string readCommand = "python3.8 /home/om/Documents/Image_Pipeline/src/Read_image.py " + filename;
    int ret = system(readCommand.c_str()); // Calling the python program from the command line
    Mat im = imread(argv[2]);              // Reading the image
    int height = im.rows, width = im.cols; // Getting the height and width of the input image
    // PixelData.txt ==> Contains the pixel values of CFA
    fstream inputFile("PixelData.txt", ios::in);
    double buffer;
    int i = 0;
    vector<double> temp;
    // Making an empty image filled with zeros
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
    // Debayering
    vector<vector<vector<double>>> debayered_image = debayering(image, height, width);
    matrix R = debayered_image[0], G = debayered_image[1], B = debayered_image[2];
    vector<vector<vector<double>>> adjusted = autoAdjust(R, G, B, R.size(), R[0].size());
    Mat adjustImage = create3DImage(scale(adjusted[0]), scale(adjusted[1]), scale(adjusted[2]));
    double avgRed = averageOfPixels(R);
    double avgGreen = averageOfPixels(G);
    double avgBlue = averageOfPixels(B);

    cout << "Auto White Balance in place" << endl;
    R = whiteBalance(R, avgRed, avgGreen, avgBlue);
    G = whiteBalance(G, avgRed, avgGreen, avgBlue);
    B = whiteBalance(B, avgRed, avgGreen, avgBlue);

    cout << "Applying gamma correction" << endl;
    R = gammaCorrection(R, atof(argv[1]));
    G = gammaCorrection(G, atof(argv[1]));
    B = gammaCorrection(B, atof(argv[1]));

    matrix R_blur = filter(R);
    matrix G_blur = filter(G);
    matrix B_blur = filter(B);
    matrix R_black = (blackLevelCorrection(R));
    matrix G_black = (blackLevelCorrection(G));
    matrix B_black = (blackLevelCorrection(B));

    Mat Black = create3DImage(R_black, G_black, B_black);

    Mat blur_image = create3DImage(R_blur, G_blur, B_blur);

    Mat final_image = create3DImage(R, G, B);
    // Mat edge = create2DImage(gaussianFilter());
    // Mat grayImage = create2DImage(cvtGray(R, G, B));
    // Mat binary_image = create2DImage(cvtBinary(cvtGray(R, G, B)));

    // // vector<vector<vector<double>>> HSV = rgb2hsv(R, G, B);
    // Mat hsv = create2DImage(edgeDetect(R, G, B));
    resize(final_image, final_image, Size(1000, 1000));
    // resize(grayImage, grayImage, Size(1000, 1000));
    // resize(binary_image, binary_image, Size(1000, 1000));
    // resize(blur_image, blur_image, Size(1000, 1000));
    resize(blur_image, blur_image, Size(1000, 1000));
    resize(adjustImage, adjustImage, Size(1000, 1000));
    resize(Black, Black, Size(1000, 1000));

    imshow("Output", final_image);
    imshow("Edges", blur_image);
    imshow("Adjusted", adjustImage);
    imshow("Black", Black);
    // imshow("Gray", grayImage);
    // imshow("Binary", binary_image);
    // imshow("HSV", hsv);
    // imshow("Blur", blur_image);
    waitKey(0);
}