class Solution {
    int R, C, M;
    unordered_map<int, int> perm;
    mt19937 rnd;
    int getID(int x) {
        auto it = perm.find(x);
        return it == perm.end() ? x : (it -> second);
    }
    void setID(int x, int y) {
        perm[x] = y;
    }
public:
    Solution(int n_rows, int n_cols) : R(n_rows), C(n_cols), M(n_rows * n_cols), perm({}), rnd(time(NULL)) {}
    
    vector<int> flip() {
        int pos = rnd() % (M--), u = getID(pos), v = getID(M);
        setID(pos, v);
        setID(M, u);
        return {u / C, u % C};
    }
    
    void reset() {
        M = R * C;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(n_rows, n_cols);
 * vector<int> param_1 = obj->flip();
 * obj->reset();
 */
