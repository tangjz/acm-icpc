class Solution {
public:
    int nextGreaterElement(int n) {
        string a = to_string(n);
        if(!next_permutation(a.begin(), a.end()))
            return -1;
        long long x = stol(a);
        return x > INT_MAX ? -1 : x;
    }
};
