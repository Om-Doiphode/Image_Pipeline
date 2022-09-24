#include <bits/stdc++.h>
#include "debayering.h"
#include "Conversion.h"
using namespace std;
matrix edgeDetect(matrix R, matrix G, matrix B);
matrix double_thresh(matrix image, double lowthreshratio = 0.05, double highthreshratio = 0.09);