class Fancy {
    typedef long long LL;
    static const int mod = (int)1e9 + 7;
    int k, b, ik;
    vector<int> seq, inv;
public:
    Fancy() {
        k = ik = 1;
        b = 0;
        seq = {};
        inv = {0, 1};
    }
    
    void append(int val) {
        val = (val - b + mod) * (LL)ik % mod;
        seq.push_back(val);
    }
    
    void addAll(int inc) {
        (b += inc) >= mod && (b -= mod);
    }
    
    void multAll(int m) {
        for(int i = inv.size(); i <= m; ++i)
            inv.push_back(mod - (int)(mod / i * (LL)inv[mod % i] % mod));
        k = (LL)k * m % mod;
        ik = (LL)ik * inv[m] % mod;
        b = (LL)b * m % mod;
    }
    
    int getIndex(int idx) {
        return idx < seq.size() ? ((LL)k * seq[idx] + b) % mod : -1;
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */
