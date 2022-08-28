class Solution {
public:
    double minRecSize(vector<vector<int>>& lines) {
        const double INF = 1e10;
        int n = lines.size();
        double xL = INF, xR = -INF, yL = INF, yR = -INF;
        sort(lines.begin(), lines.end());
        for(int i = 0, j, k = 0; i < n; ) {
            for(j = i; i < n && lines[j][0] == lines[i][0]; ++i);
            if(k < j) {
                double x1 = (lines[i - 1][1] - lines[k][1]) / (double)(lines[i - 1][0] - lines[k][0]);
                double x2 = (lines[j][1] - lines[j - 1][1]) / (double)(lines[j][0] - lines[j - 1][0]);
                if(x1 > x2)
                    swap(x1, x2);
                xL = min(xL, x1);
                xR = max(xR, x2);
                double y1 = (lines[i - 1][1] * lines[k][0] - lines[k][1] * lines[i - 1][0]) / (double)(lines[i - 1][0] - lines[k][0]);
                double y2 = (lines[j][1] * lines[j - 1][0] - lines[j - 1][1] * lines[j][0]) / (double)(lines[j][0] - lines[j - 1][0]);
                if(y1 > y2)
                    swap(y1, y2);
                yL = min(yL, y1);
                yR = max(yR, y2);
            }
            k = j;
        }
        return max(xR - xL, 0.0) * max(yR - yL, 0.0);
    }
};
