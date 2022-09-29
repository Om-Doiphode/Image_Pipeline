#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
using matrix = vector<vector<double>>;

double image[1324][2012];
double R[1324][2012];
double G[1324][2012];
double B[1324][2012];

int main()
{
    cout<<"Start "<<endl;

    ifstream f1("RAW_NIKON_D1_Scaled.txt");
    double val;

    for (int i=0; i<2012; i++)
    {
        for (int j=0; j<1324; j++)
        {
            f1 >> val;
            image[i][j] = val;
        }
    }

    f1.close();

    cout<<"Made Image Array"<<endl;

    for (int i=0; i<2012; i++)                                  //Interpolating missing Green values 
    {
        for (int j=0; j<1324; j++)
        {
            if ( i%2==0 && j%2==0 )                             //G at R in RG rows
            {
                if ( i%2==0 && j%2==0 && i>0 && j>0)            //G at R in RG rows, everywhere else
                {
                    G[i][j] = 0.25 * ( image[i-1][j] + image[i][j-1] + image[i][j+1] + image[i+1][j]) ;
                }

                else if ( i%2==0 && j==0 && i>0)                //G at R in RG rows at left edge
                {
                    G[i][j] = 0.33 * ( image[i-1][j] + image[i+1][j] + image[i][j+1]);
                }

                else if ( j%2==0 && i==0 && j>0)                //G at R in RG rows at top edge
                {
                    G[i][j] = 0.33 * ( image[i][j-1] + image[i][j+1] + image[i+1][j]);
                }

                else if ( i==0 && j==0)                         //G at R in RG rows at top left
                {
                    G[i][j] = 0.5 * ( image[i][j+1] + image[i+1][j]);
                }
            }
            
            else if ( i%2==1 && j%2==1 )                        //G at B in BG rows
            {
                if ( i%2==1 && j%2==1 && i<1323 && j<2011)      //G at B in BG rows, everywhere
                {
                    G[i][j] = 0.25 * ( image[i-1][j] + image[i][j-1] + image[i][j+1] + image[i+1][j]) ;
                }
                
                else if ( i%2==1 && j==2011 && i>0 )            //G at B in BG rows at right edge
                {
                    G[i][j] = 0.33 * ( image[i-1][j] + image[i][j-1] + image[i+1][j] );
                }

                else if ( i%2==1 && i==1323 && j>0 )            //G at B in BG rows at bottom edge
                {
                    G[i][j] = 0.33 * ( image[i-1][j] + image[i][j-1] + image[i][j+1] );
                }
                
                else if ( i==1323 && j==2011 )                  //G at B in BG rows at bottom left
                {
                    G[i][j] = 0.33 * ( image[i-1][j] + image[i][j-1] );
                }
            
            }

            else if ( ( i%2==0 && j%2==1 ) || ( i%2==1 && j%2==0 )) //G values at G pixels
            {
                G[i][j] = image[i][j];
            }
        }
    }
    
    cout<<"Interpolated Green Values"<<endl;
    
    for (int i=0; i<2012; i++)                                  //Interpolating missing Red values 
    {
        for (int j=0; j<1324; j++)
        {
            if ( i%2==1 && j%2==1 )                             //R at B in GB rows
            {
                if ( i%2==1 && j%2==1 && i<1323 && j<2011 )     //R at B in GB rows, everywhere
                {
                    R[i][j] = 0.25 * ( image[i-1][j-1] + image[i-1][j+1] + image[i+1][j-1] + image[i+1][j+1]);
                }

                else if ( i%2==1 && j==2011 )                   //R at B in GB rows, right edge
                {
                    R[i][j] = 0.5 * ( image[i-1][j-1] + image[i+1][j-1]);
                }

                else if ( j%2==1 && i==1323 )                   //R at B in GB rows, bottom edge
                {
                    R[i][j] = 0.5 * ( image[i-1][j-1] + image[i-1][j+1]);
                }

                else if ( i==1323 && j==2011 )                  //R at B in GB rows, Bottom right
                {
                    R[i][j] = image[i-1][j-1];
                }

            }

            else if ( i%2==0 && i%2==1 )                        //R at G in RG rows
            {
                if ( i%2==0 && i%2==1 && j<2011)                //R at G in RG rows, everywhere
                {
                    R[i][j] = 0.5 * ( image[i][j-1] + image[i][j+1] );
                }

                else if ( i%2==0 && j==2011 )                   //R at G in RG rows, right edge
                {
                    R[i][j] = image[i][j-1];
                }

            }

            else if ( i%2==1 && j%2==0 )                        //R at G in GB rows
            {
                if ( i%2==1 && j%2==0 && i<1323)                //R at G in GB rows, everywhere
                {
                    R[i][j] = 0.25 * (image[i-1][j-1] + image[i-1][j+1] + image[i+1][j-1] + image[i+1][j+1]);
                }

                else if ( i%2==1 && j==0 )                      //R at G in GB rows, left edge
                {
                    R[i][j] = 0.5 * (image[i-1][j] + image[i+1][j]);
                }

                else if ( j%2==0 && i==1323 )                   //R at G in GB rows, bottom edge
                {
                    R[i][j] = image[i-1][j];
                }
            }
            else if ( i%2==0 && j%2==0 )                        //R at Red pixels
            {
                R[i][j] = image[i][j];
            }
        }
    }
    
    cout<<"Interpolated Red Values"<<endl;
    
    for (int i=0; i<2012; i++)                                  //Interpolating missing Blue values 
    {
        for (int j=0; j<1324; j++)
        {
            if ( i%2==0 && j%2==0 )                             //B at R in RG rows
            {
                if ( i%2==0 && j%2==0 && i>0 && j>0 )           //B at R in RG rows, everywhere
                {
                    B[i][j] = 0.25 * (image[i-1][j-1] + image[i-1][j+1] + image[i+1][j-1] + image[i+1][j+1]);
                }

                else if ( i==0 && j%2==0 && j>0 )               //B at R in RG rows, top edge
                {
                    B[i][j] = 0.5 * ( image[i+1][j-1] + image[i+1][j+1]);
                }

                else if ( i%2==0 && j==0 & i>0 )                //B at R in RG rows, left edge
                {
                    B[i][j] = 0.5 * ( image[i-1][j+1] + image[i+1][j+1]);
                }

                else if ( i==0 && j==0 )                        //B at R in RG rows, top left
                {
                    B[i][j] = image[i+1][j+1];
                }
            }

            else if ( i%2==1 && j%2==0 )                        //B at G in GB rows
            {
                if ( i%2==1 && j%2==0 && j>0 && i<1323 )        //B at G in GB rows, everywhere
                {
                    B[i][j] = 0.5 * (image[i][j-1] + image[i][j+1]);
                }

                else if ( i%2==1 && j==0 && i<1323 )            //B at G in GB rows, left edge
                {
                    B[i][j] = image[i][j+1];
                }

                else if ( j%2==0 && i==1323 && j>0 )            //B at G in GB rows, bottom edge
                {
                    B[i][j] = 0.5 * (image[i][j-1] + image[i][j+1]);
                }

                else if ( i==1323 && j==0 )                     //B at G in GB rows, bottom left
                {
                    B[i][j] = image[i][j+1];
                }
            }

            else if ( i%2==0 && j%2==1 )                        //B at G in RG rows
            {
                if ( i%2==0 && j%2==1 && i>0 && j<2011 )        //B at G in RG rows, everywhere
                {
                    B[i][j] = 0.5 * (image[i-1][j] + image[i+1][j]);
                }

                else if ( i==0 && j%2==1 )                      //B at G in RG rows, top edge
                {
                    B[i][j] = image[i+1][j];
                }

                // else if ( i==0 && j==2011 )                     //B at G in RG rows, top right
                // {
                //     B[i][j] = image[i+1][j]
                // }
            }

            else if ( i%2==1 && j%2==1 )                        //B values at B pixels
            {
                B[i][j] = image[i][j];
            }
            
        }
    }
    
    cout<<"Interpolated Blue Values"<<endl;

    cout<<"Writing into the file now"<<endl;
    
    ofstream f2("R.txt", ios::out);
    
    for (int i=0; i<2012; i++)                                  //Writing Red pixel values in the file 
    {
        for (int j=0; j<1324; j++)
        {
            f2<<R[i][j]<<" ";
        }
        f2<<endl;
    }

    ofstream f3("G.txt", ios::out);
    
    for (int i=0; i<2012; i++)                                  //Writing Green pixel values in the file 
    {
        for (int j=0; j<1324; j++)
        {
            f3<<G[i][j]<<" ";
        }
        f3<<endl;
    }

    ofstream f4("B.txt", ios::out);
    
    for (int i=0; i<2012; i++)                                  //Writing Blue pixel values in the file 
    {
        for (int j=0; j<1324; j++)
        {
            f4<<B[i][j]<<" ";
        }
        f4<<endl;
    }

    f2.close();
    f3.close();
    f4.close();

    cout<<"\nEnd";

    return 0;
}