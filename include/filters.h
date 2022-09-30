#include <bits/stdc++.h>
using namespace std;
using matrix = vector<vector<double>>;
matrix filter(matrix);
matrix meanFilter(matrix, int kernel_size = 3);
matrix gaussianFilterCreation(int kernel_size = 3);
matrix gaussianFilter(matrix image, int kernel_size = 3);