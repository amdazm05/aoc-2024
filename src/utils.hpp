#ifndef _UTILS
#define _UTILS
#include <vector>
#include <string_view>
#include <fstream>
#include <iostream>
#include <source_location>
#include <queue>
#include <unordered_set>
#include <unordered_map>

namespace utils{
    std::vector<std::string> get_inputs_from_file(std::string_view filep,const std::source_location location =
               std::source_location::current()){
        std::vector<std::string> result;
        try{
            std::ifstream fs;
            fs.open(std::string(filep));
            if (!fs) {
                throw std::runtime_error("file opening error!"); 
            }
            std::string res;
            while(std::getline(fs,res))
            {
                result.push_back(res);
            }
        }
        catch(std::exception & e){
            std::cerr<< location.file_name() << '('
              << location.line() << ':'
              << location.column() << ") `"
              << location.function_name() << "`: "<<e.what()<<std::endl;
        }
        return result;
    }

    std::vector<std::pair<int,int>> get_number_pairs_seperated_with_characters
        (std::vector<std::string> & list,std::string_view seperation_string)
    {
        std::vector<std::pair<int,int>> res;
        res.reserve(list.size());
        for(const auto & str: list)
        {
            auto it = str.find(seperation_string);
            std::string f = str.substr(0,it);
            std::string s = str.substr(it+seperation_string.length(),str.size());
            try{
                int a = std::stoi(std::string(f));
                int b = std::stoi(std::string(s));
                res.emplace_back(std::pair<int,int>{a,b});
            }
            catch(std::exception & e)
            {   
                std::cout<<e.what()<<std::endl;
            }
        }
        return res;
    }

    std::vector<int> find_difference_of_minimum_lists(std::vector<std::pair<int,int>> & lists)
    {
        std::priority_queue<int,std::vector<int>,std::greater<int>> pq1;
        std::priority_queue<int,std::vector<int>,std::greater<int>> pq2;
        for(const auto & l:lists){
            pq1.push(l.first);
            pq2.push(l.second);
        }

        std::vector<int> diffs;
        diffs.reserve(lists.size());
        while(!pq1.empty() || !pq2.empty())
        {
            int a = pq1.top();pq1.pop();
            int b = pq2.top();pq2.pop();
            diffs.push_back(std::abs(a-b));
            // std::cout<<a<<" - "<<b<<std::endl;
        }
        return diffs;
    }

    long long compute_similarity_index(std::vector<std::pair<int,int>> & result_in_ints){
        long long res = 0;
        std::unordered_map<int,int> r;
        for(auto & entry:result_in_ints){
            r[entry.second]++;
        }

        for(auto & [left,_]:result_in_ints)
            res+=((long long)r[left] * (long long)left);
        return res;
    }

}

#endif /*_UTILS*/