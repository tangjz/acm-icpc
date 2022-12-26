class Bitset {
    int cnt;
    bool rev;
    vector<bool> vec;
public:
    Bitset(int size) {
        cnt = 0;
        rev = 0;
        vector<bool>(size).swap(vec);
    }

    void fix(int idx) {
        if(vec[idx] == rev) {
            ++cnt;
            vec[idx] = !rev;
        }
    }

    void unfix(int idx) {
        if(vec[idx] != rev) {
            --cnt;
            vec[idx] = rev;
        }
    }

    void flip() {
        rev = !rev;
        cnt = vec.size() - cnt;
    }

    bool all() {
        return cnt == vec.size();
    }

    bool one() {
        return cnt > 0;
    }

    int count() {
        return cnt;
    }

    string toString() {
        string ret = "";
        for(bool x: vec)
            ret.push_back("01"[x != rev]);
        return ret;
    }
};

/**
 * Your Bitset object will be instantiated and called as such:
 * Bitset* obj = new Bitset(size);
 * obj->fix(idx);
 * obj->unfix(idx);
 * obj->flip();
 * bool param_4 = obj->all();
 * bool param_5 = obj->one();
 * int param_6 = obj->count();
 * string param_7 = obj->toString();
 */
