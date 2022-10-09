/*
*Author List: Om Doiphode, Kedar Dhamankar
*Filename: morphology.cpp
*Functions: double sum(matrix),
            matrix multiply(matrix, matrix),
            matrix vectorSlice(matrix, int, int, int, int),
            matrix Erosion(matrix, int),
            matrix Dilation(matrix, int),
            matrix Closing(matrix, int),
            matrix Opening(matrix, int),
            matrix Gradient(matrix, int),
            matrix topHat(matrix, int),
            matrix blackHat(matrix, int)
Here, matrix=vector<vector<double>>
*Global Variables: NONE
*/
#include <bits/stdc++.h>
using namespace std;
using matrix = vector<vector<double>>;
/*
 * Function Name: sum
 * Input: A -> 2D vector of image
 * Output: returns the sum of the pixel values
 * Logic: Calculates the sum by accessing each element of 2D vector
 * Example Call: sum(image);
 */
double sum(matrix A)
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
/*
 * Function Name: multiply
 * Input: sliced_image -> A portion (2D vector) extracted from a bigger image, kernel -> a mask(2D vector) used for convolution, morphological operations,etc
 * Output: returns the product of the two matrices
 * Logic: The code loops through the rows and columns of the matrix and stores the product of the elements of a row in a temporary vector (temp) and the temporary vector is then pushed to a 2D vector
 * Example Call: multiply(sliced_image,kernel);
 */

matrix multiply(matrix sliced_image, matrix kernel)
{
    matrix C;
    int n = kernel.size();
    for (int i = 0; i < n; i++)
    {
        vector<double> temp;
        for (int j = 0; j < n; j++)
        {
            temp.push_back(sliced_image[i][j] * kernel[i][j]);
        }
        C.push_back(temp);
    }
    return C;
}
/*
 * Function Name: vectorSlice
 * Input: image -> 2D vector of image, row_lower: lower row number, row_upper: upper row number, col_lower: lower column number, col_upper: upper column number
 * Output: returns the sliced image
 * Logic: Nested for loop is used wherein the outer loop runs from row_lower to row_upper(exclusive) while the inner loop runs from col_lower to col_upper(exclusive).
 *        The elements of the image are then pushed into a temporary 1D vector and then after the completion of the inner for loop, the temporary vector is pushed into the sliced_image (2D vector)
 * Example Call: vectorSlice(image,1,3,1,3);
 */
matrix vectorSlice(matrix &image, int row_lower, int row_upper, int col_lower, int col_upper)
{
    matrix sliced_image;
    for (int i = row_lower; i < row_upper; i++)
    {
        vector<double> temp;
        for (int j = col_lower; j < col_upper; j++)
        {
            temp.push_back(image[i][j]);
        }
        sliced_image.push_back(temp);
    }
    return sliced_image;
}
/*
 * Function Name: Erosion
 * Input: img -> 2D vector of image (grayscale or binary image),
 *        kernel_size -> size of the kernel (must be odd)
 * Output: returns the eroded image
 * Logic: A kernel (kernel_size x kernel_size) is slid across the image. If all the pixels under the kernel is 1 then the input pixel will be 1 otherwise it will be 0 if at least one pixel under the kernel is zero.
 *        Default is a 3x3 kernel.
 * Example Call: Erosion(image,3);
 */
matrix Erosion(matrix img, int kernel_size = 3)
{
    // Creating a 2d vector of size kernel_size x kernel_size filled with 1's
    matrix kernal(kernel_size, vector<double>(kernel_size, 1));
    // Initialising an empty image filled with zeros
    matrix new_image(img.size(), vector<double>(img[0].size(), 0));
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
        cout << "\r [" << ceil(i * 100 / y1) << '%' << "] ";
    }
    cout << endl;
    return new_image;
}
/*
 * Function Name: Dilation
 * Input: img -> 2D vector of image (grayscale or binary image)
 *        kernel_size--> size of the kernel (must be odd)
 * Output: returns the dilated image
 * Logic: A 3x3 kernel is slid across the image. The output is 1 if at least one of the input pixels (under the kernel) is 1. Otherwise, the output is 0.
 * Example Call: Dilation(image)
 */
matrix Dilation(matrix img, int kernel_size = 3)
{
    matrix kernal(kernel_size, vector<double>(kernel_size, 1));
    matrix new_image(img.size(), vector<double>(img[0].size(), 0));
    int addition = sum(kernal);
    int m = kernal.size(), n = kernal[0].size();
    int y = img.size(), x = img[0].size();
    int y1 = y - m + 1;
    int x1 = x - n + 1;
    for (int i = 1; i < y1; i++)
    {
        for (int j = 1; j < x1; j++)
        {
            // matrix temp = vectorSlice(img, i - 1, i + 2, j - 1, j + 2);
            double product = sum(multiply(vectorSlice(img, i, i + m, j, j + n), kernal));
            if (product > 0)
            {
                new_image[i][j] = 1;
            }
            else
            {
                new_image[i][j] = 0;
            }
        }
        cout << "\r [" << ceil(i * 100 / y1) << '%' << "] ";
    }
    cout << endl;
    return new_image;
}
/*
 * Function Name: Closing
 * Input: img -> 2D vector of image (grayscale or binary image),
 *        kernel_size --> size of the kernel (must be odd)
 * Output: returns the closed image
 * Logic: First dilation is applied by calling the Dilation function and then Erosion function is called to apply erosion.
 * Example Call: Closing(image)
 */
matrix Closing(matrix image, int kernel_size = 3)
{
    matrix final_image = Erosion(image, kernel_size);
    matrix final_image2 = Dilation(final_image, kernel_size);
    return final_image2;
}
/*
 * Function Name: Opening
 * Input: img -> 2D vector of image (grayscale or binary image),
 *        kernel_size-->size of the kernel (must be odd)
 * Output: returns the opened image
 * Logic: First erosion is applied by calling the Erosion function and then Dilation function is called to apply dilation.
 * Example Call: Opening(image)
 */
matrix Opening(matrix image, int kernel_size = 3)
{
    matrix final_image = Dilation(image, kernel_size);
    matrix final_image2 = Erosion(final_image, kernel_size);
    return final_image2;
}
/*
 * Function Name: Gradient
 * Input: img -> 2D vector of image (grayscale or binary image),
 *        kernel_size --> size of the kernel (must be odd)
 * Output: returns the gradient of the image
 * Logic: First the image is dilated and then the original image is eroded. The difference between the dilated and eroded image gives the gradient.
 * Example Call: Gradient(image)
 */
matrix Gradient(matrix image, int kernel_size)
{
    matrix dilated = Dilation(image, kernel_size);
    matrix eroded = Erosion(image, kernel_size);
    matrix final_image(image.size(), vector<double>(image[0].size(), 0));
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            final_image[i][j] = dilated[i][j] - eroded[i][j];
        }
    }
    return final_image;
}
/*
 * Function Name: topHat
 * Input: image -> 2D vector of image (grayscale or binary image),
 *        kernel_size --> size of the kernel(must be odd)
 * Output: returns the top hat of the image
 * Logic: Calculates the difference between the input image and opening of the image.
 * Example Call: topHat(image,3);
 */
matrix topHat(matrix image, int kernel_size)
{
    matrix opened_image = Opening(image, kernel_size);
    matrix res(image.size(), vector<double>(image[0].size(), 0));
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            res[i][j] = image[i][j] - opened_image[i][j];
        }
    }
    return res;
}
/*
 * Function Name: blackHat
 * Input: image -> 2D vector of image (grayscale or binary image),
 *        kernel_size --> size of the kernel(must be odd)
 * Output: returns the black hat of the image
 * Logic: Calculates the difference between the closed image and input image
 * Example Call: blackHat(image,3);
 */
matrix blackHat(matrix image, int kernel_size)
{
    matrix closed_image = Closing(image);
    matrix res(image.size(), vector<double>(image[0].size(), 0));
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            res[i][j] = closed_image[i][j] - image[i][j];
        }
    }
    return res;
}
