class Solution {
public:
    int mostFrequent(vector<int>& nums, int key) {
        int ans = 0, las = 0;
        unordered_map<int, int> ctr;
        for(int x: nums) {
            if(las == key)
                ++ctr[x];
            las = x;
        }
        int best = 0;
        for(auto &it: ctr)
            if(it.second > best) {
                best = it.second;
                ans = it.first;
            }
        return ans;
    }
};
