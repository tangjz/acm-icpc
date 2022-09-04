class Solution {
public:
    int countWords(vector<string>& words1, vector<string>& words2) {
        auto getOnce = [&](vector<string> const &words) -> vector<string> {
            unordered_map<string, int> ctr;
            for(auto &item: words)
                ++ctr[item];
            vector<string> ret;
            for(auto &it: ctr)
                if(it.second == 1)
                    ret.push_back(it.first);
            return ret;
        };
        unordered_map<string, int> msk;
        for(auto &item: getOnce(words1))
            msk[item] |= 1;
        for(auto &item: getOnce(words2))
            msk[item] |= 2;
        int ret = 0;
        for(auto &it: msk)
            if(it.second == 3)
                ++ret;
        return ret;
    }
};
