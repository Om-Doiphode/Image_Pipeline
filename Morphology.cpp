#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int image[480][640];                    //for storing Binary image pixel values
int image1[480][640];                   //for storing Dilated image pixel values
int image2[480][640];                   //for storing Eroded image pixel values
int image3[480][640];                   //for storing Gradient image pixel values


void RGBtoGrayscale(string filename1, string filename2, string filename3, string filename4)
{
    double R, G, B, GS;

    fstream Red(filename1, ios::in);
    fstream Green(filename2, ios::in);
    fstream Blue(filename3, ios::in);
    fstream Grayscale(filename4, ios::out);
    for (int i=0; i<480; i++)
    {
        for (int j=0; j<640; j++)
        {
            Red >> R;
            Green >> G;
            Blue >> B;
            GS = 0.299*R + 0.587*G + 0.114*B;
            Grayscale << GS << " ";
        }
        Grayscale << endl;
    }

    Red.close();
    Green.close();
    Blue.close();
    Grayscale.close();
}


void Grayscale_to_Binary (string filename1, string filename2)
{
    double GS, max{0}, glob_thresh_value;
    fstream Grayscale(filename1, ios::in);
    for (int i=0; i<480; i++)
    {
        for (int j=0; j<640; j++)
        {
            Grayscale >> GS;
            if (GS > max)
            {
                max = GS;
            }
            else
            continue;
        }
    }
    glob_thresh_value = max/2;
    Grayscale.close();

    fstream Gray_scale(filename1, ios::in);
    fstream Binary(filename2, ios::out);

    for(int i=0; i<480; i++)
    {
        for(int j=0; j<640; j++)
        {
            Gray_scale >> GS;
            if (GS < glob_thresh_value)
            {
                GS = 0;
                Binary<<GS<<" ";
            }
            else
            {
                GS = 1;
                Binary<<GS<<" ";
            }
        }
        Binary<<endl;
    }
    Gray_scale.close();
    Binary.close();
}


void Dilation(string filename, string filename1)
{
    int X;
    fstream f1(filename, ios::in);
    fstream f2(filename1, ios::out);
    
    for( int i=0; i<480; i++)
    {
        for (int j=0; j<640; j++)
        {
            f1>>X;
            image[i][j]=X;
            image1[i][j]=X;
            // cout<<"Image : "<<image[i][j];
            // cout<<"     Image1 : "<<image1[i][j];
            // cout<<"     i = "<<i<<endl;
        }
    }
    f1.close();

    for(int i=0; i<480; i++)
    {
        for (int j=0; j<640; j++)
        {
            if (i-1>0 && i<=480 && j-1>0 && j<640)           //Kernel anywhere else
            {
                if((image[i-1][j-1]||image[i-1][j]||image[i-1][j+1]||image[i][j-1]||image[i][j]||image[i][j+1]||image[i+1][j-1]||image[i+1][j]||image[i+1][j+1])==1)
                {
                image1[i][j]=1;
                }
                else
                {
                image1[i][j]=0;
                }
            }
            else if (i-1<0 && j-1<0)                        //Kernel at top left
            {
                if((image[i][j]||image[i][j+1]||image[i+1][j]||image[i+1][j+1])==1)
                {
                    image1[i][j] = 1;
                }
                else
                {
                    image1[i][j] = 0;
                }
            }
            else if (i-1<0 && j+1 == 640)                        //Kernel at top right
            {
                if((image[i][j-1]||image[i][j]||image[i+1][j-1]||image[i+1][j])==1)
                {
                    image1[i][j] = 1;
                }
                else
                {
                    image1[i][j] = 0;
                }
            }
            else if (i+1 == 480 && j-1<0)                         //Kernel at Bottom Left
            {
                if((image[i-1][j]||image[i-1][j+1]||image[i][j]||image[i][j+1])==1)
                {
                    image1[i][j] = 1;
                }
                else
                {
                    image1[i][j] = 0;
                }
            }
            else if (i+1 == 480 && j+1 == 640)                         //Kernel at Bottom Right
            {
                if((image[i-1][j-1]||image[i-1][j]||image[i][j-1]||image[i][j])==1)
                {
                    image1[i][j] = 1;
                }
                else
                {
                    image1[i][j] = 0;
                }
            }
            else if (i==0 && j+1<640 && j-1>0)                                 //Kernel at top middle
            {
                if((image[i][j-1]||image[i][j]||image[i][j+1]||image[i+1][j-1]||image[i+1][j]||image[i+1][j+1])==1)
                {
                    image1[i][j] = 1;
                }
                else
                {
                    image1[i][j] = 0;
                }
            }
            else if (i == 479 && j+1<640 && j-1>0)                                 //Kernel at Bottom Middle
            {
                if((image[i-1][j-1]||image[i-1][j]||image[i-1][j+1]||image[i][j-1]||image[i][j]||image[i][j+1])==1)
                {
                    image1[i][j] = 1;
                }
                else
                {
                    image1[i][j] = 0;
                }
            }
            else if (i>0 && i<479 && j-1<0)                                 //Kernel at Left Edge
            {
                if((image[i-1][j]||image[i-1][j+1]||image[i][j]||image[i][j+1]||image[i+1][j]||image[i+1][j+1])==1)
                {
                    image1[i][j] = 1;
                }
                else
                {
                    image1[i][j] = 0;
                }
            }
            else if (i>0 && i<479 && j+1 == 640)                                 //Kernel at Right Edge
            {
                if((image[i-1][j-1]||image[i-1][j]||image[i][j-1]||image[i][j]||image[i+1][j-1]||image[i+1][j])==1)
                {
                    image1[i][j] = 1;
                }
                else
                {
                    image1[i][j] = 0;
                }
            }
            // cout<<"image1[i][j] : "<<image1[i][j]<<" "<<endl;
            // cout<<"image1[i][j] : "<<image1[i][j]<<" "<<endl;
            // cout<<"Image : "<<image[i][j];
            // cout<<"     Image1 : "<<image1[i][j];
            // cout<<"     i = "<<i<<endl;
        }
    }
    for(int i =0; i<480; i++)
    {
        for(int j =0; j<640; j++)
        {
            f2<<image1[i][j]<<" ";
        }
        f2<<endl;
    }
    f2.close();
}


void Erosion(string filename, string filename1)
{
    int X;
    fstream f1(filename, ios::in);
    fstream f2(filename1, ios::out);
    
    for( int i=0; i<480; i++)
    {
        for (int j=0; j<640; j++)
        {
            f1>>X;
            image[i][j]=X;
            image2[i][j]=X;
            // cout<<"Image : "<<image[i][j];
            // cout<<"     Image1 : "<<image1[i][j];
            // cout<<"     i = "<<i<<endl;
        }
    }
    f1.close();

    for(int i=0; i<480; i++)
    {
        for (int j=0; j<640; j++)
        {
            if (i-1>0 && i<=480 && j-1>0 && j<640)           //Kernel anywhere else
            {
                if((image[i-1][j-1] && image[i-1][j]&&image[i-1][j+1]&&image[i][j-1]&&image[i][j]&&image[i][j+1]&&image[i+1][j-1]&&image[i+1][j]&&image[i+1][j+1])==0)
                {
                    image2[i][j] = 0;
                }
                else
                {
                    continue;
                }
            }
            else if (i-1<0 && j-1<0)                        //Kernel at top left
            {
                if((image[i][j]&&image[i][j+1]&&image[i+1][j]&&image[i+1][j+1])==0)
                {
                    image2[i][j] = 0;
                }
                else
                {
                    continue;
                }
            }
            else if (i-1<0 && j+1 == 640)                        //Kernel at top right
            {
                if((image[i][j-1]&&image[i][j]&&image[i+1][j-1]&&image[i+1][j])==0)
                {
                    image2[i][j] = 0;
                }
                else
                {
                    continue;
                }
            }
            else if (i+1 == 480 && j-1<0)                         //Kernel at Bottom Left
            {
                if((image[i-1][j]&&image[i-1][j+1]&&image[i][j]&&image[i][j+1])==0)
                {
                    image2[i][j] = 0;
                }
                else
                {
                    continue;
                }
            }
            else if (i+1 == 480 && j+1 == 640)                         //Kernel at Bottom Right
            {
                if((image[i-1][j-1]&&image[i-1][j]&&image[i][j-1]&&image[i][j])==0)
                {
                    image2[i][j] = 0;
                }
                else
                {
                    continue;
                }
            }
            else if (i==0 && j+1<640 && j-1>0)                                 //Kernel at top middle
            {
                if((image[i][j-1]&&image[i][j]&&image[i][j+1]&&image[i+1][j-1]&&image[i+1][j]&&image[i+1][j+1])==0)
                {
                    image2[i][j] = 0;
                }
                else
                {
                    continue;
                }
            }
            else if (i == 479 && j+1<640 && j-1>0)                                 //Kernel at Bottom Middle
            {
                if((image[i-1][j-1]&&image[i-1][j]&&image[i-1][j+1]&&image[i][j-1]&&image[i][j]&&image[i][j+1])==0)
                {
                    image2[i][j] = 0;
                }
                else
                {
                    continue;
                }
            }
            else if (i>0 && i<479 && j-1<0)                                 //Kernel at Left Edge
            {
                if((image[i-1][j]&&image[i-1][j+1]&&image[i][j]&&image[i][j+1]&&image[i+1][j]&&image[i+1][j+1])==0)
                {
                    image2[i][j] = 0;
                }
                else
                {
                    continue;
                }
            }
            else if (i>0 && i<479 && j+1 == 640)                                 //Kernel at Right Edge
            {
                if((image[i-1][j-1]&&image[i-1][j]&&image[i][j-1]&&image[i][j]&&image[i+1][j-1]&&image[i+1][j])==0)
                {
                    image2[i][j] = 0;
                }
                else
                {
                    continue;
                }
            }
            // cout<<"image1[i][j] : "<<image1[i][j]<<" "<<endl;
            // cout<<"image1[i][j] : "<<image1[i][j]<<" "<<endl;
            // cout<<"Image : "<<image[i][j];
            // cout<<"     Image1 : "<<image1[i][j];
            // cout<<"     i = "<<i<<endl;
        }
    }
    for(int i =0; i<480; i++)
    {
        for(int j =0; j<640; j++)
        {
            f2<<image2[i][j]<<" ";
        }
        f2<<endl;
    }
    f2.close();
}


void Opening(string file1, string file2, string file3)
{
    Dilation(file1, file2);
    Erosion(file2, file3);
}


void Closing (string file1, string file2, string file3)
{
    Erosion(file1, file2);
    Dilation(file2, file3);
}


void Gradient (string file1)
{
    ofstream f1(file1, ios::out);
    for (int i =0; i<480; i++)
    {
        for ( int j = 0 ; j<640 ; j++)
        {
            image3[i][j] = image1[i][j] - image2[i][j];
            f1<<image3[i][j]<<" ";
        }
        f1<<endl;
    }
    f1.close();
}


int main()
{
    RGBtoGrayscale("Red1.txt","Green1.txt","Blue1.txt","Grayscale.txt");
    Grayscale_to_Binary("Grayscale.txt", "Binary.txt");
    Dilation("Binary.txt","Dilated.txt");
    Erosion("Binary.txt","Eroded.txt");
    Opening("Binary.txt", "Dilated.txt", "Opening.txt");
    Closing("Binary.txt", "Eroded.txt", "Closing.txt");
    Gradient("Gradient.txt");
}
