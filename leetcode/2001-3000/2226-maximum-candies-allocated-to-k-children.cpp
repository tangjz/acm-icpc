class Solution {
public:
    int maximumCandies(vector<int>& candies, long long k) {
        int L = 0, R = (int)1e7;
        while(L < R) {
            int M = (L + R + 1) >> 1;
            long long ctr = 0;
            for(int x: candies)
                ctr += x / M;
            if(ctr >= k) {
                L = M;
            } else {
                R = M - 1;
            }
        }
        return L;
    }
};
