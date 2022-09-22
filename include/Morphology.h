#include <bits/stdc++.h>
using namespace std;
using matrix = vector<vector<double>>;
double sum(matrix);
matrix multiply(matrix, matrix);
matrix vectorSlice(matrix, int, int, int, int);
matrix Erosion(matrix, int);
matrix Dilation(matrix);
matrix Closing(matrix);
matrix Opening(matrix);
matrix Gradient(matrix);
