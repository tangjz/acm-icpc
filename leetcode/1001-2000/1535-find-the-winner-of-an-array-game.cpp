class Solution {
public:
    int getWinner(vector<int>& arr, int k) {
        int n = (int)arr.size();
        for(int i = 0, j; i < n; i = j) {
            for(j = i + 1; j < n && arr[j] < arr[i]; ++j);
            if(j == n || j - i - !i >= k)
                return arr[i];
        }
        assert(0);
    }
};
