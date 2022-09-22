#include <vector>
using namespace std;
using matrix = std::vector<std::vector<double>>;
double minEle(matrix);
double maxEle(matrix);
matrix conv2D(matrix, matrix);
matrix G_at_BR(matrix);
matrix RB_at_G_in_RBrow_BRcol(matrix);
matrix RB_at_G_in_BRrow_RBcol(matrix);
matrix RB_at_BR(matrix);
vector<vector<vector<double>>> autoAdjust(matrix, matrix, matrix, int, int);
vector<vector<vector<double>>> debayering(matrix, int, int);