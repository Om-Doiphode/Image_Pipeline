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
#include "rotate.h"
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

    string choice;
    do
    {
        cout << "___________________________________________" << endl;
        cout << "################################ Menu ################################# " << endl;
        cout << "1: Debayered Image" << endl;
        cout << "2: Gamma corrected Image" << endl;
        cout << "3: RGB --> Grayscale Image" << endl;
        cout << "4: Grayscale --> Binary Image" << endl;
        cout << "5: Edge Detection" << endl;
        cout << "6: Blurred Image" << endl;
        cout << "7: RGB --> HSV Image" << endl;
        cout << "8: Morphological Operations" << endl;
        cout << "9: Rotate the image" << endl;
        cout << "q: To quit" << endl;
        cout << "_____________________________________________" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == "1")
        {

            Mat final_image = create3DImage(R, G, B);
            resize(final_image, final_image, Size(1000, 1000));

            // Scaling the image so that it can be saved.
            final_image.convertTo(final_image, CV_8UC3, 255.0);
            imwrite("Output.png", final_image);
            resize(final_image, final_image, Size(700, 700));
            imshow("Debayered Image", final_image);
            cout << "\n\nImage saved as \"Output.png\"" << endl;
        }
        else if (choice == "2")
        {
            cout << "Applying gamma correction" << endl;
            R = gammaCorrection(R, atof(argv[1]));
            G = gammaCorrection(G, atof(argv[1]));
            B = gammaCorrection(B, atof(argv[1]));
            Mat gammacorrectedimage = create3DImage(R, G, B);
            gammacorrectedimage.convertTo(gammacorrectedimage, CV_8UC3, 255.0);
            imwrite("Gamma.png", gammacorrectedimage);
            resize(gammacorrectedimage, gammacorrectedimage, Size(700, 700));
            imshow("Gamma", gammacorrectedimage);
            cout << "\n\nImage saved as \"Gamma.png\"" << endl;
        }
        else if (choice == "3")
        {
            Mat grayImage = create2DImage(cvtGray(R, G, B));
            grayImage.convertTo(grayImage, CV_8UC3, 255.0);
            imwrite("Grayscale.png", grayImage);
            resize(grayImage, grayImage, Size(500, 500));
            imshow("Grayscale", grayImage);
            cout << "\n\nImage saved as \"Grayscale.png\"" << endl;
        }
        else if (choice == "4")
        {
            Mat binImage = create2DImage(cvtBinary(cvtGray(R, G, B)));
            binImage.convertTo(binImage, CV_8UC3, 255.0);
            imwrite("BinaryImage.png", binImage);
            resize(binImage, binImage, Size(500, 500));
            imshow("Binary", binImage);
            cout << "\n\nImage saved as \"BinaryImage.png\"" << endl;
        }
        else if (choice == "5")
        {
            Mat edges = create2DImage(edgeDetect(R, G, B));
            edges.convertTo(edges, CV_8UC3, 255.0);
            imwrite("Edges.png", edges);
            resize(edges, edges, Size(500, 500));
            imshow("Edges", edges);
            cout << "\n\nImage saved as \"Edges.png\"" << endl;
        }
        else if (choice == "6")
        {
            cout << "___________________________________" << endl;
            cout << "######################## Blurring ####################" << endl;
            cout << "M: Mean Filter" << endl;
            cout << "Md: Median Filter" << endl;
            cout << "G: Gaussian Filter" << endl;
            cout << "______________________________________" << endl;
            string ch;
            cout << "Enter your choice: ";
            cin >> ch;
            if (ch == "M")
            {
                int n;
                cout << "Enter kernel size (Odd number): ";
                cin >> n;
                matrix r_blur = meanFilter(R, n);
                matrix g_blur = meanFilter(G, n);
                matrix b_blur = meanFilter(B, n);

                Mat blur_image = create3DImage(r_blur, g_blur, b_blur);
                blur_image.convertTo(blur_image, CV_8UC3, 255.0);

                imwrite("Mean_Blur_Image.png", blur_image);
                resize(blur_image, blur_image, Size(500, 500));
                imshow("Mean Blur", blur_image);
                cout << "\n\nImage saved as \"Mean_Blur_Image.png\"" << endl;
            }
            else if (ch == "Md")
            {
                matrix r_blur = filter(R);
                matrix g_blur = filter(G);
                matrix b_blur = filter(B);

                Mat blur_image = create3DImage(r_blur, g_blur, b_blur);
                blur_image.convertTo(blur_image, CV_8UC3, 255.0);

                imwrite("Median_Blur_Image.png", blur_image);
                resize(blur_image, blur_image, Size(500, 500));
                imshow("Median", blur_image);
                cout << "\n\nImage saved as \"Median_Blur_Image.png\"" << endl;
            }
            else if (ch == "G")
            {
                int n;
                cout << "Enter kernel size (Odd number): ";
                cin >> n;
                matrix r_blur = gaussianFilter(R, n);
                matrix g_blur = gaussianFilter(G, n);
                matrix b_blur = gaussianFilter(B, n);

                Mat blur_image = create3DImage(r_blur, g_blur, b_blur);
                blur_image.convertTo(blur_image, CV_8UC3, 255.0);

                imwrite("Gaussian_Blur_Image.png", blur_image);
                resize(blur_image, blur_image, Size(500, 500));
                imshow("Gaussian Blur", blur_image);
                cout << "\n\nImage saved as \"Gaussian_Blur_Image.png\"" << endl;
            }
        }
        else if (choice == "7")
        {
            vector<vector<vector<double>>> hsv = rgb2hsv(R, G, B);
            Mat hsvImage = create3DImage(hsv[0], hsv[1], hsv[2]);
            hsvImage.convertTo(hsvImage, CV_8UC3, 255.0);
            imwrite("HSVImage.png", hsvImage);
            resize(hsvImage, hsvImage, Size(500, 500));
            imshow("HSV", hsvImage);
            cout << "\n\nImage saved as \"HSVImage.png\"" << endl;
        }
        else if (choice == "8")
        {
            cout << "___________________________________" << endl;
            cout << "######################## Morphological Operations ####################" << endl;
            cout << "E: Erosion" << endl;
            cout << "D: Dilation" << endl;
            cout << "O: Opening" << endl;
            cout << "C: Closing" << endl;
            cout << "G: Gradient" << endl;
            cout << "T: Top Hat" << endl;
            cout << "B: Black Hat" << endl;
            cout << "______________________________________" << endl;
            string ch;
            cout << "Enter your choice: ";
            cin >> ch;
            if (ch == "E")
            {
                cout << "Enter the kernel size (Odd number): ";
                int n;
                cin >> n;
                Mat eroded_image = create2DImage(Erosion(cvtGray(R, G, B), n));
                eroded_image.convertTo(eroded_image, CV_8UC3, 255.0);
                imwrite("Erosion.png", eroded_image);
                resize(eroded_image, eroded_image, Size(500, 500));
                imshow("Erosion", eroded_image);
                cout << "\n\nImage saved as \"Erosion.png\"" << endl;
            }
            else if (ch == "D")
            {
                cout << "Enter the kernel size (Odd number): ";
                int n;
                cin >> n;
                Mat dilated_image = create2DImage(Dilation(cvtGray(R, G, B), n));
                dilated_image.convertTo(dilated_image, CV_8UC3, 255.0);
                imwrite("Dilation.png", dilated_image);
                resize(dilated_image, dilated_image, Size(500, 500));
                imshow("Dilation", dilated_image);
                cout << "\n\nImage saved as \"Dilation.png\"" << endl;
            }
            else if (ch == "O")
            {
                cout << "Enter the kernel size (Odd number): ";
                int n;
                cin >> n;
                Mat opened_image = create2DImage(Opening(cvtGray(R, G, B), n));
                opened_image.convertTo(opened_image, CV_8UC3, 255.0);
                imwrite("Opening.png", opened_image);
                resize(opened_image, opened_image, Size(500, 500));
                imshow("Opening", opened_image);
                cout << "\n\nImage saved as \"Opening.png\"" << endl;
            }
            else if (ch == "C")
            {
                cout << "Enter the kernel size (Odd number): ";
                int n;
                cin >> n;
                Mat closed_image = create2DImage(Closing(cvtGray(R, G, B), n));
                closed_image.convertTo(closed_image, CV_8UC3, 255.0);
                imwrite("Closing.png", closed_image);
                resize(closed_image, closed_image, Size(500, 500));
                imshow("Closing", closed_image);
                cout << "\n\nImage saved as \"Closing.png\"" << endl;
            }
            else if (ch == "G")
            {
                cout << "Enter the kernel size (Odd number): ";
                int n;
                cin >> n;
                Mat gradient_image = create2DImage(Gradient(cvtGray(R, G, B), n));
                gradient_image.convertTo(gradient_image, CV_8UC3, 255.0);
                imwrite("Gradient.png", gradient_image);
                resize(gradient_image, gradient_image, Size(500, 500));
                imshow("Gradient", gradient_image);
                cout << "\n\nImage saved as \"Gradient.png\"" << endl;
            }
            else if (ch == "T")
            {
                cout << "Enter the kernel size (Odd number): ";
                int n;
                cin >> n;
                Mat topHat_image = create2DImage(topHat(cvtGray(R, G, B), n));
                topHat_image.convertTo(topHat_image, CV_8UC3, 255.0);
                imwrite("TopHat.png", topHat_image);
                resize(topHat_image, topHat_image, Size(500, 500));
                imshow("TopHat", topHat_image);
                cout << "\n\nImage saved as \"TopHat.png\"" << endl;
            }
            else if (ch == "B")
            {
                cout << "Enter the kernel size (Odd number): ";
                int n;
                cin >> n;
                Mat blackHat_image = create2DImage(blackHat(cvtGray(R, G, B), n));
                blackHat_image.convertTo(blackHat_image, CV_8UC3, 255.0);
                imwrite("BlackHat.png", blackHat_image);
                resize(blackHat_image, blackHat_image, Size(500, 500));
                imshow("BlackHat", blackHat_image);
                cout << "\n\nImage saved as \"BlackHat.png\"" << endl;
            }
        }
        else if (choice == "9")
        {
            int n;
            cout << "Enter the angle of rotation(in degrees): ";
            cin >> n;
            matrix R_rotated = Rotate(R, n);
            matrix G_rotated = Rotate(G, n);
            matrix B_rotated = Rotate(B, n);
            Mat rotated_image = create3DImage(R_rotated, G_rotated, B_rotated);
            rotated_image.convertTo(rotated_image, CV_8UC3, 255.0);
            imwrite("Rotated.png", rotated_image);
            resize(rotated_image, rotated_image, Size(500, 500));
            imshow("Rotated", rotated_image);
        }
    } while (choice != "q");
    waitKey(0);
}