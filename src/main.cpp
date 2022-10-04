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
#include "auto_white_balance.h"
#include "gamma.h"
#include "color_space_conversion.h"
#include "conversion.h"
#include "morphology.h"
#include "filters.h"
#include "edges.h"
#include "create_image.h"
#include "auto_exposure.h"
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
    string readCommand = "python3.8 ../src/read_image.py " + filename;
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

    Mat final_image = create3DImage(R, G, B);
    resize(final_image, final_image, Size(1000, 1000));

    imshow("Output", final_image);
    // Scaling the image so that it can be saved.
    final_image.convertTo(final_image, CV_8UC3, 255.0);
    imwrite("Output.png", final_image);
    waitKey(0);
}