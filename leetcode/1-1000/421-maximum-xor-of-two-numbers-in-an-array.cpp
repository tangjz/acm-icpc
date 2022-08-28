class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int ans = 0, mx = 0;
        for(int x : nums)
            while((1LL << mx) <= x)
                ++mx;
        for(int i = mx - 1; i >= 0; --i) {
            unordered_set<int> sp;
            for(int x : nums)
                sp.insert(x >> i);
            ans = ans << 1 | 1;
            bool found = 0;
            for(int x : sp)
                if(sp.count(ans ^ x)) {
                    found = 1;
                    break;
                }
            if(!found)
                ans ^= 1;
        }
        return ans;
    }
};
