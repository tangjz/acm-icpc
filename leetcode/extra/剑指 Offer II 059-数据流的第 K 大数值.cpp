class KthLargest {
    int cap;
    multiset<int> val;
public:
    KthLargest(int k, vector<int>& nums) {
        cap = k;
        val.clear();
        for(int x: nums) {
            val.insert(x);
            if(val.size() > cap)
                val.erase(val.begin());
        }
    }

    int add(int x) {
        val.insert(x);
        if(val.size() > cap)
            val.erase(val.begin());
        return *val.begin();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
