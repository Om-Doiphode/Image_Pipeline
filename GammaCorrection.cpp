#include <iostream>
#include <string>
#include <fstream>
#include<math.h>
using namespace std;

void GammaCorrection (string file1, string file2)
{
    ifstream f1(file1);
    ofstream f2(file2, ios::out);
    double X1, X2;

    for( int i=0; i<480; i++) 
    {
        for (int j=0; j<640; j++) 
        {
            f1>>X1;
            // double Y1 = X1/256;
            X2 = pow(X1,0.45);
            // cout<<"X1 = "<<X1<<endl;
            // cout<<"X2 = "<<X2<<endl;
            // X2 = 255*Y2;
            f2<<X2<<" ";
        }
        f2<<endl;
    }
}

int main()
{
    GammaCorrection("RedScaled.txt", "RedG.txt");
    GammaCorrection("GreenScaled.txt", "GreenG.txt");
    GammaCorrection("BlueScaled.txt", "BlueG.txt");
}