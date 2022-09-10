#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void blacklevelcorr(string filename, string filename1) 
{
    // string filename;
    // cout<<"Enter name of file : ";
    // cin>>filename;
    fstream f1(filename , ios::in);
    double X, X1;
    double max;
    double min = 0;
    // int arr[480][640];
    while (f1>>X)
    {
        if(X>max) 
        {
            max = X;
        }
    }
    double glob_thresh_val_R=max/2;
    cout<<"Max Value for "<<filename<< " : "<<max<<endl;
    cout<<"Global Threshold Value for "<<filename<<" : "<< glob_thresh_val_R<<endl;
    f1.close();
    
    fstream f2(filename, ios::in);
    fstream f3(filename1, ios::app);
    for( int i=0; i<480; i++) 
    {
        // while (f3>>R1 && j<640) 
        // {
        for (int j=0; j<640; j++) 
        {
            // cout<<j<<" ";
            f2>>X1;
            if (X1<=glob_thresh_val_R)       // intensity <= 0.5
            {
                // cout<<"Value before correction - "<<X1<<endl;
                X1 = X1-0.30*X1;
                // cout<<"Value after correction - "<<X1<<endl;
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
            // cout<<j<<" ";
        }
        // cout<<endl;
        f3<<endl;
    }
    f2.close();
    f3.close();
}

int main() 
{
    blacklevelcorr("Red.txt","1.txt");
    blacklevelcorr("Green.txt","2.txt");
    blacklevelcorr("Blue.txt","3.txt");
    return 0;
}