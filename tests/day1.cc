#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"
using namespace utils;
TEST_CASE( "day1", "day1" ){
    auto strings_from_file = utils::get_inputs_from_file("day1.in");
    auto result_in_ints = get_number_pairs_seperated_with_characters(strings_from_file,"   ");
    long long res =0;
    auto diffs = find_difference_of_minimum_lists(result_in_ints);
    for(auto & s:diffs) res+=s;
    //part-1
    std::cout<<"part1-" << res<<std::endl;
    
    //part-2
    std::cout<<"part2-"<<
        compute_similarity_index(result_in_ints)<<std::endl;
}
