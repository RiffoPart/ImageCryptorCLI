#include <imcpyto.hpp>
#include <iostream>



int main(int argc, char** argv)
{
    std::string path = "./n.png";

    cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);

    std::string src_data = "he";
    
    std::string data ="";
    std::vector<int> rnd_used;
    srand(0);
    
    /*
    for (int i = 0; i < src_data.size()+1; i++)
    {
        int pixel_index = 0;
        do {
            pixel_index = rand() % (img.size().width * img.size().height + 1);
        } while (std::find(rnd_used.begin(), rnd_used.end(), pixel_index) != rnd_used.end());
        rnd_used.push_back(pixel_index);
        img.at<cv::Vec3b>(pixel_index) = insetInColor(img.at<cv::Vec3b>(pixel_index), (uchar)src_data[i]);
        // std::cout << "0x" << std::hex << (int)getChFromColor(img.at<cv::Vec3b>(i)) << std::endl;
        if (i == src_data.size()) {
            insetInColor(img.at<cv::Vec3b>(pixel_index), 0x0);
        }
        
    }
    */


    uchar ch = 0;
    do
    {
        int pixel_index = 0;
        do {
            pixel_index = rand() % (img.size().width * img.size().height + 1);
        } while (std::find(rnd_used.begin(), rnd_used.end(), pixel_index) != rnd_used.end());

        ch = getChFromColor(img.at<cv::Vec3b>(pixel_index));
        data += ch;

    } while (ch != 0x0);
    
    std::cout << data << std::endl;

    // cv::imwrite("./n.png", img);
    
    cv::imshow(path, img);
    cv::waitKey(0);

    
    
    return 0;
}

// 32 5 1