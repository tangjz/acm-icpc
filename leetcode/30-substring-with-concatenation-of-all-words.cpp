class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = s.size(), m = words[0].size(), q = words.size();
        if(m * q > n)
            return {};
        vector<int> idx(n);
        unordered_map<string, int> Hash;
        for(auto &it: words)
            Hash.insert({it, Hash.size()});
        for(int i = 0; i <= n - m; ++i)
            idx[i] = Hash.insert({s.substr(i, m), Hash.size()}).first -> second;
        int tot = Hash.size();
        vector<int> ctr(tot), upp(tot), ret;
        for(auto &it: words)
            ++upp[Hash[it]];
        for(int i = 0; i < m && i <= n - m; ++i) {
            int sta = n - m - i, j, k, c;
            sta = sta - sta % m + i;
            for(j = sta, k = j, c = 0; j >= 0; j -= m) {
                for(++c, ++ctr[idx[j]]; ctr[idx[j]] > upp[idx[j]]; --c, --ctr[idx[k]], k -= m);
                if(c == q)
                    ret.push_back(j);
            }
            for( ; c > 0; --c, --ctr[idx[k]], k -= m);
        }
        return ret;
    }
};
