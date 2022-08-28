class Solution {
public:
    int numSpecialEquivGroups(vector<string>& words) {
        unordered_set<string> ret;
        for(auto &it: words) {
            string odd, even;
            for(int i = 0; i < (int)it.size(); ++i)
                (i & 1 ? odd : even).push_back(it[i]);
            sort(odd.begin(), odd.end());
            sort(even.begin(), even.end());
            for(int i = 0; i < (int)it.size(); ++i)
                it[i] = (i & 1 ? odd : even)[i >> 1];
            ret.insert(it);
        }
        return ret.size();
    }
};
