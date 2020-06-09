#include <iostream>
#include <assert.h>
#include "cuda_runtime.h"
#include "imgMgr.h"

///
/// \brief Image manager contructor
/// Initializes Magick++ image library and member variables.
/// 
ImgMgr::ImgMgr(char* argv)
    : m_img_width(0), m_img_height(0), m_channel_depth(0), m_pixels(nullptr)
{
 
}

///
/// \brief Image manager destructor.
/// Frees up pixel array memory if there was any allocated.
///
ImgMgr::~ImgMgr(void)
{
    if (m_pixels != nullptr) {
        cudaFree(m_pixels);
        //delete[] m_pixels;
    }
}

///
/// \brief Return image width
///
unsigned ImgMgr::getImgWidth(void)
{
    return m_img_width;
}

///
/// \brief Return image height 
///
unsigned ImgMgr::getImgHeight(void)
{
    return m_img_height;
}

///
/// \brief Return image channel depth
///
unsigned ImgMgr::getChannelDepth(void)
{
    return m_channel_depth;
}

///
/// \brief Return total pixel count (width x height).
///
unsigned ImgMgr::getPixelCount(void)
{
    return m_img_width * m_img_height;
}

///
/// \brief Accessor to image pixel array.
/// User will call this method to gain access to the
/// internal pixel array of the image manager.
/// These pixels will then be rdwr.
///
pixel_t* ImgMgr::getPixelHandle(void)
{
    return m_pixels;
}

///
/// \brief Given a filename, open and image file and
/// copy it's pixel data to an internal array of pixel structs.
///
void ImgMgr::read_image(const std::string& in_filename)
{
    // Create openCV Mat object to read image
    cv::Mat img;
    // Read image in openCV
    img = cv::imread(in_filename);
    // Print pixel columns read for DEBUG
    std::cout << img.cols << std::endl;
        
    /* populate pixel imgMgr data structures */
    m_img_width = img.cols;
    m_img_height = img.rows;
    m_channel_depth = img.dims;

    // Delete prev or create new pixel_t array
    if (nullptr == m_pixels) {
        //m_pixels = new pixel_t[getPixelCount()]; // free'd in destructor
        cudaMallocManaged(&m_pixels, getPixelCount() * sizeof(pixel_t));
    }
    else {
        //delete[] m_pixels;
        //m_pixels = new pixel_t[getPixelCount()]; // free'd in destructor
        cudaFree(m_pixels);
        cudaMallocManaged(&m_pixels, getPixelCount() * sizeof(pixel_t));
    }
        assert(nullptr != m_pixels);

    /*NOT SURE IF WE WILL NEED THIS*/
#ifdef DEBUG
    std::cout << "Image: " << in_filename << std::endl;
    std::cout << "Resolution: " << m_img_width << "x" << m_img_height << std::endl;
    std::cout << "Pixel channels: " << img.channels() << std::endl;
    std::cout << "Channel depth: " << m_channel_depth << std::endl;
#endif

    /* extract the pixels from the image, put them in a format we can export portably */
    // MY ADD TEST
    std::cout << "** READING IMAGE **" << std::endl;
    // Loop each pixel individually by rows and cols
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            // openCV object to read the 3 channel BGR values
            cv::Vec3b intensity = img.at<cv::Vec3b>(i, j);
            // map the index of current pixel to internal structure index
            int idx = img.cols * i + j;
            // update the internal struct BGR values at that index
            m_pixels[idx].blue = (int)intensity[0] * 257;
            m_pixels[idx].green = (int)intensity[1] * 257;
            m_pixels[idx].red = (int)intensity[2] * 257;
            // Print out BGR values for DEBUG
            if (i >= 0 && i <= 5 && j >= 0 && j <= 5) 
            {
                std::cout << "Row: " << i << " -- Col " << j << "\n" <<
                            "Red: " << m_pixels[idx].red << "\nGreen: " << m_pixels[idx].green
                            << "\nBlue " << m_pixels[idx].blue << std::endl;
            }
        }
    }
    std::cout << "** READING IMAGE FIN **\n" << std::endl;   
}

///
/// \brief Given a filename, creat an image file using
/// the pixel data of this image manager instance.
///
void ImgMgr::write_image(const std::string& out_filename)
{
    /* create a new blk image of the same size as our input image */
    cv::Mat output = cv::Mat::zeros(cv::Size(m_img_width, m_img_height), CV_8UC3);
    // Loop through each pixel and add the pixel value from our output buffer
    // in imgMgr
    for (int i = 0; i < m_img_height; i++)
    {
        for (int j = 0; j < m_img_width; j++)
        {
            cv::Vec3b intensity;
            int idx = m_img_width * i + j;
            intensity[0] = m_pixels[idx].blue / 257;
            intensity[1] = m_pixels[idx].green / 257;
            intensity[2] = m_pixels[idx].red / 257;
            output.at<cv::Vec3b>(i, j) = intensity;
        }
    }
    // Save image
    cv::imwrite(out_filename, output);
    std::cout << "** IMAGE WRITE FIN **\n" << std::endl;
}