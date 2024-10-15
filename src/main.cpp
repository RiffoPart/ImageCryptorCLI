#include <imcpyto.hpp>
#include <iostream>
#include <boost/program_options.hpp>


namespace po = boost::program_options;

int main(int argc, char** argv)
{
    // std::string path = "./a.png";

    // cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);

    // std::string src_data = "he";
    
    // std::string data ="";
    // std::vector<int> rnd_used;
    // srand(0);
    

    // for (int i = 0; i < src_data.size()+1; i++)
    // {
    //     int pixel_index = 0;
    //     do {
    //         pixel_index = rand() % (img.size().width * img.size().height + 1);
    //     } while (std::find(rnd_used.begin(), rnd_used.end(), pixel_index) != rnd_used.end());
    //     rnd_used.push_back(pixel_index);
    //     img.at<cv::Vec3b>(pixel_index) = insetInColor(img.at<cv::Vec3b>(pixel_index), (uchar)src_data[i]);
    //     // std::cout << "0x" << std::hex << (int)getChFromColor(img.at<cv::Vec3b>(i)) << std::endl;
    //     if (i == src_data.size()) {
    //         insetInColor(img.at<cv::Vec3b>(pixel_index), 0x0);
    //     }
        
    // }



    // uchar ch = 0;
    // do
    // {
    //     int pixel_index = 0;
    //     do {
    //         pixel_index = rand() % (img.size().width * img.size().height + 1);
    //     } while (std::find(rnd_used.begin(), rnd_used.end(), pixel_index) != rnd_used.end());

    //     ch = getChFromColor(img.at<cv::Vec3b>(pixel_index));
    //     data += ch;

    // } while (ch != 0x0);
    
    // std::cout << data << std::endl;

    // cv::imwrite("./n.png", img);
    
    // cv::imshow(path, img);
    // cv::waitKey(0);

    po::options_description desc("Usage");

    try
    {
        
        // desc.add_options()
        //     ("help,h",                                      "Info")
        //     ("input,i",         po::value<std::string>(),   "Path to source image file")
        //     ("output,o",        po::value<std::string>(),   "Path to out image file")
        //     ("text-file,t",     po::value<std::string>(),   "Path to text file")
        //     ("key,k",           po::value<std::string>(),   "Key (seed) for random");

        desc.add_options()
            ("help,h",                                      "Info"                      )
            ("encrypt,e",     po::bool_switch(),            "Inser text in to image"    )
            ("decrypt,d",     po::bool_switch(),            "Get text from image"       )
            ("source,s",      po::value<std::string>(),     "Path to source file"       )
            ("out,o",         po::value<std::string>(),     "Path to out file"          )
            ("text,t",        po::value<std::string>(),     "Path to text file"         )
            ("key,k",         po::value<std::string>(),     "Encrypted key"             );

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 0;
        }

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << desc << std::endl;
        return 1;
    }
    
    
    return 0;
}

// 32 5 1