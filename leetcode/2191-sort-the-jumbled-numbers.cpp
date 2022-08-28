class Solution {
public:
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
        const int maxd = 10;
        int n = nums.size();
        vector<int> vals(n), ord(n);
        for(int i = 0; i < n; ++i) {
            ord[i] = i;
            vector<int> dig;
            for(int x = nums[i]; x > 0; x /= 10)
                dig.push_back(mapping[x % 10]);
            if(!nums[i])
                dig.push_back(mapping[0]);
            reverse(dig.begin(), dig.end());
            for(int x: dig)
                vals[i] = vals[i] * 10 + x;
        }
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return make_pair(vals[u], u) < make_pair(vals[v], v);
        });
        for(int i = 0; i < n; ++i)
            vals[i] = nums[ord[i]];
        return vals;
    }
};
