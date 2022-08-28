class Solution {
public:
    vector<int> masterMind(string solution, string guess) {
        int n = solution.size(), cnt0 = 0, cnt1 = 0;
        unordered_map<char, int> ctr0, ctr1;
        for(int i = 0; i < n; ++i) {
            cnt0 += solution[i] == guess[i];
            ++ctr0[solution[i]];
            ++ctr1[guess[i]];
        }
        for(auto &it: ctr0) {
            auto jt = ctr1.find(it.first);
            if(jt != ctr1.end())
                cnt1 += min(it.second, jt -> second);
        }
        return {cnt0, cnt1 - cnt0};
    }
};
