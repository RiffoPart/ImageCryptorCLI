#ifndef _LZW_H_
#define _LZW_H_

#include <unordered_map>
#include <string>
#include <vector>

namespace lzw
{

    std::vector<int> compress(const std::string& input);
    
    std::string decompress(const std::vector<int>& input);

} // namespace lzw


#endif //_LZW_H_