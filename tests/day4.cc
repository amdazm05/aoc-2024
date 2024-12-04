#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"
using namespace utils;

int dfs(int i,int j,const int m,const int n,
    std::pair<int,int> dir,std::string & res,std::vector<std::string> & graph){
    if(i==n || j==m || j<0 || i<0 || (res.size()>=4 && res!="XMAS")){
        res.clear();
        return 0;
    }
    res+=graph[i][j];
    // return path
    if(res=="XMAS"){
        res.clear();
        return 1;
    }
    int ans =0;
    ans+=dfs(i+dir.first,j+dir.second,m,n,dir,res,graph);
    return ans;
}

int dfsX(int i,int j,const int m,const int n,
    std::pair<int,int> dir,std::string & res,
    std::vector<std::string> & graph)
{
    
    // for edges //reject this
    if(i==n || j==m || j<0 || i<0 ||(res.size()>=3 && res!="MAS")){
        res.clear();
        return 0;
    }
    res+=graph[i][j];
    if(res=="MAS"){
        res.clear();
        return 1;
    }
    int ans=0;
    ans+=dfsX(i+dir.first,j+dir.second,m,n,dir,res,graph);
    return ans;
}

TEST_CASE("day4","day4"){
    auto strings_from_file =  utils::get_inputs_from_file("day4.in");
    auto & graph = strings_from_file;
    const int n = graph.size(); //vertical stride
    const int m = graph[0].size(); //horizontal stride
    std::string res="";
    int ans=0;
    for(int i =0;i<n;i++){
        for(int j =0;j<m;j++){
            ans+=dfs(i,j,m,n,{1,0},res,graph);
            ans+=dfs(i,j,m,n,{0,1},res,graph);
            ans+=dfs(i,j,m,n,{1,1},res,graph);
            ans+=dfs(i,j,m,n,{-1,-1},res,graph);
            ans+=dfs(i,j,m,n,{-1,0},res,graph); 
            ans+=dfs(i,j,m,n,{0,-1},res,graph);
            ans+=dfs(i,j,m,n,{1,-1},res,graph);
            ans+=dfs(i,j,m,n,{-1,1},res,graph);
        }
    }
    std::cout<<"part-1 "<<ans<<std::endl;

    //part-2
    //I can be greedy and start looking at 'A's
    int count = 0;
    for(int i =0;i<n;i++){
        for(int j =0;j<m;j++){
            //look for center
            if(graph[i][j]=='A'){
                ans=0;
                ans+=dfsX(i+1,j+1,m,n,{-1,-1},res,graph);
                ans+=dfsX(i+1,j-1,m,n,{-1,1},res,graph);
                ans+=dfsX(i-1,j-1,m,n,{1,1},res,graph);
                ans+=dfsX(i-1,j+1,m,n,{1,-1},res,graph);
                
                //atleast 2 scores
                if(ans==2){
                    count++;
                }
            }
        }
    }
    std::cout<<"part-2 "<<count<<std::endl;
}