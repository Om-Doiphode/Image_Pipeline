/*
* Author List: Kedar Dhamankar
* Filename: Scaling.cpp
* Functions: scaling
* Global Variables: height, width, image (2d array)
*/


#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int height = 1324;                    //Height of image
const int width = 2012;                     //Width of image
double Image [height][width];               //2d array which stores image intensity values



/*
* Function Name: scaling
* Input: 2 parameters, both are filenames from which first one is opened in read mode to read values
         and second filename is opened in write mode to store scaled values
* Output: Returns no value to the function
* Logic: First it finds the maximum and minimum values of the file and then applies scaling to each
         value as per the formula given
* Example Call: scaling("R.txt", "RedScaled.txt");
*/


void scaling(string file1, string file2)
{
    ifstream f1(file1);                     //Opening file1 in read mode
    double X;                               //Stores each value of file in X while looping through it
    double max;                             //Stores max value of file
    double min = 0;                         //Stores min value of file


    while (f1>>X)                           //Looping through the file and storing each value in X
    {
        if(X>max)                           //Finds the Maximum value of file
        {
            max = X;
        }
        else if(X<min)                      //Finds the Minimum value of file
        {
            min = X;
        }
    }


    cout<<"Max Value for "<<file1<< " : "<<max<<endl;
    cout<<"Min Value for "<<file1<< " : "<<min<<endl;
    f1.close();

    double Y;                                       //Stores each value of file1 while looping through it
    double Y1;                                      //Stores scaled value of file1
    fstream f2(file1, ios::in);                     //Opens file1 in read mode
    fstream f3(file2, ios::out);                    //Opens file2 in write mode to save scaled values


    for( int i=0; i<height; i++)                    //Looping through the file
    {
        for (int j=0; j<width; j++) 
        {
            f2>>Y;                                  
            Y1 = ((Y - min)/(max - min));           //Calculates the scaled value in range 0-1
            f3<<Y1<<" ";                            //Writes scaled value in file
        }
        f3<<endl;
    }
    f2.close();
    f3.close();
}

int main()
{
    //Calling Scaling function which takes in image channel files and creates and writes scaled image channel values
    scaling("R.txt", "RedScaled.txt");
    scaling("G.txt", "GreenScaled.txt");
    scaling("B.txt", "BlueScaled.txt");
}