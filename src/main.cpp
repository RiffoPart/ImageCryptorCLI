#include <imcpyto.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

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
           
            std::ifstream t(vm["text"].as<std::string>());
            std::stringstream buffer;
            buffer << t.rdbuf();
            t.close();

            Cryptor crypt(getSeed(vm["key"].as<std::string>()), base_callback::pack::CH2RGB323);
            cv::Mat newImage = crypt.crypt(cv::imread(vm["source"].as<std::string>()), buffer.str());
            cv::imwrite(out_file_path, newImage);


        } else if (vm["decrypt"].as<bool>()) {
            
            std::string out_file_path;
            if (vm["out"].defaulted()) {
                out_file_path = "./out.txt";
            } else {
                out_file_path = vm["out"].as<std::string>();
            }

            // decryptFile(vm["source"].as<std::string>(), getSeed(vm["key"].as<std::string>()), out_file_path);

            Encryptor encrypt(getSeed(vm["key"].as<std::string>()), base_callback::unpack::RGB323_2CH);
            std::string data = encrypt.encrypt(cv::imread(vm["source"].as<std::string>(), cv::IMREAD_COLOR));

            std::ofstream f(out_file_path);
            f << data;
            f.close();

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
