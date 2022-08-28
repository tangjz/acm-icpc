class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& a, int k) {
        if(k == (int)a.size())
            return 0;
        sort(a.begin(), a.end());
        vector<int> b;
        int las = a.front() - 1, cnt = 0;
        for(int x : a) {
            if(x != las) {
                las = x;
                b.push_back(cnt);
                cnt = 0;
            }
            ++cnt;
        }
        b.push_back(cnt);
        sort(b.begin(), b.end());
        int pos = 0, sum = 0;
        for(int x : b) {
            sum += x;
            if(sum > k)
                break;
            ++pos;
        }
        return (int)b.size() - pos;
    }
};
