class Solution {
public:
    int maxDistance(vector<int>& pos, int m) {
        int n = (int)pos.size();
        sort(pos.begin(), pos.end());
        int L = 1, R = pos.back() - pos.front();
        while(L < R) {
            int M = (L + R + 1) >> 1, idx = 0;
            for(int i = 1; i < m && idx < n; ++i)
                for(int las = pos[idx]; idx < n && pos[idx] - las < M; ++idx);
            if(idx == n) {
                R = M - 1;
            } else {
                L = M;
            }
        }
        return L;
    }
};
