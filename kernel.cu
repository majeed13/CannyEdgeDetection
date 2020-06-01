
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    Mat img;
    img = imread("Engine_in.PNG");
    int rows = img.rows;
    int col = img.cols;
    int depth = img.dims;
    cout << "Rows: " << rows << endl;
    cout << "Cols: " << rows << endl;
    cout << "Depth: " << depth << endl;
 
    for (int r = 0; r < 6; r++)
    {
        for (int c = 0; c < 6; c++)
        {
            Vec3b intensity = img.at<Vec3b>(r, c);
            cout << "Blue: " << (int)intensity.val[0] << " -- ";
            cout << "Green: " << (int)intensity.val[1] << " -- ";
            cout << "Red: " << (int)intensity.val[2] << " -- ";
            cout << endl;
        }
    }
    return 0;
}