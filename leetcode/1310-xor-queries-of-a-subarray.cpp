class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& que) {
        int n = (int)arr.size();
        for(int i = 1; i < n; ++i)
            arr[i] ^= arr[i - 1];
        vector<int> ret;
        for(auto &it : que) {
            ret.push_back(arr[it[1]] ^ (it[0] ? arr[it[0] - 1] : 0));
        }
        return ret;
    }
};
