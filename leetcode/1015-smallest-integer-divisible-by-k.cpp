class Solution {
public:
    int smallestRepunitDivByK(int k) {
        for(int i = 1, v = 0; i <= k; ++i) {
            v = (v * 10 + 1) % k;
            if(v == 0)
                return i;
        }
        return -1;
    }
};
