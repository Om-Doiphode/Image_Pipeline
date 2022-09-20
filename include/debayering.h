#include <vector>
using namespace std;
using matrix = std::vector<std::vector<double>>;
int minEle(matrix image);
double maxEle(matrix image);
matrix conv2D(matrix &img, matrix &kernal);
matrix G_at_BR(matrix &image);
matrix RB_at_G_in_RBrow_BRcol(matrix &image);
matrix RB_at_G_in_BRrow_RBcol(matrix &image);
matrix RB_at_BR(matrix &image);
vector<vector<vector<double>>> autoAdjust(matrix R, matrix G, matrix B, int height, int width);
vector<vector<vector<double>>> debayering(matrix image, int height, int width);