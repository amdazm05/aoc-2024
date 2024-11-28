#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"

TEST_CASE( "filereadtest", "filetest" ) {
    auto strings_from_file = utils::get_inputs_from_file("filereadtest.in");
    for(const auto & input:strings_from_file) std::cout<<input<<std::endl;
}