class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int ans = 0, cur = 0;
        for(int x: gain) {
            ans = max(ans, cur += x);
        }
        return ans;
    }
};
