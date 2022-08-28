class Solution {
public:
    vector<int> findBuildings(vector<int>& heights) {
        int n = heights.size(), upp = 0;
        vector<int> ret;
        for(int i = n - 1; i >= 0; --i)
            if(upp < heights[i]) {
                upp = heights[i];
                ret.push_back(i);
            }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
