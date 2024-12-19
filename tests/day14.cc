#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"

using graph_T = std::vector<std::vector<int>>;
struct RobotState{
    int x;
    int y;
    int vx;
    int vy;
};

std::vector<RobotState> parseFile(std::string && filename) {
    std::vector<RobotState> states;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        RobotState state;
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &state.x,
        &state.y,&state.vx,&state.vy);
        states.push_back(state);
    }

    return states;
}
void print_states(std::vector<RobotState> & states){
    for(auto state:states){
        std::cout<<state.x<<" "<<state.y
            <<" v="<<state.vx<<" "<<state.vy<<std::endl;
    }

}

bool outbounds(int i ,int j,int m,int n){
    if(i<0 || j<0 || i>m-1 || j>n-1){
        return true;
    }
    return false;
}
//grid is 101x103
void simulate(std::vector<RobotState> & states,int m,int n,int iters,std::vector<std::pair<int,int>> &safes){
    int iteration=0;
    int res=0;
    std::vector<std::vector<char>> grid(m,std::vector<char>(n,'.'));
    while(iteration<iters){
        //state update
        for(auto & robot:states){
            robot.x+=robot.vx;
            robot.y+=robot.vy;
            robot.x=(((robot.x%n)+n)%n);
            robot.y=(((robot.y%m)+m)%m);
        }
        iteration++;
    }
    int q1=0;
    int q2=0;
    int q3=0;
    int q4=0;

    for(const auto &robot:states){
        grid[robot.y][robot.x]='#';
        if(robot.x == (n-1)/2){
            continue;
        }
        if(robot.y == (m-1)/2){
            continue;
        }

        if(robot.y < (m-1)/2 && robot.x<(n-1)/2)
        {
            q1++;
        }

        if(robot.y > (m-1)/2 && robot.x<(n-1)/2)
        {
            q2++;
        }

        if(robot.y > (m-1)/2 && robot.x>(n-1)/2)
        {
            q3++;
        }

        if(robot.y < (m-1)/2 && robot.x>(n-1)/2)
        {
            q4++;
        }
    }
    // utils::print_vector_of_vector(grid);
    // std::cout<<(q1*q2*q3*q4)<<std::endl;
    safes.push_back({q1*q2*q3*q4,iters});
}


TEST_CASE("day14","day14"){
    auto states = parseFile("day14.in");
    // print_states(states);
    std::vector<std::pair<int,int>> safes;
    int a=7000;
    while (a<10000)
    {
        simulate(states,103,101,a,safes);
        a++;
    }
    for(auto [safe,s]:safes){
        std::cout<<safe<<" "<<s<<std::endl;
    }
    

}