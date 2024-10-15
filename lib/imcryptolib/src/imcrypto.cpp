#ifndef _IMCRYPTO_CPP_
#define _IMCRYPTO_CPP_

#include "../include/imcpyto.hpp"

cv::Vec3b insetInColor(cv::Vec3b color, uchar ch)
{
    color[0] = color[0] & 0b11111000; //BLUE
    color[1] = color[1] & 0b11111100; //GREEN
    color[2] = color[2] & 0b11111000; //RED

    color[2] += (ch & 0b11100000) >> 5; // RED
    color[1] += (ch & 0b00011000) >> 3; // GREEN
    color[0] += (ch & 0b00000111);      // BLUE

    return color;
}

uchar getChFromColor(cv::Vec3b color) 
{
    uchar ch = 0;
    ch = ((color[2] & 0b00000111) << 5) + ((color[1] & 0b00000011) << 3) + (color[0] & 0b00000111);

    return ch;
}

std::ostream& operator<<(std::ostream& cout, const cv::Vec3b& color) 
{
    return cout << "RGB(" << (int)color[2] << " " << (int)color[1] << " " << (int)color[0] << ")";
}

int32_t getSeed(const std::string& string_key) 
{
    int32_t vkey = 0;
    for (int i = 1 ; i < string_key.size() - 1; i++) {
        vkey += ((string_key[i] * string_key[i+1]) - (string_key[i-1] * i)) + i + string_key[i] + string_key[string_key[i-1] % (string_key.size()-1)];
        vkey += vkey / 0xFF + string_key.size() + i - (string_key[i-1] * i);
    }
    return vkey;
}

#endif //_IMCRYPTO_CPP_