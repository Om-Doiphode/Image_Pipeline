/*
* Author List: Kedar Dhamankar
* Filename: BlackLevelCorrection.cpp
* Functions: blacklevelcorrection
* Global Variables: height, width, image, R, G, B
* variables>
*/ 


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int height = 1324;                    //Height of image
const int width = 2012;                     //Width of image

/*
* Function Name: BlackLevelCorrection
* Input: passes 2 filename parameters to the function, 
         from which 1st file is used reading values
         and 2nd file is created to store corrected values
* Output: Performs Black Level Correction and stores in a created file
          and Returns no value to the function
* Logic: Loops through the file to find the global threshold value which is
         used for comparing intensity values and apply correction accordingly
* Example Call: BlackLevelCorrection("Red.txt","RedBLC.txt");
*/

void BlackLevelCorrection(string file1, string file2) 
{
    fstream f1(file1 , ios::in);                    //Opens the file in read mode
    double X;                                       //For storing each value of file 
    double X1;                                      //For storing corrected value
    double max;                                     //Stores maximum value of file

    while (f1>>X)                                   //Storing each value of file1 in X
    {
        if(X>max)                                   //Finding maximum value and store it in 'max' variable
        {
            max = X;
        }
    }

    double glob_thresh_val_R=max/2;                 //Calculate the global threshold value
    cout<<"Max Value for "<<file1<< " : "<<max<<endl;   
    cout<<"Global Threshold Value for "<<file1<<" : "<< glob_thresh_val_R<<endl;
    f1.close();
    
    fstream f2(file1, ios::in);                     //Opens file1 in read mode
    fstream f3(file2, ios::out);                    //Opens file2 in write mode

    for( int i=0; i<480; i++)                       //Looping through the file1 and then saving corrected values in file2
    {
        for (int j=0; j<640; j++) 
        {
            f2>>X1;
            if (X1<=glob_thresh_val_R)          // intensity <= 0.5
            {
                X1 = X1-0.30*X1;
                f3<<X1<<" ";
            }
            else if (X1 <= 0.55*max)           // 0.5 < intensity <= 0.55
            {
                X1 = X1-0.25*X1;
                f3<<X1<<" ";
            } 
            else if (X1 <= 0.59*max)           // 0.55 < intensity <= 0.59
            {
                X1 = X1-0.20*X1;
                f3<<X1<<" ";
            } 
            else if (X1 <= 0.63*max)           // 0.59 < intensity <= 0.63
            {
                X1 = X1-0.15*X1;
                f3<<X1<<" ";
            } 
            else if (X1 <= 0.65*max)           // 0.63 < intensity <= 0.65
            {
                X1 = X1-0.10*X1;
                f3<<X1<<" ";
            }
            else if (X1 <= 0.66*max)           // 0.65 < intensity <= 0.66
            {
                X1 = X1-0.06*X1;
                f3<<X1<<" ";
            }
            else if (X1 <= 0.67*max)           // 0.66 < intensity <= 0.67
            {
                X1 = X1-0.03*X1;
                f3<<X1<<" ";
            }
            else if (X1 <= 0.68*max)           // 0.67 < intensity <= 0.68
            {
                X1 = X1-0.01*X1;
                f3<<X1<<" ";
            }
            else if (X1 <= 0.69*max)           // 0.68 < intensity <= 0.69
            {
                X1 = X1-0.005*X1;
                f3<<X1<<" ";
            }
            else if (X1 <= 0.70*max)           // 0.69 < intensity <= 0.70
            {
                X1 = X1-0.001*X1;
                f3<<X1<<" ";
            }
            else 
            {
                f3<< X1 << " ";
            }
        }
        f3<<endl;
    }
    f2.close();
    f3.close();
}

int main() 
{
    //Calls the function which takes in each Image channel and stores it in a new files after applying correction
    BlackLevelCorrection("Red.txt","RedBLC.txt");
    BlackLevelCorrection("Green.txt","GreenBLC.txt");
    BlackLevelCorrection("Blue.txt","BlueBLC.txt");
    return 0;
}