#ifndef _IMCRYPTO_HPP_
#define _IMCRYPTO_HPP_


#include <stdint.h>
#include <opencv2/opencv.hpp>
#include <ostream>

cv::Vec3b insetInColor(cv::Vec3b color, uchar ch);
uchar getChFromColor(cv::Vec3b color);

std::ostream& operator<<(std::ostream& cout, const cv::Vec3b& color);

int32_t getSeed(const std::string& string_key);

#endif //_IMCRYPTO_HPP_