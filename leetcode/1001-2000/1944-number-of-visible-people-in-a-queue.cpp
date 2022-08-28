class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        int n = heights.size();
        vector<int> pL(n), pR(n), ret(n);
        for(int i = 0; i < n; ++i) {
            pL[i] = i - 1;
            for( ; pL[i] >= 0 && heights[pL[i]] <= heights[i]; pL[i] = pL[pL[i]]);
            if(pL[i] >= 0)
                ++ret[pL[i]];
        }
        for(int i = n - 1; i >= 0; --i) {
            pR[i] = i + 1;
            for( ; pR[i] < n && heights[pR[i]] <= heights[i]; pR[i] = pR[pR[i]]);
            if(pR[i] < n)
                ++ret[i];
        }
        return ret;
    }
};
