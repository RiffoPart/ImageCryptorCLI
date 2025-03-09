#ifndef _IMCRYPTO_HPP_
#define _IMCRYPTO_HPP_

#include <stdint.h>
#include <opencv2/opencv.hpp>
#include <ostream>
#include <fstream>
#include <functional>

std::ostream& operator<<(std::ostream& cout, const cv::Vec3b& color);

int32_t getSeed(const std::string& string_key);

using insert_callback = std::function<cv::Vec3b(cv::Vec3b, uchar)>;
using unpack_callback = std::function<uchar(cv::Vec3b)>;

namespace base_callback {
    namespace pack {
        cv::Vec3b CH2RGB323(cv::Vec3b colorOfPixel, uchar ch);
        cv::Vec3b CH2RGB332(cv::Vec3b colorOfPixel, uchar ch);
        cv::Vec3b CH2RGB233(cv::Vec3b colorOfPixel, uchar ch);
    };

    namespace unpack {
        uchar RGB323_2CH(cv::Vec3b colorOfPixel);
        uchar RGB332_2CH(cv::Vec3b colorOfPixel);
        uchar RGB233_2CH(cv::Vec3b colorOfPixel);
    }
};

class Cryptor {
private:
    insert_callback _callback;
    int32_t _seed;

public:
    Cryptor(const int32_t& seed, insert_callback callback);

    Cryptor(const Cryptor&) = delete;
    Cryptor(const Cryptor&&) = delete;
    ~Cryptor() = default;

    void setSeed(const int32_t& seed);
    void setInsertCallback(insert_callback callback);

    cv::Mat crypt(cv::Mat sourceMat, std::string buf);
};

class Encryptor{
private:
unpack_callback _callback;
    int32_t _seed;

public:
    Encryptor(const int32_t& seed, unpack_callback callback);
    Encryptor(const Cryptor&) = delete;
    Encryptor(const Cryptor&&) = delete;
    ~Encryptor() = default;

    void setSeed(const int32_t& seed);
    void setInsertCallback(unpack_callback callback);

    std::string encrypt(cv::Mat sourceMat);
};

#endif //_IMCRYPTO_HPP_