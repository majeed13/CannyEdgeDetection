#pragma once
#ifndef _IMG_MGR_H_
#define _IMG_MGR_H_

#include <string>
#include <stdint.h>
#include <memory>
//------ My added ------
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
//----------------------
#include "ed_pixel.h"

///
/// \brief Image manager class
///
/// Wrapper for image wrangling library, in our case libmagick++
/// Provides utilites to open and close image files, and provides 
/// the edge detector class with access to the image data.
///
class ImgMgr
{
public:
    ImgMgr(char* argv);
    ~ImgMgr();
    ImgMgr* read_frame(cv::Mat img);
    cv::Mat ImgMgr::write_writeFrame();
    unsigned getImgWidth();
    unsigned getImgHeight();
    unsigned getChannelDepth();
    unsigned getPixelCount();
    pixel_t* getPixelHandle();

    void read_image(const std::string& in_filename);
    void write_image(const std::string& out_filename);

private:
    int m_img_width;
    int m_img_height;
    int m_channel_depth;
    pixel_t* m_pixels;
};

#endif // _IMG_MGR_H_
