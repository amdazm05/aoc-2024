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

std::vector<std::vector<int>> create_disk_map_clusters(std::string &fs){
    std::vector<std::vector<int>> res; 
    res.reserve(16*(1<<16));
    int j =0;
    for(int i=0;auto & f:fs){
        if(j%2==0){
            std::vector<int> subvec;
            for(int k=0;k<(f-'0');k++){
                subvec.push_back(i);
            }
            res.push_back(subvec);
            i++;
        }else{
            for(int k=0;k<(f-'0');k++){
                res.push_back({-1});
            }
        }
        j++;
    }
    return res;
}

int lookahead(int i,int r,std::vector<std::vector<int>> & filesystem){
    int count =0;
    for(int j=i;j<r;j++){
        if(filesystem[j][0]!=-1){
            return count;
        }   
        count++;
    }
    return 0;
}

void sort_infoV2(std::vector<std::vector<int>> & filesystem){
    size_t r = 0;
    size_t l = 0;
    std::unordered_set<int> set;
    int n = filesystem.size();
    r = n-1;
    while(r>0){
        if(l<r){
            if(filesystem[l][0]==-1){
                int count=lookahead(l,r,filesystem);
                if(count>=filesystem[r].size() && filesystem[r][0]!=-1 
                    && !set.contains(filesystem[r][0])){
                    set.insert(filesystem[r][0]);
                    for(int i=0;i<filesystem[r].size();i++)
                        std::swap(filesystem[l+i][0],filesystem[r][i]);
                    // utils::print_vector_of_vector(filesystem);
                    r--;
                }
            }
            l++; 
        }
        // no space found move to next element
        else{
            l=0;
            r--;
        } 
    }
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

uint64_t checksumv2(std::vector<std::vector<int>> & filesystem){
   uint64_t ans = 0;
   uint64_t i = 0;
   for(auto & ll:filesystem){
        for(auto & r:ll){
            if(r!=-1){
                ans+=r*i;
            }
            i++;
        }
   }
   return ans;
}



TEST_CASE( "day9", "day" ){
    auto string_from_file = utils::get_inputs_from_file("day9.in");
    auto filesys= create_disk_map(string_from_file[0]);
    auto filesystem= sort_info(filesys);
    std::cout<<"part-1:"<<checksumv1(filesystem);

    // part-2
    // use file sys //sort in a special way
    auto filesys2 = create_disk_map_clusters(string_from_file[0]);
    // utils::print_vector_of_vector(filesys2);
    sort_infoV2(filesys2);
    // utils::print_vector_of_vector(filesys2);
    std::cout<<"part-2:"<<checksumv2(filesys2);
}