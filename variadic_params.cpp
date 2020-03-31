// https://openhome.cc/Gossip/CppGossip/VariadicTemplate.html?fbclid=IwAR2RdUMOTVmPJ70zZUtkKlM3i8DWsKGQSgnm_egoIyGM6vr2sXfpxIghiC4
#include <iostream> 
#include <vector> 

using namespace std; 

template <typename T, typename ...Ts>
T sum(T first, Ts... rest) {
    vector<T> nums = {rest...};
    T r = first;
    for(auto n : nums) {
        r += n;
    }
    return r;
}

int main() {
#ifdef MANY
    /*
      since template will generate multiple implementations for sum,
      the binary size will grow larger if there is only one implementation.
    */ 
    cout << sum(1, 2) << endl;
    cout << sum(1, 2, 3) << endl;
    cout << sum(1, 2, 3, 4) << endl;
    cout << sum(1, 2, 3, 4, 5) << endl;
    cout << sum(1, 2, 3, 4, 5, 6) << endl;
#else
    cout << sum(1, 2, 3) << endl;
#endif
    return 0; 
} 
