class WordDistance {
    unordered_map<string, int> idx;
    unordered_map<int, vector<int> > pos;
    unordered_map<int, unordered_map<int, int> > Hash;

    int getID(string const &s) {
        auto it = idx.find(s);
        if(it != idx.end())
            return it -> second;
        int tot = idx.size();
        idx.insert({s, tot});
        return tot;
    }
public:
    WordDistance(vector<string>& wordsDict) {
        int n = wordsDict.size();
        idx.clear();
        pos.clear();
        Hash.clear();
        vector<int> seq;
        seq.reserve(n);
        for(int i = 0; i < n; ++i) {
            seq.push_back(getID(wordsDict[i]));
            pos[seq.back()].push_back(i);
        }
        int m = sqrtl(max(n + n, 1));
        for(auto &it: pos) {
            auto &vec = it.second;
            int sz = vec.size();
            if(sz <= m)
                continue;
            unordered_map<int, int> res;
            for(int i = 0; i < vec.front(); ++i) {
                auto it = res.find(seq[i]);
                if(it != res.end())
                    it -> second = min(it -> second, vec.front() - i);
            }
            for(int i = n - 1; i > vec.back(); --i) {
                auto it = res.find(seq[i]);
                if(it != res.end())
                    it -> second = min(it -> second, vec.front() - i);
            }
            for(int i = 1; i < sz; ++i)
                for(int j = vec[i - 1] + 1; j < vec[i]; ++j) {
                    auto it = res.find(seq[j]);
                    if(it != res.end())
                        it -> second = min(it -> second, min(j - vec[i - 1], vec[i] - j));
                }
            Hash[it.first] = move(res);
        }
    }

    int shortest(string word1, string word2) {
        int u = getID(word1), v = getID(word2);
        if(pos[u].size() < pos[v].size())
            swap(u, v);
        auto iter = Hash.find(u);
        if(iter != Hash.end())
            return (iter -> second)[v];
        int ans = INT_MAX;
        auto &A = pos[u], &B = pos[v];
        auto it = A.begin(), jt = B.begin();
        int lasA = -1, lasB = -1;
        while(it != A.end() || jt != B.end())
            if(jt == B.end() || (it != A.end() && *it < *jt)) {
                if(lasB != -1)
                    ans = min(ans, *it - lasB);
                lasA = *(it++);
            } else {
                if(lasA != -1)
                    ans = min(ans, *jt - lasA);
                lasB = *(jt++);
            }
        return ans;
    }
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance* obj = new WordDistance(wordsDict);
 * int param_1 = obj->shortest(word1,word2);
 */
