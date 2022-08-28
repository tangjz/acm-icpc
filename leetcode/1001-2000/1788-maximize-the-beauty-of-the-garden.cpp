class Solution {
public:
    int maximumBeauty(vector<int>& flowers) {
        int n = flowers.size();
        vector<int> psum = {0};
        for(int x: flowers)
            psum.push_back(psum.back() + max(x, 0));
        int ans = INT_MIN;
        unordered_map<int, int> Hash;
        for(int i = 0; i < n; ++i) {
            auto it = Hash.find(flowers[i]);
            if(it != Hash.end()) {
                ans = max(ans, flowers[i] * 2 + psum[i] - it -> second);
                it -> second = min(it -> second, psum[i + 1]);
            } else {
                Hash[flowers[i]] = psum[i + 1];
            }
        }
        return ans;
    }
};
