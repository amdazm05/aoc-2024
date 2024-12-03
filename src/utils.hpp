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
#include <iostream>
#include <regex>

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

    std::vector<std::vector<int>> divide_into_list_of_lists_of_ints(
        std::vector<std::string> & list, std::string_view delim
    ){
        std::vector<std::vector<int>> results;
        results.reserve(list.size());
        for(const auto & item:list){
            std::vector<int> line;
            std::string temp = item;
            auto pos = temp.find(delim);
            auto opos = pos-pos;
            while(pos!=std::string::npos){
                auto res = temp.substr(0,pos);
                temp = temp.substr(pos+delim.size(),
                    temp.size()-pos-delim.size());
                pos = temp.find(delim);
                try{
                    int tbs = std::stoi(res);
                    line.push_back(tbs);
                }
                catch(std::exception & e){
                    std::cerr<<e.what()<<std::endl;
                }
            }
            //for last element
            {
                auto res = temp.substr(0,temp.size());
                int tbs = std::stoi(res);
                line.push_back(tbs);
            }
            results.push_back(line);
        }
        return results;
    }

    template<typename T>
    void print_vector_of_vector(std::vector<std::vector<T>> &lists_of_lists){
        std::cout<<"------------------"<<std::endl;
        for(auto & list: lists_of_lists){
            for(auto & items:list)
                std::cout<<items<<",";
            std::cout<<std::endl;
        }
        std::cout<<"------------------"<<std::endl;
    }

    bool is_negative(int in){
        return in <0;
    }

    bool is_positive(int in){
        return in >0;
    }

    template<typename T>
    int safe_list_count(std::vector<std::vector<T>> &lists_of_lists)
    {
        int res = 0;
        std::vector<std::vector<T>> comparison(lists_of_lists.size());
        
        for(size_t i =0;i<lists_of_lists.size();i++){
            for(size_t j =1;j<lists_of_lists[i].size();j++){
                comparison[i].push_back(lists_of_lists[i][j]- lists_of_lists[i][j-1]);
            }
        }
        print_vector_of_vector(comparison);
        for(size_t i =0;i<comparison.size();i++){
            bool isNeg = is_negative(comparison[i][0]);
            if((std::abs(comparison[i][0])<=3 && std::abs(comparison[i][0])>=1)){
                for(size_t j =0;j<comparison[i].size();j++){
                    if(is_negative(comparison[i][j])==isNeg && 
                        (std::abs(comparison[i][j])<=3 && std::abs(comparison[i][j])>=1)){
                    }
                    else{
                        res++;
                        break;
                    }
                }
            }
        }
        //complement of res is answer
        return lists_of_lists.size()-res;
    }

    bool is_safe(std::vector<int> & l,std::pair<int,int> filter)
    {
        auto sign = l[1]>l[0];
        if(sign){
            for(int i =1;i<l.size();i++){
                auto diff = l[i]-l[i-1];
                if(diff >filter.first or diff <filter.second)
                    return false;
            }
        }
        else{
            for(int i =1;i<l.size();i++){
                auto diff = l[i]-l[i-1];
                if(diff<-filter.first or diff>-filter.second)
                    return false;
            }
        }
        return true;
    }

    template<typename T>
    int safe_list_count_with_dampener(std::vector<std::vector<T>> &lists_of_lists)
    {
        int res = 0;
        for(auto & l:lists_of_lists)
        {
            for(int i =0;i<l.size();i++){
                std::vector<int> lc = l;
                lc.erase(lc.begin()+i);
                if(is_safe(lc,{3,1})){
                    res+=1;
                    break;
                }
            }
        }
        return res;
    }

    std::vector<std::string> find_string_patterns
        (std::string & test_string,std::string search_string)
    {
        std::vector<std::string> res;
        std::regex eng(search_string);
        std::sregex_iterator it(test_string.begin(),test_string.end(),eng);
        std::sregex_iterator end;

        while(it!=end){
            res.push_back(it->str());
            it++;
        }
        return res;
    }

    int compute_mul_string(std::vector<std::string> strings){
        auto res = 0;
        bool is_do=true;
        for(const auto & s:strings){
            if(s=="don't()"){
                is_do =false;
                continue;
            }
            else if(s=="do()"){
                is_do=true;
                continue;
            }
            if(is_do){
                auto spos = s.find('(');
                auto epos = s.find(',');
                auto eepos = s.find(')');

                auto a = std::stoi(s.substr(spos+1, epos-spos-1));
                auto b = std::stoi(s.substr(epos+1, eepos-epos-1));
                res+=(a*b);
            }
        }
        return res;
    }

}

#endif /*_UTILS*/