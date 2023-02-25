class Solution {
public:
    vector<int> vowelStrings(vector<string>& A, vector<vector<int>>& Q) {
        unordered_set<char> vis = {'a', 'e', 'i', 'o', 'u'};
        int n = A.size();
        vector<int> psum = {0};
        for(auto &it: A) {
            bool ok = vis.count(it.front()) && vis.count(it.back());
            psum.push_back(psum.back() + ok);
        }
        vector<int> ans;
        for(auto &it: Q) {
            ans.push_back(psum[it[1] + 1] - psum[it[0]]);
        }
        return ans;
    }
};
