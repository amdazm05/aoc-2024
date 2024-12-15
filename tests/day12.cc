#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include "utils.hpp"
using namespace utils;
using graph_T =std::vector<std::string>;
using visited_T =std::unordered_map<int,std::unordered_map<int,bool>>;
using visitedi_T =std::unordered_map<int,std::unordered_map<int,int>>;
using pos_set = std::unordered_map<int,std::unordered_map<int,bool>>;
#define CHECK_PRESENSE(b,y,target) ((!outbounds(b,y,graph))&&graph[b][y]==target)
#include <unordered_map>

bool outbounds(int i ,int j,graph_T &g){
    if(i<0 || j<0 || i>=g.size() || j>=g[0].size()-1){
        return true;
    }
    return false;
}

int dfsV2(int i,int j,char t,graph_T &graph,graph_T & c,visited_T & v,
    visited_T & gv,pos_set &s,int &p){
    //hit a boundry
    if(v[i][j]){
        return 0;
    }
    if(outbounds(i,j,graph) ||t!=graph[i][j]){
        s[i][j]=true;
        p++;
        return 0;
    }
    v[i][j]=true;
    gv[i][j]=true;
    c[i][j]='.';
    int res = 1;
    
    res += dfsV2(i + 1, j, t, graph,c, v, gv,s, p);
    res += dfsV2(i - 1, j, t, graph,c, v, gv,s, p);
    res += dfsV2(i, j + 1, t, graph,c, v, gv,s, p);
    res += dfsV2(i-1, j - 1, t, graph,c, v, gv,s, p);
    res += dfsV2(i + 1, j+1, t, graph,c, v, gv,s, p);
    res += dfsV2(i - 1, j+1, t, graph,c, v, gv,s, p);
    res += dfsV2(i+1, j - 1, t, graph,c, v, gv,s, p);
    res += dfsV2(i, j - 1, t, graph,c, v, gv,s, p);

    return res;
}

int countcorners(pos_set & set,graph_T & graph, char target){
    int corner_count=0;
    std::set<std::pair<int,int>> uq;
    pos_set s;
    s=set;
    for(auto [x,uu]:set){
        for(auto [y,pr]:uu){
            int count=0;
            auto t= x-1;auto b= x+1;
            auto l= y-1;auto r= y+1; 
            if(s[x][y] && s[x][l] && s[t][y] && CHECK_PRESENSE(t,l,target))
            {
                corner_count++;
            }
            if(s[x][y] 
                && CHECK_PRESENSE(x,l,target)
                && CHECK_PRESENSE(t,y,target)
                // && CHECK_PRESENSE(t,l,target)
            )
            {
                corner_count++;
            }
            if(s[x][y] && s[x][l] && s[b][y] && CHECK_PRESENSE(b,l,target))
            {
                corner_count++;
            }
            if(s[x][y] 
                && CHECK_PRESENSE(x,l,target)
                && CHECK_PRESENSE(b,y,target)
                // && CHECK_PRESENSE(b,l,target)
            )
            {
                corner_count++;
            }
            if(s[x][y] && s[x][r] && s[t][y] && CHECK_PRESENSE(t,r,target))
            {
                corner_count++;
            }
            if(s[x][y] 
                && CHECK_PRESENSE(x,r,target)
                && CHECK_PRESENSE(t,y,target)
                // && CHECK_PRESENSE(t,r,target)
            )
            {
                corner_count++;
            }

            if(s[x][y] && s[x][r] && s[b][y] && CHECK_PRESENSE(b,r,target))
            {
                corner_count++;
            }
            if(s[x][y] 
                && CHECK_PRESENSE(x,r,target)
                && CHECK_PRESENSE(b,y,target)
                // && CHECK_PRESENSE(b,r,target)
            )
            {
                corner_count++;
            } 
        }
    }
    return corner_count;
}

int dfs(int i,int j,char t,graph_T &graph,graph_T &g1,visited_T & v,visited_T & gv,int &p){
    //hit a boundry
    // -------
    //|       |
    // ------- 
    if(v[i][j]){
        return 0;
    }
    if(outbounds(i,j,graph) ||t!=graph[i][j]){
        p++;
        return 0;
    }
    v[i][j]=true;
    gv[i][j]=true;
    // g1=[i][j];

    int res = 1;
    
    res += dfs(i + 1, j, t, graph,g1, v, gv, p);
    res += dfs(i - 1, j, t, graph,g1, v, gv, p);
    res += dfs(i, j + 1, t, graph,g1, v, gv, p);
    res += dfs(i, j - 1, t, graph,g1, v, gv, p);

    return res;
}

TEST_CASE("day12","day"){
    auto graph=utils::get_inputs_from_file("day12.in");
    int m = graph.size();
    int n =graph[0].size();
    n=n-1;
    std::cout<<m<<" x "<<n-1<<std::endl;
    
    std::unordered_set<char> gardens;
    for(auto nx:graph){
        for(auto plant:nx){
            if(plant!=13)
            gardens.insert(plant);
        }
    }


    std::cout<<"Garden A : count "<<std::endl;
    visited_T gv;
    int res=0;
    for(int i=0;auto nx:graph){
        for(int j=0;auto plant:nx){
            if(plant!=13 && !gv[i][j]){
                visited_T mp;
                int p=0;
                graph_T g1=graph;
                int a=(dfs(i,j,plant,graph,g1,mp,gv,p));
                res+=a*p;
            }
            j++;
        }
        i++;
    }
    std::cout<<res<<std::endl;


    visited_T gv2;
    visited_T gv3;
    int res2=0;
    for(int i=0;auto nx:graph){
        for(int j=0;auto plant:nx){
            if(plant!=13 && !gv2[i][j]){
                visited_T mp;
                visited_T mp2;
                graph_T g1=graph;
                pos_set set;
                int p=0;
                dfsV2(i,j,plant,graph,g1,mp,gv2,set,p);
                int a=(dfs(i,j,plant,graph,g1,mp2,gv3,p));
                p=countcorners(set,g1,'.');
                std::cout<<plant<<"  "<<p<<"p*a="<<p<<"*"<<a<<"="<<(p*a)<<std::endl;
                res2+=a*p;
            }
            j++;
        }
        i++;
    }
    std::cout<<res2<<std::endl;
}