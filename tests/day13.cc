#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using Pair = std::pair<int64_t,int64_t>;
#define x first;
#define y second;

struct PrizeData {
    Pair Apair;
    Pair Bpair;
    Pair prize;
};

std::vector<PrizeData> parseFile(const std::string& filename) {
    std::vector<PrizeData> prizes;
    std::ifstream file(filename);
    std::string line;
    std::string buttonA;
    while (std::getline(file, buttonA)) {
        PrizeData prizeData;

        // Parse Button A
        std::string buttonB, prize,l;
        std::getline(file, buttonB);
        std::getline(file, prize);
        std::cout<<buttonA<<std::endl;
        std::cout<<buttonB<<std::endl;
        std::cout<<prize<<std::endl;

        // Extract coordinates for Button A
        sscanf(buttonA.c_str(), "Button A: X+%ld, Y+%ld", &prizeData.Apair.first, &prizeData.Apair.second);
        // Extract coordinates for Button B
        sscanf(buttonB.c_str(), "Button B: X+%ld, Y+%ld", &prizeData.Bpair.first, &prizeData.Bpair.second);
        // Extract coordinates for Prize
        sscanf(prize.c_str(), "Prize: X=%ld, Y=%ld", &prizeData.prize.first, &prizeData.prize.second);
        prizes.push_back(prizeData);
        std::getline(file,l);
    }

    return prizes;
}

void print_parsed_data(std::vector<PrizeData> & prizes){
        // Output parsed data for verification
    for (const auto& prize : prizes) {
        std::cout << "A Pair: {" << prize.Apair.first << ", " << prize.Apair.second << "}, "
                  << "B Pair: {" << prize.Bpair.first << ", " << prize.Bpair.second << "}, "
                  << "Prize: {" << prize.prize.first << ", " << prize.prize.second << "}\n";
    }
}

void pt2i(std::vector<PrizeData> & prizes){
    // Output parsed data for verification
    for ( auto& prize : prizes) {
      prize.prize.first+=10000000000000;
      prize.prize.second+=10000000000000;
    }
}

std::pair<int64_t,int64_t> compute_solution_of_2x2(PrizeData & data){
    int64_t D=  ((data.Apair.first) *(data.Bpair.second)) - ((data.Apair.second)*(data.Bpair.first)); 
    int64_t Dx=  ((data.Bpair.second)*(data.prize.first)) -  ((data.Bpair.first)*(data.prize.second));
    int64_t Dy=  ((data.Apair.first)*(data.prize.second)) - ((data.Apair.second)*(data.prize.first));
    if((Dx%D==0) && (Dy%D==0)){
       return {Dx/D, Dy/D};
    }
    else{
       return {-1,-1};
    }
}

int main() {
    const std::string filename = "day13.in"; // Replace with your actual file path
    std::vector<PrizeData> prizes = parseFile(filename);
    // print_parsed_data(prizes);
    int64_t res=0;
    for(auto prize:prizes){
        auto [solx,soly]=compute_solution_of_2x2(prize);
        // std::cout<<solx<<"---"<<soly<<std::endl;
        if(solx<0 || soly<0)
            continue;
        res+=(solx*3+soly);
        
    }
    std::cout<<"part-1 "<<res<<std::endl;

    res=0;
    pt2i(prizes);
    // print_parsed_data(prizes);
    for(auto prize:prizes){
        auto [solx,soly]=compute_solution_of_2x2(prize);
        // std::cout<<solx<<"---"<<soly<<std::endl;
        if(solx<0 || soly<0)
            continue;
        res+=(solx*3+soly);   
    }
    std::cout<<"part-2 "<<res<<std::endl;
    return 0;
}