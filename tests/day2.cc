#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"
using namespace utils;

TEST_CASE( "day2", "day2" ){
    auto strings_from_file = utils::get_inputs_from_file("day2.in");
    auto lists_of_lists= divide_into_list_of_lists_of_ints(strings_from_file," ");
    print_vector_of_vector<int>(lists_of_lists);
    //part 1
    std::cout<<safe_list_count(lists_of_lists)<<std::endl;
    //part 2
    std::cout<<safe_list_count_with_dampener(lists_of_lists)<<std::endl;
}