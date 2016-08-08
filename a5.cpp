

// #include lines
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

// Answer to q1
// use std::swap to swap min and max if max < min
// return a random int between min and max, inclusive
int random(int min, int max){
    if (max < min){
        std::swap<int>(max, min);
    }
    int diff = max - min;
    return ((std::rand() % (diff + 1)) + min );
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
//
//
//
int main (){
    std::srand(53); // seed therandom number generator rand() in <cstdlib>

    // q 1 output
    std::cout << "random(1, 49) returns: " << random(1, 49) << std::endl;
    
    // call q2
    // std::srand(53); // should get the same as above
    Random luckyNumber;
    std::cout << "Random luckyNumber(1, 49) returns: " << luckyNumber(1, 49) << std::endl;

    // Answer to q3
    // std::srand(53); // should get the same as above
    auto randomLambda = [](int min, int max) {if(max < min) std::swap(min, max); return ((std::rand() % (max - min + 1)) + min);};
    std::cout << "randomLambda(1, 49) returns: " << randomLambda(1, 49) << std::endl;

    //Answer to q4
    std::vector<int> va;
    std::generate_n (va.begin(), 10, std::bind(&random, 1, 5)());
    //    generate_n (myarray, 9, UniqueNumber);
    // ...
    //
}
