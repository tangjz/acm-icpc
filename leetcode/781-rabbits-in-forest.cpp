class Solution {
public:
    int numRabbits(vector<int>& answers) {
        unordered_map<int, int> ctr;
        for(int x: answers)
            ++ctr[x];
        int ans = 0;
        for(auto &it: ctr) {
            int m = it.first + 1;
            int q = (it.second - 1) / m + 1;
            ans += m * q;
        }
        return ans;
    }
};
