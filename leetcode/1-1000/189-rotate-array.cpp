class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        if(!k)
            return;
        k = n - k;
        int r = gcd(n, k);
        for(int i = 0, j = k; i < r; ++i, (++j) == n && (j = 0)) {
            int p, q, v = nums[i];
            for(p = i, q = j; q != i; p = q, (q += k) >= n && (q -= n))
                nums[p] = nums[q];
            nums[p] = v;
        }
    }
};
