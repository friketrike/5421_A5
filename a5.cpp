// Concordia Comp 5421 Summer 2016
// Assignment 5 for Federico O'Reilly 40012304
// Unfortunately ran out of time...

// #include lines
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <iterator>
#include <set>

using namespace std;

//Container print
template <class Container>
void print(const Container & c, const string & message ="")
{
    if(!message.empty()) cout << message << " : ";
    using valType = decltype(*c.begin());
    ostream_iterator<valType> osItr(cout, " ");
    copy(c.begin(), c.end(), osItr);
    cout << endl;
}

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

// is empty, pair finish, false
// all equal pair start, false
// at least two distinct, pair iter, true
template < class Iterator >
std::pair <Iterator, bool> secondMax ( Iterator start , Iterator finish )
{
     
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

    // Answer to q5
    std::vector<int> vb;
    std::copy(va.begin(), va.end(), std::back_inserter(vb));
    print(vb);

    // Answer to q6
    std::copy(va.begin(), va.end(), std::inserter(vb, vb.begin()));
    print(vb);

    // Answer to q7
    std::set<int> sa(vb.begin(), vb.end());
    print(sa);

    // Answer to q8
    std::set<int,std::greater<int>> sb(vb.begin(), vb.end());
    print(sb);

    // Answer to q9
    std::multiset<int> msa(vb.begin(), vb.end());
    print(msa);

    // Answer to q10
    std::multiset<int,std::greater<int>> msb(vb.begin(), vb.end());
    print(msb);

    // Answer to q11
    std::multiset<int> msc;
    std::transform(msa.begin(), msa.end(), std::inserter(msc, msc.begin()), [](int a){return a*10;});
    print(msc);

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
    std::cout << "There are "<< std::count_if(vb.begin(), vb.end(), [](int a){return ((a % 2) == 0);})
            << " even elements in vb." << std::endl;

    // Answer t o Q15
    vector < int > int_vec {54 , 67 , 2 , 45 , 12 , 70};
    print ( int_vec , " int_vec " );
    //auto max2_int_vec = secondMax ( int_vec . begin () , int_vec . end ());
    //cout << " The second largest element in int_vec is "
    //<< * max2_int_vec << endl ;
}
