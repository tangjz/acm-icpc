class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        vector<int> pos;
        for(int i = 0; i < n; ++i)
            if(s[i] == '1')
                pos.push_back(i);
        if(pos.size() < k)
            return "";
        int len = n + 1;
        string ret = "2";
        for(int i = pos.size() - k; i >= 0; --i) {
            int L = pos[i];
            int R = pos[i + k - 1];
            string tmp = s.substr(L, R - L + 1);
            if(R - L + 1 < len || R - L + 1 == len && ret > tmp) {
                ret = tmp;
                len = R - L + 1;
            }
        }
        return ret;
    }
};
