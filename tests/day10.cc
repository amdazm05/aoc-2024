#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"
using namespace utils;

void dfs2(int i, int j,int c, std::vector<std::string> & map,int &s){
    if(i<0 || j<0 || i>=map.size() || j>=map[0].size()){
        return;
    }
    if(c!=(map[i][j]-'0')){
        return;
    }
    if(c==9 && map[i][j]=='9'){
        s++;
        return;
    }
    dfs2(i+1,j,c+1,map,s);
    dfs2(i,j+1,c+1,map,s);
    dfs2(i-1,j,c+1,map,s);
    dfs2(i,j-1,c+1,map,s);
}

void dfs(int i, int j,int c, std::vector<std::string> & map,std::set<std::pair<int,int>> &set){
    if(i<0 || j<0 || i>=map.size() || j>=map[0].size()){
        return;
    }
    if(c!=(map[i][j]-'0')){
        return;
    }
    if(c==9 && map[i][j]=='9'){
        if(!set.contains({i,j}))
            set.insert({i,j});
        return;
    }
    dfs(i+1,j,c+1,map,set);
    dfs(i,j+1,c+1,map,set);
    dfs(i-1,j,c+1,map,set);
    dfs(i,j-1,c+1,map,set);
}

TEST_CASE( "day9", "day" ){
    auto graph = utils::get_inputs_from_file("day10.in");
    print_graph(graph);

    int sum =0;
    for(int i=0;auto & str:graph){
        for(int j =0;auto & ch:str){
            if(ch=='0'){
                std::set<std::pair<int,int>> set;
                dfs(i,j,0,graph,set);
                sum+=set.size();
            }
            j++;
        }
        i++;
    }
    std::cout<<"part-1 "<<sum<<std::endl;

    int sum2=0;
    for(int i=0;auto & str:graph){
        for(int j =0;auto & ch:str){
            if(ch=='0'){
                int s=0;
                dfs2(i,j,0,graph,s);
                sum2+=s;
            }
            j++;
        }
        i++;
    }
    std::cout<<"part-1 "<<sum2<<std::endl;
}