class Solution {
public:
    int maximumNumberOfStringPairs(vector<string>& A) {
        int n = A.size(), ans = 0;
        unordered_map<string, int> Hash;
        vector<pair<int, int> > idx(n);
        auto getID = [&](string &s) {
            return Hash.insert({s, (int)Hash.size()}).first -> second;
        };
        string t;
        for(int i = 0; i < n; ++i) {
            t = A[i];
            reverse(t.begin(), t.end());
            idx[i] = {getID(A[i]), getID(t)};
            for(int j = 0; j < i; ++j)
                ans += idx[i].first == idx[j].second;
        }
        return ans;
    }
};
