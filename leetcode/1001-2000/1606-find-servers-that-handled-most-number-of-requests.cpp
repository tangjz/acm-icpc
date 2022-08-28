class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        int n = arrival.size();
        vector<int> ctr(k);
        set<int> servers;
        priority_queue<pair<int, int> > que;
        for(int i = 0; i < k; ++i)
            servers.insert(i);
        for(int i = 0; i < n; ++i) {
            while(!que.empty()) {
                auto it = que.top();
                int tim = -it.first;
                if(tim > arrival[i])
                    break;
                int pos = it.second;
                servers.insert(pos);
                que.pop();
            }
            if(servers.empty())
                continue;
            auto it = servers.lower_bound(i % k);
            if(it == servers.end()) {
                it = servers.begin();
            }
            int pos = *it;
            ++ctr[pos];
            servers.erase(it);
            que.push({-(arrival[i] + load[i]), pos});
        }
        int best = -1;
        vector<int> ret;
        for(int i = 0; i < k; ++i) {
            if(best < ctr[i]) {
                best = ctr[i];
                ret = {};
            }
            if(best == ctr[i])
                ret.push_back(i);
        }
        return ret;
    }
};
