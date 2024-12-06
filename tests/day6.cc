#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"
#include <set>
using namespace utils;
//1503
using graph_st = std::vector<std::string>;
using visited_nodes = std::set<std::pair<int,int>>;
using dir = std::pair<int,int>;
using visited_nodes_f = std::set<std::pair<std::pair<int,int>,std::pair<int,int>>>;

// | 0  1 |
// |-1  0 | //should be the transformation matrix for 90 right rotation 
// [j]
// [i] //should be the input vector -> [j i]->[-i j] so we just need to swap direction like this 

bool valid(int i,int j, int m, int n){
    if(i>(m-1) || j>(n-1) || j<=0 || i<=0){
        return false;
    }  
    return true;
}

bool dfsF(int i, int j,dir & d, graph_st & graph,visited_nodes_f &S){
    while(true){
        if(){
            return true;
        }
        std::pair<int,int> p {i,j};
        std::pair<std::pair<int,int>,std::pair<int,int>> pp{p,d};
        if(S.contains(pp))
        {
            return false;
        }
        S.insert(pp);
        auto iu =i+d.second;
        auto ju =j+d.first;
        //looks ahead
        //direction is updated 
        if(valid(iu,ju,graph.size(),graph[i].size())){
            if(graph[iu][ju]=='#'){
                //transformation
                d = {-d.second,d.first};
            }
        }
        iu =i+d.second;
        ju =j+d.first;
        i=iu;
        j=ju;
    }
    return false;
}


void dfs(int i, int j,dir & d, graph_st & graph,visited_nodes & v){
    if(i>=graph.size() || j>=graph[i].size() || j<0 || i<0){
        return;
    }  
    // graph[i][j]='*';
    if(v.find({i,j})==v.end()) v.insert({i,j});
    auto iu =i+d.second;
    auto ju =j+d.first;
    if(valid(iu,ju,graph.size(),graph[i].size())){
        if(graph[iu][ju]=='#'){
            d = {-d.second,d.first};
        }
    }
    dfs(i+d.second,j+d.first,d,graph,v);
}

std::pair<int,int> get_start_position(std::vector<std::string> & graph,char delim){
    for(size_t i=0;i<graph.size();i++){
        for(size_t j=0;j<graph[i].size();j++){
            if(delim==graph[i][j]){
                return {i,j};
            }
        }
    }
    // if not found
    return {-1,-1};
}

void print_g(std::vector<std::string> & graph)
{
    std::cout<<"*******************"<<std::endl;
    for(auto & e: graph)
    {
        std::cout<<e<<std::endl;
    }
    std::cout<<"*******************"<<std::endl;
}

TEST_CASE( "day6", "day6" ){
    auto graph = utils::get_inputs_from_file("day6.in");
    auto [sx,sy] = get_start_position(graph,'^');
    std::cout<<sx<<" , "<<sy<<std::endl;
    visited_nodes v;
    dir d{0,-1};
    dfs(sx,sy,d,graph,v);
    std::cout<<"ans-1 "<<v.size()<<std::endl;
    // print_g(graph);
    // part-2 
    // Place an obstacle over every place visited in the previous part 
    int count = 0;
    for(auto [x,y]:v)
    {
        auto &gr = graph;
        dir d2{0,-1};
        visited_nodes_f V;           
        gr[x][y]='#';
        if(x!=sx || y!=sy)
        {
            if(!dfsF(sx,sy,d2,gr,V))
                count++;
        }
        gr[x][y]='.';
    }
    std::cout<<"part-2 "<<count<<std::endl;
}
