#include <ext/rope>
using namespace __gnu_cxx;
class Solution {
public:
    string evolutionaryRecord(vector<int>& par) {
        int n = par.size();
        vector<vector<rope<char> > > sub(n);
        for(int i = n - 1; i >= 0; --i) {
            sort(sub[i].begin(), sub[i].end());
            rope<char> cur = !i ? "" : "0";
            for(auto &it: sub[i])
                cur += it;
            if(!i) {
                while(!cur.empty() && cur.back() == '1')
                    cur.pop_back();
                return string(cur.begin(), cur.end());
            }
            sub[par[i]].push_back(cur + "1");
        }
        return "";
    }
};
