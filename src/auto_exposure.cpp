/*
* Author List: Kedar Dhamankar
* Filename: AutoExposure.cpp
* Functions: Find_Mean, AutoExposure
* Global Variables: height, width, Image
*/ 

#include <bits/stdc++.h>
using namespace std;
using matrix=vector<vector<double>>;


/*
* Function Name: Find_Mean
* Input: Passes filename parameter which finds mean value of the file 
* Output: Returns the mean value of the file having datatype -> double
* Logic: Loops through the file and adds each value to 'sum' variable at each iteration
         Then divides the sum by total number of values in the file to find Mean 
* Example Call: Find_Mean("RedScaled.txt");   
                where RedScaled.txt is a file having normalised values of image's Red Channel
*/

double Find_Mean(matrix image)
{                  //Opens the file in read mode
    double sum = 0;                         //declare sum variable to store sum of all value of file
    for ( int i=0; i<image.size(); i++)           //Looping through the whole file
    {
        for (int j=0; j<image[0].size(); j++)
        {
            sum += image[i][j];
        }
    }


    double mean = sum/(image.size()*image[0].size());       //Calculates the mean value of file
    cout<<"Sum = "<<sum<<" "<<endl;
    cout<<"Mean = "<<mean<<" "<<endl;

    return mean;                            //Returns the mean value of the file to the function
}


/*
* Function Name: AutoExposure
* Input: Passes 2 filename parameters which will read first file and stored Auto Exposure corrected values in another file
         and passes mean value of the file which was return by the Find_Mean function
* Output: Returns no value to the function
* Logic: Image channel having normalised values in the range 0-1 is run through a loop
         where each pixel value is compared to the mean intensity value of the image
         and correction is applied accordingly
* Example Call: AutoExposure("GreenScaled.txt","GreenAE.txt", Green_mean);
*/ 

matrix AutoExposure(matrix image, double mean)
{
    matrix res(image.size(),vector<double>(image[0].size(),0));
    double X1;                                  //X1 stores the value of file1 in each iteration compares it to mean value
    double X2;                                  //X2 stores the corrected intensity value of each pixel


    for (int i=0; i<image.size(); i++)                //Looping through the image channels
    {
        for (int j=0; j<image[0].size(); j++)
        {
            if (image[i][j]>mean && image[i][j]<0.8)              //Comparing each intensity value to the mean value and applying percentage correction
            {
                res[i][j]+=0.6*image[i][j];
            }
            else if(X1<mean)
            {
                res[i][j]+=0.8*image[i][j];
            }

            else if (X1>0.8 && X1<=1)
            {
                res[i][j]-=0.2*image[i][j];
            }
            
        }
    }
    return res;
}
