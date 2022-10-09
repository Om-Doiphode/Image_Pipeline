#include <bits/stdc++.h>
using namespace std;
using matrix = vector<vector<double>>;
matrix Rotate(matrix image, double angle)
{
    double rads = 2 * M_PI * (double(angle) / 360);
    cout << "rads: " << rads << endl;
    int cx = image[0].size() / 2, cy = image.size() / 2;

    int height_rot_image = round(abs(image.size() * sin(rads))) + round(abs(image[0].size() * cos(rads)));
    int width_rot_image = round(abs(image[0].size() * cos(rads))) + round(abs(image.size() * sin(rads)));

    matrix rot_image(height_rot_image, vector<double>(width_rot_image, 0));

    int midx = int(width_rot_image / 2), midy = int(height_rot_image / 2);

    for (int i = 0; i < rot_image.size(); i++)
    {
        for (int j = 0; j < rot_image[0].size(); j++)
        {
            int x = (i - midx) * cos(rads) + (j - midy) * sin(rads);
            int y = -(i - midx) * sin(rads) + (j - midy) * cos(rads);
            x = round(x) + cy;
            y = round(y) + cx;
            if (x >= 0 && y >= 0 && x < image.size() && y < image[0].size())
                rot_image[i][j] = image[x][y];
        }
    }
    return rot_image;
}