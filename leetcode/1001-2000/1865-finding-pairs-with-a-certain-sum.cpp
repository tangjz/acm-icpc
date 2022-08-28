class FindSumPairs {
    vector<int> A, B;
    unordered_map<int, int> ctr;
public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        A = move(nums1);
        sort(A.begin(), A.end(), greater<int>());
        B = move(nums2);
        ctr.clear();
        ctr.reserve(B.size() << 1);
        for(int x: B)
            ++ctr[x];
    }
    
    void add(int index, int val) {
        --ctr[B[index]];
        B[index] += val;
        ++ctr[B[index]];
    }
    
    int count(int tot) {
        int ret = 0;
        for(int x: A) {
            auto it = ctr.find(tot - x);
            if(it != ctr.end())
                ret += it -> second;
        }
        return ret;
    }
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */
