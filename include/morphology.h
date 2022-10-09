#include <bits/stdc++.h>
using namespace std;
using matrix = vector<vector<double>>;
double sum(matrix);
matrix multiply(matrix, matrix);
matrix vectorSlice(matrix, int, int, int, int);
matrix Erosion(matrix, int);
matrix Dilation(matrix, int);
matrix Closing(matrix, int);
matrix Opening(matrix, int);
matrix Gradient(matrix, int);
matrix topHat(matrix, int);
matrix blackHat(matrix, int);