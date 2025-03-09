#ifndef _IMCRYPTO_CPP_
#define _IMCRYPTO_CPP_

#include "../include/imcpyto.hpp"

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

uchar base_callback::unpack::RGB323_2CH(cv::Vec3b colorOfPixel)
{
    return ((colorOfPixel[2] & 0b00000111) << 5) + ((colorOfPixel[1] & 0b00000011) << 3) + (colorOfPixel[0] & 0b00000111);
}

uchar base_callback::unpack::RGB332_2CH(cv::Vec3b colorOfPixel)
{
    return ((colorOfPixel[2] & 0b00000111) << 5) + ((colorOfPixel[1] & 0b00000111) << 2) + (colorOfPixel[0] & 0b00000011);
}

uchar base_callback::unpack::RGB233_2CH(cv::Vec3b colorOfPixel)
{
    return ((colorOfPixel[2] & 0b00000011) << 6) + ((colorOfPixel[1] & 0b00000111) << 3) + (colorOfPixel[0] & 0b00000111);
}

cv::Vec3b base_callback::pack::CH2RGB323(cv::Vec3b colorOfPixel, uchar ch)
{
    colorOfPixel[0] = colorOfPixel[0] & 0b11111000; //BLUE
    colorOfPixel[1] = colorOfPixel[1] & 0b11111100; //GREEN
    colorOfPixel[2] = colorOfPixel[2] & 0b11111000; //RED

    colorOfPixel[2] += (ch & 0b11100000) >> 5; // RED
    colorOfPixel[1] += (ch & 0b00011000) >> 3; // GREEN
    colorOfPixel[0] += (ch & 0b00000111);      // BLUE

    return colorOfPixel;
}

cv::Vec3b base_callback::pack::CH2RGB332(cv::Vec3b colorOfPixel, uchar ch)
{
    colorOfPixel[0] = colorOfPixel[0] & 0b11111100; //BLUE
    colorOfPixel[1] = colorOfPixel[1] & 0b11111000; //GREEN
    colorOfPixel[2] = colorOfPixel[2] & 0b11111000; //RED

    colorOfPixel[2] += (ch & 0b11100000) >> 5; // RED
    colorOfPixel[1] += (ch & 0b00011100) >> 2; // GREEN
    colorOfPixel[0] += (ch & 0b00000011);      // BLUE

    return colorOfPixel;
}

cv::Vec3b base_callback::pack::CH2RGB233(cv::Vec3b colorOfPixel, uchar ch)
{
    colorOfPixel[0] = colorOfPixel[0] & 0b11111000; //BLUE
    colorOfPixel[1] = colorOfPixel[1] & 0b11111000; //GREEN
    colorOfPixel[2] = colorOfPixel[2] & 0b11111100; //RED

    colorOfPixel[2] += (ch & 0b11000000) >> 6; // RED
    colorOfPixel[1] += (ch & 0b00111000) >> 3; // GREEN
    colorOfPixel[0] += (ch & 0b00000111);      // BLUE

    return colorOfPixel;
}

Cryptor::Cryptor(const int32_t& seed, insert_callback callback)
{
    _seed = seed; 
    _callback = callback;
}

void Cryptor::setSeed(const int32_t& seed) 
{
    _seed = seed;
}

void Cryptor::setInsertCallback(insert_callback callback)
{
    _callback = callback;
}

cv::Mat Cryptor::crypt(cv::Mat sourceMat, std::string buf)
{
    cv::Mat new_img = sourceMat;
    auto size = buf.size();

    if (size >= new_img.size().width * new_img.size().height) {
        std::cerr << "Input file more high\n";
        abort();
    }

    std::vector<int> rnd_used;
    srand(_seed);

    for (int i = 0; i < size+1; i++)
    {
        int pixel_index = 0;

        do {
            pixel_index = rand() % (new_img.size().width * new_img.size().height + 1);
        } while (std::find(rnd_used.begin(), rnd_used.end(), pixel_index) != rnd_used.end());

        rnd_used.push_back(pixel_index);
        new_img.at<cv::Vec3b>(pixel_index) = _callback(new_img.at<cv::Vec3b>(pixel_index), (uchar)buf[i]);

        if (i == size) {
            _callback(new_img.at<cv::Vec3b>(pixel_index), 0x0);
        }
    }

    return new_img;
}

Encryptor::Encryptor(const int32_t& seed, unpack_callback callback)
{
    _seed = seed; 
    _callback = callback;
}

void Encryptor::setSeed(const int32_t& seed) 
{
    _seed = seed;
}

void Encryptor::setInsertCallback(unpack_callback callback)
{
    _callback = callback;
}

std::string Encryptor::encrypt(cv::Mat sourceMat)
{
    std::string data;

    std::vector<int> rnd_used;
    srand(_seed);

    uchar ch = 0;
    do
    {
        int pixel_index = 0;

        do {
            pixel_index = rand() % (sourceMat.size().width * sourceMat.size().height + 1);
        } while (std::find(rnd_used.begin(), rnd_used.end(), pixel_index) != rnd_used.end());

        ch = _callback(sourceMat.at<cv::Vec3b>(pixel_index));
        if (ch != 0x0)
            data += ch;
        rnd_used.push_back(pixel_index);

    } while (ch != 0x0);

    return data;
}

#endif //_IMCRYPTO_CPP_