class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int L = 1, R = *max_element(piles.begin(), piles.end());
        while(L < R) {
            int M = (L + R) >> 1;
            int rem = h;
            for(int x: piles) {
                rem -= (x - 1) / M + 1;
                if(rem < 0)
                    break;
            }
            if(rem < 0) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        return L;
    }
};
