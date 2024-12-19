#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"

using p = std::pair<int,int>;
using graph = std::vector<std::string>;
using pmap = std::unordered_map<int,std::unordered_map<int,int>>;
using pmapb = std::unordered_map<int,std::unordered_map<int,bool>>;

std::pair<int,int> find_start(graph & g,char find){
    for(size_t i=0;i<g.size();i++){
        auto it=std::find(g[i].begin(),g[i].end(),find);
        if(it!=g[i].end()){
            int j =it-g[i].begin();
            return {i,j};
        }
    }
    return {-1,-1};
}

using distance= std::unordered_map<p,std::vector<p>>;
using dpp = std::pair<int,std::pair<std::pair<int,int>,std::pair<int,int>>>;
#define console(p) std::cout<<"{"<<p.first<<","<<p.second<<"}"
#define x first
#define y second

pmap shortest_distance(p && source,p && end,graph & g){
    pmap distance;
    pmapb visited;
    
    std::array<std::pair<int,int>,4> directions;
    directions[0]={0,1};
    directions[1]={0,-1};
    directions[2]={1,0};
    directions[3]={-1,0};
    
    std::priority_queue<dpp,std::vector<dpp>,std::greater<>> pq; 
    //populate distance 
    for(int i=0;i<g.size();i++){
        for(int j=0;j<g.size();j++){
            if(g[i][j]!='#')
                distance[i][j]=INT_MAX;
        }
    }
    auto [x0,y0]=source;
    distance[x0][y0]=0;
    pq.push({distance[x0][y0],{{x0,y0},{0,1}}});
    while(!pq.empty()){
        auto [dis,pos_dir] = pq.top();pq.pop();
        auto [point,dir] = pos_dir;
        if(visited[point.x][point.y]) continue;
        visited[point.x][point.y]=true;
        for(auto & d:directions){
            auto x = point.x+d.x;
            auto y = point.y+d.y;
            auto diffx = d.x;
            int score = 0; 
            if((dir.x==-d.x && dir.y==0 && d.y==0)||
                (dir.y==-d.y && dir.x==0 && d.x==0)){
                    continue;
            }
            score +=
                (abs(dir.x-d.x!=0) && abs(dir.y-d.y)!=0)?1001:1;
            score += dis;
            if(g[x][y]!='#'){
                if(score<distance[x][y]){
                    distance[x][y]=score;
                    pq.push({distance[x][y],{{x,y},{d.x,d.y}}});
                }
            }
        }
    }
    return distance;
}


int shortest_distanceV2(p && source,p && end,graph & g, pmap & exp){
    pmap distance;
    pmapb visited;
    
    std::array<std::pair<int,int>,4> directions;
    directions[0]={0,1};
    directions[1]={0,-1};
    directions[2]={1,0};
    directions[3]={-1,0};
    std::vector<std::vector<std::pair<int, int>>> 
        parent(g.size(), std::vector<std::pair<int, int>>(g[0].size()
            , {-1, -1}));
    
    std::priority_queue<dpp,std::vector<dpp>,std::greater<>> pq; 
    //populate distance 
    for(int i=0;i<g.size();i++){
        for(int j=0;j<g.size();j++){
            if(g[i][j]!='#')
                distance[i][j]=INT_MAX;
        }
    }
    auto [x0,y0]=end;
    distance[x0][y0]=0;
    pq.push({distance[x0][y0],{{x0,y0},{0,1}}});
    while(!pq.empty()){
        auto [dis,pos_dir] = pq.top();pq.pop();
        auto [point,dir] = pos_dir;
        if(visited[point.x][point.y]) continue;
        visited[point.x][point.y]=true;
        for(auto & d:directions){
            auto x = point.x+d.x;
            auto y = point.y+d.y;
            auto diffx = d.x;
            int score = 0; 
            if((dir.x==-d.x && dir.y==0 && d.y==0)||
                (dir.y==-d.y && dir.x==0 && d.x==0)){
                    continue;
            }
            score +=
                (abs(dir.x-d.x!=0) && abs(dir.y-d.y)!=0)?1001:1;
            score += dis;
            if(g[x][y]!='#'){
                if(score<distance[x][y]){
                    distance[x][y]=score;
                    pq.push({distance[x][y],{{x,y},{d.x,d.y}}});
                    parent[x][y]={point.x,point.y};
                }
            }
        }
    }

    // std::vector<std::pair<int,int>> res;
    // auto temp = end;
    // res.push_back(temp);
    // while(temp!=source){
    //     temp = parent[temp.x][temp.y];
    //     res.push_back(temp);
    // }
    // std::cout<<res.size()<<std::endl;
    return distance[source.x][source.y];
}


TEST_CASE("day16","day"){
    auto graph = utils::get_inputs_from_file("day16.in");
    //start
    auto [x0,y0] = find_start(graph,'S');
    auto [xfin,yfin] = find_start(graph,'E');
    auto res= shortest_distance({x0,y0},{xfin,yfin},graph);
    std::cout<<"part-1 "<<res[xfin][yfin]<<std::endl;
    std::cout<<"part-2 "<<shortest_distanceV2({x0,y0},{xfin,yfin},graph,res);


}