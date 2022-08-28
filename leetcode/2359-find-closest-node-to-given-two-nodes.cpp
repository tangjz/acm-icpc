class Solution {
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size();
        vector<pair<int, int> > dis(n, {INT_MAX, INT_MAX});
        for(int u = node1, d = 0; u != -1; u = edges[u], ++d) {
            if(dis[u].first != INT_MAX)
                break;
            dis[u].first = d;
        }
        for(int u = node2, d = 0; u != -1; u = edges[u], ++d) {
            if(dis[u].second != INT_MAX)
                break;
            dis[u].second = d;
        }
        int ans = -1, best = INT_MAX;
        for(int u = 0; u < n; ++u) {
            int dist = max(dis[u].first, dis[u].second);
            if(dist < best) {
                ans = u;
                best = dist;
            }
        }
        return ans;
    }
};
