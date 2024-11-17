#include <imcpyto.hpp>
#include <iostream>
#include <fstream>
#include <lzw.h>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

std::string getTextFromFile(const std::string& filePath) 
{
    std::fstream text_file(filePath);

    if (!text_file.is_open()) {
        std::cerr << "File " << filePath << "not opened." << std::endl;
        abort();
    }

    std::stringstream buffer;
    buffer << text_file.rdbuf();
    std::string data = buffer.str();
    text_file.close();

    return data;
}

int main(int argc, char** argv)
{
    po::options_description desc("Usage: \n\timcrypto -e -s <path_to_img> -o [path_to_out_image=out.*] -t <path_to_text_file> -k <crypt key>\n\
    \timcrypto -d -s <path_to_img> -o [path_to_out_text_file=out.txt] -k <crypt key>\n\nArguments");

    desc.add_options()
            ("help,h",                                                              "Info"                      )
            ("encrypt,e",     po::bool_switch(),                                    "Inser text in to image"    )
            ("decrypt,d",     po::bool_switch(),                                    "Get text from image"       )
            ("source,s",      po::value<std::string>(),                             "Path to source file"       )
            ("out,o",         po::value<std::string>()->default_value("out"),       "Path to out file"          )
            ("text,t",        po::value<std::string>(),                             "Path to text file"         )
            ("key,k",         po::value<std::string>(),                             "Encrypted key"             );

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);


    try {

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 0;
        }

        if (vm["encrypt"].as<bool>()) {

            std::string out_file_path;
            if (vm["out"].defaulted()) {
                size_t pos = vm["source"].as<std::string>().find_last_of('.');
                out_file_path = "./out." + vm["source"].as<std::string>().substr(pos + 1);
            } else {
                out_file_path = vm["out"].as<std::string>();
            }

            cv::Mat img = cv::imread(vm["source"].as<std::string>(), cv::IMREAD_COLOR);
            std::string text = getTextFromFile(vm["text"].as<std::string>());
            text = "";
            for (uint i : lzw::compress<uint>(text)) {
                text += std::string(1, uchar(i));
            }
            
            cv::imwrite(out_file_path, cryptText(img, text, getSeed(vm["key"].as<std::string>())));

        } else if (vm["decrypt"].as<bool>()) {
            
            std::string out_file_path;
            if (vm["out"].defaulted()) {
                out_file_path = "./out.txt";
            } else {
                out_file_path = vm["out"].as<std::string>();
            }

            decryptFile(vm["source"].as<std::string>(), getSeed(vm["key"].as<std::string>()), out_file_path);

            cv::Mat img = cv::imread(vm["source"].as<std::string>(), cv::IMREAD_COLOR);
            std::string compressed_data = decryptText(img, getSeed(vm["key"].as<std::string>()));

            int uintSize = sizeof(uint);
            std::vector<uint> data;
            for (int i = 0; i < compressed_data.size(); i += uintSize) {
                uint value = 0;

                value += compressed_data[i]     << 24;
                value += compressed_data[i+1]   << 16;
                value += compressed_data[i+2]   << 8;
                value += compressed_data[i+3];

                data.push_back(value); 
            }
            std::string text = lzw::decompress(data);
            std::ofstream out_file(out_file_path);
            if (!out_file.is_open()) {
                std::cerr << "File " << out_file_path << "not opened or not created" << std::endl;
                abort();
            }

            out_file << text;
            out_file.close();

        } else {
            throw std::exception();
        }

    } catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
        std::cout << desc << std::endl;
        return 1;
    }
    
    return 0;
}
