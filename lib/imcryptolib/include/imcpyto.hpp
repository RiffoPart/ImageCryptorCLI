#ifndef _IMCRYPTO_HPP_
#define _IMCRYPTO_HPP_


#include <stdint.h>
#include <opencv2/opencv.hpp>

typedef struct color
{
    uint8_t red,green,blue;
    color(uint8_t red,uint8_t green, uint8_t blue);
} color_t;

color_t vec3bToColor(cv::Vec3b color_vect);


#endif //_IMCRYPTO_HPP_