/*
 * Author List: Kedar Dhamankar
 * Filename: auto_exposure.cpp
 * Functions: Find_Mean, AutoExposure
 * Global Variables: matrix (2d vector)
 */

#include <bits/stdc++.h>
#include <auto_exposure.h>

using namespace std;
using matrix = vector<vector<double>>;

/*
* Function Name: Find_Mean
* Input: Passes 2d image vector of whose mean value is to be calculated
* Output: Returns the mean value of the image matrix
* Logic: Loops through the matri and adds each value to 'sum' variable at each iteration
         Then divides the sum by total number of values in the vector to find Mean
* Example Call: Find_Mean(image);
*/

double Find_Mean(matrix image)
{
    double sum = 0;                        // declare sum variable to store sum of all value of matrix
    for (int i = 0; i < image.size(); i++) // Looping through the matrix
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            sum += image[i][j];
        }
    }

    double mean = sum / (image.size() * image[0].size()); // Calculates the mean value of matrix
    cout << "Sum = " << sum << " " << endl;
    cout << "Mean = " << mean << " " << endl;

    return mean; // Returns the mean value of the matrix to the function
}

/*
* Function Name: AutoExposure
* Input: Passes image matrix and mean value of that matrix
* Output: Returns auto exposure corrected matrix to the function
* Logic: Image channel having normalised values in the range 0-1 is run through a loop
         where each pixel value is compared to the mean intensity value of the image
         and correction is applied accordingly
* Example Call: AutoExposure(image, Green_mean);
*/

matrix AutoExposure(matrix image)
{
    double mean = Find_Mean(image);
    matrix res(image.size(), vector<double>(image[0].size(), 0)); // Corrected image matrix declared

    for (int i = 0; i < image.size(); i++) // Looping through the image channel
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            if (image[i][j] > mean && image[i][j] < 0.8) // Comparing each intensity value to the mean value and applying percentage correction
            {
                res[i][j] += 0.6 * image[i][j];
            }
            else if (image[i][j] < mean)
            {
                res[i][j] += 0.8 * image[i][j];
            }

            else if (image[i][j] > 0.8 && image[i][j] <= 1)
            {
                res[i][j] -= 0.2 * image[i][j];
            }
        }
    }
    return res; // Returns corrected image to the function
}
