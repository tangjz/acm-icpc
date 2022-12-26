class KthLargest {
    int cap;
    multiset<int> sp;
public:
    KthLargest(int k, vector<int>& nums) {
        cap = k;
        for(int x: nums) {
            sp.insert(x);
            if(sp.size() > cap)
                sp.erase(sp.begin());
        }
    }

    int add(int val) {
        sp.insert(val);
        if(sp.size() > cap)
            sp.erase(sp.begin());
        return *sp.begin();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
