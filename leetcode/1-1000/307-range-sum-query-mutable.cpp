class NumArray {
    int sz;
    vector<int> vals, bits;
public:
    NumArray(vector<int>& nums) {
        vals = {0};
        vals.insert(vals.end(), nums.begin(), nums.end());
        sz = vals.size();
        vector<int>(sz).swap(bits);
        for(int i = 1, j; i < sz; ++i) {
            bits[i] += vals[i];
            j = i + (i & -i);
            if(j < sz)
                bits[j] += bits[i];
        }
    }

    void update(int index, int val) {
        int adt = val - vals[++index];
        vals[index] = val;
        for( ; index < sz; index += index & -index)
            bits[index] += adt;
    }

    int sumRange(int left, int right) {
        int ret = 0;
        for( ; left > 0; left -= left & -left)
            ret -= bits[left];
        for(++right; right > 0; right -= right & -right)
            ret += bits[right];
        return ret;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
