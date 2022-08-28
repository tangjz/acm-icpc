class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        unordered_set<string> Hash;
        int n = word.size();
        for(int i = 0; i < n; ++i)
            for(int j = i; j < n; ++j)
                Hash.insert(word.substr(i, j - i + 1));
        int ans = 0;
        for(auto &it: patterns)
            ans += Hash.count(it);
        return ans;
    }
};
