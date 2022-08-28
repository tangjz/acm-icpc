class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int L = *max_element(weights.begin(), weights.end()), R = (int)3e7, n = weights.size();
        while(L < R) {
            int M = (L + R) >> 1;
            int cnt = 0;
            for(int i = 0, j = 0; i < n; i = j, ++cnt) {
                int s = 0;
                for( ; j < n && (s += weights[j]) <= M; ++j);
            }
            // printf("%d: %d\n", M, cnt);
            if(cnt <= days) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
