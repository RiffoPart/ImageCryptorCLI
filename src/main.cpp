#include <imcpyto.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    std::string path = "./a.png";

    cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);

    cv::imshow(path, img);
    cv::waitKey(0);
    
    return 0;
}
