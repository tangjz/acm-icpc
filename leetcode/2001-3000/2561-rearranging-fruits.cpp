class Solution {
public:
    long long minCost(vector<int>& A, vector<int>& B) {
        unordered_map<int, int> ctr;
        for(int x: A)
            ++ctr[x];
        for(int x: B)
            --ctr[x];
        int adt = 0x3f3f3f3f;
        vector<int> seq;
        for(auto &it: ctr) {
            if(it.second & 1)
                return -1;
            adt = min(adt, it.first);
            for(int rem = abs(it.second) / 2; rem--; seq.push_back(it.first));
        }
        sort(seq.begin(), seq.end());
        int m = seq.size() / 2;
        seq.resize(m);
        long long ans = 0;
        for(int x: seq)
            ans += min(x, adt + adt);
        return ans;
    }
};
