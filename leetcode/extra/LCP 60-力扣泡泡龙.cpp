/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int getMaxLayerSum(TreeNode* root) {
        int n = 0;
        vector<TreeNode *> seq;
        vector<int> par;
        vector<vector<int> > e;
        auto new_node = [&](TreeNode *rt, int p = -1) {
            if(rt == nullptr)
                return -1;
            // printf("new node %d: val %d par %d\n", n, rt -> val, p);
            seq.push_back(rt);
            par.push_back(p);
            e.push_back({});
            if(p >= 0)
                e[p].push_back(n);
            return n++;
        };
        new_node(root);
        for(int i = 0; i < n; ++i) {
            new_node(seq[i] -> left, i);
            new_node(seq[i] -> right, i);
        }
        vector<int> dep(n), tot_ctr(n), tot(n), las(n);
        vector<vector<int> > sub(n), sub_ctr(n);
        vector<set<pair<int, int> > > upp(n);
        for(int i = 0; i < n; ++i) {
            int p = par[i];
            dep[i] = p == -1 ? 0: dep[p] + 1;
            ++tot_ctr[dep[i]];
            tot[dep[i]] += seq[i] -> val;
        }
        int ans = INT_MIN;
        for(int i = 0; i < n; ++i)
            ans = max(ans, tot[dep[i]]);
        auto get_tot = [&](int d) {
            return d < tot.size() ? tot[d] : 0;
        };
        auto get_sub = [&](int u, int d) {
            return dep[u] <= d && d <= las[u] ? sub[u][las[u] - d] : 0;
        };
        auto upd = [&](int u, int d, int x, int c) {
            assert(dep[u] <= d && d <= las[u]);
            assert(sub[u].size() == las[u] - dep[u] + 1);
            // printf("upd %d %d %d\n", u, d, x);
            upp[u].erase({get_tot(d) - get_sub(u, d) + get_sub(u, d + 1), d});
            // printf("upp[%d] del %d %d\n", u, get_tot(d) - get_sub(u, d) + get_sub(u, d + 1), d);
            if(d - 1 >= dep[u]) {
                upp[u].erase({get_tot(d - 1) - get_sub(u, d - 1) + get_sub(u, d), d - 1});
                // printf("upp[%d] del %d %d\n", u, get_tot(d - 1) - get_sub(u, d - 1) + get_sub(u, d), d - 1);
            }
            sub[u][las[u] - d] += x;
            sub_ctr[u][las[u] - d] += c;
            upp[u].insert({get_tot(d) - get_sub(u, d) + get_sub(u, d + 1), d});
            // printf("upp[%d] ins %d %d\n", u, get_tot(d) - get_sub(u, d) + get_sub(u, d + 1), d);
            if(d - 1 >= dep[u]) {
                upp[u].insert({get_tot(d - 1) - get_sub(u, d - 1) + get_sub(u, d), d - 1});
                // printf("upp[%d] ins %d %d\n", u, get_tot(d - 1) - get_sub(u, d - 1) + get_sub(u, d), d - 1);
            }
        };
        for(int i = n - 1; i >= 0; --i) {
            int top = -1;
            for(int v: e[i])
                top = top == -1 ? v : (las[top] > las[v] ? top : v);
            if(top == -1) {
                las[i] = dep[i];
                sub[i] = {seq[i] -> val};
                sub_ctr[i] = {1};
                upp[i].insert({tot[dep[i]] - sub[i].back(), dep[i]});
                // printf("## upp[%d] ins %d %d\n", i, tot[dep[i]] - sub[i].back(), dep[i]);
            } else {
                las[i] = las[top];
                sub[i] = move(sub[top]);
                sub_ctr[i] = move(sub_ctr[top]);
                upp[i] = move(upp[top]);
                for(int d = las[i] - sub[i].size(); d >= dep[i]; --d) {
                    int prev = sub[i].back();
                    sub[i].push_back(0);
                    sub_ctr[i].push_back(0);
                    upp[i].insert({tot[d] + prev, d});
                    // printf("### upp[%d] ins %d %d prev %d\n", i, tot[d] + prev, d, prev);
                }
                upd(i, dep[i], seq[i] -> val, 1);
                for(int v: e[i]) {
                    if(v == top)
                        continue;
                    for(int j = 0; j < (int)sub[v].size(); ++j) {
                        upd(i, las[v] - j, sub[v][j], sub_ctr[v][j]);
                    }
                    vector<int>().swap(sub[v]);
                    vector<int>().swap(sub_ctr[v]);
                    upp[v].clear();
                }
            }
            if(e[i].size() <= 1) {
                if(tot_ctr[las[i]] == sub_ctr[i][0]) {
                    upp[i].erase({get_tot(las[i]) - get_sub(i, las[i]) + get_sub(i, las[i] + 1), las[i]});
                    // printf("upp[%d] del %d %d\n", i, get_tot(las[i]) - get_sub(i, las[i]) + get_sub(i, las[i] + 1), las[i]);
                }
                if(!upp[i].empty()) {
                    // printf("chk %d: %d %d\n", i, upp[i].rbegin() -> first, upp[i].rbegin() -> second);
                    ans = max(ans, upp[i].rbegin() -> first);
                }
                if(tot_ctr[las[i]] == sub_ctr[i][0]) {
                    upp[i].insert({get_tot(las[i]) - get_sub(i, las[i]) + get_sub(i, las[i] + 1), las[i]});
                    // printf("upp[%d] ins %d %d\n", i, get_tot(las[i]) - get_sub(i, las[i]) + get_sub(i, las[i] + 1), las[i]);
                }
            }
        }
        return ans;
    }
};
