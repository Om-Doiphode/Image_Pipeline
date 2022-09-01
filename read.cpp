#include <bits/stdc++.h>
using namespace std;
int main()
{
    fstream file("Image1.bin", ios::in | ios::binary);
    fstream output("Data.txt", ios::out);
    if (file.is_open())
    {
        char buffer[40];
        while (file.good()) // Checks for any error while opening the file
        {
            output << hex << setfill('0'); // Storing the output in hexadecimal format
            file.read(buffer, 16);         // Each line consists of 16 bytes data
            for (unsigned int i = 0; i < 16; i++)
            {
                if (i % 2 == 0)
                    output << " ";
                output << setw(2) << (unsigned short)(unsigned int)buffer[i];
            }
            output << endl;
        }
    }
    fstream inputFile("Data.txt", ios::in);
}