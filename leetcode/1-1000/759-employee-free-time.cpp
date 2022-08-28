/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/

class Solution {
    vector<Interval> combine(vector<Interval> &lft, vector<Interval> &rht) {
        Interval cur(-1, -1), nxt;
        vector<Interval> ret;
        for(auto it = lft.begin(), jt = rht.begin(); it != lft.end() || jt != rht.end(); ) {
            if(jt == rht.end() || (it != lft.end() && it -> start < jt -> start)) {
                nxt = *(it++);
            } else {
                nxt = *(jt++);
            }
            if(cur.end >= nxt.start) {
                cur.end = max(cur.end, nxt.end);
                continue;
            }
            if(cur.end >= 0)
                ret.push_back(cur);
            cur = nxt;
        }
        if(cur.end >= 0)
            ret.push_back(cur);
        return ret;
    }
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        int n = schedule.size();
        priority_queue<pair<int, int> > que;
        for(int i = 0; i < n; ++i)
            que.push({-schedule[i].size(), i});
        for(int i = 1; i < n; ++i) {
            int u = que.top().second;
            que.pop();
            int v = que.top().second;
            que.pop();
            schedule[u] = combine(schedule[u], schedule[v]);
            que.push({-schedule[u].size(), u});
        }
        int u = que.top().second;
        int sz = schedule[u].size();
        for(int i = 1; i < sz; ++i) {
            schedule[u][i - 1].start = schedule[u][i - 1].end;
            schedule[u][i - 1].end = schedule[u][i].start;
        }
        schedule[u].pop_back();
        return schedule[u];
    }
};
