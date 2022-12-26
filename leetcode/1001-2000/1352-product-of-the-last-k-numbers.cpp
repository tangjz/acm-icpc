class ProductOfNumbers {
    int tot, las;
    vector<pair<int, int> > que;
public:
    ProductOfNumbers() {
        tot = 0;
        las = -1;
        vector<pair<int, int> >().swap(que);
    }

    void add(int num) {
        if(!num) {
            las = tot;
        } else if(num > 1) {
            que.push_back({tot, num});
        }
        ++tot;
    }

    int getProduct(int k) {
        int low = tot - k;
        if(las >= low)
            return 0;
        int ret = 1;
        for(auto it = que.rbegin(); it != que.rend(); ++it)
            if(it -> first >= low)
                ret *= it -> second;
        return ret;
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
