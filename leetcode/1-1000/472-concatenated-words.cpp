class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        int n = words.size();
        vector<unordered_set<string> > Hash;
        for(auto &it: words) {
            int m = it.size();
            if(m >= Hash.size())
                Hash.resize(m + 1);
            Hash[m].insert(it);
        }
        vector<string> ret;
        for(auto &vec: Hash)
            for(auto &buf: vec) {
                int m = buf.size(), msk = 1;
                if(!m)
                    continue;
                for(int i = 0; i < m; ++i) {
                    if(!((msk >> i) & 1))
                        continue;
                    string cur = "";
                    for(int j = i; j < m - !i; ++j) {
                        cur.push_back(buf[j]);
                        if(Hash[j - i + 1].count(cur))
                            msk |= 1 << (j + 1);
                    }
                }
                // printf("%s: %d %d\n", buf.c_str(), m, msk);
                if((msk >> m) & 1)
                    ret.push_back(buf);
            }
        return ret;
    }
};
