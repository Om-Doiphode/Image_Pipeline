/*
* Author List: Kedar Dhamankar
* Filename: AutoExposure.cpp
* Functions: Find_Mean, AutoExposure
* Global Variables: height, width, Image
*/ 


#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int height = 1324;                        //Height of image
const int width = 2012;                         //Width of image
double Image [height][width];                   //2d array which will store values of image file


/*
* Function Name: Find_Mean
* Input: Passes filename parameter which finds mean value of the file 
* Output: Returns the mean value of the file having datatype -> double
* Logic: Loops through the file and adds each value to 'sum' variable at each iteration
         Then divides the sum by total number of values in the file to find Mean 
* Example Call: Find_Mean("RedScaled.txt");   
                where RedScaled.txt is a file having normalised values of image's Red Channel
*/

double Find_Mean(string filename)
{
    ifstream f1(filename);                  //Opens the file in read mode
    double sum = 0;                         //declare sum variable to store sum of all value of file
    double X;                               //Each value of file will be stored in X at each iteration
    int k=0;
    for ( int i=0; i<height; i++)           //Looping through the whole file
    {
        for (int j=0; j<width; j++)
        {
            f1>>X;
            sum += X;
            k++;
        }
    }


    double mean = sum/(height*width);       //Calculates the mean value of file
    cout<<"Sum = "<<sum<<" "<<endl;
    cout<<"Mean = "<<mean<<" "<<endl;

    f1.close();

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

void AutoExposure(string file1, string file2, double mean)
{
    ifstream f1(file1);                         //opens file1 in read mode to read and compare it's values
    ofstream f2(file2, ios::out);               //opens file2 in write mode to write corrected values in

    double X1;                                  //X1 stores the value of file1 in each iteration compares it to mean value
    double X2;                                  //X2 stores the corrected intensity value of each pixel


    for (int i=0; i<height; i++)                //Looping through the image channels
    {
        for (int j=0; j<width; j++)
        {
            f1>>X1;
            if (X1>mean && X1<0.8)              //Comparing each intensity value to the mean value and applying percentage correction
            {
                X2+=0.6*X1;
                f2<<X2<<" ";
            }
            else if(X1<mean)
            {
                X2+= 0.8*X1;
                f2<<X2<<" ";
            }

            else if (X1>0.8 && X1<=1)
            {
                X2-= 0.2*X1;
                f2<<X2<<" ";
            }
            else
            {
                f2<<X2<<" ";
            }
        }
        f2<<endl;
    }
    f1.close();
    f2.close();
}

int main()
{

    double Red_mean = Find_Mean("RedScaled.txt");               //Calling Find_Mean function which will find and store mean value of file in Red_Mean
    double Green_mean = Find_Mean("GreenScaled.txt");           //Calling Find_Mean function which will find and store mean value of file in Green_Mean
    double Blue_mean = Find_Mean("BlueScaled.txt");             //Calling Find_Mean function which will find and store mean value of file in Blue_Mean

    AutoExposure("RedScaled.txt","RedAE.txt", Red_mean);        //Calling AutoExposure function which will apply correction to the image channel and store in another file
    AutoExposure("GreenScaled.txt","GreenAE.txt", Green_mean);
    AutoExposure("BlueScaled.txt","BlueAE.txt", Blue_mean);

}