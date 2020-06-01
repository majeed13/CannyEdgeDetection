
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void cpu_canny();

int main()
{
    cpu_canny();
    
    // Test to see if we can read BGR values
    /*
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
    */
    return 0;
}

void cpu_canny()
{
    // openCV Matrices to read images
    Mat src, src_gray;
    Mat dst, detected_edges;

    // Canny variables
    int edgeThresh;
    int lowThresh = 100;
    int const max_lowThresh = 100;
    int ratio = 3;
    int kernel_size = 3;

    // Window Name
    char* window_name = "Edge Map";
    // Read image
    src = imread("Engine_in.PNG");
    if (!src.data)
    {
        cout << "No src picture found" << endl;
    }
    // Create matrix of same size and type
    dst.create(src.size(), src.type());
    // Covnert to grayscale
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    // Reduce noise (can experiment with size)
    blur(src_gray, detected_edges, Size(3, 3));
    // openCV Canny detecor
    Canny(detected_edges, detected_edges, lowThresh, lowThresh * ratio, kernel_size);
    
    // Explained as: "USING CANNY'S OUTPUT AS A MASK, DISPLAY RESULTS"
    //this fills dst with all 0s making it completely black
    dst = Scalar::all(0);

    // Copy src image to dst. copies only the pixelsin the locations where
    // they have non-zero vals. Since output of teh Canny detector is the edge
    // contours on a black background, the resulting dst will be black in all
    // the area but the detected edges
    src.copyTo(dst, detected_edges);
    // Display result
    imshow(window_name, dst);
    // Wait for key press.
    waitKey(0);
}