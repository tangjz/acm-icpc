class ATM {
    static constexpr int maxd = 5, cost[maxd] = {20, 50, 100, 200, 500};
    long long ctr[maxd];
public:
    ATM() {
        memset(ctr, 0, sizeof(ctr));
    }

    void deposit(vector<int> banknotesCount) {
        for(int i = 0; i < maxd; ++i)
            ctr[i] += banknotesCount[i];
    }

    vector<int> withdraw(int amount) {
        vector<int> ret(maxd);
        for(int i = maxd - 1; i >= 0; --i) {
            ret[i] = min((long long)amount / cost[i], ctr[i]);
            amount -= ret[i] * cost[i];
        }
        if(amount > 0)
            return {-1};
        for(int i = 0; i < maxd; ++i)
            ctr[i] -= ret[i];
        return ret;
    }
};

/**
 * Your ATM object will be instantiated and called as such:
 * ATM* obj = new ATM();
 * obj->deposit(banknotesCount);
 * vector<int> param_2 = obj->withdraw(amount);
 */
