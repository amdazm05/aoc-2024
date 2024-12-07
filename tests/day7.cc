#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"
using namespace utils;

inline long long concat(long long l1,long long l2){
    return std::stoll(std::to_string(l1)+std::to_string(l2));
}

bool lrtree(int i ,long long res ,long long target,std::vector<long long> & data){   
    if(i==data.size()){
        if(target==res){
            return true;
        }
        return false;
    } 
    int ret=false;   
    ret|=lrtree(i+1,res*data[i],target,data);
    ret|=lrtree(i+1,res+data[i],target,data);
    ret|=lrtree(i+1,concat(res,data[i]),target,data);
    return ret;
}

bool dfs(long long i ,long long res ,long long target,std::vector<long long> & data){
    // std::cout<<res<<"----"<<target<<std::endl;
    if(i==data.size()){
        if(res==target)
            return true;
        return false;
    }
    bool ret=false;
    ret|=dfs(i+1,res*data[i],target,data);
    ret|=dfs(i+1,res+data[i],target,data);
    return ret;
}

std::pair<std::vector<long long>,std::vector<std::vector<long long>>> get_target_and_equation(std::vector<std::string> & list){
    std::pair<std::vector<long long>,std::vector<std::vector<long long>>> res;
    std::vector<std::string> l2;
    for(auto & l:list){
        auto pos = l.find(":");
        auto target = l.substr(0,pos);
        auto rest_of_string = l.substr(pos+2,l.size()-pos-2);
        res.first.push_back(std::stoll(target)); 
        l2.push_back(rest_of_string);
    }
    auto l2_ints = divide_into_list_of_lists_of_ll(l2," ");
    for(auto & i2:l2_ints){
        res.second.push_back(i2);
    }
    // print_vector_of_vector(res.second);
    return res;
}

TEST_CASE( "day7", "day7" ){
    auto strings_from_file = utils::get_inputs_from_file("day7.in");
    auto [targets,operands]=get_target_and_equation(strings_from_file);

    long long res=0;
    for(size_t i=0;i<targets.size();i++){
        auto check = dfs(1,operands[i][0],targets[i],operands[i]);
        if(check){
            res+=targets[i];
        }
    }
    std::cout<<"part-1 "<< res<<std::endl;

    res=0;
    for(size_t i=0;i<targets.size();i++){
    auto check = lrtree(1,operands[i][0],targets[i],operands[i]);
        if(check){
            res+=targets[i];
        }
    }
    std::cout<<"part-2 "<< res<<std::endl;
}   