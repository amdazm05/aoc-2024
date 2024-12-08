#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"
using namespace utils;

using position_t = std::pair<int,int>;
using list_of_positions = std::vector<position_t>;

// specific frequency
// digit , low case , high case is freq
// antinodes are there when
// 1- inline with antenna with two antennas
// 2- twice as faraway from  as the other
// 3- different node frequencies dont create antinodes

bool inbounds(position_t &p, int m , int n){
    // end with character ascii  13 carriage for some reason so n-2
    if(p.first<0 || p.second<0 || p.second>n-2 || p.first>m-1)
        return false;
    return true;
}

void find_and_insert(position_t &pos,std::set<position_t>& set){
    if(!set.contains(pos)){
        set.insert(pos);
    }
}

size_t  check_anti_nodesV2(std::unordered_map<char,list_of_positions> & map, int m ,int n){
    std::set<position_t> set;
    for(auto &[key,ll]:map){
        for(auto &[x,y]:ll){
            for(auto &[x2,y2]:ll){
                //skip same nodes
                // if(x2==x && y2==y)
                //     continue;
                auto diffx=x2-x;
                auto diffy=y2-y;
                if(diffx==0 && diffy==0)
                    continue;

                position_t res1{x2,y2};
                position_t res2{x, y};

                while(inbounds(res1,m,n)){
                    find_and_insert(res1,set);
                    res1.first+=diffx;
                    res1.second+=diffy;
                }

                if(inbounds(res2,m,n)){
                    find_and_insert(res2,set);
                    res2.first+=diffx;
                    res2.second+=diffy;
                }
            }
        }
    }
    return set.size();
}

size_t  check_anti_nodes(std::unordered_map<char,list_of_positions> & map, int m ,int n){
    std::set<position_t> set;
    for(auto &[key,ll]:map){
        for(auto &[x,y]:ll){
            for(auto &[x2,y2]:ll){
                //skip same nodes
                // if(x2==x && y2==y)
                //     continue;
                auto diffx=x2-x;
                auto diffy=y2-y;
                if(diffx==0 && diffy==0)
                    continue;
                position_t res1{x2+diffx,y2+diffy};
                position_t res2{x-diffx, y-diffy};

                if(inbounds(res1,m,n)){
                    find_and_insert(res1,set);
                }

                if(inbounds(res2,m,n)){
                    find_and_insert(res2,set);
                }
            }
        }
    }
    return set.size();
}

void fill_map_of_chars(std::vector<std::string> & map,
    std::unordered_map<char,list_of_positions> & charmap){
    for(int i=0;i<map.size();i++){
        for(int j=0;j<map[i].size()-1;j++){
            if(map[i][j]!='.')
            {
                charmap[map[i][j]].push_back({i,j});
            }
        }
    }
}

TEST_CASE( "day8", "day" ){
    auto map = utils::get_inputs_from_file("day8.in");
    std::unordered_map<char,list_of_positions> charmap;

    fill_map_of_chars(map,charmap);
    for(auto & [key,l]:charmap){
        std::cout<<"key found: "<<key<<" :";
        for(auto e:l){
            std::cout<<"{"<<e.first<<","<<e.second<<"},";
        }
        std::cout<<" size()="<<l.size()<<std::endl;
    }

    std::cout<<"part-1 "<<check_anti_nodes(charmap,map.size(),map[0].size())<<std::endl;
    std::cout<<"part-2 "<<check_anti_nodesV2(charmap,map.size(),map[0].size())<<std::endl;
}
