class Solution {
public:
    double calculateEntropy(vector<int>& input) {
        int n = input.size();
        if(!n)
            return 0;
        unordered_map<int, int> ctr;
        for(int x: input)
            ++ctr[x];
        double ret = 0;
        for(auto &it: ctr) {
            int cnt = it.second;
            ret += cnt * log2(cnt);
        }
        ret = log2(n) - ret / n;
        return max(ret, 0.0);
    }
};
