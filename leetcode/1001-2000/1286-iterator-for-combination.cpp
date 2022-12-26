class CombinationIterator {
    string buf;
    int tot, cnt, pos;
    vector<int> cur;
public:
    CombinationIterator(string characters, int combinationLength) {
        buf = move(characters);
        tot = buf.size();
        cnt = combinationLength;
        cur.resize(cnt);
        iota(cur.begin(), cur.end(), 0);
        pos = 0;
    }

    string next() {
        string ret = "";
        for(int x : cur)
            ret += buf[x];
        for(pos = cnt - 1; pos >= 0 && cur[pos] == tot - cnt + pos; --pos);
        if(pos >= 0) {
            ++cur[pos];
            for(int i = pos + 1; i < cnt; ++i)
                cur[i] = cur[i - 1] + 1;
        }
        return ret;
    }

    bool hasNext() {
        return pos >= 0;
    }
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
