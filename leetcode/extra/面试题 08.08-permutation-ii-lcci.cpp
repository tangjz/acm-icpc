class Solution {
public:
    vector<string> permutation(string S) {
        vector<string> ret;
        sort(S.begin(), S.end());
        do ret.push_back(S); while(next_permutation(S.begin(), S.end()));
        return ret;
    }
};
