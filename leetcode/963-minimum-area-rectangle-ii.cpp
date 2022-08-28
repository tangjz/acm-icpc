class Solution {
    struct Point {
        int x, y;
        Point operator - (Point const &t) const {
            return (Point){x - t.x, y - t.y};
        }
        int dot(Point const &t) const {
            return x * t.x + y * t.y;
        }
        int det(Point const &t) const {
            return x * t.y - y * t.x;
        }
    };
public:
    double minAreaFreeRect(vector<vector<int>>& points) {
        int n = points.size();
        vector<Point> p(n);
        for(int i = 0; i < n; ++i) {
            p[i].x = points[i][0];
            p[i].y = points[i][1];
        }
        int ans = INT_MAX;
        for(int i = 0; i < n; ++i) {
            Point &A = p[i];
            for(int j = 0; j < n; ++j) {
                if(i == j)
                    continue;
                Point &B = p[j], AB = B - A;
                for(int k = 0; k < n; ++k) {
                    if(i == k || j == k)
                        continue;
                    Point &C = p[k], BC = C - B;
                    int area = AB.det(BC);
                    if(AB.dot(BC) || area <= 0 || area >= ans)
                        continue;
                    for(int l = 0; l < n; ++l) {
                        if(i == l || j == l || k == l)
                            continue;
                        Point &D = p[l], CD = D - C, DA = A - D;
                        if(BC.dot(CD) || BC.det(CD) <= 0
                           || CD.dot(DA) || CD.det(DA) <= 0
                           || DA.dot(AB) || DA.det(AB) <= 0)
                            continue;
                        ans = min(ans, area);
                    }
                }
            }
        }
        return ans < INT_MAX ? ans : 0;
    }
};
