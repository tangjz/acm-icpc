class Solution {
public:
    bool gcdSort(vector<int>& nums) {
        int n = nums.size();
        map<int, vector<int> > pos;
        for(int i = 0; i < n; ++i) {
            for(int x = 2, v = nums[i]; x <= v; ++x) {
                if(x * x > v)
                    x = v;
                if(v % x > 0)
                    continue;
                pos[x].push_back(i);
                while(v % x == 0)
                    v /= x;
            }
        }
        vector<vector<int> > e(n);
        for(auto &it: pos) {
            int u = it.second.front();
            for(int v: it.second) {
                if(u == v)
                    continue;
                e[u].push_back(v);
                e[v].push_back(u);
            }
        }
        vector<bool> vis(n);
        for(int i = 0; i < n; ++i) {
            if(vis[i])
                continue;
            vector<int> ord, seq;
            vis[i] = 1;
            ord.push_back(i);
            seq.push_back(nums[i]);
            for(int j = 0; j < (int)ord.size(); ++j) {
                int u = ord[j];
                for(int v: e[u])
                    if(!vis[v]) {
                        vis[v] = 1;
                        ord.push_back(v);
                        seq.push_back(nums[v]);
                    }
            }
            sort(ord.begin(), ord.end());
            sort(seq.begin(), seq.end());
            for(int j = 0; j < (int)ord.size(); ++j)
                nums[ord[j]] = seq[j];
        }
        for(int i = 1; i < n; ++i)
            if(nums[i - 1] > nums[i])
                return false;
        return true;
    }
};
