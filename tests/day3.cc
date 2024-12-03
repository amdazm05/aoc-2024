#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"
#include <regex>
#include <iostream>
using namespace utils;

TEST_CASE("day3","day3"){
    auto strings_from_file =  utils::get_inputs_from_file("day3.in");
    std::string res_string;
    for(auto & str:strings_from_file)
        res_string+=str; 
    // std::cout<<"input strings"<<strings_from_file[0]<<std::endl;
    auto identified_muls= find_string_patterns(res_string,"mul\\(\\d{1,3},\\d{1,3}\\)");
    std::cout<<"part-1: "<<compute_mul_string(identified_muls)<<std::endl;

    //part-2 
    auto do_muls= find_string_patterns(res_string,"mul\\(([0-9]+),([0-9]+)\\)|do\\(\\)|don't\\(\\)");
    std::cout<<"part-2: "<<compute_mul_string(do_muls)<<std::endl;


}