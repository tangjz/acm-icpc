class Solution {
public:
    int maxSum(vector<int>& nums) {
        int ans = -1;
        unordered_map<char, int> las;
        for(int x: nums) {
            string s = to_string(x);
            char upp = *max_element(s.begin(), s.end());
            auto it = las.find(upp);
            if(it != las.end()) {
                ans = max(ans, x + it -> second);
                it -> second = max(it -> second, x);
            } else {
                las.insert({upp, x});
            }
        }
        return ans;
    }
};
