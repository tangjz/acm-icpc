class Solution {
public:
    int addRungs(vector<int>& rungs, int dist) {
        int las = 0, ans = 0;
        for(int x: rungs) {
            int diff = x - las;
            if(diff > dist) {
                ans += (diff - 1) / dist;
            }
            las = x;
        }
        return ans;
    }
};
