#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"

std::pair<std::vector<std::vector<char>>, std::string> parseInput(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::vector<char>> grid;
    std::string commands;
    std::string command;

    // Read the grid from the file
    while (std::getline(file, line)) {
        if (line.empty()) {
            break;
        }
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }
    
    while (std::getline(file, command)){
        commands+=command;
    }

    return {grid, commands};  // Return a pair of grid and commands
}


std::vector<std::vector<char>> transformGrid(const std::vector<std::vector<char>>& input) {
    std::vector<std::vector<char>> output;
    int rows = input.size();
    
    // Process each row
    for (int i = 0; i < rows; ++i) {
        std::vector<char> newRow;
        // Check if it's the first or last row
        if (i == 0 || i == rows - 1) {
            newRow.push_back('#');
            newRow.push_back('#');
            for (size_t j = 1; j < input[i].size() - 1; ++j) {
                newRow.push_back(input[i][j]); // Copy internal characters
                newRow.push_back(input[i][j]);
            }
            newRow.push_back('#');
            newRow.push_back('#');
        } else {
            for (char c : input[i]) {
                if (c == 'O') {
                    newRow.push_back('[');
                    newRow.push_back(']');
                } else if (c == '#') {
                    newRow.push_back('#'); // Keep internal #
                    newRow.push_back('#'); // Keep internal #
                } else if (c == '@') {
                    newRow.push_back('@'); // Keep @ unchanged
                    newRow.push_back('.'); // Keep @ unchanged
                } else if (c == '.') {
                    newRow.push_back('.'); // Add the first .
                    newRow.push_back('.'); // Add the second .
                }
            }
        }
        output.push_back(newRow);
    }

    return output;
}

bool isoutbounds(int i,int j,std::vector<std::vector<char>> &grid){
    if(i<0 || j<0 || j>grid[0].size() || i>grid.size()){
        return true;
    }
    return false;
}

#define x first
#define y second
using p= std::pair<int,int>;

void print_grid(std::vector<std::vector<char>> & grid){
    std::cout<<"************************************\n";
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
    std::cout<<"************************************\n";
}

void dfs(p before, p after, p dir,std::vector<std::vector<char>> &grid){
    if(isoutbounds(after.x,after.y,grid)){
        return;
    }
    if(grid[after.x][after.y]=='#') return; //straight down 
    if(grid[after.x][after.y]=='O'){
        dfs(after,{after.x+dir.x,after.y+dir.y},dir,grid);
    }
    if(grid[after.x][after.y]=='.'){
        std::swap(grid[after.x][after.y],grid[before.x][before.y]);
        return;
    }
}

std::pair<int,int> find(std::vector<std::vector<char>> & grid){
    for(int i=0;i<grid.size();i++){
        for(int j = 0;j<grid[i].size();j++){
            if(grid[i][j]=='@'){
                return {i,j};
            };
        }
    }
    return {-1,-1};
}

int64_t sum(std::vector<std::vector<char>> & grid){
    int64_t res=0;
    for(int64_t i=0;i<grid.size();i++){
        for(int64_t j = 0;j<grid[i].size();j++){
            if(grid[i][j]=='O'){
                res+=(i*100+j);
            }
        }
    }
    return res;
}

void apply(std::vector<std::vector<char>> &grid,std::string & commands){

    std::unordered_map<char,std::pair<int,int>> dir;
    dir['^']={-1,0};
    dir['>']={0,1};
    dir['<']={0,-1};
    dir['v']={1,0};
    auto [i,j] = find(grid);
    for(auto command:commands){
        std::cout<<command<<std::endl;
        int di= i+dir[command].x;
        int dj= j+dir[command].y;
        dfs({i,j},{di,dj},dir[command],grid);
        if(grid[di][dj]=='@'){
            i=di;
            j=dj;
        }   
        // print_grid(grid);
    }
    std::cout<<"part-1 "<<sum(grid)<<std::endl;
    return;
}

/// @brief Part 2 dfs
/// @param before 
/// @param after 
/// @param dir 
/// @param grid 
void dfsV2(p before, p after, p dir,std::vector<std::vector<char>> &grid){
    // print_grid(grid);
    if(isoutbounds(after.x,after.y,grid)){
        return;
    }
    if(grid[after.x][after.y]=='#') return; //straight down 
    if(grid[after.x][after.y]=='['){
        dfsV2(after,{after.x+dir.x,after.y+dir.y},dir,grid);
        dfsV2(after,{after.x,after.y+dir.y+1},dir,grid);
    }
    if(grid[after.x][after.y]==']'){
        dfsV2(after,{after.x+dir.x,after.y+dir.y},dir,grid);
        dfsV2(after,{after.x,after.y+dir.y-1},dir,grid);
    }
    if(grid[after.x][after.y]=='.'){
            std::swap(grid[after.x][after.y],grid[before.x][before.y]);
    }
}
/// @brief 
/// @param before 
/// @param after 
/// @param dir 
/// @param grid 
void dfsH(p before, p after, p dir,std::vector<std::vector<char>> &grid){
    if(isoutbounds(after.x,after.y,grid)){
        return;
    }
    if(grid[after.x][after.y]=='#') return; //straight down 
    if(grid[after.x][after.y]==']' || grid[after.x][after.y]=='['){
        dfsH(after,{after.x+dir.x,after.y+dir.y},dir,grid);
    }
    if(grid[after.x][after.y]=='.'){
        std::swap(grid[after.x][after.y],grid[before.x][before.y]);
        return;
    }
}

bool ispushableV(p before, p after, p dir,std::vector<std::vector<char>> &grid,bool d){
    if(isoutbounds(after.x,after.y,grid)){
        return false;
    }
    if(grid[after.x][after.y]=='#'){
        return false;
    } 
    if(grid[after.x][after.y]=='.'){
        return true;
    }
    bool res=true;
    if(grid[after.x][after.y]=='[')
    {
        res&=ispushableV(after,{after.x+dir.x,after.y+dir.y},dir,grid,false);
        if(d==false){
            res&=ispushableV(after,{after.x,after.y+dir.y+1},dir,grid,true);
        }
    }
    else if(grid[after.x][after.y]==']')
    {
        res&=ispushableV(after,{after.x+dir.x,after.y+dir.y},dir,grid,false);
        if(d==false){
           res&=ispushableV(after,{after.x,after.y+dir.y-1},dir,grid,true);
        } 
    }
    return res;
}
/// @brief v2 sum
/// @param grid 
/// @return 
int64_t sum2(std::vector<std::vector<char>> & grid){
    int64_t res=0;
    for(int64_t i=0;i<grid.size();i++){
        for(int64_t j = 0;j<grid[i].size();j++){
            if(grid[i][j]=='['){
                res+=(i*100+j);
            }
        }
    }
    return res;
}

/// @brief Part2
/// @param grid 
/// @param commands 
void applyV2(std::vector<std::vector<char>> &grid,std::string & commands){

    std::unordered_map<char,std::pair<int,int>> dir;
    dir['^']={-1,0};
    dir['>']={0,1};
    dir['<']={0,-1};
    dir['v']={1,0};
    auto [i,j] = find(grid);
    for(auto command:commands){
        std::cout<<command<<std::endl;
        int di= i+dir[command].x;
        int dj= j+dir[command].y;
        if(command=='^' || command=='v'){
            bool ispush_able= ispushableV({i,j},{di,dj},dir[command],grid,false);
            if(ispush_able){
                dfsV2({i,j},{di,dj},dir[command],grid);
            }
        }
        else{
            dfsH({i,j},{di,dj},dir[command],grid);
        }
        // dfsV2();
        if(grid[di][dj]=='@'){
            i=di;
            j=dj;
        }   
        // print_grid(grid);
    }
    std::cout<<"part-2 "<<sum2(grid)<<std::endl;
    return;
}


TEST_CASE("day15","day15"){
    auto [grid, commands] = parseInput("day15.in");
    //part-1// apply(grid,commands);
    grid=transformGrid(grid);
    print_grid(grid);
    applyV2(grid,commands);
    // Output the commands for verification
    // std::cout << "Commands: " << commands << std::endl;
}