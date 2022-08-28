class Solution {
    struct Point {
        int x, y;
        void init(vector<int> &vec) {
            x = vec[0];
            y = vec[1];
        }
        bool operator < (Point const &t) const {
            return x != t.x ? (x < t.x) : (y < t.y);
        }
        Point operator - (Point const &t) const {
            return (Point){x - t.x, y - t.y};
        }
        int det(Point const &t) const {
            return x * t.y - y * t.x;
        }
    };
public:
    vector<vector<int>> outerTrees(vector<vector<int>>& points) {
        vector<Point> p;
        p.reserve(points.size());
        for(auto &it : points) {
            static Point tmp;
            tmp.init(it);
            p.push_back(tmp);
        }
        sort(p.begin(), p.end());
        int n = (int)p.size();
        vector<int> stk, seq;
        for(int i = 0; i < n; ++i) {
            for( ; stk.size() > 1 && (p[stk.back()] - p[stk[stk.size() - 2]]).det(p[i] - p[stk.back()]) < 0; stk.pop_back());
            stk.push_back(i);
        }
        stk.swap(seq);
        for(int i = n - 1; i >= 0; --i) {
            for( ; stk.size() > 1 && (p[stk.back()] - p[stk[stk.size() - 2]]).det(p[i] - p[stk.back()]) < 0; stk.pop_back());
            stk.push_back(i);
        }
        reverse(stk.begin(), stk.end());
        int len = (int)seq.size();
        seq.insert(seq.end(), stk.begin(), stk.end());
        inplace_merge(seq.begin(), seq.begin() + len, seq.end());
        seq.erase(unique(seq.begin(), seq.end()), seq.end());
        vector<vector<int> > ret;
        for(int &i : seq)
            ret.push_back({p[i].x, p[i].y});
        return ret;
    }
};
