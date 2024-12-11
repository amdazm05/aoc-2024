
#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include "utils.hpp"
using namespace utils;

int countdigits(long long v){
    int count=0;
    while(v!=0){
        count++;
        v=v/10;
    }
    return count;
}

int iseven_digits(int v){
    return countdigits(v)%2==0;
}

std::vector<long long> get_digits(long long e){
    std::vector<long long> res;
    int n = countdigits(e);
    long long div=1;
    for(int i=0;i<n/2;i++)
        div*=10;
    int half1 = e/div;
    int half2 = e%div;   
    return {half2,half1};  
}

std::string multiply(std::string nums1, std::string nums2)
{
    int n = nums1.size();
    int m = nums2.size();
    std::string ans(n + m, '0');
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            int p = (nums1[i] - '0') * (nums2[j] - '0') + (ans[i + j + 1] - '0');
            ans[i + j + 1] = p % 10 + '0';
            ans[i + j] += p / 10;
        }
    }
    for (int i = 0; i < m + n; i++)
    {
        if (ans[i] != '0')
            return ans.substr(i);
    }
    return "0";
}

void run_cases(std::vector<std::string> & input){ 
    for(int i=0;i<25;i++){
        int sad=0;
        std::cout<<i<<std::endl;
        for(int j =0;j<input.size();j++){
            if(input[j]=="0"){
                input[j]="1";
            }
            else if(input[j].size()%2==0){
                int n = input[j].size();
                auto f = input[j].substr(0,n/2);
                auto s = input[j].substr(n/2,n-n/2);
                // checkforzeros
                int zz=0;
                for(;zz<s.size();zz++){
                    if(s[zz]!='0'){break;}
                }
                //all 0s1
                if(zz==s.size()) s="0";
                else{
                    s=s.substr(zz,s.size()-zz);
                }
                input.insert(input.begin()+j,f);
                j++;
                input.insert(input.begin()+j,s);
                j++;
                input.erase(input.begin()+j);
                j--;
            }
            else{
                input[j]=multiply(input[j],"2024");
            }
        }   
    }
}


TEST_CASE( "day11", "day" ){
    auto strings = utils::get_inputs_from_file("day11.in");
    auto inputs = divide_into_list_of_lists_of_strings(strings," ");
    utils::print_vector_of_vector(inputs);
    auto & input = inputs[0];
    run_cases(input);
    // utils::print_vector_of_vector(inputs);
    // int i = 102;
    std::cout<<input.size()<<std::endl;
}