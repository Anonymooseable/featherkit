#pragma once
#include <cstdint>

namespace fea
{
    struct VideoMode
    {
            VideoMode();
            VideoMode(uint32_t w, uint32_t h, uint32_t bitDepth = 32);

            uint32_t width;
            uint32_t height;
            uint32_t bitsPerPixel;
    };

    /** @addtogroup UserInterface
     *@{
     *  @struct VideoMode
     *@}
     ***
     *  @struct VideoMode
     *  @brief Defines a video mode used to set up windows at creation time.
     *
     ***
     *  @fn VideoMode::VideoMode(uint32_t w, uint32_t h, uint32_t bitDepth=32) 
     *  @brief Default constructor.
     *
     *  @param w Width in pixels.
     *  @param h Width in pixels.
     *  @param bitDepth Pixel depth in bits per pixel.
     ***
     *  @var VideoMode::width
     *  @brief The width of the video mode in pixels.
     ***
     *  @var VideoMode::height
     *  @brief The height of the video mode in pixels.
     ***
     *  @var VideoMode::bitsPerPixel
     *  @brief The depth of the video mode in bits per pixels.
     ***/

}