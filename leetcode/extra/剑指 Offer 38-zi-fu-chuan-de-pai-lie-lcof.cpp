class Solution {
public:
    vector<string> permutation(string s) {
        vector<string> ret;
        sort(s.begin(), s.end());
        do {
            ret.push_back(s);
        } while(next_permutation(s.begin(), s.end()));
        return ret;
    }
};
