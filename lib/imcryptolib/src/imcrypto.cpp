#ifndef _IMCRYPTO_CPP_
#define _IMCRYPTO_CPP_

#include "../include/imcpyto.hpp"

color::color(uint8_t red, uint8_t green, uint8_t blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

color_t vec3bToColor(cv::Vec3b color_vect) {
    color_t color(0,0,0);
    color.red = color_vect.val[2];
    color.green = color_vect.val[1];
    color.blue = color_vect.val[0];

    return color;
}

#endif //_IMCRYPTO_CPP_