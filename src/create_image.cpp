/*
*Author List: Om Doiphode
*Filename: create_image.cpp
*Functions: create2DImage(matrix),
            create3DImage(matrix)
Here, matrix=vector<vector<double>>
*Global Variables: NONE
*/
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace cv;
using matrix = vector<vector<double>>;
/*
 * Function Name: create2DImage
 * Input: image -> 2D vector (single channel)
 * Output: returns the Mat object in order to display the image through opencv
 * Logic: Copies each element of the matrix into a Mat object.
 * Example Call: create2DImage(image)
 */
Mat create2DImage(matrix image)
{
    Mat final_img(image.size(), image.at(0).size(), CV_64FC1);
    for (int i = 0; i < final_img.rows; ++i)
    {
        for (int j = 0; j < final_img.cols; ++j)
        {
            final_img.at<double>(i, j) = image.at(i).at(j);
        }
    }
    return final_img;
}
/*
 * Function Name: create3DImage
 * Input: image1 -> 2D vector (single channel),
 *        image2 -> 2D vector (single channel),
 *        image3 -> 2D vector (single channel)
 * Generally these will be the 3 color channels (eg: RGB)
 * Output: returns the Mat object for the image to be displayed the image through opencv
 * Logic: Copies each element of the matrix into a Mat object.
 * Example Call: create3DImage(image)
 */
Mat create3DImage(matrix image1, matrix image2, matrix image3)
{
    vector<Mat> rgb_image;
    Mat r_img(image1.size(), image1.at(0).size(), CV_64FC1);
    for (int i = 0; i < r_img.rows; ++i)
    {
        for (int j = 0; j < r_img.cols; ++j)
        {
            r_img.at<double>(i, j) = image1.at(i).at(j);
        }
    }
    Mat g_img(image2.size(), image2.at(0).size(), CV_64FC1);
    for (int i = 0; i < g_img.rows; ++i)
    {
        for (int j = 0; j < g_img.cols; ++j)
        {
            g_img.at<double>(i, j) = image2.at(i).at(j);
        }
    }
    Mat b_img(image3.size(), image3.at(0).size(), CV_64FC1);
    for (int i = 0; i < b_img.rows; ++i)
    {
        for (int j = 0; j < b_img.cols; ++j)
        {
            b_img.at<double>(i, j) = image3.at(i).at(j);
        }
    }
    // Creating a 3D image
    rgb_image.push_back(r_img);
    rgb_image.push_back(g_img);
    rgb_image.push_back(b_img);

    Mat final_image;
    // Merging the color channels
    cv::merge(rgb_image, final_image);
    return final_image;
}