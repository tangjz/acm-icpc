class Solution {
public:
    int maximumSwap(int num) {
        string a = to_string(num), b = a;
        sort(b.begin(), b.end(), greater<>());
        int n = a.size(), p, q;
        for(p = 0; p < n && a[p] == b[p]; ++p);
        if(p == n)
            return num;
        for(q = n - 1; q >= 0 && a[q] != b[p]; --q);
        swap(a[p], a[q]);
        return stoi(a);
    }
};
