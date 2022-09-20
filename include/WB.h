#include <bits/stdc++.h>
using namespace std;
using matrix = vector<vector<double>>;

matrix whiteBalance(matrix image, double avgRed, double avgGreen, double avgBlue);
double averageOfPixels(matrix image);
matrix scale(matrix image, double a = 0, double b = 1);
double maxNumber(double a, double b, double c);
