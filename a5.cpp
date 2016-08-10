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
#include <cctype>
#include <map>
#include <iomanip>
#include <sstream>

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
    using valType = decltype(*start);
    //using itType = decltype(start);
    std::greater<valType> gv;
    std::not_equal_to<valType> nev;
    std::less<valType> lv;
    Iterator ref{start};
    Iterator max{start};
    Iterator second{start};
    for(ref; ref!= finish; ++ref) {
        max = (gv(*ref, *max)) ? ref : max;
        second = (lv(*ref, *second)) ? ref : second;
    }    
    for(ref = start; ref != finish; ref++) {
        second = (gv(*ref, *second) && *ref != *max) ? ref : second;
    }
    return std::pair<Iterator, bool>(second, (second != max));
}

// Answer to Q16
bool IsPalindrome(const string & phrase) {
    string temp;

    // std::remove copy_if - copy only alphabet chars
    //      temp is empty, need an inserter
    std::copy_if(phrase.begin(), phrase.end(), 
            std::inserter(temp, temp.begin()), 
            [](char c){return std::isalpha(c);});
    // std::transform to convert all chars to lowercase
    std::transform(temp.begin(), temp.end(), temp.begin(), 
            [](char c){return std::tolower(c);});
    // std::equal to compare first half to second half
    //         1.begin() / 2.rbegin()
    bool isPalindrome = true;
    // return what std::equal returns
    return std::equal(temp.begin(), temp.end(), temp.rbegin());
}

// Assignment-supplied function:
void wordFreq() {
    std::map<string, int> wordFreqMap;
    std::string word;
    while(std::cin >> word) {
        ++wordFreqMap[word];
    }
    for (auto it = wordFreqMap.begin();
              it != wordFreqMap.end(); ++it) {
        std::cout << std::setw(5) << it->second << ": "
                             << it->first << std:: endl;
    }
}

// Answer to Q17
void wordIndex() {
    std::map<string, vector<int>> wordLineMap;
    std::string line;
    int line_no = 1;
    while(std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string word;
        while(ss >> word) {    
            wordLineMap[word].push_back(line_no);
        }
        ++line_no;
    }
    for (auto it = wordLineMap.begin();
              it != wordLineMap.end(); ++it) {
        std::cout << std::setw(10) << it->first << ": ";
        for (auto it_v = it->second.begin(); it_v != it->second.end(); ++it_v) {
            std::cout << std::setw(4) << *it_v; 
        }
        std::cout << std:: endl;
    }

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
    //vector < int > int_vec;
    //vector <int> int_vec {2};
    //vecotr <int< int_vec {2, 2};
    print ( int_vec , " int_vec " );
    auto max2_int_vec = secondMax ( int_vec . begin () , int_vec . end ());
    if (max2_int_vec.second) {
        cout << " The second largest element in int_vec is "
        << * max2_int_vec.first << endl ;
    } else if (max2_int_vec.first == int_vec.end()) {
        cout << " The vector is empty!" << endl;
    } else {
        cout << " The vector only contains repeated instances of the same value" << endl;
    }
    
    // Calling answer to Q16
    string str_cat = string("Was it a car or a cat I saw?");
    string str_kat = string("Was it a car or a kat I saw?");
    bool is_str_cat = IsPalindrome( str_cat );
    bool is_str_kat = IsPalindrome( str_kat );
    cout << "the phrase \"" + str_cat + "\" is " +
        (is_str_cat ? "" : "not ") + "a palindrome\n";
    cout << "the phrase \"" + str_kat + "\" is " +
        (is_str_kat ? "" : "not ") + "a palindrome\n";
    
    // Calling answer to Q17
    wordIndex();
}
