#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace cv;
using matrix = vector<vector<double>>;

Mat create2DImage(matrix);
Mat create3DImage(matrix, matrix, matrix);