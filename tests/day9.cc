#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"
using namespace utils;

//2333133121414131402
std::vector<int> create_disk_map(std::string &fs)
{
    std::vector<int> res; 
    res.reserve((1<<16) *16*sizeof(int));
    int j =0;
    for(int i=0;auto & f:fs){
        if(j%2==0){
            for(int k=0;k<(f-'0');k++){
                res.push_back(i);
            }
            i++;
        }else{
            for(int k=0;k<(f-'0');k++){
                res.push_back(-1);
            }
        }
        j++;
    }
    return res;
}

std::vector<int> sort_info(std::vector<int> & filesystem){
    size_t r = 0;
    size_t l = 0;
    r = filesystem.size()-1;
    for(;l<r;){
        while(filesystem[r]==-1)
            r--;
        while(filesystem[l]!=-1)
            l++;
        //breakout for crossing
        if(l>=r) break;
        std::swap(filesystem[l],filesystem[r]);
        r--;
        l++;
    }
    return filesystem;
}

uint64_t checksumv1(std::vector<int> & filesystem){
   uint64_t ans = 0;
   uint64_t i = 0;
   for(auto & r:filesystem){
        if(r!=-1){
            ans+=r*i;
        }
        i++;
   }
   return ans;
}

TEST_CASE( "day9", "day" ){
    auto string_from_file = utils::get_inputs_from_file("day9.in");
    auto filesys= create_disk_map(string_from_file[0]);
    auto filesystem= sort_info(filesys);
    std::cout<<"part-1:"<<checksumv1(filesystem);

}