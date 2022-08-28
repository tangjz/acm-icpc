class Solution {
    int sgn(double x) {
        static const double eps = 1e-9;
        return (x > eps) - (x < -eps);
    }
    vector<double> intersection(vector<int> const &start1, vector<int> const &end1, vector<int> const &start2, vector<int> const &end2) {
        // printf("check (%d,%d)-(%d,%d) with (%d,%d)-(%d,%d)\n", start1[0], start1[1], end1[0], end1[1], start2[0], start2[1], end2[0], end2[1]);
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
            if(points[0].second != points[1].second || points[1].first == points[2].first) {
                // printf("ins (%d,%d)\n", points[1].first[0], points[1].first[1]);
                return {(double)points[1].first[0], (double)points[1].first[1]};
            }
            return {};
        }
        det0 /= det1;
        // if(sgn(det0) < 0 || sgn(det0 - 1) > 0)
        //     return {};
        vector<double> ret = {start1[0] + det0 * x1, start1[1] + det0 * y1};
        int xL = min(start2[0], end2[0]);
        int xR = max(start2[0], end2[0]);
        int yL = min(start2[1], end2[1]);
        int yR = max(start2[1], end2[1]);
        if(sgn(ret[0] - xL) < 0 || sgn(ret[0] - xR) > 0 || sgn(ret[1] - yL) < 0 || sgn(ret[1] - yR) > 0)
            return {};
        // printf("ins (%f,%f)\n", ret[0], ret[1]);
        return ret;
    }
public:
    vector<double> cutSquares(vector<int>& square1, vector<int>& square2) {
        for(int &v: square1)
            v *= 2;
        for(int &v: square2)
            v *= 2;
        int x1 = square1[0] + square1[2] / 2;
        int y1 = square1[1] + square1[2] / 2;
        int x2 = square2[0] + square2[2] / 2;
        int y2 = square2[1] + square2[2] / 2;
        if(x1 == x2 && y1 == y2) {
            int yL = min(square1[1], square2[1]);
            int yR = max(square1[1] + square1[2], square2[1] + square2[2]);
            vector<double> ret = {(double)x1, (double)yL, (double)x1, (double)yR};
            for(double &v: ret)
                v /= 2;
            return ret;
        }
        vector<vector<double> > cand;
        cand.push_back(intersection({x1, y1}, {x2, y2}, {square1[0], square1[1]}, {square1[0] + square1[2], square1[1]}));
        cand.push_back(intersection({x1, y1}, {x2, y2}, {square1[0], square1[1]}, {square1[0], square1[1] + square1[2]}));
        cand.push_back(intersection({x1, y1}, {x2, y2}, {square1[0] + square1[2], square1[1] + square1[2]}, {square1[0] + square1[2], square1[1]}));
        cand.push_back(intersection({x1, y1}, {x2, y2}, {square1[0] + square1[2], square1[1] + square1[2]}, {square1[0], square1[1] + square1[2]}));
        cand.push_back(intersection({x1, y1}, {x2, y2}, {square2[0], square2[1]}, {square2[0] + square2[2], square2[1]}));
        cand.push_back(intersection({x1, y1}, {x2, y2}, {square2[0], square2[1]}, {square2[0], square2[1] + square2[2]}));
        cand.push_back(intersection({x1, y1}, {x2, y2}, {square2[0] + square2[2], square2[1] + square2[2]}, {square2[0] + square2[2], square2[1]}));
        cand.push_back(intersection({x1, y1}, {x2, y2}, {square2[0] + square2[2], square2[1] + square2[2]}, {square2[0], square2[1] + square2[2]}));
        sort(cand.begin(), cand.end());
        // for(auto &it: cand)
        //     if(!it.empty())
        //         printf("%f %f\n", it[0], it[1]);
        int pos = 0;
        while(pos < cand.size() && cand[pos].empty())
            ++pos;
        vector<double> ret = {cand[pos][0], cand[pos][1], cand.back()[0], cand.back()[1]};
        for(double &v: ret)
            v /= 2;
        return ret;
    }
};
