class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations) {
        int ans = 0;
        for(auto &it: operations)
            ans += it[1] == '+' ? 1 : -1;
        return ans;
    }
};
