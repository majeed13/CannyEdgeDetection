<<<<<<< Updated upstream
#include <iostream>
#include "ed_error.h"
//#include "ed_args.h"
#include "imgMgr.h"
#include "cannyEdgeDetector.h"
#include "canny.h"

int main(int argc, char** argv)
{
    bool ser = false;
    
    std::cout << "Canny Edge Detection" << std::endl;
    if (ser) {
        std::cout << "Executing serially on CPU" << std::endl;
    }
    else {
        std::cout << "Executing in parallel on GPU" << std::endl;
    }

    /* Instantiate image manager */
    std::shared_ptr<ImgMgr> img_mgr = std::make_shared<ImgMgr>(*argv);
    
    /* read input file */
    img_mgr->read_image("Engine_in.PNG");

    /* Instantiate our edge detector */
    CannyEdgeDetector ced(img_mgr);

    /* run edge detection algorithm */
    ced.detect_edges(ser);

    /* write results */
    img_mgr->write_image("C:\\Users\\Mustafa\\Desktop\\sample1.PNG");
    std::cout << "Edge detection complete" << std::endl;

    return ED_SUCCESS;
}
=======
#include <iostream>
#include "ed_error.h"
//#include "ed_args.h"
#include "imgMgr.h"
#include "cannyEdgeDetector.h"
#include "canny.h"

int main(int argc, char** argv)
{
    /* boolean for method of processing false = gpu, true = cpu */
    bool ser = false;

    /* creates video capture object for live feed */
    cv::VideoCapture cap;


    std::cout << "Canny Edge Detection" << std::endl;
    if (ser) {
        std::cout << "Executing serially on CPU" << std::endl;
    }
    else {
        std::cout << "Executing in parallel on GPU" << std::endl;
    }

    /* Starts video capture on the host webcam */
    cap.open(0, 0);
    /* Instantiate image manager */
    std::shared_ptr<ImgMgr> img_mgr = std::make_shared<ImgMgr>(*argv);

    /* Original Frame */
    cv::Mat frame;

    /* Edge Detected Frame*/
    cv::Mat endFrame;

    /*Loop for live feed of Canny Edge Detection*/
    while (true)
    {
        /*Creates Window*/
        cv::namedWindow("EdgeDetectionLive", cv::WINDOW_NORMAL);

        /*Reads each frame from the video capture into Mat Frame object*/
        cap >> frame;

        /* Converts the frame to Pixel_t Objects */
        img_mgr->read_frame(frame);

        /* Creates CannyEdgeDetector Object from the frame */
        CannyEdgeDetector ced(img_mgr);

        /* Detects edges of the frame */
        ced.detect_edges(ser);

        /* Writes the result frame for viewing */
        endFrame = (img_mgr->write_writeFrame());

        /* Ends the loop when any key is pressed */
        if (cv::waitKey(1) >= 0)
        {
            return 1;
        }

        /* Shows the edge detected image */
        imshow("EdgeDetectionLive", endFrame);
    }
    //img_mgr->read_frame(frame);
    /* read input file */
    //img_mgr->read_image("road.jpg");

    /* Instantiate our edge detector */
    //CannyEdgeDetector ced(img_mgr);

    /* run edge detection algorithm */
    //ced.detect_edges(ser);

    /* write results */
    //img_mgr->write_image("C:\\Users\\cjhow\\Desktop\\sample1.jpg");
    //std::cout << "Edge detection complete" << std::endl;

    return ED_SUCCESS;
}
/*
=======
#include <iostream>
#include "ed_error.h"
//#include "ed_args.h"
#include "imgMgr.h"
#include "cannyEdgeDetector.h"
#include "canny.h"

int main(int argc, char** argv)
{
    bool ser = false;
    
    std::cout << "Canny Edge Detection" << std::endl;
    if (ser) {
        std::cout << "Executing serially on CPU" << std::endl;
    }
    else {
        std::cout << "Executing in parallel on GPU" << std::endl;
    }

    // Instantiate image manager 
    std::shared_ptr<ImgMgr> img_mgr = std::make_shared<ImgMgr>(*argv);
    
    // read input file 
    img_mgr->read_image("C:\\Users\\Mustafa\\Desktop\\test4k.jpg");

    // Instantiate our edge detector 
    CannyEdgeDetector ced(img_mgr);

    // run edge detection algorithm 
    ced.detect_edges(ser);

    // write results 
    img_mgr->write_image("C:\\Users\\Mustafa\\Desktop\\sample3.PNG");
    std::cout << "Edge detection complete" << std::endl;

    return ED_SUCCESS;
>>>>>>> Stashed changes
}
*/
>>>>>>> Stashed changes
