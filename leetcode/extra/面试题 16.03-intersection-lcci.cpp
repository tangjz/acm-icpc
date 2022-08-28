class Solution {
    int sgn(double x) {
        static const double eps = 1e-9;
        return (x > eps) - (x < -eps);
    }
public:
    vector<double> intersection(vector<int>& start1, vector<int>& end1, vector<int>& start2, vector<int>& end2) {
        double x0 = start1[0] - start2[0];
        double y0 = start1[1] - start2[1];
        double x1 = end1[0] - start1[0];
        double y1 = end1[1] - start1[1];
        double x2 = end2[0] - start2[0];
        double y2 = end2[1] - start2[1];
        double det1 = x1 * y2 - y1 * x2;
        double det0 = x2 * y0 - y2 * x0;
        if(!sgn(det1)) {
            if(sgn(det0))
                return {};
            vector<pair<vector<int>, int> > points;
            points.push_back({start1, 1});
            points.push_back({end1, 1});
            points.push_back({start2, 2});
            points.push_back({end2, 2});
            sort(points.begin(), points.end());
            if(points[0].second != points[1].second || points[1].first == points[2].first)
                return {(double)points[1].first[0], (double)points[1].first[1]};
            return {};
        }
        det0 /= det1;
        if(sgn(det0) < 0 || sgn(det0 - 1) > 0)
            return {};
        vector<double> ret = {start1[0] + det0 * x1, start1[1] + det0 * y1};
        int xL = min(start2[0], end2[0]);
        int xR = max(start2[0], end2[0]);
        int yL = min(start2[1], end2[1]);
        int yR = max(start2[1], end2[1]);
        if(sgn(ret[0] - xL) < 0 || sgn(ret[0] - xR) > 0 || sgn(ret[1] - yL) < 0 || sgn(ret[1] - yR) > 0)
            return {};
        return ret;
    }
};
