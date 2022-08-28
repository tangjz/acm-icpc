class Solution {
public:
    int maximizeSweetness(vector<int>& sweetness, int k) {
        int L = 0, R = (int)1e9;
        while(L < R) {
            int M = (L + R + 1) >> 1;
            int cnt = 0, rem = 0;
            for(int x: sweetness) {
                rem += x;
                if(rem >= M) {
                    ++cnt;
                    rem = 0;
                }
            }
            if(cnt >= k + 1) {
                L = M;
            } else {
                R = M - 1;
            }
        }
        return L;
    }
};
