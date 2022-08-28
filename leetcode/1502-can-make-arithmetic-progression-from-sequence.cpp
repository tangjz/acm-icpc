class Solution {
public:
    bool canMakeArithmeticProgression(vector<int>& arr) {
        int n = (int)arr.size();
        sort(arr.begin(), arr.end());
        for(int i = 1; i + 1 < n; ++i)
            if(arr[i - 1] + arr[i + 1] != arr[i] * 2)
                return 0;
        return 1;
    }
};
