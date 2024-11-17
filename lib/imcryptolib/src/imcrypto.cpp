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


cv::Mat cryptText(cv::Mat img, std::string data, uint32_t key) 
{
    cv::Mat new_img = img;

    if (data.size() >= new_img.size().width * new_img.size().height) {
        std::cerr << "Input file more high\n";
        abort();
    }

    std::vector<int> rnd_used;
    srand(key);

    for (int i = 0; i < data.size()+1; i++)
    {
        int pixel_index = 0;

        do {
            pixel_index = rand() % (new_img.size().width * new_img.size().height + 1);
        } while (std::find(rnd_used.begin(), rnd_used.end(), pixel_index) != rnd_used.end());

        rnd_used.push_back(pixel_index);
        new_img.at<cv::Vec3b>(pixel_index) = insetInColor(new_img.at<cv::Vec3b>(pixel_index), (uchar)data[i]);

        if (i == data.size()) {
            insetInColor(new_img.at<cv::Vec3b>(pixel_index), 0x0);
        }
    }

    return new_img;
}

void cryptFile(std::string image_path, std::string text_path, uint32_t key, std::string out) 
{
    std::fstream text_file(text_path);

    if (!text_file.is_open()) {
        std::cerr << "File " << text_path << "not opened." << std::endl;
        abort();
    }

    std::stringstream buffer;
    buffer << text_file.rdbuf();
    std::string data = buffer.str();
    text_file.close();

    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);

    if (data.size() >= img.size().width * img.size().height) {
        std::cerr << "Input file more high\n";
        abort();
    }

    std::vector<int> rnd_used;
    srand(key);

    for (int i = 0; i < data.size()+1; i++)
    {
        int pixel_index = 0;

        do {
            pixel_index = rand() % (img.size().width * img.size().height + 1);
        } while (std::find(rnd_used.begin(), rnd_used.end(), pixel_index) != rnd_used.end());

        rnd_used.push_back(pixel_index);
        img.at<cv::Vec3b>(pixel_index) = insetInColor(img.at<cv::Vec3b>(pixel_index), (uchar)data[i]);

        if (i == data.size()) {
            insetInColor(img.at<cv::Vec3b>(pixel_index), 0x0);
        }
    }

    cv::imwrite(out, img);
}

void decryptFile(std::string image_path, uint32_t key, std::string out)
{
    std::string data;

    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);

    std::vector<int> rnd_used;
    srand(key);

    uchar ch = 0;
    do
    {
        int pixel_index = 0;

        do {
            pixel_index = rand() % (img.size().width * img.size().height + 1);
        } while (std::find(rnd_used.begin(), rnd_used.end(), pixel_index) != rnd_used.end());

        ch = getChFromColor(img.at<cv::Vec3b>(pixel_index));
        if (ch != 0x0)
            data += ch;
        rnd_used.push_back(pixel_index);

    } while (ch != 0x0);


    std::ofstream out_file(out);
    if (!out_file.is_open()) {
        std::cerr << "File " << out << "not opened or not created" << std::endl;
        abort();
    }

    out_file << data;
    out_file.close();
}

std::string decryptText(cv::Mat img, uint32_t key) 
{
    std::string data;

    std::vector<int> rnd_used;
    srand(key);

    uchar ch = 0;
    do
    {
        int pixel_index = 0;

        do {
            pixel_index = rand() % (img.size().width * img.size().height + 1);
        } while (std::find(rnd_used.begin(), rnd_used.end(), pixel_index) != rnd_used.end());

        ch = getChFromColor(img.at<cv::Vec3b>(pixel_index));
        if (ch != 0x0)
            data += ch;
        rnd_used.push_back(pixel_index);

    } while (ch != 0x0);

    return data;
}
#endif //_IMCRYPTO_CPP_