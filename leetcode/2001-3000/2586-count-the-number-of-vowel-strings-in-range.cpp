class Solution {
public:
    int vowelStrings(vector<string>& words, int left, int right) {
        unordered_set<char> sp = {'a', 'e', 'i','o', 'u'};
        int ans = 0;
        for(int i = left; i <= right; ++i)
            ans += sp.count(words[i].front()) && sp.count(words[i].back());
        return ans;
    }
};
