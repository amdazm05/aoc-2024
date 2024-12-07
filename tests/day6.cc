#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"

using namespace utils;
using graph_t = std::vector<std::string>;
using visited_nodes_t = std::set<std::pair<int,int>>;
using direction_t = std::pair<int,int>;
using position_t  = std::pair<int,int>;
using visited_states_t = std::set<std::pair<position_t,direction_t>>;

// For base coordinates rotating clockwise //equivalent to right 90deg
// ^ -i Coordinate System
// |
// |---> +j
// 
// [-1 0] -> [0 1] -> [1 0] -> [0 -1]
// first->-second
// second->first


std::pair<int,int> get_start_position(graph_t & graph,char delim){
    for(size_t i=0;i<graph.size();i++){
        for(size_t j=0;j<graph[i].size();j++)
            if(delim==graph[i][j])
                return {i,j};
    }
    return {-1,-1};
}

inline bool is_in_range(int i,int j,graph_t & graph){
    if(i<0 || j<0 || graph.size()<=i || graph[i].size()<=j)
        return false;
    return true;
}

inline void update_pos(int& i,int &j,direction_t & d){
    i+=d.first;
    j+=d.second;
}

inline void rotate_right(direction_t& d){
    std::swap(d.first,d.second);
    d.second = -d.second;
}

inline void add_state_to_map(position_t p, direction_t d, visited_states_t & vs){
    vs.insert({p,d});
}

inline bool is_state_in_visited_states(position_t p, direction_t d,visited_states_t & vs){
    return vs.contains({p,d});
}

int count_looped_paths(graph_t & graph,visited_nodes_t & visited,direction_t & d, int i, int j){
    int results=0;
    int io = i;
    int jo = j;
    auto dir = d;
    for(const auto & [x,y]:visited)
    {
        graph[x][y]='#';
        visited_states_t states;
        while(is_in_range(i,j,graph)){
            if(is_state_in_visited_states({i,j},d,states)){
                results++;
                break;
            }
            add_state_to_map({i,j},d,states);
            if(is_in_range(i+d.first,j+d.second,graph)){
                while(graph[i+d.first][j+d.second]=='#'){
                    rotate_right(d);
                }
            }
            update_pos(i,j,d);
        }
        //previous start
        i = io;
        j = jo;
        d = dir;
        graph[x][y]='.';
    }
    return results;
}

int count_unique_paths(graph_t & graph,visited_nodes_t & visited,direction_t & d, int i, int j){
    while(is_in_range(i,j,graph)){
        visited.insert({i,j});
        if(is_in_range(i+d.first,j+d.second,graph)){
            while(graph[i+d.first][j+d.second]=='#')
                rotate_right(d);
        }
        update_pos(i,j,d);
    }
    return visited.size();
}

TEST_CASE( "day6", "day6" ){
    auto graph = utils::get_inputs_from_file("day6.in");
    auto [sx,sy] = get_start_position(graph,'^');
    visited_nodes_t visited;
    direction_t dir{-1,0};

    //part-1
    std::cout<<"part-1 "<<count_unique_paths(graph,visited,dir,sx,sy)<<std::endl;
    dir = {-1,0};
    //part-2
    std::cout<<"part-2 "<<count_looped_paths(graph,visited,dir,sx,sy)<<std::endl;
}