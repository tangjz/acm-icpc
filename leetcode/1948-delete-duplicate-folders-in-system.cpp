class Solution {
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        int n = paths.size();
        vector<int> par(n, n), las(n, -1);
        vector<vector<int> > edges(n + 1);
        map<string, int> itemHash;
        map<vector<string>, int> nodeHash;
        sort(paths.begin(), paths.end(), [&](auto &u, auto &v) {
            return u.size() > v.size();
        });
        paths.push_back(vector<string>());
        nodeHash[paths.back()] = n;
        for(int i = n - 1; i >= 0; --i) {
            string &item = paths[i].back();
            auto it = itemHash.find(item);
            if(it == itemHash.end()) {
                int sz = itemHash.size();
                las[i] = itemHash[item] = sz;
            } else {
                las[i] = it -> second;
            }
            nodeHash[paths[i]] = i;
            vector<string> tmp(paths[i].begin(), --paths[i].end());
            par[i] = nodeHash[tmp];
            edges[par[i]].push_back(i);
            // printf("paths %d:", i);
            // for(auto &jt: paths[i])
            //     printf(" %s (%d)", jt.c_str(), itemHash[jt]);
            // printf(": par %d las %d\n", par[i], las[i]);
        }
        vector<int> idx(n + 1, -1);
        map<vector<pair<int, int> >, int> subHash;
        map<int, int> subCtr;
        for(int i = 0; i <= n; ++i) {
            if(edges[i].empty())
                continue;
            vector<pair<int, int> > sub;
            for(int j: edges[i])
                sub.push_back({idx[j], las[j]});
            sort(sub.begin(), sub.end());
            auto it = subHash.find(sub);
            if(it == subHash.end()) {
                int sz = subHash.size();
                idx[i] = subHash[sub] = sz;
            } else {
                idx[i] = it -> second;
            }
            ++subCtr[idx[i]];
            // printf("paths %d:", i);
            // for(auto &jt: sub) {
            //     printf(" (%d, %d)", jt.first, jt.second);
            // }
            // printf(": idx %d (ctr %d)\n", idx[i], subCtr[idx[i]]);
        }
        vector<vector<string> > ret;
        for(int i = 0; i < n; ++i) {
            int u = edges[i].empty() ? par[i] : i;
            // printf("paths %d: check %d (ctr %d)\n", i, u, subCtr[idx[u]]);
            if(subCtr[idx[u]] == 1)
                ret.push_back(paths[i]);
        }
        return ret;
    }
};
