class Solution {
public:
    int kIncreasing(vector<int>& arr, int k) {
        int n = arr.size(), ans = 0;
        for(int i = 0; i < n && i < k; ++i) {
            vector<int> v;
            for(int j = i, c = 0; j < n; j += k, ++c) {
                int val = arr[j];
                int pos = upper_bound(v.begin(), v.end(), val) - v.begin();
                if(pos >= v.size()) {
                    v.push_back(val);
                } else {
                    v[pos] = val;
                    ++ans;
                }
            }
        }
        return ans;
    }
};
