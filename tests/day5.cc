#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"
using namespace utils;

template<typename T>
void list_print(std::vector<T> &l){
    std::cout<<"********************\n";
    for(auto & e:l){
        std::cout<<e<<std::endl;
    }
    std::cout<<"********************\n";
}

void split_string_lists(
    std::vector<std::string> & original,
    std::vector<std::string> & list1,std::vector<std::string> & list2){
    
    size_t found = 0;
    for(std::size_t i=0;i<original.size();i++){
        // std::cout<<original[i].size()<<std::endl;
        if(original[i].size()==1){
            std::cout<<" found list 2 start"<<i<<std::endl;
            found=i;
            break;
        }
    }

    list1 = std::vector<std::string>{original.begin(),original.begin()+found};
    list2 = std::vector<std::string>{original.begin()+found+1,original.end()};
    // list_print(list1);
    // list_print(list2);
}

bool is_good_order(std::vector<int> & l,std::vector<std::pair<int,int>> &l2){
    std::unordered_map<int,int> umap;
    bool isgood = true;
    for(size_t i=0;i<l.size();i++){
        umap[l[i]]=i;
    }

    for(auto & [g,l]:l2){
        //this pair does not exist or rule not applicable
        if(umap.find(g)==umap.end() ||umap.find(l)==umap.end())
            continue;
        //if its in the list then continue
        if(umap[g]>umap[l]){
            isgood=false;
            return isgood;
        }
    }
    return isgood;
}

void fix_unordered_ones(std::vector<int> & l,std::vector<std::pair<int,int>> &l2){
    std::unordered_map<int,int> umap;
    for(size_t i=0;i<l.size();i++){
        umap[l[i]]=i;
    }

    for(auto & [g,lu]:l2){
        //this pair does not exist or rule not applicable
        if(umap.find(g)==umap.end() ||umap.find(lu)==umap.end())
            continue;
        //if its in the list then continue
        if(umap[g]>umap[lu]){
            std::cout<<g<<" "<<lu<<std::endl;
            std::swap(l[umap[g]],l[umap[lu]]);
        }
    }
}

//Topological sort
//
std::vector<int> topological_sort_list(std::vector<std::pair<int,int>> & nodes,std::vector<int> &list){
    //res
    std::vector<int> res;
    //checks if current list elements for pushing back
    std::unordered_map<int,bool> umap;
    std::unordered_map<int,int> indegrees;

    // for(auto [a,ll]:adj){
    //     std::cout<<a<<"--";
    //     for(auto n : ll){
    //         std::cout<<n<<",";
    //     }
    //     std::cout<<"\n";
    // }

    for(auto & n:list){
        umap[n]=true;
    }

        //create an adjoint from nodes
    std::unordered_map<int,std::vector<int>> adj;
    for(auto & [f,s]:nodes){
        //only add rules to make adj if they are present in initial list
        if(umap[f] && umap[s]){
            adj[f].push_back(s);
        }
    }

    for(auto & [p,ll]: adj){
        for(auto & s:ll){
            indegrees[s]++;
        }
    }
    std::queue<int> q;
    for(auto [key,_]:adj){
        if(indegrees[key]==0){
            q.push(key);
        }
    }

    while(!q.empty()){
        int f = q.front();q.pop();
        //if the element was part of the current list then use this

        if(umap[f]){
            res.push_back(f);
        }
        for(auto & a:adj[f]){
            indegrees[a]--;
            if(indegrees[a]==0){
                q.push(a);
            }
        }
    }
    // list_print(res);
    return res;
}

TEST_CASE("day5","day5"){
    auto strings_from_file = utils::get_inputs_from_file("day5.in");
    // get_number_pairs_seperated_with_characters

    std::vector<std::string> order;
    std::vector<std::string> printing_queue;
    //1- list order of printing 
    //2- pages to produce in each update

    split_string_lists(strings_from_file,order,printing_queue);
    //All strings have been split 

    auto pair_orders= get_number_pairs_seperated_with_characters(order,"|");
    auto list = get_number_seperated_with_delim(printing_queue,",");
    // print_vector_of_vector(list);
    int ans=0;
    for(auto & l:list){
        if(is_good_order(l,pair_orders)){
            ans+=l[l.size()/2];
        }
    }
    std::cout<<"part-1 "<<ans<<std::endl;

    int ans2=0;
    // print_vector_of_vector(list);
    for(auto & l:list){
        if(!is_good_order(l,pair_orders)){
            l=topological_sort_list(pair_orders,l);
            ans2+=l[l.size()/2];
        }
    }
    std::cout<<"part-2 "<<ans2<<std::endl;
}