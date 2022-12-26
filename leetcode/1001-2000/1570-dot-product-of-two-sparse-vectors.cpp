class SparseVector {
    map<int, int> poly;
public:

    SparseVector(vector<int> &nums) {
        poly.clear();
        int n = nums.size();
        for(int i = 0; i < n; ++i)
            if(nums[i] > 0)
                poly[i] = nums[i];
    }

    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        int ans = 0;
        auto it = poly.begin(), jt = vec.poly.begin();
        while(it != poly.end() && jt != vec.poly.end())
            if(it -> first == jt -> first) {
                ans += it -> second * jt -> second;
                ++it;
                ++jt;
            } else if(it -> first < jt -> first) {
                ++it;
            } else {
                ++jt;
            }
        return ans;
    }
};

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1(nums1);
// SparseVector v2(nums2);
// int ans = v1.dotProduct(v2);
