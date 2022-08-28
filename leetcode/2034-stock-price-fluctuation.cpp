class StockPrice {
    multiset<int> sp;
    map<int, int> hs;
public:
    StockPrice() {
        sp.clear();
        hs.clear();
    }
    
    void update(int ts, int pr) {
        auto it = hs.find(ts);
        if(it != hs.end()) {
            sp.erase(sp.find(it -> second));
        }
        hs[ts] = pr;
        sp.insert(pr);
    }
    
    int current() {
        return hs.rbegin() -> second;
    }
    
    int maximum() {
        return *sp.rbegin();
    }
    
    int minimum() {
        return *sp.begin();
    }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */
