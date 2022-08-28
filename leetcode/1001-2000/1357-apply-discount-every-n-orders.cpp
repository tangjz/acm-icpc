class Cashier {
    int rem, mod, pct;
    unordered_map<int, int> Hash;
public:
    Cashier(int n, int discount, vector<int>& products, vector<int>& prices) {
        rem = 0;
        mod = n;
        pct = discount;
        int m = (int)products.size();
        for(int i = 0; i < m; ++i)
            Hash.insert({products[i], prices[i]});
    }
    
    double getBill(vector<int> product, vector<int> amount) {
        int ret = 0, m = (int)product.size();
        for(int i = 0; i < m; ++i)
            ret += Hash[product[i]] * amount[i];
        if((++rem) == mod) {
            rem = 0;
            return (double)ret * (100 - pct) / 100;
        }
        return ret;
    }
};

/**
 * Your Cashier object will be instantiated and called as such:
 * Cashier* obj = new Cashier(n, discount, products, prices);
 * double param_1 = obj->getBill(product,amount);
 */
