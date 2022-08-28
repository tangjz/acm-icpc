class Bank {
    typedef long long LL;
    int n;
    vector<LL> seq;
public:
    Bank(vector<long long>& balance) {
        n = balance.size();
        seq = move(balance);
    }
    
    bool isValid(int account) {
        return 0 <= account && account < n;
    }
    
    bool transfer(int account1, int account2, long long money) {
        if(!isValid(--account1) || !isValid(--account2))
            return false;
        if(seq[account1] < money)
            return false;
        seq[account1] -= money;
        seq[account2] += money;
        return true;
    }
    
    bool deposit(int account, long long money) {
        if(!isValid(--account))
            return false;
        seq[account] += money;
        return true;
    }
    
    bool withdraw(int account, long long money) {
        if(!isValid(--account))
            return false;
        if(seq[account] < money)
            return false;
        seq[account] -= money;
        return true;
    }
};

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */
