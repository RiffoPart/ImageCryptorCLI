#ifndef _LZW_H_
#define _LZW_H_

#include <unordered_map>
#include <string>
#include <vector>

namespace lzw
{
    template<typename T>
    std::vector<T> compress(const std::string& input) {
        // Initialize
        std::vector<T> result;
        std::unordered_map<std::string, T> dict;

        for (int c = 0; c < 256; c++) {
            dict[std::string(1,c)] = c;
        }

        //Compression
        std::string current = "";
        
        for (int i = 0; i < input.size(); i++) {
            if (dict.count(current + input[i])) {
                current += input[i];
                
            } else {
                result.push_back(dict[current]);
                dict[current + input[i]] = dict.size();
                current = input[i];
            }
        }
        if (!current.empty()) {
            result.push_back(dict[current]);
        }

        return result;
    }

    template<typename T>
    std::string decompress(const std::vector<T>& input) {
        // Initialize
        std::string result = "";
        std::unordered_map<T, std::string> dict;
        for (int i = 0 ; i < 256; i++) {
            dict[i] = std::string(1,char(i));
            
        }

        //Decompression
        std::string w(1, char(input[0]));
        result += w;

        for (int i = 1; i < input.size(); ++i) {
            int k = input[i];
            std::string entry;

            if (dict.count(k)) {
                entry = dict[k];
            }
            else  if (k == dict.size()){
                entry = w + w[0];
            }

            result += entry;
            dict[dict.size()] = w + entry[0];
            w = entry;
        }


        return result;
    }

} // namespace lzw


#endif //_LZW_H_
