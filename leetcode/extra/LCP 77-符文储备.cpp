class Solution {
public:
    int runeReserve(vector<int>& runes) {
        int ans = 0;
        unordered_map<int, int> ctr;
        for(int x: runes)
            ++ctr[x];
        for(auto &it: ctr) {
            auto jt = ctr.find(it.first - 1);
            if(jt != ctr.end())
                continue;
            int tmp = it.second, val = it.first + 1;
            for( ; (jt = ctr.find(val)) != ctr.end(); ++val)
                tmp += jt -> second;
            ans = max(ans, tmp);
        }
        return ans;
    }
};
