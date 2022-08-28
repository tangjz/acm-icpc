class Solution {
public:
    int findBestValue(vector<int>& arr, int val) {
        const int INF = 0x3f3f3f3f, maxv = (int)1e5;
        int n = (int)arr.size();
        sort(arr.begin(), arr.end());
        int ret = arr.back(), dif = 0;
        for(int x : arr)
            dif += x;
        dif = abs(dif - val);
        for(int i = 0, sum = 0; i < n; ++i) {
            int L = i > 0 ? arr[i - 1] : 0;
            int R = arr[i];
            int pos = min(max((val - sum) / (n - i), L), R);
            for(int dt = -1; dt <= 1; ++dt) {
                int tmp = pos + dt;
                if(L <= tmp && tmp <= R) {
                    int tmp2 = abs(sum + tmp * (n - i) - val);
                    if(dif > tmp2 || (dif == tmp2 && tmp < ret)) {
                        ret = tmp;
                        dif = tmp2;
                    }
                }
            }
            sum += arr[i];
        }
        return ret;
    }
};
