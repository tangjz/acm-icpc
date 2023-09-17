class Solution {
public:
    string minimumString(string a, string b, string c) {
        vector<string> vec = {a, b, c};
        sort(vec.begin(), vec.end(), [&](string const &u, string const &v) {
            return u.size() > v.size();
        });
        for(int i = 0; i < (int)vec.size(); ++i)
            for(int j = i + 1; j < (int)vec.size(); ++j)
                if(vec[i].find(vec[j]) != string::npos) {
                    vec.erase(vec.begin() + j, vec.begin() + j + 1);
                    --j;
                }
        string ans, tmp;
        sort(vec.begin(), vec.end());
        do {
            tmp = "";
            for(auto &s: vec) {
                int i = min(tmp.size(), s.size()), m = tmp.size();
                for( ; i > 0; --i) {
                    bool chk = 1;
                    for(int j = 0; chk && j < i; ++j)
                        chk &= tmp[m - i + j] == s[j];
                    if(chk)
                        break;
                }
                tmp += s.substr(i);
            }
            if(!ans.size() || ans.size() > tmp.size() || (ans.size() == tmp.size() && ans > tmp))
                ans = tmp;
        } while(next_permutation(vec.begin(), vec.end()));
        return ans;
    }
};
