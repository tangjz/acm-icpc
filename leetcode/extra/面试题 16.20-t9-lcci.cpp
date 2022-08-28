class Solution {
public:
    vector<string> getValidT9Words(string num, vector<string>& words) {
        int n = num.size();
        vector<pair<char, char> > seg(n);
        for(int i = 0; i < n; ++i) {
            int d = num[i] - '2';
            int L = d * 3 + (d > 5);
            int R = (d + 1) * 3 - 1 + (d >= 5) + (d >= 7);
            seg[i] = {'a' + L, 'a' + R};
        }
        vector<string> ret;
        for(auto &it: words) {
            bool ban = 0;
            for(int i = 0; !ban && i < n; ++i)
                ban |= it[i] < seg[i].first || it[i] > seg[i].second;
            if(!ban)
                ret.push_back(it);
        }
        return ret;
    }
};
