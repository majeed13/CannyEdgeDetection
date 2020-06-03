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