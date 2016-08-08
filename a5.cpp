

// #include lines
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <iterator>
#include <set>

// Answer to q1
// use std::swap to swap min and max if max < min
// return a random int between min and max, inclusive
int myRandom(int min, int max){
    if (max < min){
        std::swap<int>(max, min);
    }
    int diff = max - min;
    return ((std::rand() % (diff + 1)) + min);
}

// Answer to q2
class Random {
  public:
    int operator()(int min, int max){
        if (max < min){
            std::swap<int>(max, min);
        }
        int diff = max - min;
        return ((std::rand() % (diff + 1)) + min );
    }
};

// a few class definitions and functions

// get some info an vector contents
void print_vec(const std::vector<int>& vec){
    for(auto it = vec.begin(); it != vec.end(); it++){
        std::cout << *it << "  ";
    }
    std::cout << std::endl;
}

int main (){
    std::srand(53); // seed therandom number generator rand() in <cstdlib>

    // q 1 output
    std::cout << "myRandom(1, 49) returns: " << myRandom(1, 49) << std::endl;
    
    // call q2
    // std::srand(53); // should get the same as above
    Random luckyNumber;
    std::cout << "Random luckyNumber(1, 49) returns: " << luckyNumber(1, 49) << std::endl;

    // Answer to q3
    // std::srand(53); // should get the same as above
    auto randomLambda = [](int min, int max) {if(max < min) std::swap(min, max); return ((std::rand() % (max - min + 1)) + min);};
    std::cout << "randomLambda(1, 49) returns: " << randomLambda(1, 49) << std::endl;

    // Answer to q4
    std::vector<int> va(10);
    std::generate_n (va.begin(), 10, std::bind(myRandom, 1, 5)); 
    //print_vec(va);

    // Answer to q5
    std::vector<int> vb;
    std::copy(va.begin(), va.end(), std::back_inserter(vb));
    std::cout << "contents of vb after back inserter:" << std::endl;
    print_vec(vb);

    // Answer to q6
    std::copy(va.begin(), va.end(), std::inserter(vb, vb.begin()));
    std::cout << "contents of vb after inserter:" << std::endl;
    print_vec(vb);

    // Answer to q7
    std::set<int> sa(vb.begin(), vb.end());
    std::cout << "contents of sa after range constructn:" << std::endl;
    for(auto it = sa.begin(); it != sa.end(); it++){
        std::cout << *it << "   ";
    }
    std::cout << std::endl;

    // Answer to q8
    std::set<int,std::greater<int>> sb(vb.begin(), vb.end());
    std::cout << "contents of sb, descending order range construction:" << std::endl;
    for(auto it = sb.begin(); it != sb.end(); it++){
        std::cout << *it << "   ";
    }
    std::cout << std::endl;

    // Answer to q9
    std::multiset<int> msa(vb.begin(), vb.end());
    std::cout << "contents of msa after range constructn:" << std::endl;
    for(auto it = msa.begin(); it != msa.end(); it++){
        std::cout << *it << "   ";
    }
    std::cout << std::endl;

    // Answer to q10
    std::multiset<int,std::greater<int>> msb(vb.begin(), vb.end());
    std::cout << "contents of msb, descending order range construction:" << std::endl;
    for(auto it = msb.begin(); it != msb.end(); it++){
        std::cout << *it << "   ";
    }
    std::cout << std::endl;

    // Answer to q11
    std::multiset<int> msc;
    std::transform(msa.begin(), msa.end(), std::inserter(msc, msc.begin()), [](int a){return a*10;});
    std::cout << "contents of msc, after insertion with transform:" << std::endl;
    for(auto it = msc.begin(); it != msc.end(); it++){

        std::cout << *it << "  ";
    }
    std::cout << std::endl;

    // Answer to q12
    for (int i = 1; i <= 5; ++i){
        auto range = msc.equal_range(i*10);
        std::cout << "There are " << std::distance(range.first, range.second) 
                << " " << i*10 << "'s in msc." << std::endl;
    }

    // Answer to q13
    auto fifteen = msc.equal_range(15);
    auto thirtyFive = msc.equal_range(35); 
    std::cout << "The total sum of numbers between 15 and 35 is: " 
        << std::accumulate(fifteen.first, thirtyFive.first, 0) << std::endl;


    // Answer to q14

}
