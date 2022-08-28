class Solution {
    int calc(string const &s) {
        int cnt = 0;
        char best = s.front();
        for(char ch: s) {
            if(ch < best) {
                best = ch;
                cnt = 0;
            }
            cnt += best == ch;
        }
        return cnt;
    }
public:
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        vector<int> ctr;
        for(auto &it: words) {
            int v = calc(it);
            if(v >= ctr.size())
                ctr.resize(v + 1);
            ++ctr[v];
        }
        for(int i = ctr.size() - 2; i >= 0; --i)
            ctr[i] += ctr[i + 1];
        vector<int> ret;
        for(auto &it: queries) {
            int v = calc(it);
            ret.push_back(v + 1 < ctr.size() ? ctr[v + 1] : 0);
        }
        return ret;
    }
};
