#include <bits/stdc++.h>
using namespace std;
using matrix = vector<vector<double>>;
double sum(matrix A);
matrix multiply(matrix A, matrix B);
matrix vectorSlice(matrix &orig, int row_lower, int row_limit, int col_lower, int col_limit);
matrix Erosion(matrix img);
matrix Dilation(matrix img);
matrix Closing(matrix image);
matrix Opening(matrix image);
matrix Gradient(matrix image);
