/*
*Author List: Om Doiphode
*Filename: rotate.cpp
*Functions: vector<int> shear(double, int, int),
            matrix Rotate(matrix, double)
Here, matrix=vector<vector<double>>
*Global Variables: NONE
*/
#include <bits/stdc++.h>
using namespace std;
using matrix = vector<vector<double>>;
/*
* Function Name: shear
* Input: angle --> angle of rotation in degrees
         x, y--> coordinates of the pixel
* Output: Returns the coordinates after shear transformation
* Logic:
    |1  -tan(𝜃/2) |  |1        0|  |1  -tan(𝜃/2) |
    |0      1     |  |sin(𝜃)   1|  |0      1     |
* Example Call: shear(45,3,4);
*/
vector<int> shear(double angle, int x, int y)
{
    vector<int> coordinates;
    //  shear 1
    double tangent = tan(angle / 2);
    int new_x = round(x - y * tangent);
    int new_y = y;

    // shear 2
    new_y = round(new_x * sin(angle) + new_y); // since there is no change in new_x according to the shear matrix

    // shear 3
    new_x = round(new_x - new_y * tangent); // since there is no change in new_y according to the shear matrix

    coordinates.push_back(new_y);
    coordinates.push_back(new_x);

    return coordinates;
}
/*
* Function Name: Rotate
* Input: image --> single channel image,
         angle --> angle of rotation in degrees
         -ve angle --> Counter clockwise rotation
         +ve angle --> Clockwise rotation
* Output: Returns the rotated image
* Logic:
        --> This works by expanding 2D rotation matrix into three different matrices.
        -->In the first shear operation, raster columns are simply shifted up and down relative to each other.
        -->The shearing is symmetric around the center of the image.
        -->It’s analogous to shearing a deck of playing cards.

        -->The second shear operation does a similar thing on the previous image, but this time does the shearing left to right.

        -->The final shear is the same as the first operation; this time applied to the intermediate image.
* Example Call: Rotate(image, 45);
*/
matrix Rotate(matrix image, double angle)
{
    // Define the most occuring variables
    double rads = 2 * M_PI * (double(angle) / 360); // Convverting the angle to radians
    double cosine = cos(rads);
    double sine = sin(rads);

    int height = image.size();   // define the height of the image
    int width = image[0].size(); // define the width of the image

    // Define the height and width of the new image that is to be formed
    int new_height = round(abs(image.size() * cosine) + abs(image[0].size() * sine)) + 1;
    int new_width = round(abs(image[0].size() * cosine) + abs(image.size() * sine)) + 1;

    // Define another image variable of dimensions of new_height and new _column filled with zeros
    matrix output(new_height, vector<double>(new_width, 0));

    // Find the centre of the image about which we have to rotate the image
    int original_centre_height = round(((image.size() + 1) / 2) - 1);   // with respect to the original image
    int original_centre_width = round(((image[0].size() + 1) / 2) - 1); // with respect to the original image

    // Find the centre of the new image that will be obtained
    int new_centre_height = round(((new_height + 1) / 2) - 1); // with respect to the original image
    int new_centre_width = round(((new_width + 1) / 2) - 1);   // with respect to the original image

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // co-ordinates of pixel with respect to the centre of original image
            int y = image.size() - 1 - i - original_centre_height;
            int x = image[0].size() - 1 - j - original_centre_width;

            // Applying shear Transformation
            vector<int> coordinates = shear(rads, x, y);
            int new_y = coordinates[0];
            int new_x = coordinates[1];

            // since image will be rotated the centre will change too,
            // so to adust to that we will need to change new_x and new_y with respect to the new centre
            new_y = new_centre_height - new_y;
            new_x = new_centre_width - new_x;

            output[new_y][new_x] = image[i][j]; // writing the pixels to the new destination in the output image
        }
    }
    return output;
}