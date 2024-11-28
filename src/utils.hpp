#ifndef _UTILS
#define _UTILS
#include <vector>
#include <string_view>
#include <fstream>
#include <iostream>
#include <source_location>

namespace utils{
    std::vector<std::string_view> get_inputs_from_file(std::string_view filep,const std::source_location location =
               std::source_location::current()){
        std::vector<std::string_view> result;
        try{
            std::ifstream fs;
            fs.open(std::string(filep));
            if (!fs) {
                throw std::runtime_error("file opening error!"); 
            }
            std::string res;
            while(std::getline(fs,res))
            {
                result.emplace_back(res);
            }
        }
        catch(std::exception & e){
            std::cerr<< location.file_name() << '('
              << location.line() << ':'
              << location.column() << ") `"
              << location.function_name() << "`: "<<e.what()<<std::endl;
        }
        return std::move(result);
    }
}

#endif /*_UTILS*/