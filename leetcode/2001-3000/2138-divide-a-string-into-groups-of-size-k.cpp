class Solution {
public:
    vector<string> divideString(string s, int k, char fill) {
        while(s.size() % k != 0)
            s.push_back(fill);
        vector<string> ret;
        for(int i = 0; i < s.size(); i += k)
            ret.push_back(s.substr(i, k));
        return ret;
    }
};
