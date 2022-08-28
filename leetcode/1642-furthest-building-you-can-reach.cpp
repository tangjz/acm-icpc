class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int n = heights.size();
        vector<pair<int, int> > cost;
        for(int i = 1; i < n; ++i) {
            int dt = heights[i] - heights[i - 1];
            if(dt > 0)
                cost.push_back({dt, i});
        }
        sort(cost.begin(), cost.end());
        reverse(cost.begin(), cost.end());
        int L = 0, R = n - 1;
        while(L < R) {
            int M = (L + R + 1) >> 1;
            int rem = ladders;
            long long sum = 0;
            for(auto &it: cost) {
                if(it.second > M)
                    continue;
                if(rem > 0) {
                    --rem;
                    continue;
                }
                sum += it.first;
            }
            if(sum <= bricks) {
                L = M;
            } else {
                R = M - 1;
            }
        }
        return L;
    }
};
