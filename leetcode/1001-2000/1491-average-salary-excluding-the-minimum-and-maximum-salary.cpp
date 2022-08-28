class Solution {
public:
    double average(vector<int>& a) {
        sort(a.begin(), a.end());
        int n = (int)a.size(), sum = 0;
        for(int i = 1; i + 1 < n; ++i)
            sum += a[i];
        return (double)sum / (n - 2);
    }
};
