class StockSpanner {
    static const int maxn = (int)1e4 + 1;
    int n, m;
    pair<int, int> stk[maxn];
public:
    StockSpanner() {
        n = m = 0;
        stk[n++] = make_pair(INT_MAX, -1);
    }

    int next(int price) {
        for( ; stk[n - 1].first <= price; --n);
        int ans = m - stk[n - 1].second;
        stk[n++] = make_pair(price, m++);
        return ans;
    }
};

static auto fastio = [](){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
