/*
* Author List: Kedar Dhamankar
* Filename: GammaCorrection.cpp
* Functions: GammaCorrection
* Global Variables: height, width
* variables>
*/ 


#include <iostream>
#include <string>
#include <fstream>
#include<math.h>
using namespace std;

const int height = 1324;
const int width = 2012;


/*
* Function Name: GammaCorrection
* Input: filename -> image which is to be gamma corrected and stores corrected values in another file
* Output: Performs Gamma Correction and creates a file having corrected values
          and Returns no value to the function
* Logic: First loops through the file and stores each value in X1, then applies gamma correction
         and stores corrected values in X2 and then creates file2 and stores corrected values in it
* Example Call: GammaCorrection("R.txt", "RedGamma.txt");
*/


void GammaCorrection (string file1, string file2)
{
    ifstream f1(file1);                         //Opens file1 in read mode
    ofstream f2(file2, ios::out);               //Opens file2 in write mode
    double X1;                                  //for storing each value of file1
    double X2;                                  //for storing corrected values


    for( int i=0; i<height; i++)                //Looping through the file
    {
        for (int j=0; j<width; j++) 
        {
            f1>>X1;                             //Storing value in X1
            X2 = pow(X1,0.45);                  //Applying gamma correction to it
            f2<<X2<<" ";                        //Writing the value in file2 
        }
        f2<<endl;
    }
}

int main()
{
    //Calling the function GammaCorrection which takes in one image channel and creates and writes in a new image channel having corrected values
    GammaCorrection("R.txt", "RedGamma.txt");
    GammaCorrection("G.txt", "GreenGamma.txt");
    GammaCorrection("B.txt", "BlueGamma.txt");
}