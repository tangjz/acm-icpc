class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        sort(strs.begin(), strs.end(), [&](string const &u, string const &v) {
            return u.size() > v.size();
        });
        for(auto &it: strs) {
            int n = it.size();
            bool ban = 0, skp = 0;
            for(auto &jt: strs) {
                if(it == jt) {
                    if(!skp) {
                        skp = 1;
                        continue;
                    }
                    ban = 1;
                    break;
                }
                if(jt.size() < n)
                    break;
                int p = 0;
                for(char ch: jt)
                    if(ch == it[p] && (++p) == n)
                        break;
                if(p == n) {
                    ban = 1;
                    break;
                }
            }
            if(!ban)
                return n;
        }
        return -1;
    }
};
