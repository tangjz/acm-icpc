class Solution {
public:
    int minimumSeconds(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> las, upp;
        for(int i = 0; i < n; ++i)
            las[nums[i]] = i - n;
        for(int i = 0; i < n; ++i) {
            int v = nums[i];
            upp[v] = max(upp[v], i - las[v]);
            las[v] = i;
        }
        int ans = upp.begin() -> second;
        for(auto &it: upp)
            ans = min(ans, it.second);
        return ans / 2;
    }
};
