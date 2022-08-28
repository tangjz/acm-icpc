class Solution {
public:
    vector<int> threeEqualParts(vector<int>& arr) {
        bool zero = 1;
        for(int x: arr)
            zero &= !x;
        if(zero)
            return {0, 2};
        int n = arr.size();
        vector<int> pR(n + 1);
        pR[n] = n;
        for(int i = n - 1; i >= 0; --i)
            pR[i] = arr[i] ? i : pR[i + 1];
        for(int i = pR[0] + 1; i + 1 < n; ++i) {
            int len = i - pR[0];
            int j = pR[i] + len;
            if(j >= n || n - pR[j] != len)
                continue;
            bool ban = 0;
            for(int k = 0; !ban && k < len; ++k)
                ban |= !(arr[pR[0] + k] == arr[pR[i] + k] && arr[pR[0] + k] == arr[pR[j] + k]);
            if(!ban)
                return {i - 1, j};
        }
        return {-1, -1};
    }
};
