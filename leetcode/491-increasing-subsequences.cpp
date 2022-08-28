class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        int n = nums.size();
        vector<map<int, int> > seq(n);
        for(int i = n - 1; i >= 0; --i) {
            if(i + 1 < n)
                seq[i] = seq[i + 1];
            seq[i][nums[i]] = i;
        }
        vector<vector<int> > sol;
        vector<int> path;
        function<void(int)> gen = [&](int pos) {
            if(path.size() >= 2)
                sol.push_back(path);
            if(pos == n)
                return;
            for(auto it = path.empty() ? seq[pos].begin() : seq[pos].lower_bound(path.back()); it != seq[pos].end(); ++it) {
                path.push_back(nums[it -> second]);
                gen(it -> second + 1);
                path.pop_back();
            }
        };
        gen(0);
        return sol;
    }
};
