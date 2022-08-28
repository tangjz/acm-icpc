class Solution {
    vector<int> check(int dt, vector<int> &seq) {
        int n = seq.size();
        vector<bool> vis(n);
        vector<int> ret;
        // printf("check %d\n", dt);
        for(int i = 0, j = 0; i < n; ++i) {
            if(vis[i])
                continue;
            vis[i] = 1;
            for( ; j < n && (vis[j] || seq[j] < seq[i] + dt); ++j);
            if(j < n && seq[j] == seq[i] + dt) {
                vis[j] = 1;
                ret.push_back(seq[i]);
                // printf("match %d %d\n", seq[i], seq[j]);
            } else {
                // printf("mismatch %d: %d\n", seq[i], seq[i] + dt);
                return {};
            }
        }
        return ret;
    }
public:
    vector<int> recoverArray(vector<int>& nums) {
        int n = nums.size() >> 1;
        sort(nums.begin(), nums.end());
        for(int i = 1; i < n + n; ++i) {
            int dt = nums[i] - nums[0];
            if(!dt || (dt & 1))
                continue;
            dt >>= 1;
            vector<int> res = check(dt << 1, nums);
            if(res.empty())
                continue;
            for(int &x: res)
                x += dt;
            return res;
        }
        return {};
    }
};
